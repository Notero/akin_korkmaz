#pragma once

#include <QSqlDatabase>
#include <QSqlQuery>
#include <optional>

#include "ArbitrageTypes.h"

// DbRepository
// -----------------------------------------------------------------------------
// SQLite repository responsible for atomic inserts of arbitrage opportunities,
// trade instructions, and tracking transaction outcomes. Designed to be used in
// a single-threaded Qt context or protected by queued connections to ensure
// serialization.
// -----------------------------------------------------------------------------
class DbRepository {
public:
    explicit DbRepository(QSqlDatabase db);

    bool insertOpportunityAndInstruction(const Opportunity& opp, const TradeInstruction& ti);
    std::optional<TradeInstruction> fetchNextPendingInstruction();
    bool markInstructionStatus(qint64 id, const QString& status);
    bool insertCompletedTx(qint64 instrId, const QString& hash, qint64 feeDrops, qint64 ledger);
    bool insertFailedTx(qint64 instrId, const QString& hash, const QString& reason);

    static bool initialize(QSqlDatabase& db);

private:
    QSqlDatabase db_;
};
