/**
 * Calculate slippage for buying tokens from XRPL AMM pool.
 * Accepts amounts in drops (1 XRP = 1,000,000 drops) when inputsInDrops = true.
 *
 * @param {number} tokenInAmount - Amount of token being spent (drops if inputsInDrops=true)
 * @param {number} poolReserveIn - Reserve of token being spent (drops if inputsInDrops=true)
 * @param {number} poolReserveOut - Reserve of token being received (drops if inputsInDrops=true)
 * @param {number} fee - AMM trading fee (e.g., 0.003 for 0.3%)
 * @param {object} opts
 * @param {boolean} opts.inputsInDrops - true if the three amounts above are in drops (default: false)
 * @param {number} opts.slippageTolerance - e.g. 0.01 for 1% minAmountOut buffer (default: 0.01)
 * @returns {object} Slippage details. tokenOutAmount and minAmountOut will be returned in the same unit as inputs.
 */
function calculateAMMSlippage(
  tokenInAmount,
  poolReserveIn,
  poolReserveOut,
  fee = 0.003,
  { inputsInDrops = false, slippageTolerance = 0.01 } = {}
) {
  const DROPS_PER_XRP = 1e6;
  const scale = inputsInDrops ? DROPS_PER_XRP : 1;

  // convert to canonical units for math (XRP units if inputs were drops)
  const tIn = tokenInAmount / scale;
  const rIn = poolReserveIn / scale;
  const rOut = poolReserveOut / scale;

  // Apply fee to input amount
  const adjustedInput = tIn * (1 - fee);

  // Constant product formula: dy = y * dx / (x + dx)
  const tokenOutAmountUnits = (rOut * adjustedInput) / (rIn + adjustedInput);

  // Spot price (no slippage, infinitesimal trade): quote per base (e.g. USDC per XRP)
  const poolSpotPrice = rOut / rIn;

  // Actual execution price: quote per base (USDC per XRP)
  const executionPrice = tokenOutAmountUnits / tIn;

  // Slippage / price impact in %
  const priceImpact =
    ((executionPrice - poolSpotPrice) / poolSpotPrice) * 100;

  // min amount out with tolerance (returned in same unit as inputs)
  const minAmountOutUnits = tokenOutAmountUnits * (1 - slippageTolerance);

  return {
    tokenInAmount,                         // original unit
    tokenOutAmount: tokenOutAmountUnits * scale,
    tokenOutAmountUnits,                   // canonical units
    minAmountOut: minAmountOutUnits * scale,
    minAmountOutUnits,
    poolSpotPrice,                         // for debugging: AMM mid price
    executionPrice,                        // USDC per XRP
    priceImpact                            // % relative to spot
  };
}

module.exports = { calculateAMMSlippage };
