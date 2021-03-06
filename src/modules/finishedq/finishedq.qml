/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3

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
        text: qsTr("Installation Completed")

        Text {
            anchors.top: header.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 12
            text: qsTr("%1 has been installed on your computer.<br/>
            You may now restart into your new system, or continue using the Live environment.").arg(Branding.string(Branding.ProductName))
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
            text: qsTr("Close Installer")
            icon.name: "application-exit"
            onClicked: { ViewManager.quit(); }
        }

        Button {
            text: qsTr("Restart System")
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
            This log is copied to /var/log/installation.log of the target system.</p>")
        }
    }

    function onActivate()
    {
    }

    function onLeave()
    {
    }
}
