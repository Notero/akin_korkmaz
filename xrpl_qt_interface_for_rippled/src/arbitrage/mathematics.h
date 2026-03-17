#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <QObject>
#include <QQmlEngine>

#include <string>

// Represents the AMM balances (XRP in drops, counter-asset as a numeric value).
// Each field is documented to make unit conversions explicit.
struct AmmAmounts {
    std::string amountInDrops; // XRP balance expressed in drops (1 XRP = 1,000,000 drops)
    double amount2Value;       // Counter asset balance (e.g., USDC) expressed as a decimal value
};

// Wrapper that makes it obvious when we are passing a paired set of balances
// to helper functions that model AMM behavior.
struct Amm {
    AmmAmounts amounts;
};

// Converts drops (string) to XRP as a double. Keeping the signature small
// keeps the helpers usable both from the engine and the UI layer.
double DropsToXrp(const std::string& drops);

// Calculates the AMM price after hypothetically executing a trade of the
// provided size. This is intentionally pure to make it easier to test.
double AmmPriceAfterTrade(const Amm& amm, double tradeAmount);

// Returns the price required to hit the targeted margin after fees for either
// a buy or sell operation.
double getTargetPrice(double offerPrice, double totalFee, bool isBuy = true);

// Determines how much XRP must be moved through the AMM to hit the target
// price and fully capture the spread.
double xrpNeededtoFillTheGap(double targetPrice, const Amm& amm, bool isBuy = true);

#endif // CODE_HPP

