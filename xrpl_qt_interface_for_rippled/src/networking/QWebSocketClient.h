#pragma once

#include <QObject>
#include <QUrl>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>

#include "RippledCommands.h"
#include "XrplJsonParser.h"

// QWebSocketClient
// -----------------------------------------------------------------------------
// Thin wrapper around Qt's QWebSocket that provides a convenient API for
// connecting to the local rippled WebSocket endpoint and sending XRPL commands
// as JSON. Connection state and incoming messages are exposed via Qt signals so
// the backend can easily forward details to the UI.
// -----------------------------------------------------------------------------
class QWebSocketClient : public QObject
{
    Q_OBJECT
public:
    explicit QWebSocketClient(QObject *parent = nullptr);

    void connectToServer();
    void disconnectFromServer();

    bool sendCommand(const QString &cominto);

    void setEndpoint(const QUrl &url);
    QUrl endpoint() const;

signals:
    void connected();
    void disconnected();
    void textMessageReceived(const QString &message);
    void errorOccurred(const QString &message);

private slots:
    void handleConnected();
    void handleDisconnected();
    void handleError(QAbstractSocket::SocketError error);

private:
    QWebSocket m_socket;
    QUrl m_endpoint;
};

