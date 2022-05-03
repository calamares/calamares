/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020-2022 Anke Boersma <demm@kaosx.us>
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

    id: control
    property string currentRegion
    property string currentZone

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
                text: qsTr("Select your preferred Region, or use the default settings.")
            }

            ListView {

                id: list
                ScrollBar.vertical: ScrollBar {
                    active: true
                }

                width: parent.width / 2
                height: parent.height / 1.5
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

                model: config.regionModel
                currentIndex: -1
                delegate: ItemDelegate {

                    hoverEnabled: true
                    width: parent.width
                    height: 30
                    highlighted: ListView.isCurrentItem

                    Label {

                        text: model.name
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        width: parent.width
                        height: 30
                        color: highlighted ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor

                        background: Rectangle {

                            color: highlighted || hovered ? Kirigami.Theme.highlightColor : "white" //Kirigami.Theme.backgroundColor
                            opacity: highlighted || hovered ? 0.5 : 0.3
                        }
                    }

                    onClicked: {

                        list.currentIndex = index
                        control.currentRegion = model.name
                        config.regionalZonesModel.region = control.currentRegion
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
                    height: parent.height / 1.5
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

                    model: config.regionalZonesModel
                    currentIndex : -1
                    delegate: ItemDelegate {

                        hoverEnabled: true
                        width: parent.width
                        height: 30
                        highlighted: ListView.isCurrentItem

                        Label {

                            text: model.name
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            width: parent.width
                            height: 30
                            color: highlighted ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor

                            background: Rectangle {

                                color: highlighted || hovered ? Kirigami.Theme.highlightColor : "white" //Kirigami.Theme.backgroundColor
                                opacity: highlighted || hovered ? 0.5 : 0.3
                            }
                        }

                        onClicked: {

                            list2.currentIndex = index
                            list2.positionViewAtIndex(index, ListView.Center)
                            control.currentZone = model.name
                            config.setCurrentLocation(control.currentRegion, control.currentZone)
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
