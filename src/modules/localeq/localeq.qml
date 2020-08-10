/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

Page {
    width: 800
    height: 550

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

        Kirigami.FormLayout {
            id: lang

            GridLayout {
                anchors {
                    left: parent.left
                    top: parent.top
                    right: parent.right
                }
                rowSpacing: Kirigami.Units.largeSpacing
                columnSpacing: Kirigami.Units.largeSpacing

                Image {
                    source: "img/locale.svg"
                    Layout.fillHeight: true
                    Layout.maximumHeight: Kirigami.Units.iconSizes.medium
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
                    Label {
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                        text: config.currentLCStatus
                    }
                }
                Button {
                    Layout.alignment: Qt.AlignRight|Qt.AlignVCenter
                    Layout.columnSpan: 2
                    text: qsTr("Change")
                    //onClicked: console.log("Adjust Language clicked");
                    onClicked: {
                        onClicked: load.source = "i18n.qml"
                    }
                }
            }
        }

    }
    Loader {
        id:load
        anchors.fill: parent
    }
}
