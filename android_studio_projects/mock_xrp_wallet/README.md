# Android XRP Wallet (Room-powered)

This project implements a simple XRP wallet simulator using the MVC pattern and Android Room for local persistence. Wallets and their transactions are stored entirely on-device.

## Architecture & Storage
- **Model:** `Wallet` and `Payment` Room entities with a one-to-many relationship.
- **Controllers:** Activities drive CRUD operations via DAOs and background executors.
- **Views:** RecyclerView lists use `ListAdapter`/`DiffUtil` for efficient updates.

## How to Run
1. Open the project in Android Studio Hedgehog or later.
2. Sync Gradle to download the Room, Lifecycle, RecyclerView, and CardView dependencies.
3. Build and run the app on an emulator or device running Android 13 (API 33) or higher.

## Testing CRUD Functionality
1. **Create wallets**
   - Tap **Add/Import Wallet**.
   - Choose **Generate New Wallet** to create a dummy wallet with random credentials, or fill key/seed fields and tap **Add Existing Wallet**.
2. **Read wallets**
   - Return to the home screen to see wallets fetched from Room; the list updates automatically via `LiveData`.
   - Tap a wallet to open details and view its transaction history.
3. **Update wallets**
   - In the wallet detail screen, enter a new name and tap **Rename**. The change is saved to Room and reflected in the list.
4. **Delete wallets**
   - Long-press a wallet on the home screen **or** tap **Delete Wallet** in the detail screen. Associated payments are deleted to keep data consistent.
5. **Create transactions**
   - From the home screen, tap **Make Payment** (uses the selected or first wallet) or open a wallet detail screen and then **Make Payment** to log a dummy transaction.
   - Enter amount, destination, and an optional memo, then submit. The payment is stored for the chosen wallet and appears in its history.

## Notes
- All database writes run on a background executor to keep the UI responsive.
- Performance logging in `MainActivity` measures wallet fetch time to highlight the benefit of Room + LiveData updates.
- Wallet generation and transactions are simulated locally; no network calls are made.
