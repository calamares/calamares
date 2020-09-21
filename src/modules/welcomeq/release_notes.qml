/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.ui 1.0

import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3

Rectangle {
    width: parent.width
    height: parent.height
    focus: true
    color: "#f2f2f2"

    Flickable {
        id: flick
        anchors.fill: parent
        contentHeight: 3500

        ScrollBar.vertical: ScrollBar {
            id: fscrollbar
            width: 10
            policy: ScrollBar.AlwaysOn
        }

        TextArea {
            id: intro
            x: 130
            y: 8
            width: 640
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
