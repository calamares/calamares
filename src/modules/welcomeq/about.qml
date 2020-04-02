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
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Item {
    width: parent.width
    height: parent.height
    focus: true
    
    property var appName: "Calamares"
    property var appVersion: "3.2.22"

    Rectangle {
        id: textArea
        x: 28
        y: 14
        anchors.fill: parent
        color: "#f2f2f2"
        
        Column {
            id: column
            x: 130
            y: 40

            
            Rectangle {
                width: 560
                height: 250
                radius: 10
                border.width: 0
                
                Text {
                    width: 400
                    height: 250
                    anchors.centerIn: parent
                    text: qsTr("<h1>%1</h1><br/>
                        <strong>%2<br/>
                        for %3</strong><br/><br/>
                        Copyright 2014-2017 Teo Mrnjavac &lt;teo@kde.org&gt;<br/>
                        Copyright 2017-2020 Adriaan de Groot &lt;groot@kde.org&gt;<br/>
                        Thanks to <a href='https://calamares.io/team/'>the Calamares team</a> 
                        and the <a href='https://www.transifex.com/calamares/calamares/'>Calamares 
                        translators team</a>.<br/><br/>
                        <a href='https://calamares.io/'>Calamares</a> 
                        development is sponsored by <br/>
                        <a href='http://www.blue-systems.com/'>Blue Systems</a> - 
                        Liberating Software." )
                        .arg(appName)
                        .arg(appVersion)
                        .arg(Branding.string(Branding.VersionedName))
                        
                        onLinkActivated: Qt.openUrlExternally(link)
                        
                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.NoButton
                            cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
                        }
                        
                    font.pointSize: 10
                    anchors.verticalCenterOffset: 10
                    anchors.horizontalCenterOffset: 40
                    wrapMode: Text.WordWrap
                }

                Image {
                    id: image
                    x: 8
                    y: 12
                    height: 100
                    fillMode: Image.PreserveAspectFit
                    source: "img/squid.png"
                }

            }

        }

        ToolButton {
            id: toolButton
            x: 19
            y: 29
            width: 105
            height: 48
            text: qsTr("Back")
            hoverEnabled: true
            onClicked: load.source = ""

            Image {
                id: image1
                x: 0
                y: 13
                width: 22
                height: 22
                source: "img/chevron-left-solid.svg"
                fillMode: Image.PreserveAspectFit
            }
        }
    }

}
