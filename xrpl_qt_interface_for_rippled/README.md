# XRP Ledger Qt Interface

A desktop-based graphical user interface (GUI) for interacting with the XRP Ledger (XRPL), built using C++ and the Qt/QML framework.

## Project Inventory

- **[qml](./qml)**: The declarative QML files defining the user interface layouts and styles (e.g., `Main.qml`, `Wallet.qml`).
- **[src](./src)**: The C++ source code responsible for the application's core logic, networking, and storage.
- **`CMakeLists.txt`**: The project's build configuration for managing dependencies and generating the application binary.

## Core Features
- **Wallet Interaction**: Manage and view XRP wallet balances and transactions within the UI.
- **XRPL Integration**: Securely connect to the XRP Ledger via the application's networking module.
- **Cross-Platform**: Built with Qt for a consistent user experience across different operating systems.

## How-To
- **Build**: Requires the Qt framework and CMake installed on the system.
- **Execution**: Generate the project build files and compile using the generated makefiles or project files.

---
*Created as a functional utility to simplify desktop interaction with the XRP Ledger.*
