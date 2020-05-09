/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Anke Boersma <demm@kaosx.us>
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

    //Needs to come from Locale config
    property var confLang: "en_US.UTF8"
    property var confLocale: "nl_NL.UTF8"

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
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is <strong>%1</strong>.").arg(confLang)
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

                        // bogus entries, need to come from Locale config
                        model: ["en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8", "en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8", "en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8", "en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8", "en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8"]

                        currentIndex: 1
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
                                    confLang = list1.currentIndex
                                }
                            }
                        }
                    }
                }
            }
        }

        Column {
            id: i18n
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
                    The system locale setting affects the language and character set for some command line user interface elements. The current setting is <strong>%1</strong>.").arg(confLocale)
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

                        // bogus entries, need to come from Locale config
                        model: ["en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8", "en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8", "en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8", "en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8", "en_GB.UTF-8 UTF-8", "en_US.UTF-8 UTF-8 ", "nl_NL.UTF-8 UTF-8"]

                        currentIndex: 2
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
                                    confLocale = list1.currentIndex
                                }
                            }
                        }
                        onCurrentItemChanged: console.debug(currentIndex)
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
