/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.ui 1.0

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    width: parent.width
    height: parent.height
    focus: true

    Rectangle {
        id: textArea
        x: 28
        y: 14
        anchors.fill: parent
        color: "#f2f2f2"

        Column {
            id: column
            x: 130
            y: 40


            Rectangle {
                width: 560
                height: 250
                radius: 10
                border.width: 0

                Text {
                    width: 400
                    height: 250
                    anchors.centerIn: parent
                    text: config.aboutMessage.arg(Branding.string(Branding.VersionedName))

                        onLinkActivated: Qt.openUrlExternally(link)

                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.NoButton
                            cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                        }

                    font.pointSize: 10
                    anchors.verticalCenterOffset: 10
                    anchors.horizontalCenterOffset: 40
                    wrapMode: Text.WordWrap
                }

                Image {
                    id: image
                    x: 8
                    y: 12
                    height: 100
                    fillMode: Image.PreserveAspectFit
                    source: "img/squid.png"
                }

            }

        }

        ToolButton {
            id: toolButton
            x: 19
            y: 29
            width: 105
            height: 48
            text: qsTr("Back")
            hoverEnabled: true
            onClicked: load.source = ""

            Image {
                id: image1
                x: 0
                y: 13
                width: 22
                height: 22
                source: "img/chevron-left-solid.svg"
                fillMode: Image.PreserveAspectFit
            }
        }
    }

}
