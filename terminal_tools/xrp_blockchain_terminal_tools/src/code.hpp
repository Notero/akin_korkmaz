#ifndef CODE_HPP
#define CODE_HPP

#include <string>

// Represents the AMM balances (XRP in drops, counter-asset as a numeric value).
struct AmmAmounts {
    std::string amountInDrops; // XRP balance in drops
    double amount2Value;       // Counter asset balance (e.g., USDC)
};

struct Amm {
    AmmAmounts amounts;
};

// Converts drops (string) to XRP as a double.
double DropsToXrp(const std::string& drops);

double AmmPriceAfterTrade(const Amm& amm, double tradeAmount);
double getTargetPrice(double offerPrice, double totalFee, bool isBuy = true);
double xrpNeededtoFillTheGap(double targetPrice, const Amm& amm, bool isBuy = true);

#endif // CODE_HPP
