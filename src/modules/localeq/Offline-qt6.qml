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

import QtQuick
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

import org.kde.kirigami as Kirigami

Page {
    width: 800 //parent.width
    height: 500

    id: control
    property string currentRegion
    property string currentZone

    readonly property color backgroundColor: Kirigami.Theme.backgroundColor //"#F5F5F5"
    readonly property color backgroundLighterColor: "#ffffff"
    readonly property color highlightColor: Kirigami.Theme.highlightColor //"#3498DB"
    readonly property color textColor: Kirigami.Theme.textColor
    readonly property color highlightedTextColor: Kirigami.Theme.highlightedTextColor

     StackView {
        id: stack
        anchors.fill: parent
        clip: true

        initialItem: Item {

            Label {

                id: region
                anchors.horizontalCenter: parent.horizontalCenter
                color: textColor
                horizontalAlignment: Text.AlignCenter
                text: qsTr("Select your preferred region, or use the default settings", "@label")
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
                    color: backgroundLighterColor
                }

                model: config.regionModel
                currentIndex: 1 // offline install, means locale from config
                delegate: ItemDelegate {

                    hoverEnabled: true
                    width: parent.width
                    height: 28
                    highlighted: ListView.isCurrentItem

                    Label {

                        text: model.name
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        width: parent.width
                        height: 28
                        color: highlighted ? highlightedTextColor : textColor

                        background: Rectangle {

                            color: highlighted || hovered ? highlightColor : backgroundLighterColor
                            opacity: highlighted || hovered ? 0.5 : 1
                        }
                    }

                    onClicked: {

                        list.currentIndex = index
                        control.currentRegion = model.name
                        config.regionalZonesModel.region = control.currentRegion
                        tztext.text = qsTr("Timezone: %1", "@label").arg(config.currentTimezoneName)
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
                    color: textColor
                    text: qsTr("Select your preferred zone within your region", "@label")
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
                        color: backgroundLighterColor
                        //radius: 5
                        //opacity: 0.7
                    }

                    model: config.regionalZonesModel
                    currentIndex : 99 // index of New York
                    Component.onCompleted: positionViewAtIndex(currentIndex, ListView.Center)
                    delegate: ItemDelegate {

                        hoverEnabled: true
                        width: parent.width
                        height: 24
                        highlighted: ListView.isCurrentItem

                        Label {

                            text: model.name
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            width: parent.width
                            height: 24
                            color: highlighted ? highlightedTextColor : textColor

                            background: Rectangle {

                                color: highlighted || hovered ? highlightColor : backgroundLighterColor
                                opacity: highlighted || hovered ? 0.5 : 1
                            }
                        }

                        onClicked: {

                            list2.currentIndex = index
                            list2.positionViewAtIndex(index, ListView.Center)
                            control.currentZone = model.name
                            config.setCurrentLocation(control.currentRegion, control.currentZone)
                            tztext.text = qsTr("Timezone: %1", "@label").arg(config.currentTimezoneName)
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
                    text: qsTr("Zones", "@button")
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
                    text: qsTr("Timezone: %1", "@label").arg(config.currentTimezoneName)
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
            text: qsTr("You can fine-tune language and locale settings below", "@label")
        }
    }
}
