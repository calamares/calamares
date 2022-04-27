/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 - 2022 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.14
import QtQuick.Layouts 1.3

import org.kde.kirigami 2.7 as Kirigami
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
        color: backgroundColor

        Label {
            id: header
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("To activate keyboard preview, select a layout.")
            color: textColor
            font.bold: true
        }

        Label {
            id: intro
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: header.bottom
            color: textColor
            horizontalAlignment: Text.AlignHCenter
            width: parent.width / 1.2
            wrapMode: Text.WordWrap
            text: ( config.prettyStatus)
        }

        RowLayout {
            id: models
            anchors.top: intro.bottom
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width /1.5
            spacing: 10

            Label {
                Layout.alignment: Qt.AlignCenter
                text: qsTr("Keyboard Model:")
                color: textColor
                font.bold: true
            }

            ComboBox {
                Layout.fillWidth: true
                textRole: "label"
                model: config.keyboardModelsModel
                currentIndex: model.currentIndex
                onCurrentIndexChanged: config.keyboardModels = currentIndex
            }
        }

        StackView {
            id: stack
            anchors.top: models.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            clip: true

            initialItem: Item {

                ListView {
                    id: layouts

                    ScrollBar.vertical: ScrollBar {
                        active: true
                    }

                    width: parent.width / 2
                    height: 200
                    anchors.horizontalCenter: parent.horizontalCenter
                    focus: true
                    clip: true
                    boundsBehavior: Flickable.StopAtBounds
                    spacing: 2

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
                        height: 18
                        highlighted: ListView.isCurrentItem

                        RowLayout {
                            anchors.fill: parent

                            Label {
                                id: label1
                                text: model.label
                                Layout.fillHeight: true
                                Layout.fillWidth: true
                                padding: 10
                                width: parent.width
                                height: 32
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
                            stack.push(variantsList)
                            layouts.positionViewAtIndex(index, ListView.Center)
                        }
                    }
                }
                Button {

                    Layout.fillWidth: true
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: -parent.height / 3.5
                    anchors.left: parent.left
                    anchors.leftMargin: parent.width / 15
                    icon.name: "go-next"
                    text: qsTr("Variants")
                    onClicked: stack.push(variantsList)
                }
            }

            Component {
                id: variantsList

                Item {

                    ListView {
                        id: variants

                        ScrollBar.vertical: ScrollBar {
                            active: true
                        }

                        width: parent.width / 2
                        height: 200
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.topMargin: 10
                        focus: true
                        clip: true
                        boundsBehavior: Flickable.StopAtBounds
                        spacing: 2

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
                            height: 18
                            highlighted: ListView.isCurrentItem

                            RowLayout {
                            anchors.fill: parent

                                Label {
                                    text: model.label
                                    Layout.fillHeight: true
                                    Layout.fillWidth: true
                                    padding: 10
                                    width: parent.width
                                    height: 30
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

                    Button {
                        Layout.fillWidth: true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.verticalCenterOffset: -parent.height / 3.5
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
            id: textInput
            placeholderText: qsTr("Type here to test your keyboard")
            height: 36
            width: parent.width / 1.5
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
