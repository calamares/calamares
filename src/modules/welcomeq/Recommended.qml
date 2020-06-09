/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Anke Boersma <demm@kaosx.us>
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

/* THIS COMPONENT IS UNUSED -- from the default welcomeq.qml at least */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

Rectangle {
    focus: true
    Kirigami.Theme.backgroundColor: Kirigami.Theme.backgroundColor
    anchors.fill: parent
    anchors.topMargin: 50

    TextArea {
        id: recommended
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 1
        horizontalAlignment: TextEdit.AlignHCenter
        width: 640
        font.pointSize: 11
        textFormat: Text.RichText
        antialiasing: true
        activeFocusOnPress: false
        wrapMode: Text.WordWrap

        text: qsTr("<p>This computer does not satisfy some of the recommended requirements for setting up %1.<br/>
        Setup can continue, but some features might be disabled.</p>").arg(Branding.string(Branding.VersionedName))
    }

    Rectangle {
        width: 640
        height: 360
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: recommended.bottom
        anchors.topMargin: 5

        Component {
            id: requirementsDelegate

            Item {
                width: 640
                height: 35

                Column {
                    anchors.centerIn: parent

                    Rectangle {
                        implicitWidth: 640
                        implicitHeight: 35
                        border.color: satisfied ? "#228b22" : "#ffa411"
                        color: satisfied ? "#f0fff0" : "#ffefd5"

                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.margins: 20
                            source: satisfied ? "qrc:/data/images/yes.svgz" : "qrc:/data/images/information.svgz"
                        }

                        Text {
                            text: satisfied ? details : negatedText
                            anchors.centerIn: parent
                            font.pointSize: 11
                        }
                    }
                }
            }
        }

        ListView {
            anchors.fill: parent
            spacing: 5
            model: config.requirementsModel
            delegate: requirementsDelegate
        }
    }
}
