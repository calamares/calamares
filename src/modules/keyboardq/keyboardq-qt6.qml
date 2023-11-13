/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 - 2023 Anke Boersma <demm@kaosx.us>
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
import "data"

Item {
    width: 800 //parent.width
    height: 600

    readonly property color backgroundColor: "#E6E9EA" //Kirigami.Theme.backgroundColor
    readonly property color listBackgroundColor: "white"
    readonly property color textFieldColor: "#121212"
    readonly property color textFieldBackgroundColor: "#F8F8F8"
    readonly property color textColor: Kirigami.Theme.textColor
    readonly property color highlightedTextColor: Kirigami.Theme.highlightedTextColor
    readonly property color highlightColor: Kirigami.Theme.highlightColor

    property var langXml: ["de", "en", "es", "fr", "ru",]
    property var arXml: ["Arabic"]
    property var ruXml: ["Azerba", "Belaru", "Kazakh", "Kyrgyz", "Mongol",
        "Russia", "Tajik", "Ukrain"]
    property var frXml: ["Bambar", "Belgia","French", "Wolof"]
    property var enXml: ["Bikol", "Chines", "Englis", "Irish", "Lithua", "Maori"]
    property var esXml: ["Spanis"]
    property var deXml: ["German"]
    property var ptXml: ["Portug"]
    property var scanXml: ["Danish", "Finnis", "Norweg", "Swedis"]
    property var afganiXml: ["Afghan"]
    property var genericXml: ["Armeni", "Bulgar", "Dutch", "Estoni", "Icelan",
        "Indone", "Italia", "Latvia", "Maltes", "Moldav", "Romani", "Swahil", "Turkis"]
    property var genericQzXml: ["Albani", "Bosnia", "Croati", "Czech", "Hungar",
        "Luxemb", "Monten", "Polish", "Serbia", "Sloven", "Slovak"]
    property var genericAzXml: []

    property var keyIndex: []

    Rectangle {
        id: backgroundItem
        anchors.fill: parent
        width: 800
        color: backgroundColor

        Label {
            id: header
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Select a layout to activate keyboard preview", "@label")
            color: textColor
            font.bold: true
        }

        Drawer {
            id: drawer
            width: 0.4 * backgroundItem.width
            height: backgroundItem.height
            edge: Qt.RightEdge

            ScrollView {
                id: scroll1
                anchors.fill: parent
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView {
                    id: models
                    focus: true
                    clip: true
                    boundsBehavior: Flickable.StopAtBounds
                    width: parent.width

                    model: config.keyboardModelsModel
                    Component.onCompleted: positionViewAtIndex(model.currentIndex, ListView.Center)
                    currentIndex: model.currentIndex
                    delegate: ItemDelegate {

                        property variant currentModel: model
                        hoverEnabled: true
                        width: 0.4 * backgroundItem.width
                        implicitHeight: 24
                        highlighted: ListView.isCurrentItem
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            width: parent.width
                            height: 24
                            color: highlighted ? "#eff0f1" : "#1F1F1F"
                            text: model.label
                            background: Rectangle {

                                color: highlighted || hovered ? "#3498DB" : "#ffffff"
                                opacity: highlighted || hovered ? 0.5 : 0.9
                            }

                            MouseArea {
                                hoverEnabled: true
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    models.currentIndex = index
                                    drawer.close()
                                }
                            }
                        }
                    }
                    onCurrentItemChanged: { config.keyboardModels = model[currentIndex] } /* This works because model is a stringlist */
                }
            }
        }

        Rectangle {
            id: modelLabel
            anchors.top: header.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 1.5
            height: 36
            color: mouseBar.containsMouse ? "#eff0f1" : "transparent";

            MouseArea {
                id: mouseBar
                anchors.fill: parent;
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true

                onClicked: {
                    drawer.open()
                }
                Text {
                    anchors.centerIn: parent
                    text: qsTr("<b>Keyboard model:&nbsp;&nbsp;</b>", "@label") + models.currentItem.currentModel.label
                    color: textColor
                }
                Image {
                    source: "data/pan-end-symbolic.svg"
                    anchors.centerIn: parent
                    anchors.horizontalCenterOffset : parent.width / 2.5
                    fillMode: Image.PreserveAspectFit
                    height: 22
                }
            }
        }

        RowLayout {
            id: stack
            anchors.top: modelLabel.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width / 1.1
            spacing: 10

            ListView {
                id: layouts

                ScrollBar.vertical: ScrollBar {
                    active: true
                }

                Layout.preferredWidth: parent.width / 2
                height: 220
                focus: true
                clip: true
                boundsBehavior: Flickable.StopAtBounds
                spacing: 2
                headerPositioning: ListView.OverlayHeader
                header: Rectangle{
                    height: 24
                    width: parent.width
                    z: 2
                    color:backgroundColor
                    Text {
                        text: qsTr("Layout", "@label")
                        anchors.centerIn: parent
                        color: textColor
                        font.bold: true
                    }
                }

                Rectangle {
                    z: parent.z - 1
                    anchors.fill: parent
                    color: listBackgroundColor
                    opacity: 0.7
                }

                model: config.keyboardLayoutsModel
                currentIndex: model.currentIndex
                Component.onCompleted: positionViewAtIndex(model.currentIndex, ListView.Center)
                delegate: ItemDelegate {

                    hoverEnabled: true
                    width: parent.width
                    implicitHeight: 24
                    highlighted: ListView.isCurrentItem

                    RowLayout {
                        anchors.fill: parent

                        Label {
                            id: label1
                            text: model.label
                            horizontalAlignment: Text.AlignHCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            width: parent.width
                            height: 24
                            color: highlighted ? highlightedTextColor : textColor

                            background: Rectangle {
                                color: highlighted || hovered ? highlightColor : listBackgroundColor
                                opacity: highlighted || hovered ? 0.5 : 0.3
                            }
                        }
                    }

                    onClicked: {

                        layouts.model.currentIndex = index
                        keyIndex = label1.text.substring(0,6)
                        layouts.positionViewAtIndex(index, ListView.Center)
                    }
                }
            }

            ListView {
                id: variants

                ScrollBar.vertical: ScrollBar {
                    active: true
                }

                Layout.preferredWidth: parent.width / 2
                height: 220
                focus: true
                clip: true
                boundsBehavior: Flickable.StopAtBounds
                spacing: 2
                headerPositioning: ListView.OverlayHeader
                header: Rectangle{
                    height: 24
                    width: parent.width
                    z: 2
                    color:backgroundColor
                    Text {
                        text: qsTr("Variant", "@label")
                        anchors.centerIn: parent
                        color: textColor
                        font.bold: true
                    }
                }

                Rectangle {
                    z: parent.z - 1
                    anchors.fill: parent
                    color: listBackgroundColor
                    opacity: 0.7
                }

                model: config.keyboardVariantsModel
                currentIndex: model.currentIndex
                Component.onCompleted: positionViewAtIndex(model.currentIndex, ListView.Center)

                delegate: ItemDelegate {
                    hoverEnabled: true
                    width: parent.width
                    implicitHeight: 24
                    highlighted: ListView.isCurrentItem

                    RowLayout {
                    anchors.fill: parent

                        Label {
                            text: model.label
                            horizontalAlignment: Text.AlignHCenter
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            width: parent.width
                            height: 24
                            color: highlighted ? highlightedTextColor : textColor

                            background: Rectangle {
                                color: highlighted || hovered ? highlightColor : listBackgroundColor
                                opacity: highlighted || hovered ? 0.5 : 0.3
                            }
                        }
                    }

                    onClicked: {
                        variants.model.currentIndex = index
                        variants.positionViewAtIndex(index, ListView.Center)
                    }
                }
            }
        }

        TextField {
            id: textInput
            placeholderText: qsTr("Type here to test your keyboard…", "@label")
            height: 36
            width: parent.width / 1.6
            horizontalAlignment: TextInput.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: keyboard.top
            anchors.bottomMargin: parent.height / 25
            color: textFieldColor

            background:Rectangle {
                z: parent.z - 1
                anchors.fill: parent
                color: textFieldBackgroundColor
                radius: 2
            }
        }

        Keyboard {
            id: keyboard
            width: parent.width
            height: parent.height / 3
            anchors.bottom: parent.bottom
            source: langXml.includes(keyIndex) ? (keyIndex + ".xml") :
                afganiXml.includes(keyIndex) ? "afgani.xml" :
                scanXml.includes(keyIndex) ? "scan.xml" :
                genericXml.includes(keyIndex) ? "generic.xml" :
                genericQzXml.includes(keyIndex) ? "generic_qz.xml" :
                arXml.includes(keyIndex) ? "ar.xml" :
                deXml.includes(keyIndex) ? "de.xml" :
                enXml.includes(keyIndex) ? "en.xml" :
                esXml.includes(keyIndex) ? "es.xml" :
                frXml.includes(keyIndex) ? "fr.xml" :
                ptXml.includes(keyIndex) ? "pt.xml" :
                ruXml.includes(keyIndex) ? "ru.xml" :"empty.xml"
            rows: 4
            columns: 10
            keyColor: "transparent"
            keyPressedColorOpacity: 0.2
            keyImageLeft: "button_bkg_left.png"
            keyImageRight: "button_bkg_right.png"
            keyImageCenter: "button_bkg_center.png"
            target: textInput
            onEnterClicked: console.log("Enter!")
        }
    }
}
