/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

import QtQuick 2.0;
import calamares.slideshow 1.0;

Presentation
{
    id: presentation

    Timer {
        interval: 5000
        running: false
        repeat: true
        onTriggered: presentation.goToNextSlide()
    }
    
    Slide {
        Image {
            id: background1  // Must be unique
            source: "squid.png"
            width: 200; height: 200
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        Text {
            anchors.horizontalCenter: background1.horizontalCenter
            anchors.top: background1.bottom
            text: qsTr("This is a customizable QML slideshow.")
            wrapMode: Text.WordWrap
            width: presentation.width
            horizontalAlignment: Text.Center
        }
    }

    Slide {
        Image {
            id: background2
            source: "squid2.png"
            width: 200; height: 200
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        Text {
            id: namelabel2
            anchors.horizontalCenter: background2.horizontalCenter
            anchors.top: background2.bottom
            text: qsTr("Welcome to Fancy GNU/Linux.")
            wrapMode: Text.WordWrap
            width: presentation.width
            horizontalAlignment: Text.Center
            font.pointSize: 20
        }
        Text {
            anchors.horizontalCenter: background2.horizontalCenter
            anchors.top: namelabel2.bottom
            text: qsTr("This is example branding for your GNU/Linux distribution. " +
                "Long texts in the slideshow are translated and word-wrapped appropriately. " +
                "Calamares is a distribution-independent installer framework. ")
            wrapMode: Text.WordWrap
            width: presentation.width
            horizontalAlignment: Text.Center
        }
    }

    Slide {
        Image {
            id: background3
            source: "squid3.png"
            width: 200; height: 200
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        centeredText: qsTr("This is a third Slide element.")
    }

    Slide {
        Image {
            id: background4
            source: "squid4.png"
            width: 200; height: 200
            fillMode: Image.PreserveAspectFit
            anchors.centerIn: parent
        }
        centeredText: qsTr("This is a fourth Slide element.")
    }
}
