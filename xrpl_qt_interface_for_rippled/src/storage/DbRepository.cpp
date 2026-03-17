#include "DbRepository.h"

#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>

DbRepository::DbRepository(QSqlDatabase db) : db_(std::move(db)) {}

bool DbRepository::initialize(QSqlDatabase& db) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("arbitrage.db");
    if (!db.open()) {
        return false;
    }

    QSqlQuery pragma(db);
    pragma.exec("PRAGMA journal_mode = WAL;");
    pragma.exec("PRAGMA synchronous = NORMAL;");
    pragma.exec("PRAGMA temp_store = MEMORY;");
    pragma.exec("PRAGMA cache_size = -200000;");
    pragma.exec("PRAGMA foreign_keys = ON;");

    QSqlQuery q(db);
    const QString schema = R"SQL(
CREATE TABLE IF NOT EXISTS opportunities (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  dex_price REAL NOT NULL,
  amm_price REAL NOT NULL,
  spread REAL NOT NULL,
  est_profit_xrp REAL NOT NULL,
  detected_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS trade_instructions (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  opportunity_id INTEGER NOT NULL REFERENCES opportunities(id) ON DELETE CASCADE,
  pair TEXT NOT NULL,
  side TEXT NOT NULL,
  amount_xrp REAL NOT NULL,
  min_profit_xrp REAL NOT NULL,
  max_fee_drops INTEGER NOT NULL,
  status TEXT NOT NULL CHECK (status IN ('PENDING','SENT','CONFIRMED','FAILED')),
  created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
  updated_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE INDEX IF NOT EXISTS idx_trade_instructions_status
  ON trade_instructions(status, created_at);

CREATE TABLE IF NOT EXISTS tx_completed (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  instruction_id INTEGER NOT NULL REFERENCES trade_instructions(id) ON DELETE CASCADE,
  tx_hash TEXT NOT NULL,
  fee_drops INTEGER NOT NULL,
  validated_ledger INTEGER NOT NULL,
  completed_at DATETIME DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS tx_failed (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  instruction_id INTEGER NOT NULL REFERENCES trade_instructions(id) ON DELETE CASCADE,
  tx_hash TEXT,
  reason TEXT NOT NULL,
  failed_at DATETIME DEFAULT CURRENT_TIMESTAMP
);
)SQL";

    if (!q.exec(schema)) {
        return false;
    }
    return true;
}

bool DbRepository::insertOpportunityAndInstruction(const Opportunity& opp, const TradeInstruction& ti) {
    QSqlQuery q(db_);
    if (!db_.transaction()) return false;

    q.prepare("INSERT INTO opportunities (dex_price, amm_price, spread, est_profit_xrp) VALUES (?,?,?,?)");
    q.addBindValue(opp.dexPrice);
    q.addBindValue(opp.ammPrice);
    q.addBindValue(opp.spread);
    q.addBindValue(opp.estProfitXrp);
    if (!q.exec()) { db_.rollback(); return false; }
    qint64 oppId = q.lastInsertId().toLongLong();

    q.prepare("INSERT INTO trade_instructions (opportunity_id, pair, side, amount_xrp, min_profit_xrp, max_fee_drops, status) VALUES (?,?,?,?,?,?, 'PENDING')");
    q.addBindValue(oppId);
    q.addBindValue(ti.pair);
    q.addBindValue(ti.side);
    q.addBindValue(ti.amountXrp);
    q.addBindValue(ti.minProfitXrp);
    q.addBindValue(ti.maxFeeDrops);
    if (!q.exec()) { db_.rollback(); return false; }

    return db_.commit();
}

std::optional<TradeInstruction> DbRepository::fetchNextPendingInstruction() {
    QSqlQuery begin(db_);
    if (!begin.exec("BEGIN IMMEDIATE TRANSACTION")) {
        return std::nullopt;
    }

    QSqlQuery q(db_);
    q.prepare("SELECT id, pair, side, amount_xrp, min_profit_xrp, max_fee_drops FROM trade_instructions WHERE status='PENDING' ORDER BY created_at LIMIT 1");
    if (!q.exec() || !q.next()) { db_.rollback(); return std::nullopt; }

    TradeInstruction ti;
    ti.id = q.value(0).toLongLong();
    ti.pair = q.value(1).toString();
    ti.side = q.value(2).toString();
    ti.amountXrp = q.value(3).toDouble();
    ti.minProfitXrp = q.value(4).toDouble();
    ti.maxFeeDrops = q.value(5).toLongLong();

    QSqlQuery upd(db_);
    upd.prepare("UPDATE trade_instructions SET status='SENT', updated_at=CURRENT_TIMESTAMP WHERE id=?");
    upd.addBindValue(ti.id);
    if (!upd.exec()) { db_.rollback(); return std::nullopt; }

    db_.commit();
    return ti;
}

bool DbRepository::markInstructionStatus(qint64 id, const QString& status) {
    QSqlQuery q(db_);
    q.prepare("UPDATE trade_instructions SET status=?, updated_at=CURRENT_TIMESTAMP WHERE id=?");
    q.addBindValue(status);
    q.addBindValue(id);
    return q.exec();
}

bool DbRepository::insertCompletedTx(qint64 instrId, const QString& hash, qint64 feeDrops, qint64 ledger) {
    QSqlQuery q(db_);
    q.prepare("INSERT INTO tx_completed (instruction_id, tx_hash, fee_drops, validated_ledger) VALUES (?,?,?,?)");
    q.addBindValue(instrId);
    q.addBindValue(hash);
    q.addBindValue(feeDrops);
    q.addBindValue(ledger);
    return q.exec();
}

bool DbRepository::insertFailedTx(qint64 instrId, const QString& hash, const QString& reason) {
    QSqlQuery q(db_);
    q.prepare("INSERT INTO tx_failed (instruction_id, tx_hash, reason) VALUES (?,?,?)");
    q.addBindValue(instrId);
    q.addBindValue(hash);
    q.addBindValue(reason);
    return q.exec();
}
