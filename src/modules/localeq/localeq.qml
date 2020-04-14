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

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

Page
{
    Map  {
        id: image
        anchors.horizontalCenter: parent.horizontalCenter
    }
    
    RowLayout {
 
        anchors.top: image.bottom
        width: parent.width
        
        Kirigami.FormLayout {
            id: region
            Layout.fillWidth: true

            ComboBox {
                Kirigami.FormData.label: qsTr("Country: ")
                id: regionIndex
                currentIndex: model.currentIndex
                textRole: "label"
                model: config.regionModel
                onCurrentIndexChanged: console.debug(currentText, currentIndex)
            }
            Kirigami.Separator {
                Kirigami.FormData.isSection: true
                Kirigami.FormData.label: "System language set to American English"
            }
            
            Button {
                text: qsTr("Adjust Language")
                Layout.fillWidth: true
            }
        }
        
        Kirigami.FormLayout {
            id: zone
            Layout.fillWidth: true

            ComboBox {
                Kirigami.FormData.label: qsTr("City: ")
                id: zoneIndex
                currentIndex: model.currentIndex
                textRole: "label"
                model: config.zonesModel
                onCurrentIndexChanged: console.debug(currentText, currentIndex)
            }
            Kirigami.Separator {
                Kirigami.FormData.isSection: true
                Kirigami.FormData.label: "Numbers and dates locale set to American English"
            }
            Button {
                text: qsTr("Adjust Locale")
                Layout.fillWidth: true
            }
        }
    }
}
