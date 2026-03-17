#pragma once

#include <QObject>
#include <QWebSocket>

#include "ArbitrageTypes.h"
#include "DbRepository.h"

// ArbitrageEngine
// -----------------------------------------------------------------------------
// Consumes live price updates and decides when to write arbitrage opportunities
// and trade instructions to the database.
// -----------------------------------------------------------------------------
class ArbitrageEngine : public QObject {
    Q_OBJECT
public:
    explicit ArbitrageEngine(DbRepository& repo, QObject* parent = nullptr);

    void start_arbitrage();

public slots:
    void check_live_arbitrage_opportunities_between_DEX_and_AMM(const QWebSocket* socket);

private:
    double calculate_the_amount_of_xrp_to_buy_to_be_profitable(const PriceTick& dex, const PriceTick& amm) const;
    void put_all_trade_information_to_Database(const Opportunity& opp, const TradeInstruction& ti);

    DbRepository& repo_;
};
