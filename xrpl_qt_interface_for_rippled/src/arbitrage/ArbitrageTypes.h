#pragma once

#include <QtGlobal>
#include <QString>

// Data structures shared between arbitrage components. The names intentionally
// mirror the terminology used throughout the architecture description so the
// pipeline is easy to follow from price tick ingestion through trade
// execution.
struct PriceTick {
    QString pair;
    double xrpBuy{0.0};
    double xrpSell{0.0};
};
struct AMMTick {
    QString pairxy;
    double constant{0.0};
    double price{0.0};
};

struct Opportunity {
    double dexPrice{0.0};
    double ammPrice{0.0};
    double spread{0.0};
    double estProfitXrp{0.0};
};

struct TradeInstruction {
    qint64 id{0};
    QString pair;
    QString side;
    double amountXrp{0.0};
    double minProfitXrp{0.0};
    qint64 maxFeeDrops{0};
};
