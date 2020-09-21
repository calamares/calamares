/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
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

                id: header
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Keyboard Model")
                color: Kirigami.Theme.textColor
                font.bold: true
                font.weight: Font.Bold
                font.pointSize: 24
            }

            Label {

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: header.bottom
                color: Kirigami.Theme.textColor
                horizontalAlignment: Text.AlignHCenter
                width: parent.width / 1.5
                wrapMode: Text.WordWrap
                text: qsTr("Click your preferred keyboard model to select layout and variant, or use the default one based on the detected hardware.")
            }

            ListView {

                id: list1

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

                model: config.keyboardModelsModel
                //model: ["Africa", "America", "Antarctica", "Arctic", "Asia", "Atlantic", "Australia", "Europe", "Indian", "Pacific"]

                currentIndex: model.currentIndex
                delegate: ItemDelegate {

                    hoverEnabled: true
                    width: parent.width
                    highlighted: ListView.isCurrentItem

                    RowLayout {
                        anchors.fill: parent

                        Label {

                            text: model.label // modelData
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            width: parent.width
                            height: 32
                            color: highlighted ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor

                            background: Rectangle {

                                color: highlighted || hovered ? Kirigami.Theme.highlightColor : "white" //Kirigami.Theme.backgroundColor
                                opacity: highlighted || hovered ? 0.5 : 0.3
                            }
                        }

                        Kirigami.Icon {

                            source: "checkmark"
                            Layout.preferredWidth: 22
                            Layout.preferredHeight: 22
                            color: Kirigami.Theme.highlightedTextColor
                            visible: highlighted
                        }
                    }

                    onClicked: {

                        list1.model.currentIndex = index
                        stack.push(layoutsList)
                        list1.positionViewAtIndex(index, ListView.Center)
                    }
                }
            }
        }

        Component {
            id: layoutsList

            Item {

                Label {

                id: header
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Keyboard Layout")
                color: Kirigami.Theme.textColor
                font.bold: true
                font.weight: Font.Bold
                font.pointSize: 24
                }

                Label {

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: header.bottom
                    color: Kirigami.Theme.textColor
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width / 1.5
                    wrapMode: Text.WordWrap
                    text: config.prettyStatus
                    //text: qsTr("Set keyboard model or use the default one based on the detected hardware.")
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

                    model: config.keyboardLayoutsModel
                    //model: ["Brussels", "London", "Madrid", "New York", "Melbourne", "London", "Madrid", "New York", "Brussels", "London", "Madrid", "New York", "Brussels", "London", "Madrid", "New York"]

                    currentIndex: model.currentIndex
                    delegate: ItemDelegate {

                        hoverEnabled: true
                        width: parent.width
                        highlighted: ListView.isCurrentItem

                        RowLayout {
                        anchors.fill: parent

                            Label {

                                text: model.label // modelData
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

                            Kirigami.Icon {

                                source: "checkmark"
                                Layout.preferredWidth: 22
                                Layout.preferredHeight: 22
                                color: Kirigami.Theme.highlightedTextColor
                                visible: highlighted
                            }
                        }

                        onClicked: {

                            list2.model.currentIndex = index
                            stack.push(variantsList)
                            list2.positionViewAtIndex(index, ListView.Center)
                        }
                    }
                }

                ColumnLayout {

                    spacing: 2
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: -30
                    anchors.left: parent.left 
                    anchors.leftMargin: parent.width / 15

                    Button {

                        icon.name: "go-previous"
                        text: qsTr("Models")
                        onClicked: stack.pop()
                    }

                    Button {

                        icon.name: "go-next"
                        text: qsTr("Variants")
                        onClicked: stack.push(variantsList)
                    }
                }
            }
        }

        Component {
            id: variantsList

            Item {

                Label {

                    id: header
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: qsTr("Keyboard Variant")
                    color: Kirigami.Theme.textColor
                    font.bold: true
                    font.weight: Font.Bold
                    font.pointSize: 24
                }

                Label {

                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: header.bottom
                    color: Kirigami.Theme.textColor
                    horizontalAlignment: Text.AlignHCenter
                    width: parent.width / 1.5
                    wrapMode: Text.WordWrap
                    text: config.prettyStatus
                    //text: qsTr("Variant keyboard model or use the default one based on the detected hardware.")
                }

                ListView {

                    id: list3

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

                    model: config.keyboardVariantsModel
                    //model: ["Brussels", "London", "Madrid", "New York", "Melbourne", "London", "Madrid", "New York", "Brussels", "London", "Madrid", "New York", "Brussels", "London", "Madrid", "New York"]

                    currentIndex: model.currentIndex
                    delegate: ItemDelegate {

                        hoverEnabled: true
                        width: parent.width
                        highlighted: ListView.isCurrentItem

                        RowLayout {
                        anchors.fill: parent

                            Label {

                                text: model.label //modelData
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

                            Kirigami.Icon {

                                source: "checkmark"
                                Layout.preferredWidth: 22
                                Layout.preferredHeight: 22
                                color: Kirigami.Theme.highlightedTextColor
                                visible: highlighted
                            }
                        }

                        onClicked: {

                            list3.model.currentIndex = index
                            list3.positionViewAtIndex(index, ListView.Center)
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
                    text: qsTr("Layouts")
                    onClicked: stack.pop()
                }
            }
        }
    }

    TextField {

        placeholderText: qsTr("Test your keyboard")
        height: 48
        width: parent.width / 1.5
        horizontalAlignment: TextInput.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height / 10
        color: "#1F1F1F"

        background:Rectangle {

            z: parent.z - 1
            anchors.fill: parent
            color: "#BDC3C7"
            radius: 2
            opacity: 0.3
        }
    }
}
