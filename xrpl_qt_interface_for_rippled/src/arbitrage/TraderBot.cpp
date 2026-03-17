#include "TraderBot.h"

#include <QJsonObject>
#include <QtGlobal>

TraderBot::TraderBot(DbRepository& repo, XrplWebSocketClient& client, QObject* parent)
    : QObject(parent), repo_(repo), client_(client) {}

void TraderBot::start() {
    // Listen for live transaction results so we can reconcile submissions with
    // ledger outcomes.
    connect(&client_, &XrplWebSocketClient::txProposed, this, &TraderBot::onTxProposed);
    connect(&client_, &XrplWebSocketClient::txValidated, this, &TraderBot::onTxValidated);

    // Drive the worker loop on a timer to pull queued trade instructions and
    // submit them to the network.
    connect(&timer_, &QTimer::timeout, this, &TraderBot::loopOnce);
    timer_.start(50);
}

void TraderBot::loopOnce() {
    // Pull the next pending instruction from the database. If nothing is
    // pending we simply return and wait for the next tick.
    auto instrOpt = repo_.fetchNextPendingInstruction();
    if (!instrOpt) return;
    const auto& instr = *instrOpt;

    // Translate the instruction into the minimal JSON structure required by
    // rippled. In a production bot this is where signing and account selection
    // would take place.
    QJsonObject tx;
    tx["TransactionType"] = "OfferCreate";
    tx["Account"] = "rPLACEHOLDER";
    tx["TakerPays"] = QString::number(instr.amountXrp, 'f', 6);
    tx["Fee"] = QString::number(instr.maxFeeDrops);
    client_.submitTx(tx, [this, id = instr.id](QJsonObject resp) {
        Q_UNUSED(resp);
        // Keep status SENT until validation.
        Q_UNUSED(id);
    });
}

void TraderBot::onTxProposed(const QString& hash, const QJsonObject& meta) {
    // Reserved hook for feeding proposal results back into the UI or metrics.
    Q_UNUSED(hash);
    Q_UNUSED(meta);
}

void TraderBot::onTxValidated(const QString& hash, const QJsonObject& meta) {
    // Update persistence based on whether the ledger accepted the transaction.
    bool success = meta.value("engine_result").toString() == "tesSUCCESS";
    qint64 instrId = meta.value("instruction_id").toInteger();
    if (success) {
        repo_.insertCompletedTx(instrId, hash, meta.value("Fee").toInteger(), meta.value("ledger_index").toInteger());
        repo_.markInstructionStatus(instrId, "CONFIRMED");
    } else {
        repo_.insertFailedTx(instrId, hash, meta.value("engine_result").toString());
        repo_.markInstructionStatus(instrId, "FAILED");
    }
}
