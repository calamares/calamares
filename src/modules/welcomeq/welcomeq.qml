/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
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
import calamares.ui 1.0

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
        height: 150

        Text
        {
            id: welcomeTopText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            // In QML, QString::arg() only takes one argument
            text: qsTr("<h3>%1 <quote>%2</quote></h3>").arg(Branding.string(Branding.ProductName)).arg(Branding.string(Branding.Version))
        }
        Image
        {
            id: welcomeImage
            anchors.centerIn: parent
            // imagePath() returns a full pathname, so make it refer to the filesystem
            // .. otherwise the path is interpreted relative to the "call site", which
            // .. might be the QRC file.
            source: "file:/" + Branding.imagePath(Branding.ProductWelcome)
            height: Math.min(100, parent.height)
            width: height
            sourceSize.width: width
            sourceSize.height: height
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
                icon.name: "documentinfo"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: "#fff"

                visible: false
                onClicked: { } // TODO: show an about-Calamares window
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Support")
                icon.name: "documentinfo"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: "#fff"

                visible: config.helpUrl.isValid
                onClicked: Qt.openUrlExternally(config.helpUrl)
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Known issues")
                icon.name: "documentinfo"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: "#fff"

                visible: config.issuesUrl.isValid
                onClicked: Qt.openUrlExternally(config.issuesUrl)
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Release notes")
                icon.name: "documentinfo"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: "#fff"

                visible: config.notesUrl.isValid
                onClicked: Qt.openUrlExternally(config.notesUrl)
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Donate")
                icon.name: "documentinfo"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: "#fff"

                visible: config.donateUrl.isValid
                onClicked: Qt.openUrlExternally(config.donateUrl)
            }
        }
    }
}
