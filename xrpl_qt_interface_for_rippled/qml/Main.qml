// AppWindow.qml
// =============================================================================
// Application Window Container for Rippled Node Monitor
// =============================================================================
// This file serves as the runtime shell that wraps MainView.qml in an
// ApplicationWindow. It acts as the bridge between the C++ backend (main.cpp)
// and the pure visual component (MainView.qml).
//
// Key Responsibilities:
//   1. Provide the top-level ApplicationWindow container
//   2. Expose MainView properties to C++ via property aliases
//   3. Forward signals from MainView to the window level (accessible to C++)
//   4. Set up window properties (title, size, visibility)
//
// Architecture:
//   C++ main.cpp ←→ AppWindow.qml ←→ MainView.qml
//
//   - C++ connects to AppWindow signals/properties
//   - AppWindow aliases MainView properties
//   - MainView contains all visual UI elements
// =============================================================================

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

ApplicationWindow {
    id: window

    // -------------------------------------------------------------------------
    // Window Properties
    // -------------------------------------------------------------------------
    visible: true                                    // Show window immediately on startup
    width: 1000                                      // Initial window width in pixels
    height: 620                                      // Initial window height in pixels
    title: qsTr("Rippled Node Monitor")            // Window title bar text

    // =========================================================================
    // Property Aliases - Expose MainView Properties to C++
    // =========================================================================
    // These aliases allow C++ code (main.cpp) to directly access and modify
    // MainView properties through the AppWindow. The C++ backend uses
    // root->setProperty("propertyName", value) to update these.
    //
    // Without these aliases, C++ would need to navigate the QML object tree
    // to find MainView, which is more fragile and less efficient.
    // =========================================================================

    // -------------------------------------------------------------------------
    // Server State Property
    // -------------------------------------------------------------------------
    // Tracks the current state of the rippled server:
    //   0 = Stopped/offline (red indicator)
    //   1 = Connected/syncing (blue indicator)
    //   2 = Fully synced (green indicator)
    property alias serverState: mainView.serverState

    // -------------------------------------------------------------------------
    // Ledger Statistics Properties
    // -------------------------------------------------------------------------
    // Track blockchain synchronization progress
    property alias ledgersValidated: mainView.ledgersValidated  // Highest validated ledger
    property alias completedLedgers: mainView.completedLedgers  // First ledger in range

    // -------------------------------------------------------------------------
    // Text Output Properties
    // -------------------------------------------------------------------------
    // Store text content for various display areas in the UI
    property alias latestOutput: mainView.latestOutput          // JSON responses from rippled
    property alias logStream: mainView.logStream                // Stdout/stderr logs
    property alias commandout: mainView.commandout              // Command execution output

    // -------------------------------------------------------------------------
    // Animation Properties
    // -------------------------------------------------------------------------
    // Control brief flash animations when new content arrives
    // When set to 1.0, the text area brightens briefly then fades back to 0.0
    property alias logHighlight: mainView.logHighlight          // Log window flash intensity
    property alias outputHighlight: mainView.outputHighlight    // Output window flash intensity

    // =========================================================================
    // Signals - User Actions to C++ Backend
    // =========================================================================
    // These signals are emitted when the user interacts with UI controls.
    // The C++ backend (main.cpp) connects to these signals to handle actions.
    //
    // Signal flow:
    //   User clicks button in MainView
    //   → MainView emits signal
    //   → AppWindow forwards signal to window level
    //   → C++ main.cpp receives signal and calls Backend slot
    // =========================================================================

    signal startServerRequested()                    // Emitted when "Start Server" is clicked
    signal stopServerRequested()                     // Emitted when "Stop Server" is clicked
    signal commandEntered(string commandText)        // Emitted when user sends a command

    // =========================================================================
    // MainView Component
    // =========================================================================
    // The actual UI implementation with all visual elements and layouts.
    // MainView is designed to be a pure visual component that could be used
    // in Qt Design Studio without C++ dependencies.
    // =========================================================================
    MainView {
        id: mainView
        anchors.fill: parent  // Fill entire window area

        // ---------------------------------------------------------------------
        // Signal Forwarding
        // ---------------------------------------------------------------------
        // Forward MainView signals up to the AppWindow level where C++ can
        // connect to them. This creates a clean separation between the visual
        // component (MainView) and the application shell (AppWindow).
        // ---------------------------------------------------------------------

        // Forward start server request
        onStartServerRequested: window.startServerRequested()

        // Forward stop server request
        onStopServerRequested: window.stopServerRequested()

        // Forward command entry with the command text
        // Using function syntax to properly pass the parameter
        onCommandEntered: function(cmd) {
            window.commandEntered(cmd)
        }
    }
}
