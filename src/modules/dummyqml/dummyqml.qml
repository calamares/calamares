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

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1

Item {
    width: 740
    height: 420

    Flickable {
        id: flick
        anchors.fill: parent
        contentHeight: 800
        
        ScrollBar.vertical: ScrollBar {
            width: 10
            policy: ScrollBar.AlwaysOn
        }

        TextArea {
            id: intro
            x: 1
            y: 0
            width: 720
            font.pointSize: 14
            textFormat: Text.RichText
            antialiasing: true
            activeFocusOnPress: false
            wrapMode: Text.WordWrap

            text: qsTr("<h3>Generic GNU/Linux 2017.8 LTS <quote>Soapy Sousaphone</quote></h3>
            <p>This an example QML file, showing options in RichText with Flickable content.</p>
            
            <p>QML with RichText can use HTML tags, Flickable content is useful for touchscreens.</p>
            
            <p><b>This is bold text</b></p>
            <p><i>This is italic text</i></p>
            <p><u>This is underlined text</u></p>
            <p><strike>This is strikethrough</strike></p>
            
            <p>Code example:
            <code>ls -l /home</code></p>
            
            <p><b>Lists:</b></p>
            <ul>
                <li>Intel CPU systems</li>
                <li>AMD CPU systems</li>
            </ul>
            
            <p>The vertical scrollbar is adjustable, current width set to 10.</p>")

        }
    }
}
