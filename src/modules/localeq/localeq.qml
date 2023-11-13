/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020 - 2022 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

Page {
    id: root
    width: parent.width
    height: parent.height

    readonly property color headerBackgroundColor: Kirigami.Theme.alternateBackgroundColor //"#eff0f1"
    readonly property color backgroundLighterColor: "#ffffff"
    readonly property color highlightColor: Kirigami.Theme.highlightColor //"#3498DB"
    readonly property color textColor: Kirigami.Theme.textColor //"#1F1F1F"
    readonly property color highlightedTextColor: Kirigami.Theme.highlightedTextColor

    function onActivate() {
        /* If you want the map to follow Calamares's GeoIP
         * lookup or configuration, call the update function
         * here, and disable the one at onCompleted in Map.qml.
         */
        if (Network.hasInternet) { image.item.getIpOffline() }
    }

    Loader {
        id: image
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: parent.height / 1.28
        // Network is in io.calamares.core
        source: Network.hasInternet ? "Map.qml" : "Offline.qml"
    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.bottomMargin : 20
        width: parent.width
        spacing: 50

        GridLayout {
            rowSpacing: Kirigami.Units.largeSpacing
            columnSpacing: Kirigami.Units.largeSpacing

            Kirigami.Icon {
                source: "qrc:/img/locale.svg"
                Layout.fillHeight: true
                Layout.maximumHeight: Kirigami.Units.iconSizes.large
                Layout.preferredWidth: height
            }

            ColumnLayout {
                Label {
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    text: config.currentLanguageStatus
                }
                Kirigami.Separator {
                    Layout.fillWidth: true
                }
                Button {
                    Layout.alignment: Qt.AlignRight|Qt.AlignVCenter
                    Layout.columnSpan: 2
                    text: qsTr("Change", "@button")
                    onClicked: {
                        drawerLanguage.open()
                    }
                }
            }
        }

        GridLayout {
            rowSpacing: Kirigami.Units.largeSpacing
            columnSpacing: Kirigami.Units.largeSpacing

            Kirigami.Icon {
                source: "qrc:/img/locale.svg"
                Layout.fillHeight: true
                Layout.maximumHeight: Kirigami.Units.iconSizes.large
                Layout.preferredWidth: height
            }
            ColumnLayout {
                Label {
                    Layout.fillWidth: true
                    wrapMode: Text.WordWrap
                    text: config.currentLCStatus
                }
                Kirigami.Separator {
                    Layout.fillWidth: true
                }
                Button {
                    Layout.alignment: Qt.AlignRight|Qt.AlignVCenter
                    Layout.columnSpan: 2
                    text: qsTr("Change", "@button")
                    onClicked: {
                        drawerLocale.open()
                    }
                }
            }
        }

        Drawer {
            id: drawerLanguage
            width: 0.33 * root.width
            height: root.height
            edge: Qt.LeftEdge

            ScrollView {
                id: scroll1
                anchors.fill: parent
                contentHeight: 800
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView {
                    id: list1
                    focus: true
                    clip: true
                    width: parent.width

                    model: config.supportedLocales
                    currentIndex: -1 //config.localeIndex

                    header: Rectangle {
                        width: parent.width
                        height: 100
                        color: "#eff0f1" //headerBackgroundColor
                        Text {
                            anchors.fill: parent
                            wrapMode: Text.WordWrap
                            text: qsTr("<h3>Languages</h3> </br>
                            The system locale setting affects the language and character set for some command line user interface elements. The current setting is <strong>%1</strong>.", "@info").arg(config.currentLanguageCode)
                            font.pointSize: 10
                        }
                    }

                    delegate: ItemDelegate {

                        property variant myData: model
                        hoverEnabled: true
                        width: drawerLanguage.width
                        implicitHeight: 24
                        highlighted: ListView.isCurrentItem
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            width: parent.width
                            height: 24
                            color: highlighted ? "#eff0f1" : "#1F1F1F" // headerBackgroundColor : textColor
                            text: modelData
                            background: Rectangle {

                                color: highlighted || hovered ? highlightColor : backgroundLighterColor
                                opacity: highlighted || hovered ? 0.5 : 0.9
                            }

                            MouseArea {
                                hoverEnabled: true
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    list1.currentIndex = index
                                    drawerLanguage.close()
                                }
                            }
                        }
                    }
                    onCurrentItemChanged: { config.currentLanguageCode = model[currentIndex] } /* This works because model is a stringlist */
                }
            }
        }

        Drawer {
            id: drawerLocale
            width: 0.33 * root.width
            height: root.height
            edge: Qt.RightEdge

            ScrollView {
                id: scroll2
                anchors.fill: parent
                contentHeight: 800
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff

                ListView {
                    id: list2
                    focus: true
                    clip: true
                    width: parent.width

                    model: config.supportedLocales
                    currentIndex: -1 //model.currentLCCodeIndex

                    header: Rectangle {
                        width: parent.width
                        height: 100
                        color: "#eff0f1" // headerBackgroundColor
                        Text {
                            anchors.fill: parent
                            wrapMode: Text.WordWrap
                            text: qsTr("<h3>Locales</h3> </br>
                                The system locale setting affects the numbers and dates format. The current setting is <strong>%1</strong>.", "@info").arg(config.currentLCCode)
                            font.pointSize: 10
                        }
                    }

                    delegate: ItemDelegate {

                        hoverEnabled: true
                        width: drawerLocale.width
                        implicitHeight: 24
                        highlighted: ListView.isCurrentItem
                        Label {
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            horizontalAlignment: Text.AlignHCenter
                            width: parent.width
                            height: 24
                            color: highlighted ? "#eff0f1" : "#1F1F1F" // headerBackgroundColor : textColor
                            text: modelData
                            background: Rectangle {

                                color: highlighted || hovered ? highlightColor : backgroundLighterColor
                                opacity: highlighted || hovered ? 0.5 : 0.9
                            }

                            MouseArea {
                                hoverEnabled: true
                                anchors.fill: parent
                                cursorShape: Qt.PointingHandCursor
                                onClicked: {
                                    list2.currentIndex = index
                                    drawerLocale.close()
                                }
                            }
                        }
                    }
                    onCurrentItemChanged: { config.currentLCCode = model[currentIndex]; } /* This works because model is a stringlist */
                }
            }
        }
    }
    Loader {
        id:load
        anchors.fill: parent
    }
}
