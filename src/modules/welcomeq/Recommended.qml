/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
