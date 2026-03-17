#include "XrplWebSocketClient.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QUuid>

XrplWebSocketClient::XrplWebSocketClient(const QUrl& url, QObject* parent)
    : QObject(parent), url_(url) {}

void XrplWebSocketClient::connectAndSubscribe() {
    connect(&socket_, &QWebSocket::connected, this, &XrplWebSocketClient::onConnected);
    connect(&socket_, &QWebSocket::textMessageReceived, this, &XrplWebSocketClient::onMessageReceived);
    socket_.open(url_);
}

void XrplWebSocketClient::sendRequest(const QJsonObject& req, std::function<void(QJsonObject)> cb) {
    QString id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QJsonObject copy = req;
    copy.insert("id", id);
    pending_[id] = std::move(cb);
    socket_.sendTextMessage(QJsonDocument(copy).toJson(QJsonDocument::Compact));
}

void XrplWebSocketClient::submitTx(const QJsonObject& tx, std::function<void(QJsonObject)> cb) {
    QJsonObject req;
    req.insert("command", "submit");
    req.insert("tx_json", tx);
    sendRequest(req, std::move(cb));
}

void XrplWebSocketClient::onConnected() { subscribeStreams(); }

void XrplWebSocketClient::onMessageReceived(const QString& message) {
    QJsonObject obj = QJsonDocument::fromJson(message.toUtf8()).object();
    if (obj.contains("id")) {
        const auto id = obj.value("id").toString();
        const auto cb = pending_.take(id);
        if (cb) cb(obj);
        return;
    }
    handleStreamMessage(obj);
}

void XrplWebSocketClient::subscribeStreams() {
    QJsonObject bookSub{{"command", "subscribe"}, {"streams", QJsonArray{"transactions", "ledger"}}};
    sendRequest(bookSub, [](QJsonObject) {});
}

void XrplWebSocketClient::handleStreamMessage(const QJsonObject& obj) {
    const QString type = obj.value("type").toString();
    if (type == "transaction") {
        const auto tx = obj.value("transaction").toObject();
        const auto meta = obj.value("meta").toObject();
        emit txProposed(tx.value("hash").toString(), meta);
        return;
    }
    if (type == "ledgerClosed") {
        const auto tx = obj.value("transaction").toObject();
        const auto meta = obj.value("meta").toObject();
        emit txValidated(tx.value("hash").toString(), meta);
        return;
    }
    if (type == "book") {
        const auto bids = obj.value("bids").toArray();
        const auto asks = obj.value("asks").toArray();
        if (!bids.isEmpty() && !asks.isEmpty()) {
            double bid = bids.first().toObject().value("price").toDouble();
            double ask = asks.first().toObject().value("price").toDouble();
            emit dexPriceUpdate(obj.value("pair").toString(), bid, ask);
        }
    }
    if (type == "amm") {
        emit ammPriceUpdate(obj.value("pair").toString(), obj.value("price").toDouble());
    }
}
