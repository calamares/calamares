/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 shivanandvp <shivanandvp@rebornos.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import 

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    width: 800
    height: 800
    property string image_source: ""
    Rectangle {
        id: page
        color: "#f2f2f2"
        anchors.fill: parent
        Column{
            spacing: 10
            anchors.topMargin: 10
            anchors.fill: parent
            Text {
                anchors.leftMargin: 10
                x: 10
                id: description_text
                wrapMode: Text.Wrap
                text: qsTr(config.promptMessage)
                font.pixelSize: 14
            }
            ListView {
                id: listView
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height - 25
                clip: true
                spacing: 10
                ScrollBar.vertical: ScrollBar {
                    active: hovered || pressed
                }
                model: config.entryIds
                delegate: Rectangle {
                    id: rectangle
                    anchors.leftMargin: 10
                    anchors.rightMargin: 10
                    x: 10
                    //            height: 500
                    width: listView.width - 20
                    height: column.implicitHeight + 20
                    //                        Layout.fillHeight: true
                    //                        Layout.fillWidth: true
                    color: "#ffffff"
                    radius: 10
                    border.width: 0
                    Column{
                        id: column
                        spacing: 10
                        anchors.topMargin: 10
                        anchors.leftMargin: 10
                        anchors.rightMargin: 10
                        anchors.fill: parent
                        Text {
                            anchors.leftMargin: 10
                            width: parent.width - 30
                            wrapMode: Text.Wrap
                            text: qsTr(config.entryNames[index])
                            font.pixelSize: 16
                            font.bold: true
                        }
                        Row{
                            id: row
                            anchors.left: parent.left
                            anchors.right: parent.right
                            spacing: 10
                            Image {
                                anchors.leftMargin: 10
                                source: config.entryScreenshots[index]
                                fillMode: Image.PreserveAspectFit
                                width: (parent.width - 30) / 3
                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        image_source = config.entryScreenshots[index]
                                        popup.open()
                                    }
                                }
                            }
                            Text {
                                width: (parent.width - 30) * 2/3
                                anchors.rightMargin: 10
                                wrapMode: Text.Wrap
                                text: qsTr(config.entryDescriptions[index])
                                font.pixelSize: 14
                            }
                        }
                        Switch {
                            anchors.right: parent.right
                            checked: false
                            hoverEnabled: true
                            onCheckedChanged: {
                                if ( checked ) {
                                    config.addSelection(config.entryIds[index])
                                } else {
                                    config.removeSelection(config.entryIds[index])
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    Popup {
        id: popup
        x: 50
        y: 50
        modal: true
        focus: true
//        height: enlarged_image.implicitHeight
//        width: enlarged_image.implicitWidth
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnReleaseOutside
        contentItem: ColumnLayout {
            Image{
                id: enlarged_image
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.maximumWidth: page.width - 100
                Layout.maximumHeight: page.implicitHeight - 100
                Layout.preferredWidth: page.implicitWidth - 100
                Layout.fillWidth: true
                Layout.fillHeight: true
                fillMode: Image.PreserveAspectFit
                source: image_source
            }
        }
    }
}
