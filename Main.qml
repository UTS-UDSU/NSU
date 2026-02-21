import QtQuick
import QtQuick.VirtualKeyboard
import QtQuick.Layouts
import QtQuick.Controls

import edu.udsu

Window {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    // connection
    TCPConnectionController {
        id: connectionController
    }

    MavlinkController {
        connectionController: connectionController
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 6

        RowLayout {
            spacing: 6

            Text {
                text: qsTr("ХОСТ")
            }
            TextField {
                id: hostInput
                text: "127.0.0.1"
            }

            Text {
                text: qsTr("ПОРТ")
            }
            TextField {
                id: portInput
                text: "5763"
                validator: IntValidator {
                    bottom: 65000
                    top: 1034
                }
            }

            Button {
                text: connectionController.isConnected ? qsTr("ОТКЛ.") : qsTr("ПОДКЛ.")
                onClicked: {
                    if (connectionController.isConnected)
                        connectionController.disconnectFrom()
                    else
                        connectionController.connectTo(hostInput.text, parseInt(portInput.text, 10))
                }
            }
        }
        Text {
            text: connectionController.state
        }
        Text {
            text: qsTr("принято ") + connectionController.onReaded + qsTr(" байт")
        }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }
        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    properties: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
