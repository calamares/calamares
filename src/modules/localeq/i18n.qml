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
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import org.kde.kirigami 2.7 as Kirigami

Item {
    width: parent.width
    height: parent.height
    focus: true
    MouseArea {
        anchors.fill: parent
    }

    Rectangle {
        id: textArea
        x: 28
        y: 14
        anchors.fill: parent
        Kirigami.Theme.backgroundColor: Kirigami.Theme.backgroundColor

        Column {
            id: languages
            x: 130
            y: 40

            Rectangle {
                width: 250
                height: 140
                color: "#d3d3d3"
                Text {
                    anchors.top: parent.top
                    width: 240
                    wrapMode: Text.WordWrap
                    text: qsTr("<h1>Languages</h1> </br>
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is <strong>%1</strong>.").arg(config.currentLanguageCode)
                    font.pointSize: 10
                }
            }

            Rectangle {
                width: 250
                height: 300

                ScrollView {
                    id: scroll1
                    anchors.fill: parent
                    contentHeight: 800
                    clip: true

                    ListView {
                        id: list1
                        focus: true

                        model: config.supportedLocales

                        currentIndex: -1
                        highlight: Rectangle {
                            color: Kirigami.Theme.highlightColor
                        }
                        delegate: Text {
                            text: modelData

                            MouseArea {
                                hoverEnabled: true
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onEntered: {
                                    color: "#0000ff"
                                }
                                onClicked: {
                                    list1.currentIndex = index
                                }
                            }
                        }
                        onCurrentItemChanged: { config.currentLanguageCode = model[currentIndex] } /* This works because model is a stringlist */
                    }
                }
            }
        }

        Column {
            id: lc_numeric
            x: 430
            y: 40

            Rectangle {
                width: 250
                height: 140
                color: "#d3d3d3"
                Text {
                    anchors.top: parent.top
                    width: 240
                    wrapMode: Text.WordWrap
                    text: qsTr("<h1>Locales</h1> </br>
                    The system locale setting affects the numbers and dates format. The current setting is <strong>%1</strong>.").arg(config.currentLCCode)
                    font.pointSize: 10
                }
            }

            Rectangle {
                width: 250
                height: 300

                ScrollView {
                    id: scroll2
                    anchors.fill: parent
                    contentHeight: 800
                    clip: true

                    ListView {
                        id: list2
                        width: 180; height: 200
                        focus: true

                        model: config.supportedLocales

                        currentIndex: -1
                        highlight: Rectangle {
                            color: Kirigami.Theme.highlightColor
                        }
                        delegate: Text {
                            text: modelData

                            MouseArea {
                                hoverEnabled: true
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    list2.currentIndex = index
                                }
                            }
                        }
                        onCurrentItemChanged: { config.currentLCCode = model[currentIndex]; } /* This works because model is a stringlist */
                    }
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
