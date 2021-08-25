/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
    width:  parent.width
    height: parent.height

    Rectangle {
        anchors.fill: parent
        color: "#f2f2f2"
        ScrollView{
            anchors.fill: parent
            ScrollBar.horizontal.policy: ScrollBar.AsNeeded
            ScrollBar.vertical.policy: ScrollBar.AsNeeded
            clip: true
            Column {
                id: column
                anchors.centerIn: parent
                spacing: 10                
                Repeater {
                    model: config.entryIds
                    anchors.centerIn: parent
                    Rectangle {
                        width: 700
                        height: 150
                        color: "#ffffff"
                        radius: 10
                        border.width: 0
                        Text {
                            width: 450
                            height: 104
                            anchors.centerIn: parent
                            text: qsTr(config.entryDescriptions[index])
                            font.pointSize: 10
                            anchors.verticalCenterOffset: -10
                            anchors.horizontalCenterOffset: 100
                            wrapMode: Text.WordWrap
                        }
                        Switch {
                            x: 500
                            y: 110
                            width: 187
                            height: 14
                            text: qsTr(config.entryNames[index])
                            checked: true
                            hoverEnabled: true
                            onCheckedChanged: {
                                if ( checked ) {
                                    config.addSelection(config.entryIds[index])
                                } else {
                                    config.removeSelection(config.entryIds[index])
                                }
                            }
                        }
                        Image {
                            x: 8
                            y: 25
                            height: 100
                            fillMode: Image.PreserveAspectFit
                            source: ":/images/desktops/" + config.entryIds[index] + ".png"
                        }
                    }
                }
                Rectangle {
                    width: 700
                    height: 25
                    color: "#f2f2f2"
                    border.width: 0
                    Text {
                        height: 25
                        anchors.centerIn: parent
                        text: qsTr("Please select a desktop environment to install. Not selecting one will give you a text console with no graphics.")
                        font.pointSize: 10
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }
    }
}
