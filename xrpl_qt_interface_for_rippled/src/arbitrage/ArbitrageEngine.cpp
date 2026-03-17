#include "ArbitrageEngine.h"

#include <QtGlobal>
#include <QWebSocket>

ArbitrageEngine::ArbitrageEngine(DbRepository& repo, QObject* parent)
    : QObject(parent), repo_(repo) {}

void ArbitrageEngine::start_arbitrage() {
    // Reserved for wiring signals from a real price source. Keeping this method
    // allows the rest of the application to call a single entry point.
}

void ArbitrageEngine::check_live_arbitrage_opportunities_between_DEX_and_AMM(const QWebSocket* socket) {
    // Look at the difference between the centralized exchange price (DEX) and
    // the AMM pool price to see if an immediate arbitrage exists.



//     double spread = dex.ask - amm.price; // buy AMM, sell DEX example.
//     if (spread <= 0) return;
//     double amount = calculate_the_amount_of_xrp_to_buy_to_be_profitable(dex, amm);
//     if (amount <= 0) return;

//     // Build descriptive records for both the UI (opportunity) and the trader
//     // loop (instruction).
//     Opportunity opp{dex.ask, amm.price, spread, spread * amount};
//     TradeInstruction ti{.pair = dex.pair,
//                         .side = "BUY_AMM_SELL_DEX",
//                         .amountXrp = amount,
//                         .minProfitXrp = opp.estProfitXrp * 0.9,
//                         .maxFeeDrops = 12000};
//     put_all_trade_information_to_Database(opp, ti);
 }

double ArbitrageEngine::calculate_the_amount_of_xrp_to_buy_to_be_profitable(const PriceTick& dex, const PriceTick& amm) const {
    // Stubbed sizing logic: prefer to keep the math readable until a real
    // order book model is plugged in.
    // Q_UNUSED(amm);
    // double feeDrops = 12; // sample base fee in drops.
    // double maxSpend = 1000.0; // cap risk.
    // double grossSpread = dex.ask - amm.price;
    // if (grossSpread <= 0) return 0;
    // double bestAmount = std::min(maxSpend, grossSpread * 50); // pseudo sizing.
    // double profit = grossSpread * bestAmount - (feeDrops / 1000000.0);
    // return profit > 0 ? bestAmount : 0;
    return 0;
}

void ArbitrageEngine::put_all_trade_information_to_Database(const Opportunity& opp, const TradeInstruction& ti) {
    // // Persist both the human-readable opportunity and the instruction that the
    // // TraderBot will later convert into network calls.
    // repo_.insertOpportunityAndInstruction(opp, ti);
}
