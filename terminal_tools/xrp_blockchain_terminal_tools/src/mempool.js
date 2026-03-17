// txProposedListener.js
import xrpl from "xrpl"

// Your endpoints
const nodeRippled = "ws://127.0.0.1:6006"
const MAINNET = "wss://s1.ripple.com" // kept here if you want to switch later

export async function getMempool() {
  const client = new xrpl.Client(nodeRippled)

  await client.connect()
  console.log("Connected to XRPL node:", nodeRippled)

  // Subscribe to proposed (unvalidated) transactions
    await client.request({
    command: "subscribe",
    streams: ["transactions_proposed"]
  })

  

  // Listen for proposed transactions from this node
  client.on("transaction", (event) => {
    console.log("===== Proposed TX =====")
    if(JSON.stringify(event.tx_json.TransactionType, null, 2) === '"OfferCreate"') {
        console.log("OfferCreate transaction detected:")
        console.log(JSON.stringify(event.tx_json, null, 2))
    }
    if(JSON.stringify(event.tx_json.TransactionType, null, 2) !== '"OfferCancel"') {
        console.log("OfferCancel transaction detected:")
        console.log(JSON.stringify(event.tx_json, null, 2))
    }
  })

  // Optional: basic error logging
  client.on("error", (err) => {
    console.error("XRPL client error:", err)
  })

}
