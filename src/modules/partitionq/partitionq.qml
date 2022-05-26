/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Aditya Mehra <aix.m@outlook.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.14
import QtQuick.Layouts 1.3

import org.kde.kirigami 2.7 as Kirigami

Page {
    id: partitionPage
    
    Connections {
        target: core
        onInitCompleted: {
            console.log("Partition Core Module Init Completed")
            busyIndicator.running = false
            busyIndicator.visible = false
            partitionViewLoader.source = "qrc:/ChoosePage.qml"
        }
    }
    
    BusyIndicator {
        id: busyIndicator
        anchors.centerIn: parent
        running: true
        visible: true
        width: parent.width / 2
        height: parent.height / 2
    }

    Loader {
        id: partitionViewLoader
        anchors.fill: parent
    }
}