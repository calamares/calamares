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

/* This control just shows a (non-translated) count of the slides
 * in the slideshow in the format "n / total".
 */

import QtQuick 2.5;

Rectangle {
    id: slideCounter
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    width: 100
    height: 50

    Text {
        id: slideCounterText
        anchors.centerIn: parent
        //: slide counter, %1 of %2 (numeric)
        text: qsTr("%L1 / %L2").arg(parent.parent.currentSlide + 1).arg(parent.parent.slides.length)
    }
}
