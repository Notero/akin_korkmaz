// MainView.qml
// Pure visual view for Rippled Node Monitor (designable in Qt Design Studio)
// This QML file provides the user interface for monitoring and controlling a Rippled server node

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "."

Rectangle {
    id: root
    width: 1000
    height: 620

    // ============================================================================
    // THEME COLORS - Define the color palette for the entire interface
    // ============================================================================
    property color bgColor:      "#101018"  // Main background color (dark blue-black)
    property color panelColor:   "#181824"  // Panel background color (slightly lighter)
    property color panelBorder:  "#2c2c3a"  // Border color for panels
    property color textColor:    "#f2f2f7"  // Primary text color (off-white)
    property color subTextColor: "#a0a0bb"  // Secondary text color (gray-purple)
    property color accentColor:  "#00bcd4"  // Accent color for highlights (cyan)
    property color dangerColor:  "#ff5252"  // Error/danger color (red)

    color: bgColor

    // ============================================================================
    // SERVER STATE MODEL
    // ============================================================================
    // serverState tracks the current state of the Rippled server:
    // 0 = Stopped / offline
    // 1 = Connecting / syncing
    // 2 = Online / fully synced
    property int serverState: 0
    property bool serverOnline: serverState === 2  // Convenience property for checking if fully online

    // ============================================================================
    // BACKEND-BOUND PROPERTIES
    // These properties are expected to be updated by the C++ backend
    // ============================================================================
    property int    ledgersValidated: 0      // Number of ledgers validated by the node
    property int    completedLedgers: 0      // First ledger in the completed range
    property string latestOutput: ""         // Latest JSON response from Rippled
    property string logStream: ""            // Continuous log output from the server
    property string commandout: ""           // Terminal command response output

    // ============================================================================
    // HIGHLIGHT ANIMATION PROPERTIES
    // These properties create a brief visual flash when new content arrives
    // ============================================================================
    property real logHighlight: 0.0          // Controls log window highlight intensity (0.0 to 1.0)
    property real outputHighlight: 0.0       // Controls output window highlight intensity (0.0 to 1.0)

    // Animate logHighlight back to 0.0 over 800ms whenever it changes
    Behavior on logHighlight {
        NumberAnimation { duration: 800; to: 0.0 }
    }

    // Animate outputHighlight back to 0.0 over 800ms whenever it changes
    Behavior on outputHighlight {
        NumberAnimation { duration: 800; to: 0.0 }
    }

    // ============================================================================
    // SIGNALS TO BACKEND
    // These signals are emitted when user actions require backend processing
    // ============================================================================
    signal startServerRequested()                   // Emitted when user clicks "Start Server"
    signal stopServerRequested()                    // Emitted when user clicks "Stop Server"
    signal commandEntered(string commandText)       // Emitted when user sends a command

    // ============================================================================
    // MAIN LAYOUT - Two-column layout with controls on left, monitoring on right
    // ============================================================================
    RowLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 12

        // ========================================================================
        // LEFT COLUMN - Server controls and command interface
        // ========================================================================
        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: root.width * 0.35  // Left column takes 35% of width
            spacing: 10

            // ====================================================================
            // START / STOP BUTTON
            // Dynamic button that changes based on server state
            // ====================================================================
            Button {
                id: startStopButton

                // Button text changes based on server state
                text: serverState === 0
                      ? qsTr("Start Server")           // State 0: Stopped
                      : (serverState === 1
                         ? qsTr("Connecting…")         // State 1: Connecting
                         : qsTr("Stop Server"))        // State 2: Online

                Layout.fillWidth: true
                font.bold: true
                enabled: serverState !== 1  // Disable button while connecting

                // Handle button clicks based on current state
                onClicked: {
                    if (serverState === 0) {
                        startServerRequested()  // Start the server if stopped
                    } else if (serverState === 2 || serverState === 1) {
                        stopServerRequested()   // Stop the server if running or connecting
                    }
                }
            }

            // ====================================================================
            // OUTPUT SCREEN - Terminal response display
            // Shows responses from command-line interface commands
            // ====================================================================
            GroupBox {
                Layout.fillWidth: true
                Layout.fillHeight: true

                // Outer container with rounded corners and border
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 6
                    color: panelColor
                    radius: 8
                    border.color: panelBorder

                    // Inner container with subtle highlight animation
                    Rectangle {
                        anchors.fill: parent
                        anchors.margins: 8
                        radius: 6
                        // Background color brightens when outputHighlight > 0
                        color: Qt.rgba(0.08 + outputHighlight * 0.12,
                                       0.08 + outputHighlight * 0.12,
                                       0.15 + outputHighlight * 0.15,
                                       1.0)

                        // Scrollable text area for output
                        ScrollView {
                            id: outputScrollView  // Fixed: gave meaningful ID
                            anchors.fill: parent
                            anchors.margins: 6

                            TextArea {
                                id: outputArea
                                readOnly: true  // User cannot edit this text
                                wrapMode: TextArea.WrapAnywhere  // Wrap long lines
                                text: commandout  // Bound to backend property
                                color: textColor
                                placeholderText: qsTr("Terminal Response")

                                // Auto-scroll to bottom when new text arrives
                                onTextChanged: {
                                    cursorPosition = length
                                }
                            }
                        }
                    }
                }
            }

            // ====================================================================
            // SEND COMMANDS PANEL
            // Input field and button for sending commands to Rippled server
            // ====================================================================
            GroupBox {
                Layout.fillWidth: true
                Layout.preferredHeight: 72

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 6
                    color: panelColor
                    radius: 8
                    border.color: panelBorder

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 8
                        spacing: 8

                        // Command input field
                        TextField {
                            id: commandInput
                            Layout.fillWidth: true
                            placeholderText: qsTr("Type exec...")
                            color: textColor
                            selectByMouse: true  // Allow mouse text selection

                            // Send command when Enter/Return is pressed
                            Keys.onReturnPressed: {
                                if (commandInput.text.length > 0) {
                                    commandEntered(commandInput.text)
                                    commandInput.text = ""  // Clear input after sending
                                }
                            }
                        }

                        // Send button (alternative to pressing Enter)
                        Button {
                            text: qsTr("Send")
                            onClicked: {
                                if (commandInput.text.length > 0) {
                                    commandEntered(commandInput.text)
                                    commandInput.text = ""  // Clear input after sending
                                }
                            }
                        }
                    }
                }
            }
        }

        // ========================================================================
        // RIGHT COLUMN - Server status and monitoring displays
        // ========================================================================
        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: root.width * 0.65  // Right column takes 65% of width
            spacing: 5

            // ====================================================================
            // SERVER STATUS PANEL
            // Displays current server state and ledger information
            // ====================================================================
            GroupBox {
                Layout.fillWidth: true
                Layout.preferredHeight: 55

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 6
                    color: panelColor
                    radius: 8
                    border.color: panelBorder

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 10
                        spacing: 6

                        // Overall server status indicator
                        RowLayout {
                            spacing: 8
                            Label { text: qsTr("Status:"); color: subTextColor }

                            // Color-coded status indicator circle
                            Rectangle {
                                width: 18
                                height: 18
                                radius: 9  // Make it circular
                                border.width: 1
                                border.color: "#444444"
                                // Red = offline, light blue = connecting, cyan = online
                                color: serverState === 0
                                       ? dangerColor
                                       : (serverState === 1
                                          ? Qt.lighter(accentColor, 1.4)
                                          : accentColor)
                            }

                            // Status text label
                            Label {
                                text: serverState === 0
                                      ? qsTr("Offline")
                                      : (serverState === 1
                                         ? qsTr("Connected")
                                         : qsTr("Online"))
                                color: textColor
                                font.bold: true
                            }
                        }

                        // Sync status with color-coded text
                        RowLayout {
                            spacing: 8
                            Label { text: qsTr("Sync status:"); color: subTextColor }
                            Label {
                                text: serverState === 0
                                      ? qsTr("Not running")
                                      : (serverState === 1
                                         ? qsTr("Syncing…")
                                         : qsTr("Synced"))
                                // Red = not running, blue = syncing, green = synced
                                color: serverState === 0
                                       ? dangerColor
                                       : (serverState === 1
                                          ? "#3399ff"
                                          : "#00c853")
                                font.bold: true
                            }
                        }

                        // Display first ledger in completed range
                        RowLayout {
                            spacing: 8
                            Label { text: qsTr("First ledger in range:"); color: subTextColor }
                            Label { text: completedLedgers.toString(); color: textColor }
                        }
                    }
                }
            }

            // ====================================================================
            // LOG WINDOW
            // Displays continuous stream of server logs
            // ====================================================================
            GroupBox {
                Layout.fillWidth: true
                Layout.preferredHeight: 250

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 6
                    color: panelColor
                    radius: 8
                    border.color: panelBorder

                    // Inner rectangle with highlight animation
                    Rectangle {
                        anchors.fill: parent
                        anchors.margins: 8
                        radius: 6
                        // Background brightens slightly when new logs arrive
                        color: Qt.rgba(0.06 + logHighlight * 0.10,
                                       0.06 + logHighlight * 0.10,
                                       0.12 + logHighlight * 0.14,
                                       1.0)

                        ScrollView {
                            id: logScrollView  // Fixed: gave meaningful ID
                            anchors.fill: parent
                            anchors.margins: 6

                            TextArea {
                                id: logArea
                                readOnly: true
                                text: logStream  // Bound to backend log stream
                                color: textColor
                                wrapMode: TextArea.NoWrap  // Don't wrap log lines
                                placeholderText: qsTr("Ripple")

                                // Auto-scroll to bottom when new logs arrive
                                onTextChanged: {
                                    cursorPosition = length
                                }
                            }
                        }
                    }
                }
            }

            // ====================================================================
            // JSON RESPONSE WINDOW
            // Displays JSON responses from Rippled server
            // ====================================================================
            GroupBox {
                Layout.fillWidth: true
                Layout.fillHeight: true  // Takes remaining vertical space

                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 6
                    color: panelColor
                    radius: 8
                    border.color: panelBorder

                    // Inner rectangle with highlight animation
                    Rectangle {
                        anchors.fill: parent
                        anchors.margins: 8
                        radius: 6
                        // Background brightens when new JSON arrives
                        color: Qt.rgba(0.08 + outputHighlight * 0.12,
                                       0.08 + outputHighlight * 0.12,
                                       0.15 + outputHighlight * 0.15,
                                       1.0)

                        ScrollView {
                            id: jsonScrollView  // Fixed: gave meaningful ID
                            anchors.fill: parent
                            anchors.margins: 6

                            TextArea {
                                id: jsonoutput
                                readOnly: true
                                wrapMode: TextArea.WrapAnywhere  // Wrap long JSON lines
                                text: latestOutput  // Bound to backend JSON output
                                color: textColor
                                placeholderText: qsTr("Json Response from Rippled")

                                // Auto-scroll to bottom when new JSON arrives
                                onTextChanged: {
                                    cursorPosition = length
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    Wallet{
        id: walletWindow
    }
    Connections {
        target: backend

        function onWalletGenerated(address, pubkey, seed) {
            walletWindow.openWithData(address, pubkey, seed)
        }
    }

}
