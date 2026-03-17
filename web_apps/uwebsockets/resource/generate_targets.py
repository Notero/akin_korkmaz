import urllib.request
import json

# URL for XRPScan AMM Pools
URL = "https://api.xrpscan.com/api/v1/amm/pools"

def get_top_amms():
    print("Fetching data from XRPScan...")
    try:
        # Create a request with a fake browser User-Agent to bypass 403 Forbidden
        req = urllib.request.Request(URL)
        req.add_header('User-Agent', 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.114 Safari/537.36')
        
        with urllib.request.urlopen(req) as response:
            data = json.loads(response.read().decode())
    except Exception as e:
        print(f"Error fetching data: {e}")
        return

    print(f"Processing {len(data)} pools...")

    cleaned_pools = []

    for pool in data:
        try:
            # 1. Check if the pool holds XRP (Balance is in drops)
            xrp_balance_drops = int(pool.get("Balance", 0))
            xrp_balance = xrp_balance_drops / 1_000_000.0
            
            # Filter: Ignore empty pools (< 1000 XRP)
            if xrp_balance < 1000:
                continue

            # 2. Identify the Token
            asset1 = pool.get("Asset", {})
            asset2 = pool.get("Asset2", {})
            
            token = None
            
            if asset1.get("currency") == "XRP":
                token = asset2
            elif asset2.get("currency") == "XRP":
                token = asset1
            
            if token and "issuer" in token:
                cleaned_pools.append({
                    "name": token.get("currency"), 
                    "currency": token.get("currency"),
                    "issuer": token.get("issuer"),
                    "amm_account": pool.get("Account"),
                    "liquidity": xrp_balance
                })

        except Exception as e:
            continue

    # 3. Sort by Liquidity (Highest XRP Balance first)
    cleaned_pools.sort(key=lambda x: x["liquidity"], reverse=True)

    # 4. Generate C++ Output for Top 100
    top_100 = cleaned_pools[:100]
    
    print(f"\nFound {len(cleaned_pools)} valid pools. Generating C++ code for top {len(top_100)}...\n")
    print("-" * 60)
    print("std::vector<json> targets = {")
    
    for i, p in enumerate(top_100):
        currency = p['currency']
        display_name = currency
        
        # Simple Hex-to-ASCII check for display name
        if len(currency) == 40 and currency.isupper():
            try:
                bytes_object = bytes.fromhex(currency).rstrip(b'\x00')
                decoded = bytes_object.decode("utf-8")
                if decoded.isalnum():
                    display_name = decoded
            except:
                pass
        
        comma = "," if i < len(top_100) - 1 else ""
        
        print(f'    {{')
        print(f'        {{"name", "{display_name}"}},')
        print(f'        {{"currency", "{currency}"}},')
        print(f'        {{"issuer", "{p["issuer"]}"}},')
        print(f'        {{"amm_account", "{p["amm_account"]}"}}')
        print(f'    }}{comma}')

    print("};")
    print("-" * 60)

if __name__ == "__main__":
    get_top_amms()
