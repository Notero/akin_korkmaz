#include "mathematics.h"

#include <cmath>
#include <string>

// Converts a raw drop balance into XRP, keeping precision by delaying division
// until the final step. This helper is shared by the pricing routines so they
// remain easy to follow.
double DropsToXrp(const std::string& drops) {
    return std::stod(drops) / 1'000'000.0;
}

// Implements the invariant k = x * y for a constant product AMM. Given an
// input trade size, we compute the new balances and derive the implied price
// after the trade completes.
double AmmPriceAfterTrade(const Amm& amm, double tradeAmount) {
    double X = DropsToXrp(amm.amounts.amountInDrops); // XRP reserve
    double Y = amm.amounts.amount2Value;              // Counter-asset reserve
    const double k = X * Y;
    double newX = X - tradeAmount;
    double newY = k / newX;
    return newY / newX;
}

// Applies a fee-adjusted multiplier depending on the trade direction. We keep
// the math small so that the caller can compose it with other pricing helpers.
double getTargetPrice(double offerPrice, double totalFee, bool isBuy) {
    return isBuy ? offerPrice * (1.0 + totalFee) : offerPrice * (1.0 - totalFee);
}

// Solves for the amount of XRP that needs to be traded through the pool to
// move the price to the provided target. This is used to estimate how much
// inventory to deploy when capturing an arbitrage spread.
double xrpNeededtoFillTheGap(double targetPrice, const Amm& amm, bool isBuy) {
    double X = DropsToXrp(amm.amounts.amountInDrops);
    double Y = amm.amounts.amount2Value;
    const double k = X * Y;
    double totalTradeSize = 0.0;
    if (isBuy) {
        totalTradeSize = X - std::sqrt(k / targetPrice);
    } else {
        totalTradeSize = std::sqrt(k / targetPrice) - X;
    }
    return totalTradeSize;
}
