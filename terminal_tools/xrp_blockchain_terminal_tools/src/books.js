import xrpl from "xrpl"
import { getMempool } from "./mempool.js"
import { calculateAMMSlippage } from "./slippage.js"

const nodeRippled= "ws://127.0.0.1:6006"
const MAINNET = "wss://s1.ripple.com"
const client = new xrpl.Client(MAINNET)

async function main() {
  await client.connect()
  console.log("Connected to XRPL Mainnet")


const BitstampUSD = {
  name: "BitstampUSD",
  currency: "USD",
  issuer: "rvYAfWj5gh67oV6fW32ZzP3Aw4Eubs59B"
}
const GatehubUSD = {
  name: "GatehubUSD",
  currency: "USD",
  issuer: "rhub8VRN55s94qWKDv6jmDy1pUykJzF3wq"
}

const CircleUSDC = {
  name: "CircleUSDC",
  currency: "5553444300000000000000000000000000000000",
  issuer: "rGm7WCVp9gb4jZHWTEtGUr4dd74z2XuWhE"
}

const GatehubUSDC = {
  name: "GatehubUSDC",
  currency: "5553444300000000000000000000000000000000",
  issuer: "rcEGREd8NmkKRE8GE424sksyt1tJVFZwu"
}


let map = new Map([
  [CircleUSDC.name, CircleUSDC],
  [GatehubUSDC.name, GatehubUSDC],
  [BitstampUSD.name, BitstampUSD],
  [GatehubUSD.name, GatehubUSD]
])

// assuming this is inside an async function
const entries = map instanceof Map ? map.entries() : Object.entries(map);

const fees = await client.request({
    command: "fee"
})

console.log("Fees:", fees.result)

const repsonsee = await client.request({
  "command": "account_info",
  "account": "rGm7WCVp9gb4jZHWTEtGUr4dd74z2XuWhE",
  "ledger_index": "validated"
})

const repsonseee = await client.request({
  "command": "account_info",
  "account": "rvYAfWj5gh67oV6fW32ZzP3Aw4Eubs59B",
  "ledger_index": "validated"
})

console.log("Account Info:", repsonsee.result)
console.log("Account Info:", repsonseee.result)

for (const [name, issuer] of entries) {

    const bestSellRaw = await BookBuilderUSD(issuer, name);
    const amminf = await AMMprice(issuer, name);
    account_info(issuer);

}


  await client.disconnect()
  console.log("Disconnected")

async function account_info(issuer) {
    const response = await client.request({
      "command": "account_info",
      "account": issuer.issuer,
      "ledger_index": "validated"
    })
    console.log("Account Info:", issuer.name, response.result)
  }

async function AMMprice(issuer, name) {
  const respAMM = await client.request({
    command: "amm_info",
    asset: { "currency": "XRP" },
    asset2: {
      currency: issuer.currency,
      issuer: issuer.issuer // Bitstamp USD
    }
})

  let a = respAMM.result.amm.amount2.value
  let b = xrpl.dropsToXrp(respAMM.result.amm.amount) 
  console.log("AMM Price {1 XRP}/", name , ":",(a / b).toFixed(4))
  console.log("----------")
  console.log("AMM Info:", respAMM.result.amm)

  return respAMM
}

  async function BookBuilderUSD(issuer, name) {

      const respR = await client.request({
    command: "book_offers",
    taker_gets: { currency: issuer.currency, issuer: issuer.issuer }, // Bitstamp USD
    taker_pays: { currency: "XRP" },
    limit: 5
  })

  const respL = await client.request({
    command: "book_offers",
    taker_gets: { currency: "XRP" },
    taker_pays: { currency: issuer.currency, issuer: issuer.issuer }, // Bitstamp USD
    limit: 5
  })


    //getting offers
    let offersBuy = []
    let offersSell = []
    offersBuy = respL.result.offers ?? []
    //console.log(offersBuy)
    offersSell = respR.result.offers ?? []
    //console.log(offersSell)
    if (offersBuy.length === 0 && offersSell.length === 0) {
      console.log("No offers in atleast one direction")
      return
    }
    let sb = []
    let ss = []
    let buyp
    let sellp
    //getting data
    for (const o of offersBuy) {
      //object
      var USD = o.taker_pays || o.TakerPays
      //string
      var XRP = o.taker_gets || o.TakerGets
      XRP = xrpl.dropsToXrp(XRP)
      var XRPfloat = parseFloat(XRP)
      //price
      USD.value /= XRPfloat
      USD.value = USD.value.toFixed(4)
      sb.push(`taker_gets 1 XRP: ${USD.value}`)
      buyp = USD.value
    }
    for (const o of offersSell) {
      //object
      var USD = o.taker_gets || o.TakerGets
      //string
      var XRP = o.taker_pays || o.TakerPays

      XRP = xrpl.dropsToXrp(XRP)
      var XRPfloat = parseFloat(XRP)
      //price
      USD.value /= XRPfloat
      USD.value = USD.value.toFixed(4)
      ss.push(`taker_gives 1 XRP: ${USD.value}`)
      sellp = USD.value
    }
    let final = []
    for (let i = 0; i < sb.length; i++) {
      final [i] = String(sb[i]) + " | " + String(ss[i])
    }
    console.log("XRP/", name)
    for (const line of final) {
      console.log(line)
    }

    return sellp
  }

}
main()
