/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 shivanandvp <shivanandvp@rebornos.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

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
                width: parent.width - 20
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
        width: {
            if (image_width > image_height || image_width < 2){
                page.width - 50
            } else {
                (page.height - 50) * image_width / image_height
                // if (new_width >= page.width - 50) {
                //     page.width - 50
                // }
            } 
        }
        height: {
            if (image_height > image_width || image_height < 2){
                page.height - 50
            } else {
                (page.width - 50) * image_height / image_width
                // if (new_height >= page.height - 50) {
                //     page.height - 50
                // }
            } 
        }
        anchors.centerIn: parent
        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnReleaseOutside | Popup.CloseOnReleaseInside
        padding: 0
        contentItem:
            Image{
                id: enlarged_image
                fillMode: Image.PreserveAspectFit
                source: image_source
                onStatusChanged: {
                    image_width= enlarged_image.paintedWidth
                    image_height= enlarged_image.paintedHeight
                }
            }
    }
}
