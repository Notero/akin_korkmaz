#include "QWebSocketClient.h"

#include <QDebug>

QWebSocketClient::QWebSocketClient(QObject *parent)
    : QObject(parent)
    , m_socket()
    , m_endpoint(QStringLiteral("ws://127.0.0.1:6006"))
{
    connect(&m_socket, &QWebSocket::connected, this, &QWebSocketClient::handleConnected);
    connect(&m_socket, &QWebSocket::disconnected, this, &QWebSocketClient::handleDisconnected);
    connect(&m_socket, &QWebSocket::textMessageReceived,
            this, &QWebSocketClient::textMessageReceived);
    connect(&m_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::errorOccurred),
            this, &QWebSocketClient::handleError);
}

void QWebSocketClient::connectToServer()
{
    if (m_socket.state() == QAbstractSocket::ConnectedState ||
        m_socket.state() == QAbstractSocket::ConnectingState) {
        return;
    }

    m_socket.open(m_endpoint);
}

void QWebSocketClient::disconnectFromServer()
{
    if (m_socket.state() == QAbstractSocket::ConnectedState ||
        m_socket.state() == QAbstractSocket::ConnectingState) {
        m_socket.close();
    }
}

bool QWebSocketClient::sendCommand(const QString &command)
{
    if (m_socket.state() != QAbstractSocket::ConnectedState)
        return false;

    m_socket.sendTextMessage(command);
    return true;
}

void QWebSocketClient::setEndpoint(const QUrl &url)
{
    m_endpoint = url;
}

QUrl QWebSocketClient::endpoint() const
{
    return m_endpoint;
}

void QWebSocketClient::handleConnected()
{
    emit connected();
}

void QWebSocketClient::handleDisconnected()
{
    emit disconnected();
}

void QWebSocketClient::handleError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error)
    emit errorOccurred(m_socket.errorString());
}

