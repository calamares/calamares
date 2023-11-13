/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2021 - 2023 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.kirigami as Kirigami
import QtQuick.Window

Page {

    id: finished

    width: parent.width
    height: parent.height

    header: Kirigami.Heading {
        width: parent.width
        height: 100
        id: header
        Layout.fillWidth: true
        horizontalAlignment: Qt.AlignHCenter
        color: Kirigami.Theme.textColor
        level: 1
        text: qsTr("Installation Completed", "@title")

        Text {
            anchors.top: header.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
            text: qsTr("%1 has been installed on your computer.<br/>
            You may now restart into your new system, or continue using the Live environment.", "@info, %1 is the product name")
                .arg(Branding.string(Branding.ProductName))
        }

        Image {
            source: "seedling.svg"
            anchors.top: header.bottom
            anchors.topMargin: 80
            anchors.horizontalCenter: parent.horizontalCenter
            width: 64
            height: 64
            mipmap: true
        }
    }

    RowLayout {
        Layout.alignment: Qt.AlignRight|Qt.AlignVCenter
        anchors.centerIn: parent
        spacing: 6

        Button {
            id: button
            text: qsTr("Close Installer", "@button")
            icon.name: "application-exit"
            onClicked: { ViewManager.quit(); }
        }

        Button {
            text: qsTr("Restart System", "@button")
            icon.name: "system-reboot"
            onClicked: { config.doRestart(true); }
        }
    }

    Item {

        Layout.fillHeight: true
        Layout.fillWidth: true
        anchors.bottom: parent.bottom
        anchors.bottomMargin : 100
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            anchors.centerIn: parent
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("<p>A full log of the install is available as installation.log in the home directory of the Live user.<br/>
            This log is copied to /var/log/installation.log of the target system.</p>", "@info")
        }
    }

    function onActivate() {
    }

    function onLeave() {
    }
}
