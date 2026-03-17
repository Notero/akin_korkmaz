import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
Window {
    id: popupWin
    width: 520
    height: 280
    title: "Wallet Information"

    // --- THEME (mirrors MainView.qml) ---
    property color bgColor:      "#101018"
    property color panelColor:   "#181824"
    property color panelBorder:  "#2c2c3a"
    property color textColor:    "#f2f2f7"
    property color subTextColor: "#a0a0bb"
    property color accentColor:  "#00bcd4"

    // Call like: popupWin.openWithData(addr, key, seed)
    function openWithData(address, key, seed) {
        addressText.text = address
        keyText.text = key
        seedText.text = seed

        visible = true
        raise()
        requestActivate()
    }

    color: "transparent"

    Rectangle {
        anchors.fill: parent
        color: bgColor
        border.color: panelBorder
        radius: 8

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 16
            spacing: 12

            // Header
            RowLayout {
                Layout.fillWidth: true
                spacing: 8

                Label {
                    text: qsTr("Unregistered Wallet")
                    color: textColor
                    font.pixelSize: 18
                    font.bold: true
                }

                Rectangle {
                    Layout.preferredWidth: 8
                    Layout.preferredHeight: 8
                    radius: 4
                    color: accentColor
                }

                Item { Layout.fillWidth: true }

            }

            // Content panel
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: panelColor
                radius: 8
                border.color: panelBorder

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 14
                    spacing: 10

                    // Address
                    ColumnLayout {
                        spacing: 4

                        Label {
                            text: qsTr("Wallet Address")
                            color: subTextColor
                            font.bold: true
                        }

                        Text {
                            id: addressText
                            color: textColor
                            wrapMode: Text.WrapAnywhere
                            font.family: "DejaVu Sans Mono"
                            font.pixelSize: 13
                            Layout.fillWidth: true
                        }
                    }

                    // Divider
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 1
                        color: panelBorder
                    }

                    // Public Key
                    ColumnLayout {
                        spacing: 4

                        Label {
                            text: qsTr("Wallet Public Key")
                            color: subTextColor
                            font.bold: true
                        }

                        Text {
                            id: keyText
                            color: textColor
                            wrapMode: Text.WrapAnywhere
                            font.family: "DejaVu Sans Mono"
                            font.pixelSize: 13
                            Layout.fillWidth: true
                        }
                    }

                    // Divider
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 1
                        color: panelBorder
                    }

                    // Seed
                    ColumnLayout {
                        spacing: 4

                        Label {
                            text: qsTr("Wallet Seed")
                            color: subTextColor
                            font.bold: true
                        }

                        Text {
                            id: seedText
                            color: textColor
                            wrapMode: Text.WrapAnywhere
                            font.family: "DejaVu Sans Mono"
                            font.pixelSize: 13
                        }
                    }
                }
            }

            // Wallet naming and persistence
            Rectangle {
                Layout.fillWidth: true
                color: panelColor
                border.color: panelBorder
                radius: 6

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 12
                    spacing: 8

                    Label {
                        text: qsTr("Rename and Save this Wallet")
                        color: subTextColor
                        font.pixelSize: 12
                        wrapMode: Text.WordWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        TextField {
                            id: walletNameInput
                            Layout.fillWidth: true
                            placeholderText: qsTr("Enter Name Here")
                            color: textColor
                            selectionColor: accentColor
                            font.pixelSize: 12
                            background: Rectangle {
                                radius: 4
                                color: Qt.rgba(panelColor.r, panelColor.g, panelColor.b, 0.6)
                                border.color: panelBorder
                            }
                            onAccepted: saveWalletConfig()
                        }

                        Button {
                            id: saveButton
                            text: qsTr("Save")
                            highlighted: true
                            background: Rectangle {
                                radius: 4
                                color: accentColor
                                border.color: panelBorder
                            }
                            onClicked: saveWalletConfig()
                        }
                    }

                    Label {
                        id: saveStatus
                        text: ""
                        color: subTextColor
                        font.pixelSize: 11
                    }
                }
            }
        }


        function saveWalletConfig() {
            var name = walletNameInput.text.trim()
            if (name.length === 0) {
                saveStatus.text = qsTr("Please enter a wallet name before saving.")
                return
            }

            var success = backend.saveWalletConfig(name, addressText.text, keyText.text, seedText.text)
            saveStatus.text = success ? qsTr("Wallet saved to walletconfig.txt") : qsTr("Unable to save wallet configuration")
        }

        Component.onCompleted: {
            var config = backend.loadWalletConfig()
            if (config && config.name !== undefined) {
                walletNameInput.text = config.name
                if (config.address !== undefined && config.address.length > 0) addressText.text = config.address
                if (config.pubkey !== undefined && config.pubkey.length > 0) keyText.text = config.pubkey
                if (config.seed !== undefined && config.seed.length > 0) seedText.text = config.seed
            }
        }


    }
}
