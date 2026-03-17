#pragma once

#include <QObject>
#include <QJsonObject>
#include <QTimer>

#include "ArbitrageTypes.h"
#include "DbRepository.h"
#include "XrplWebSocketClient.h"

// TraderBot
// -----------------------------------------------------------------------------
// Worker loop that pulls pending trade instructions, builds XRPL transactions,
// and records outcomes based on validation results streamed from the WebSocket
// client.
// -----------------------------------------------------------------------------
class TraderBot : public QObject {
    Q_OBJECT
public:
    TraderBot(DbRepository& repo, XrplWebSocketClient& client, QObject* parent = nullptr);
    void start();

private slots:
    void onTxProposed(const QString& hash, const QJsonObject& meta);
    void onTxValidated(const QString& hash, const QJsonObject& meta);
    void loopOnce();

private:
    DbRepository& repo_;
    XrplWebSocketClient& client_;
    QTimer timer_;
};
