/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 - 2022 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

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
    anchors.topMargin: 60

    TextArea {
        id: required
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        horizontalAlignment: TextEdit.AlignHCenter
        width: parent.width
        font.pointSize: 11
        textFormat: Text.RichText
        antialiasing: true
        activeFocusOnPress: false
        wrapMode: Text.WordWrap

        property var requirementsText: qsTr("<p>This computer does not satisfy the minimum requirements for installing %1.<br/>
        Installation cannot continue.</p>").arg(Branding.string(Branding.VersionedName))
        property var recommendationsText: qsTr("<p>This computer does not satisfy some of the recommended requirements for setting up %1.<br/>
        Setup can continue, but some features might be disabled.</p>").arg(Branding.string(Branding.VersionedName))

        text: config.requirementsModel.satisfiedMandatory ? recommendationsText : requirementsText
    }

    Rectangle {
        width: parent.width * 0.8
        height: parent.height * 0.6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: required.bottom
        anchors.topMargin: 5

        Component {
            id: requirementsDelegate

            Item {
                width: parent.width
                implicitHeight: message.implicitHeight + 30
                visible: true

                Column {
                    anchors.centerIn: parent

                    Rectangle {
                        implicitWidth: 640
                        implicitHeight: message.implicitHeight + 30
                        // Colors and images based on the two satisfied-bools:
                        // - if satisfied, then green / ok
                        // - otherwise if mandatory, then red / stop
                        // - otherwise, then yellow / warning
                        border.color: satisfied ? "#228b22" : (mandatory ? "#ff0000" : "#ffa411")
                        color: satisfied ? "#f0fff0" : (mandatory ? "#ffc0cb" : "#ffefd5")

                        Image {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.right: parent.right
                            anchors.margins: 20
                            source: satisfied ? "qrc:/data/images/yes.svgz" : (mandatory ? "qrc:/data/images/no.svgz" : "qrc:/data/images/information.svgz")
                        }

                        Text {
                            id: message
                            text: satisfied ? details : negatedText
                            anchors.centerIn: parent
                            font.pointSize: 11
                        }
                    }
                }
            }
        }

        ListView {
            id: requirementsList
            anchors.fill: parent
            spacing: 5
            clip: true
            // This uses the unfiltered model, so that all requirements are
            // shown. You could use *unsatisfiedRequirements* to get the
            // filtered model so that only unsatisfied requirements are ever shown.
            //model: config.unsatisfiedRequirements
            model: config.requirementsModel
            delegate: requirementsDelegate
            ScrollBar.vertical: ScrollBar {
                active: true
            }
        }
    }
}

