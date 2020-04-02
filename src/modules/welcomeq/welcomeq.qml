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
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3

Page
{
    id: welcome

    header: Item
    {
        width: parent.width
        height: parent.height

        Text
        {
            id: welcomeTopText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            // In QML, QString::arg() only takes one argument
            text: qsTr("<h3>Welcome to the %1 <quote>%2</quote> installer</h3>").arg(Branding.string(Branding.ProductName)).arg(Branding.string(Branding.Version))
        }
        Image
        {
            id: welcomeImage
            anchors.centerIn: parent
            // imagePath() returns a full pathname, so make it refer to the filesystem
            // .. otherwise the path is interpreted relative to the "call site", which
            // .. might be the QRC file.
            source: "file:/" + Branding.imagePath(Branding.ProductWelcome)
            sourceSize.width: width
            sourceSize.height: height
            fillMode: Image.PreserveAspectFit
        }

        RowLayout
        {
            id: buttonBar
            width: parent.width
            height: 64

            anchors.bottom: parent.bottom

            spacing: Kirigami.Units.largeSpacing* 2

/* Traditionally Calamares has had an "About" button that talks about
 * Calamares itself, which just isn't a very useful thing in someone
 * else's installation ISO.
 */
            Button
            {
                Layout.fillWidth: true
                text: qsTr("About")
                icon.name: "dialog-information"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor
                
                visible: false
                onClicked: { 
                    //onClicked: load.source = "file:/usr/share/calamares/branding/kaos_branding/show.qml"
                    onClicked: load.source = "about.qml"
                }
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Support")
                icon.name: "system-help"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: config.supportUrl !== ""
                onClicked: Qt.openUrlExternally(config.supportUrl)
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Known issues")
                icon.name: "tools-report-bug"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: config.knownIssuesUrl !== ""
                onClicked: Qt.openUrlExternally(config.knownIssuesUrl)
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Release notes")
                icon.name: "folder-text"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: config.releaseNotesUrl !== ""
                onClicked: Qt.openUrlExternally(config.releaseNotesUrl)
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Donate")
                icon.name: "taxes-finances"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: config.donateUrl !== ""
                onClicked: Qt.openUrlExternally(config.donateUrl)
            }
        }
        Loader
        { 
            id:load 
            anchors.fill: parent
        }
    }
}
