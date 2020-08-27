/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Window 2.14
import QtQuick.Layouts 1.3

import org.kde.kirigami 2.7 as Kirigami

Page {
    width: 800 //parent.width
    height: 500

     StackView {
        id: stack
        anchors.fill: parent
        clip: true

        initialItem: Item {

            Label {

                id: region
                anchors.horizontalCenter: parent.horizontalCenter
                color: Kirigami.Theme.textColor
                horizontalAlignment: Text.AlignCenter
                text: qsTr("Select your preferred Region, or use the default one based on your current location.")
            }

            ListView {

                id: list
                ScrollBar.vertical: ScrollBar {
                    active: true
                }

                width: parent.width / 2
                height: 250
                anchors.centerIn: parent
                anchors.verticalCenterOffset: -30
                focus: true
                clip: true
                boundsBehavior: Flickable.StopAtBounds
                spacing: 2

                Rectangle {

                    z: parent.z - 1
                    anchors.fill: parent
                    color: "#BDC3C7"
                    radius: 5
                    opacity: 0.7
                }

                // model loads, dozens of variations tried for currentIndex all fail
                model: config.regionModel
                currentIndex: config.currentIndex
                delegate: ItemDelegate {
                    
                    hoverEnabled: true
                    width: parent.width
                    highlighted: ListView.isCurrentItem

                    Label {

                        text: name
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        width: parent.width
                        height: 30
                        color: highlighted ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor

                        background: Rectangle {

                            color: highlighted || hovered ? Kirigami.Theme.highlightColor : "white" //Kirigami.Theme.backgroundColor
                            opacity: highlighted || hovered ? 0.5 : 0.3
                        }
                    }

                    onClicked: {

                        list.model.currentIndex = index
                        // correct to use config.currentTimezoneName when index is updated?
                        tztext.text = qsTr("Timezone: %1").arg(config.currentTimezoneName)
                        stack.push(zoneView)
                    }
                }
            }
        }

        Component {
            id: zoneView

            Item {

                Label {

                    id: zone
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: Kirigami.Theme.textColor
                    text: qsTr("Select your preferred Zone within your Region.")
                }

                ListView {

                    id: list2
                    ScrollBar.vertical: ScrollBar {
                        active: true
                    }

                    width: parent.width / 2
                    height: 250
                    anchors.centerIn: parent
                    anchors.verticalCenterOffset: -30
                    focus: true
                    clip: true
                    boundsBehavior: Flickable.StopAtBounds
                    spacing: 2

                    Rectangle {

                        z: parent.z - 1
                        anchors.fill: parent
                        color: "#BDC3C7"
                        radius: 5
                        opacity: 0.7
                    }

                    // model loads, dozens of variations tried for currentIndex all fail
                    model: config.regionalZonesModel
                    currentIndex: config.currentIndex
                    delegate: ItemDelegate {

                        hoverEnabled: true
                        width: parent.width
                        highlighted: ListView.isCurrentItem

                        Label {

                            text: name
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            width: parent.width
                            height: 30
                            color: highlighted ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor

                            background: Rectangle {

                                color: highlighted || hovered ? Kirigami.Theme.highlightColor : "white" //Kirigami.Theme.backgroundColor
                                opacity: highlighted || hovered ? 0.5 : 0.3
                            }
                        }

                        onClicked: {

                            list2.model.currentIndex = index
                            list2.positionViewAtIndex(index, ListView.Center)
                            // correct to use config.currentTimezoneName when index is updated?
                            tztext.text = qsTr("Timezone: %1").arg(config.currentTimezoneName)
                        }
                    }
                }
                
                Button {

                    Layout.fillWidth: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: -30
                    anchors.left: parent.left 
                    anchors.leftMargin: parent.width / 15
                    icon.name: "go-previous"
                    text: qsTr("Zones")
                    onClicked: stack.pop()
                }
            }
        }
    }

    Rectangle {

        width: parent.width
        height: 60
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Item {

            id: location
            Kirigami.Theme.inherit: false
            Kirigami.Theme.colorSet: Kirigami.Theme.Complementary
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {

                anchors.centerIn: parent
                width: 300
                height: 30
                color: Kirigami.Theme.backgroundColor

                Text {

                    id: tztext
                    text: qsTr("Timezone: %1").arg(config.currentTimezoneName)
                    color: Kirigami.Theme.textColor
                    anchors.centerIn: parent
                }
            }
        }

        Text {

            anchors.top: location.bottom
            anchors.topMargin: 20
            padding: 10
            width: parent.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            Kirigami.Theme.backgroundColor: Kirigami.Theme.backgroundColor
            text: qsTr("You can fine-tune Language and Locale settings below.")
        }
    }
}
