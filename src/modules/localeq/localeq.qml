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

    property var confLang: "American English"
    property var confLocale: "Nederland"
    //Needs to come from .conf/geoip
    property var hasInternet: true

    function getInt(format) {
        var requestURL = "https://example.org/";
        var xhr = new XMLHttpRequest;

        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {

                if (xhr.status !== 200) {
                    console.log("Disconnected!!");
                    var connected = false
                    hasInternet = connected
                    return;
                }

                else {
                    console.log("Connected!!");
                }
            }
        }
        xhr.open("GET", requestURL, true);
        xhr.send();
    }
    Component.onCompleted: {
        getInt();
    }

    Loader {
        id: image
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: parent.height / 1.28
        source: (hasInternet) ? "Map.qml" : "Offline.qml"
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

                Kirigami.Icon {
                    source: "application-x-gettext-translation"
                    Layout.fillHeight: true
                    Layout.maximumHeight: Kirigami.Units.iconSizes.medium
                    Layout.preferredWidth: height
                }
                ColumnLayout {
                    Label {
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                        text: qsTr("System language set to %1").arg(confLang)
                    }
                    Kirigami.Separator {
                        Layout.fillWidth: true
                    }
                    Label {
                        Layout.fillWidth: true
                        wrapMode: Text.WordWrap
                        text: qsTr("Numbers and dates locale set to %1").arg(confLocale)
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
