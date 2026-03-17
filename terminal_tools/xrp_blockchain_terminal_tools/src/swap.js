// Swap tokens with AMM
const nodeRippled = "ws://127.0.0.1:6006"
const MAINNET = "wss://s1.ripple.com"

async function swapTokens() {

    const client = new xrpl.Client(MAINNET)
    results = `\n\nConnecting to ${MAINNET} ...`
    standbyResultField.value = results

    await client.connect()
    results += '\n\nConnected.'
    standbyResultField.value = results

    try {

        const standby_wallet = xrpl.Wallet.fromSeed(standbySeedField.value)

        const takerPaysCurrency = standbyTakerPaysCurrencyField.value
        const takerPaysIssuer = standbyTakerPaysIssuerField.value
        const takerPaysAmount = standbyTakerPaysAmountField.value

        const takerGetsCurrency = standbyTakerGetsCurrencyField.value
        const takerGetsIssuer = standbyTakerGetsIssuerField.value
        const takerGetsAmount = standbyTakerGetsAmountField.value

        let takerPays = null
        let takerGets = null

        if ( takerPaysCurrency == 'XRP' ) {
            takerPays = xrpl.xrpToDrops(takerPaysAmount)
        } else {
            takerPays = {
                "currency": takerPaysCurrency,
                "issuer": takerPaysIssuer,
                "value": takerPaysAmount
            }
        }

        if ( takerGetsCurrency == 'XRP' ) {
            takerGets = xrpl.xrpToDrops(takerGetsAmount)
        } else {
            takerGets = {
                "currency": takerGetsCurrency,
                "issuer": takerGetsIssuer,
                "value": takerGetsAmount
            }
        }

        results += '\n\nSwapping tokens ...'
        standbyResultField.value = results

        const offer_result = await client.submitAndWait({
            "TransactionType": "OfferCreate",
            "Account": standby_wallet.address,
            "TakerPays": takerPays,
            "TakerGets": takerGets
        }, {autofill: true, wallet: standby_wallet})
        
        if (offer_result.result.meta.TransactionResult == "tesSUCCESS") {
            results += `\n\nTransaction succeeded.`
            checkAMM()
        } else {
            results += `\n\nError sending transaction: ${JSON.stringify(offer_result.result.meta.TransactionResult, null, 2)}`
        }        
    } catch (error) {
        results += `\n\n${error.message}`
    }
}