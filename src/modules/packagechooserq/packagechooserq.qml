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

        ButtonGroup {
            id: switchGroup
        }

        Column {
            id: column
            anchors.centerIn: parent
            spacing: 5

            Rectangle {
                //id: rectangle
                width: 700
                height: 150
                color: "#ffffff"
                radius: 10
                border.width: 0
                Text {
                    width: 450
                    height: 104
                    anchors.centerIn: parent
                    text: qsTr("LibreOffice is a powerful and free office suite, used by millions of people around the world. It includes several applications that make it the most versatile Free and Open Source office suite on the market.<br/>
                    Default option.")
                    font.pointSize: 10
                    anchors.verticalCenterOffset: -10
                    anchors.horizontalCenterOffset: 100
                    wrapMode: Text.WordWrap
                }

                Switch {
                    id: element2
                    x: 500
                    y: 110
                    width: 187
                    height: 14
                    text: qsTr("LibreOffice")
                    checked: true
                    hoverEnabled: true
                    ButtonGroup.group: switchGroup

                    indicator: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 14
                        radius: 10
                        color: element2.checked ? "#3498db" : "#B9B9B9"
                        border.color: element2.checked ? "#3498db" : "#cccccc"

                        Rectangle {
                            x: element2.checked ? parent.width - width : 0
                            y: (parent.height - height) / 2
                            width: 20
                            height: 20
                            radius: 10
                            color: element2.down ? "#cccccc" : "#ffffff"
                            border.color: element2.checked ? (element1.down ? "#3498db" : "#3498db") : "#999999"
                        }
                    }

                    onCheckedChanged: {
                        if ( checked ) {
                            config.packageChoice = "libreoffice"
                        }
                    }
                }

                Image {
                    id: image2
                    x: 8
                    y: 25
                    height: 100
                    fillMode: Image.PreserveAspectFit
                    source: "images/libreoffice.jpg"
                }
            }

            Rectangle {
                width: 700
                height: 150
                radius: 10
                border.width: 0
                Text {
                    width: 450
                    height: 104
                    anchors.centerIn: parent
                    text: qsTr("If you don't want to install an office suite, just select No Office Suite. You can always add one (or more) later on your installed system as the need arrives.")
                    font.pointSize: 10
                    anchors.verticalCenterOffset: -10
                    anchors.horizontalCenterOffset: 100
                    wrapMode: Text.WordWrap
                }

                Switch {
                    id: element1
                    x: 500
                    y: 110
                    width: 187
                    height: 14
                    text: qsTr("No Office Suite")
                    checked: false
                    hoverEnabled: true
                    ButtonGroup.group: switchGroup

                    indicator: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 14
                        radius: 10
                        color: element1.checked ? "#3498db" : "#B9B9B9"
                        border.color: element1.checked ? "#3498db" : "#cccccc"

                        Rectangle {
                            x: element1.checked ? parent.width - width : 0
                            y: (parent.height - height) / 2
                            width: 20
                            height: 20
                            radius: 10
                            color: element1.down ? "#cccccc" : "#ffffff"
                            border.color: element1.checked ? (element1.down ? "#3498db" : "#3498db") : "#999999"
                        }
                    }

                    onCheckedChanged: {
                        if ( checked ) {
                            config.packageChoice = "no_office_suite"
                        }
                    }
                }

                Image {
                    id: image
                    x: 8
                    y: 25
                    height: 100
                    fillMode: Image.PreserveAspectFit
                    source: "images/no-selection.png"
                }

            }

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
                    text: qsTr("Create a minimal Desktop install, remove all extra applications and decide later on what you would like to add to your system. Examples of what won't be on such an install, there will be no Office Suite, no media players, no image viewer or print support.  It will be just a desktop, file browser, package manager, text editor and simple web-browser.")
                    font.pointSize: 10
                    anchors.verticalCenterOffset: -10
                    anchors.horizontalCenterOffset: 100
                    wrapMode: Text.WordWrap
                }

                Switch {
                    id: element3
                    x: 500
                    y: 110
                    width: 187
                    height: 14
                    text: qsTr("Minimal Install")
                    checked: false
                    hoverEnabled: true
                    ButtonGroup.group: switchGroup

                    indicator: Rectangle {
                        implicitWidth: 40
                        implicitHeight: 14
                        radius: 10
                        color: element3.checked ? "#3498db" : "#B9B9B9"
                        border.color: element3.checked ? "#3498db" : "#cccccc"

                        Rectangle {
                            x: element3.checked ? parent.width - width : 0
                            y: (parent.height - height) / 2
                            width: 20
                            height: 20
                            radius: 10
                            color: element3.down ? "#cccccc" : "#ffffff"
                            border.color: element3.checked ? (element3.down ? "#3498db" : "#3498db") : "#999999"
                        }
                    }

                    onCheckedChanged: {
                        if ( checked ) {
                            config.packageChoice = "minimal_install"
                        }
                    }
                }

                Image {
                    id: image3
                    x: 8
                    y: 25
                    height: 100
                    fillMode: Image.PreserveAspectFit
                    source: "images/plasma.png"
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
                    text: qsTr("Please select an option for your install, or use the default: LibreOffice included.")
                    font.pointSize: 10
                    wrapMode: Text.WordWrap
                }
            }
        }
    }

}
