/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
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

/* This is a navigation (arrow) button that fades in on hover, and
 * which calls forward / backward navigation on the presentation it
 * is in. It should be a child item of the presentation (not of a
 * single slide). Use the ForwardButton or BackButton for a pre-
 * configured instance that interacts with the presentation.
 */

import QtQuick 2.5;

Image {
    id: fade
    
    property bool isForward : true
    
    width: 100
    height: 100
    anchors.verticalCenter: parent.verticalCenter
    opacity: 0.3
    
    OpacityAnimator {
        id: fadeIn
        target: fade
        from: fade.opacity
        to: 1.0
        duration: 500
        running: false
    }
    
    OpacityAnimator {
        id: fadeOut
        target: fade
        from: fade.opacity
        to: 0.3
        duration: 250
        running: false
    }
    
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onEntered: { fadeOut.running = false; fadeIn.running = true }
        onExited: { fadeIn.running = false ; fadeOut.running = true }
        onClicked: {
            if (isForward)
                fade.parent.goToNextSlide()
            else
                fade.parent.goToPreviousSlide()
        }
    }
}
