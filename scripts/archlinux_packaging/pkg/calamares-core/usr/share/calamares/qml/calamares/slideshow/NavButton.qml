/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
