/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Anke Boersma <demm@kaosx.us>
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

/* Some Calamares internals are available to all QML modules.
 * They live in the calamares.ui namespace (filled programmatically
 * by Calamares). One of the internals that is exposed is the
 * Branding object, which can be used to retrieve strings and paths
 * and colors.
 */
import calamares.ui 1.0

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
            id: fscrollbar
            width: 10
            policy: ScrollBar.AlwaysOn
        }

        TextArea {
            id: intro
            x: 1
            y: 0
            width: parent.width - fscrollbar.width
            font.pointSize: 14
            textFormat: Text.RichText
            antialiasing: true
            activeFocusOnPress: false
            wrapMode: Text.WordWrap

            text: qsTr("<h3>%1</h3>
            <p>This an example QML file, showing options in RichText with Flickable content.</p>

            <p>QML with RichText can use HTML tags, Flickable content is useful for touchscreens.</p>

            <p><b>This is bold text</b></p>
            <p><i>This is italic text</i></p>
            <p><u>This is underlined text</u></p>
            <p><center>This text will be center-aligned.</center></p>
            <p><s>This is strikethrough</s></p>

            <p>Code example:
            <code>ls -l /home</code></p>

            <p><b>Lists:</b></p>
            <ul>
                <li>Intel CPU systems</li>
                <li>AMD CPU systems</li>
            </ul>

            <p>The vertical scrollbar is adjustable, current width set to 10.</p>").arg(Branding.string(Branding.VersionedName))

        }
    }
}
