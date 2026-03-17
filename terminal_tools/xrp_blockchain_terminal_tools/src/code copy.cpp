#include "code.hpp"

#include <cmath>
#include <string>

double DropsToXrp(const std::string& drops) {
    return std::stod(drops) / 1'000'000.0;
}

double AmmPriceAfterTrade(const Amm& amm, double tradeAmount) {
    double X = DropsToXrp(amm.amounts.amountInDrops); // XRP
    double Y = amm.amounts.amount2Value;              // USDC (or other)
    const double k = X * Y;
    double newX = X - tradeAmount;
    double newY = k / newX;
    return newY / newX;
}

double getTargetPrice(double offerPrice, double totalFee, bool isBuy) {
    return isBuy ? offerPrice * (1.0 + totalFee) : offerPrice * (1.0 - totalFee);
}

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
