import urllib.request
import json

URL = "https://api.xrpscan.com/api/v1/amm/pools"

def get_targets_with_liquidity():
    print("Fetching live liquidity data from XRPScan...")
    try:
        req = urllib.request.Request(URL)
        req.add_header('User-Agent', 'Mozilla/5.0')
        
        with urllib.request.urlopen(req) as response:
            data = json.loads(response.read().decode())
    except Exception as e:
        print(f"Error fetching data: {e}")
        return

    cleaned_pools = []

    for pool in data:
        try:
            # Get XRP Balance (in drops)
            xrp_balance_drops = int(pool.get("Balance", 0))
            xrp_balance = xrp_balance_drops / 1_000_000.0
            
            if xrp_balance < 1000: continue # Filter dust

            # Identify Token
            asset1 = pool.get("Asset", {})
            asset2 = pool.get("Asset2", {})
            token = None
            
            if asset1.get("currency") == "XRP": token = asset2
            elif asset2.get("currency") == "XRP": token = asset1
            
            if token and "issuer" in token:
                cleaned_pools.append({
                    "currency": token.get("currency"),
                    "issuer": token.get("issuer"),
                    "amm_account": pool.get("Account"),
                    "liquidity": xrp_balance
                })

        except: continue

    # Sort by Liquidity
    cleaned_pools.sort(key=lambda x: x["liquidity"], reverse=True)
    top_list = cleaned_pools[:100]

    print("\nstd::vector<json> targets = {")
    
    for i, p in enumerate(top_list):
        # Hex to ASCII decoding for Name
        currency = p['currency']
        name = currency
        if len(currency) == 40:
            try:
                decoded = bytes.fromhex(currency).rstrip(b'\x00').decode('utf-8')
                if decoded.isalnum(): name = decoded
            except: pass

        comma = "," if i < len(top_list) - 1 else ""
        
        # Format liquidity with commas (e.g. 1,234,567)
        liq_str = "{:,.0f}".format(p['liquidity'])

        print(f'    {{')
        print(f'        {{"name", "{name}"}},')
        print(f'        {{"currency", "{currency}"}},')
        print(f'        {{"issuer", "{p["issuer"]}"}},')
        print(f'        {{"amm_account", "{p["amm_account"]}"}}')
        print(f'    }}{comma} // Liquidity: {liq_str} XRP')

    print("};")

if __name__ == "__main__":
    get_targets_with_liquidity()
