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
            You may now restart your device.").arg(Branding.string(Branding.ProductName))
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
            text: qsTr("Close")
            icon.name: "application-exit"
            onClicked: { ViewManager.quit(); }
        }

        Button {
            text: qsTr("Restart")
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

        ProgressBar {
            id: autoRestartBar
            value: 1.0
            anchors.horizontalCenter: parent.horizontalCenter

        }

        Timer {
            id: autoRestartTimer
            // This is in milliseconds and should be less than 1000 (because of logic in onTriggered)
            interval: 100
            repeat: true
            running: false
            // Whenever the timer fires (1000 / interval times a second) count the progress bar down
            // by 1%. When the bar is empty, try to restart normally; as a backup, when the bar
            // is empty change settings and schedule it to quit 1000 milliseconds (1s) later.
            onTriggered: {
                autoRestartBar.value -= 0.01;
                if (autoRestartBar.value <= 0.0) {
                    // First time through here, set the interval to 1000 so that the
                    // second time (1 second later) goes to quit().
                    if ( interval > 999) { ViewManager.quit(); }
                    else { config.doRestart(true); running = false; interval = 1000; repeat = false; start(); }
                }
            }
        }
    }

    function onActivate()
    {
        autoRestartTimer.running = true
    }

    function onLeave()
    {
    }
}
