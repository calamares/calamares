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

Rectangle {
    focus: true
    Kirigami.Theme.backgroundColor: Kirigami.Theme.backgroundColor
    anchors.fill: parent
    anchors.topMargin: 70

    TextArea {
        id: required
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 20
        width: 640
        font.pointSize: 12
        textFormat: Text.RichText
        antialiasing: true
        activeFocusOnPress: false
        wrapMode: Text.WordWrap

        text: qsTr("<p>This computer does not satisfy the minimum requirements for setting up %1.</p>
        <p>Setup cannot continue.</p>").arg(Branding.string(Branding.VersionedName))
    }

    TextArea {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: required.bottom
        anchors.topMargin: 20
        width: 640
        background: Rectangle {
            implicitWidth: 640
            implicitHeight: 50
            border.color: "#ff0000"
            color: "#ffc0cb"
        }
        font.pointSize: 12
        textFormat: Text.RichText
        antialiasing: true
        activeFocusOnPress: false
        wrapMode: Text.WordWrap

        text: qsTr("<p>The installer is not running with administrator rights.</p>")//.arg(requirementsModel)
    }
}
