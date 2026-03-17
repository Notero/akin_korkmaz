#pragma once

#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <QUrl>
#include <QWebSocket>
#include <functional>

// XrplWebSocketClient
// -----------------------------------------------------------------------------
// Lightweight wrapper around QWebSocket that handles request/response
// correlation for XRPL WebSocket usage. It exposes high level signals for
// pricing streams and transaction lifecycle events so downstream components can
// remain decoupled from the transport layer.
// -----------------------------------------------------------------------------
class XrplWebSocketClient : public QObject {
    Q_OBJECT
public:
    explicit XrplWebSocketClient(const QUrl& url, QObject* parent = nullptr);

    void connectAndSubscribe();
    void sendRequest(const QJsonObject& req, std::function<void(QJsonObject)> cb);
    void submitTx(const QJsonObject& tx, std::function<void(QJsonObject)> cb);

signals:
    void dexPriceUpdate(const QString& pair, double bid, double ask);
    void ammPriceUpdate(const QString& pair, double price);
    void txProposed(const QString& hash, const QJsonObject& meta);
    void txValidated(const QString& hash, const QJsonObject& meta);

private slots:
    void onConnected();
    void onMessageReceived(const QString& message);

private:
    void subscribeStreams();
    void handleStreamMessage(const QJsonObject& obj);

    QWebSocket socket_;
    QUrl url_;
    QHash<QString, std::function<void(QJsonObject)>> pending_; // id -> cb
};
