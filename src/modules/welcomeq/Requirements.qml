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
        id: required
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

        property var requirementsText: qsTr("<p>This computer does not satisfy the minimum requirements for installing %1.<br/>
        Installation cannot continue.</p>").arg(Branding.string(Branding.VersionedName))
        property var recommendationsText: qsTr("<p>This computer does not satisfy some of the recommended requirements for setting up %1.<br/>
        Setup can continue, but some features might be disabled.</p>").arg(Branding.string(Branding.VersionedName))

        text: config.requirementsModel.satisfiedMandatory ? recommendationsText : requirementsText
    }

    Rectangle {
        width: 640
        height: 360
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: required.bottom
        anchors.topMargin: 5

        Component {
            id: requirementsDelegate

            Item {
                width: 640
                height: 35
                visible: true

                Column {
                    anchors.centerIn: parent

                    Rectangle {
                        implicitWidth: 640
                        implicitHeight: 35
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
            // This uses the filtered model, so that only unsatisfied
            // requirements are ever shown. You could use *requirementsModel*
            // to get all of them.
            model: config.unsatisfiedRequirements
            delegate: requirementsDelegate
        }
    }
}

