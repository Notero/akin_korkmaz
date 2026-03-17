#include "Link.h"
#include <iostream>
#include <regex>
#include <vector>

Link::Link() : stopped_(false), counter(0), writing_(false) {}

void Link::poll() {
    ioc.poll();
}

void Link::start(std::string uri) {
    this->counter = 0;
    this->stopped_ = false;
    this->writing_ = false;

    // 1. CLEAN THE URI
    std::string clean_host = uri;
    if (clean_host.rfind("wss://", 0) == 0) {
        clean_host = clean_host.substr(6);
    }
    this->host = clean_host;

    std::cout << "[Link] Connecting to: " << this->host << std::endl;

    // 2. Setup SSL
    ssl::context ctx{ssl::context::tlsv12_client};
    ctx.set_default_verify_paths();

    // 3. Create stream and resolver
    ws_stream = std::make_shared<StreamType>(net::make_strand(ioc), ctx);
    resolver_ = std::make_shared<tcp::resolver>(net::make_strand(ioc));

    // 4. Resolve
    resolver_->async_resolve(
        this->host,
        "443",
        beast::bind_front_handler(&Link::on_resolve, shared_from_this()));
}

void Link::on_resolve(beast::error_code ec, tcp::resolver::results_type results) {
    if (ec) {
        std::cerr << "[Link] Resolve Error: " << ec.message() << std::endl;
        return stop();
    }

    net::async_connect(
        beast::get_lowest_layer(*ws_stream),
        results,
        beast::bind_front_handler(&Link::on_connect, shared_from_this()));
}

void Link::on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep) {
    if (ec) {
        std::cerr << "[Link] Connect Error: " << ec.message() << std::endl;
        return stop();
    }

    if (!SSL_set_tlsext_host_name(ws_stream->next_layer().native_handle(), this->host.c_str())) {
        ec = beast::error_code(static_cast<int>(::ERR_get_error()), net::error::get_ssl_category());
        std::cerr << "[Link] SNI Error: " << ec.message() << std::endl;
        return stop();
    }

    ws_stream->next_layer().async_handshake(
        ssl::stream_base::client,
        beast::bind_front_handler(&Link::on_ssl_handshake, shared_from_this()));
}

void Link::on_ssl_handshake(beast::error_code ec) {
    if (ec) {
        std::cerr << "[Link] SSL Handshake Error: " << ec.message() << std::endl;
        return stop();
    }

    ws_stream->async_handshake(this->host, "/", beast::bind_front_handler(&Link::on_handshake, shared_from_this()));
}

void Link::on_handshake(beast::error_code ec) {
    if (ec) {
        std::cerr << "[Link] Handshake Error: " << ec.message() << std::endl;
        return stop();
    }

    messageQueue.push("CONNECTED");
    std::cout << "[Link] Connected!" << std::endl;

    for (size_t i = 0; i < targets.size(); ++i) {
    for (size_t j = i + 1; j < targets.size(); ++j) {
        const auto& assetA = targets[i];
        const auto& assetB = targets[j];
        
        nlohmann::json sub;
        sub["id"] = assetA.name + "_" + assetB.name + "_cross";
        sub["command"] = "book_offers";
        sub["taker_gets"] = {{"currency", assetA.currency}, {"issuer", assetA.issuer}};
        sub["taker_pays"] = {{"currency", assetB.currency}, {"issuer", assetB.issuer}};
        sub["both"] = true;
        this->sendmsg(sub.dump());

        nlohmann::json sub2;
        sub2["id"] = assetA.name + "_" + assetB.name + "_amm";
        sub2["command"] = "amm_info";
        sub2["asset"] = {{"currency", assetA.currency}, {"issuer", assetA.issuer}};
        sub2["asset2"] = {{"currency", assetB.currency}, {"issuer", assetB.issuer}};
        this->sendmsg(sub2.dump());
    }
}

    // Subscribe to streams
    nlohmann::json ledgerSub;
    ledgerSub["id"] = "ledger_sys";
    ledgerSub["command"] = "subscribe";
    ledgerSub["streams"] = {"ledger"};
    this->sendmsg(ledgerSub.dump());

    nlohmann::json serverStateSub;
    serverStateSub["id"] = "server_state";
    serverStateSub["command"] = "server_state";
    this->sendmsg(serverStateSub.dump());

    for(const auto &target : this->targets) {
        nlohmann::json info;
        info["id"] = target.name + "_info";
        info["command"] = "amm_info";
        info["asset1"] = {"currency", "XRP"};
        info["asset2"] = {"currency", target.currency, "issuer", target.issuer};
        this->sendmsg(info.dump());
    }

    for(const auto &target : this->targets) {
        nlohmann::json info;
        info["id"] = target.name + "_info";
        info["command"] = "account_info";
        info["account"] = target.issuer;
        this->sendmsg(info.dump());
    }

    for (const auto &target : this->targets) {
        nlohmann::json sub;
        sub["id"] = target.name;
        sub["command"] = "subscribe";
        sub["accounts"] = {target.amm_account, target.issuer};
        this->sendmsg(sub.dump());
    }

    for (const auto &target : this->targets) {
        nlohmann::json sub;
        sub["id"] = target.name + "_orderbook";
        sub["command"] = "subscribe";
        sub["books"] = {          // Outer brace = JSON Array []
            {                     // Inner brace = JSON Object {} inside the array
                {"taker_gets", {{"currency", target.currency}, {"issuer", target.issuer}}}, 
                {"taker_pays", {{"currency", "XRP"}}}, // XRP has no issuer, correct.
                {"snapshot", true}, 
                {"both", true}
            }
        };
        this->sendmsg(sub.dump());
    }

    // Start the read and write loops
    ws_stream->async_read(buffer_, beast::bind_front_handler(&Link::on_read, shared_from_this()));
    do_write();
}

void Link::on_read(beast::error_code ec, std::size_t bytes_transferred) {
    if (ec) {
        return stop();
    }

    std::string msg = beast::buffers_to_string(buffer_.data());
    buffer_.consume(buffer_.size());
    
    try {
        auto j = nlohmann::json::parse(msg);
        
        if (j.contains("type") && j["type"] == "ledgerClosed") {
            this->counter++;
            if (this->counter >= 5) {
                std::cout << "[Link] Limit reached (5). Stopping..." << std::endl;
                return stop();
            }
            this->sendmsg(R"({"command": "fee", "id": "fee_book"})");
        }
        messageQueue.push(msg);
    } catch (const std::exception &e) {
        std::cerr << "[Link] JSON Error: " << e.what() << std::endl;
    }

    if (!stopped_.load()) {
        ws_stream->async_read(buffer_, beast::bind_front_handler(&Link::on_read, shared_from_this()));
    }
}

void Link::sendmsg(std::string_view msg) {
    if (stopped_.load()) return;
    write_queue_.push(std::string(msg));
    // No need to call do_write here, the write loop is self-sustaining
}

void Link::do_write() {
    if (writing_ || stopped_.load()) return;
    
    std::string msg;
    if (!write_queue_.try_pop(msg)) return;

    writing_ = true;
    ws_stream->async_write(
        net::buffer(msg),
        beast::bind_front_handler(&Link::on_write, shared_from_this()));
}

void Link::on_write(beast::error_code ec, std::size_t bytes_transferred) {
    writing_ = false;
    if (ec) {
        std::cerr << "[Link] Write Error: " << ec.message() << std::endl;
        return stop();
    }
    
    if (!stopped_.load()) {
        do_write();
    }
}

void Link::stop() {
    bool expected = false;
    if (!stopped_.compare_exchange_strong(expected, true)) {
        return;
    }
    
    if (ws_stream && ws_stream->is_open()) {
        // Post the close operation to the strand to ensure it's serialized
        net::post(ws_stream->get_executor(), [self = shared_from_this()](){
            self->ws_stream->async_close(websocket::close_code::normal, [](beast::error_code){});
        });
    }

    messageQueue.push("STOP");
}

