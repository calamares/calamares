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

        Column {
            id: column
            anchors.centerIn: parent
            spacing: 5

            Repeater {
                id: repeater
                model: config.entryIds
                Rectangle {
                    id: config.entryIds[index]
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
                        id: config.entryIds[index] + "_switch"
                        x: 500
                        y: 110
                        width: 187
                        height: 14
                        text: qsTr(config.entryNames[index])
                        checked: true
                        hoverEnabled: true

                        indicator: Rectangle {
                            implicitWidth: 40
                            implicitHeight: 14
                            radius: 10
                            color: repeater.itemAt[index].checked ? "#3498db" : "#B9B9B9"
                            border.color: gnome_switch.checked ? "#3498db" : "#cccccc"

                            Rectangle {
                                x: gnome_switch.checked ? parent.width - width : 0
                                y: (parent.height - height) / 2
                                width: 20
                                height: 20
                                radius: 10
                                color: gnome_switch.down ? "#cccccc" : "#ffffff"
                                border.color: gnome_switch.checked ? (gnome_switch.down ? "#3498db" : "#3498db") : "#999999"
                            }
                        }

                        onCheckedChanged: {
                            if ( checked ) {
                                config.addSelection("gnome")
                            } else {
                                config.removeSelection("gnome")
                            }
                        }
                    }

                    Image {
                        id: gnome_image
                        x: 8
                        y: 25
                        height: 100
                        fillMode: Image.PreserveAspectFit
                        source: "images/desktops/gnome.png"
                    }
                }
            }

            Rectangle {
                id: gnome_rectangle
                width: 700
                height: 150
                color: "#ffffff"
                radius: 10
                border.width: 0
                Text {
                    width: 450
                    height: 104
                    anchors.centerIn: parent
                    text: qsTr("GNOME (GNU Network Object Model Environment, pronounced gah-NOHM) is a graphical user interface (GUI) and set of computer desktop applications for users of the Linux operating system")
                    font.pointSize: 10
                    anchors.verticalCenterOffset: -10
                    anchors.horizontalCenterOffset: 100
                    wrapMode: Text.WordWrap
                }

                Switch {
                    id: gnome_switch
                    x: 500
                    y: 110
                    width: 187
                    height: 14
                    text: qsTr("Gnome")
                    checked: true
                    hoverEnabled: true

                    indicator: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 14
                        radius: 10
                        color: gnome_switch.checked ? "#3498db" : "#B9B9B9"
                        border.color: gnome_switch.checked ? "#3498db" : "#cccccc"

                        Rectangle {
                            x: gnome_switch.checked ? parent.width - width : 0
                            y: (parent.height - height) / 2
                            width: 20
                            height: 20
                            radius: 10
                            color: gnome_switch.down ? "#cccccc" : "#ffffff"
                            border.color: gnome_switch.checked ? (gnome_switch.down ? "#3498db" : "#3498db") : "#999999"
                        }
                    }

                    onCheckedChanged: {
                        if ( checked ) {
                            config.addSelection("gnome")
                        } else {
                            config.removeSelection("gnome")
                        }
                    }
                }

                Image {
                    id: gnome_image
                    x: 8
                    y: 25
                    height: 100
                    fillMode: Image.PreserveAspectFit
                    source: "images/desktops/gnome.png"
                }
            }

            Rectangle {
                id: plasma_rectangle
                width: 700
                height: 150
                color: "#ffffff"
                radius: 10
                border.width: 0
                Text {
                    width: 450
                    height: 104
                    anchors.centerIn: parent
                    text: qsTr("KDE Plasma a graphical workspaces environment created by KDE primarily for Linux systems. The graphical interface was fully migrated to QML, which uses OpenGL for hardware acceleration, which resulted in better performance and reduced power consumption.")
                    font.pointSize: 10
                    anchors.verticalCenterOffset: -10
                    anchors.horizontalCenterOffset: 100
                    wrapMode: Text.WordWrap
                }

                Switch {
                    id: plasma_switch
                    x: 500
                    y: 110
                    width: 187
                    height: 14
                    text: qsTr("Plasma")
                    checked: false
                    hoverEnabled: true

                    indicator: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 14
                        radius: 10
                        color: plasma_switch.checked ? "#3498db" : "#B9B9B9"
                        border.color: plasma_switch.checked ? "#3498db" : "#cccccc"

                        Rectangle {
                            x: plasma_switch.checked ? parent.width - width : 0
                            y: (parent.height - height) / 2
                            width: 20
                            height: 20
                            radius: 10
                            color: plasma_switch.down ? "#cccccc" : "#ffffff"
                            border.color: plasma_switch.checked ? (plasma_switch.down ? "#3498db" : "#3498db") : "#999999"
                        }
                    }

                    onCheckedChanged: {
                        if ( checked ) {
                            config.addSelection("plasma")
                        } else {
                            config.removeSelection("plasma")
                        }
                    }
                }

                Image {
                    id: plasma_image
                    x: 8
                    y: 25
                    height: 100
                    fillMode: Image.PreserveAspectFit
                    source: "images/desktops/plasma.png"
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
