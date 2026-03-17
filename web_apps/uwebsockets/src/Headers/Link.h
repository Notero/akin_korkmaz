#ifndef LINK_H
#define LINK_H

#include "SafeQueue.h" // Fixed capitalization to match CMake
#include <thread>
#include <string>
#include <queue>
#include <vector>
#include <memory>
#include <atomic>
#include <nlohmann/json.hpp>

// Boost.Beast headers
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>

namespace beast = boost::beast;
namespace http = boost::beast::http;
namespace websocket = boost::beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = boost::asio::ip::tcp;

class Link : public std::enable_shared_from_this<Link>
{
private:
    std::atomic<int> counter{0};
    
    // The IO context manages the event loop
    net::io_context ioc;
    
    // The SSL Websocket Stream
    using StreamType = websocket::stream<beast::ssl_stream<tcp::socket>>;
    std::shared_ptr<StreamType> ws_stream;
    std::shared_ptr<tcp::resolver> resolver_;

    // Store the hostname for the SSL handshake
    std::string host; 
    std::atomic<bool> stopped_{false};
    bool writing_{false};

    struct Target {
        std::string name;
        std::string currency;
        std::string issuer;
        std::string amm_account;
    };
    
    // Your extensive list of targets
    std::vector<Target> targets = {
        // --- TIER 1: THE SAFE GIANTS ---
        { "RLUSD", "524C555344000000000000000000000000000000", "rMxCKbEDwqr76QuheSUMdEGf4B9xJ8m5De", "rhWTXC2m2gGGA9WozUaoMm6kLAVPb1tcS3" },
        { "CRYPTO", "43525950544F0000000000000000000000000000", "rRbiKwcueo6MchUpMFDce9XpDwHhRLPFo", "rLjUKpwUVmz3vCTmFkXungxwzdoyrWRsFG" },
        { "MAG", "MAG", "rXmagwMmnFtVet3uL26Q2iwk287SRvVMJ", "rNZ2ZVF1ZU34kFQvcN4xkFAvdSvve5bXce" },
        { "USDC", "5553444300000000000000000000000000000000", "rGm7WCVp9gb4jZHWTEtGUr4dd74z2XuWhE", "rM7cHVPfhe9yxQNk2kDNBEQqoQmMcQGPWE" },
        { "SOLO", "534F4C4F00000000000000000000000000000000", "rsoLo2S1kiGeCcn6hCUXVrCpGMWLrRrLZz", "rMEJo9H5XvTe17UoAJzj8jtKVvTRcxwngo" },
        { "CORE", "434F524500000000000000000000000000000000", "rcoreNywaoz2ZCQ8Lg2EbSLnGuRBmun6D", "rBu4LXTxM9cfs3JsFCuDbPMzvGBDR66wpi" },
        { "FLR", "FLR", "rcxJwVnftZzXqyH9YheB8TgeiZUhNo1Eu", "r9ZKrNu1RJQg1UoqJ24pn5ZqynJg7rifGY" },
        // --- TIER 2 ---
        { "USDC_GATEHUB", "5553444300000000000000000000000000000000", "rcEGREd8NmkKRE8GE424sksyt1tJVFZwu", "rGHt6LT5v9DVaEAmFzj5ciuxuj41ZjLofs" },
        { "USDT", "5553445400000000000000000000000000000000", "rGbUjUtNVq5M3Un5r4efJqHed4o5P2Usdt", "rwDMCDG2s1qDJovdLJm4Hnpyv1ib9LzQkk" },
        { "XLM", "XLM", "rKiCet8SdvWxPXnAgYarFUXMh1zCPz432Y", "rprDM9hEWv7ACi1y9ZXrtRyySoWVLuU5zs" },
        { "CNY", "CNY", "rKiCet8SdvWxPXnAgYarFUXMh1zCPz432Y", "rEKkGGiLMfL28q74W4QAEPeRwXvcxWdutn" },
        { "WETH", "5745544800000000000000000000000000000000", "rfmS3zqrQrka8wVyhXifEeyTwe8AMz2Yhw", "rnSB7YPhTMfWzWH9ecv9VL2cU65b2TpXdn" },
        { "CSC", "CSC", "rCSCManTZ8ME9EoLrSHHYKW8PPwWMgkwr", "rf7g4JWCxu9oE1MKsWTihL9whY75AphCaV" },
        { "XAH", "XAH", "rswh1fvyLqHizBS2awu1vs6QcmwTBd9qiv", "r9zeQhjj3scQFDRriCJpMjDtW6eWjWnp6M" },
        // --- TIER 3 ---
        { "FUZZY", "46555A5A59000000000000000000000000000000", "rhCAT4hRdi2Y9puNdkpMzxrdKa5wkppR62", "rBudi9ArACZzLrReUWKFZmHve13LD7CbrM" },
        { "XPM", "XPM", "rXPMxBeefHGxx2K7g5qmmWq3gFsgawkoa", "rakZprdzwsUJ1rD2ouhYYAVP7tPbhrCbtz" },
        { "ARMY", "41524D5900000000000000000000000000000000", "rGG3wQ4kUzd7Jnmk1n5NWPZjjut62kCBfC", "rnsRq5ahgbFeRiAgBVvFTafyAgiS9x9Ztn" },
        { "PHNIX", "50484E4958000000000000000000000000000000", "rDFXbW2ZZCG5WgPtqwNiA2xZokLMm9ivmN", "rLJMi56CJMUnELQ5XzSrefn2WuFAwKQmDt" },
        { "EVR", "EVR", "ra9g3LAJm9xJu8Awe7oWzR6VXFB1mpFtSe", "r36cEzVdd1rzFMjCf7NdBWHYNREjoNUbsm" },
    };

    beast::flat_buffer buffer_;
    SafeQueue<std::string> write_queue_;

    // Handlers
    void on_resolve(beast::error_code ec, tcp::resolver::results_type results);
    void on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep);
    void on_ssl_handshake(beast::error_code ec);
    void on_handshake(beast::error_code ec);
    void on_read(beast::error_code ec, std::size_t bytes_transferred);
    void on_write(beast::error_code ec, std::size_t bytes_transferred);
    void do_write();

public:
    Link();
    ~Link() = default; 
    SafeQueue<std::string> messageQueue;

    void start(std::string uri);
    void stop();
    void sendmsg(std::string_view msg);
    void poll();
    bool is_stopped() { return stopped_.load(); }
};

#endif
