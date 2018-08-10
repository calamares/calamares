/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
 *     - added looping, keys-instead-of-shortcut
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
 *     - make looping a property, drop the 'c' fade-key
 *     - drop navigation through entering a slide number
 *       (this and the 'c' key make sense in a *presentation*
 *       slideshow, not in a passive slideshow like Calamares)
 *     - remove quit key
 *
 *   SPDX-License-Identifier: LGPL-2.1
 *   License-Filename: LICENSES/LGPLv2.1-Presentation
 */

/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QML Presentation System.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


import QtQuick 2.5
import QtQuick.Window 2.0

Item {
    id: root

    property variant slides: []
    property int currentSlide: 0

    property bool loopSlides: true

    property bool showNotes: false;
    property bool allowDelay: true;
    property alias mouseNavigation: mouseArea.enabled
    property bool arrowNavigation: true
    property bool keyShortcutsEnabled: true

    property color titleColor: textColor;
    property color textColor: "black"
    property string fontFamily: "Helvetica"
    property string codeFontFamily: "Courier New"

    // Private API
    property int _lastShownSlide: 0

    Component.onCompleted: {
        var slideCount = 0;
        var slides = [];
        for (var i=0; i<root.children.length; ++i) {
            var r = root.children[i];
            if (r.isSlide) {
                slides.push(r);
            }
        }

        root.slides = slides;

        // Make first slide visible...
        if (root.slides.length > 0)
            root.slides[root.currentSlide].visible = true;
    }

    function switchSlides(from, to, forward) {
        from.visible = false
        to.visible = true
        return true
    }

    onCurrentSlideChanged: {
        switchSlides(root.slides[_lastShownSlide], root.slides[currentSlide], currentSlide > _lastShownSlide)
        _lastShownSlide = currentSlide
        // Always keep focus on the slideshow
        root.focus = true
    }

    function goToNextSlide() {
        if (root.slides[currentSlide].delayPoints) {
            if (root.slides[currentSlide]._advance())
                return;
        }
        if (currentSlide + 1 < root.slides.length)
            ++currentSlide;
        else if (loopSlides)
            currentSlide = 0;  // Loop at the end
    }

    function goToPreviousSlide() {
        if (currentSlide - 1 >= 0)
            --currentSlide;
        else if (loopSlides)
            currentSlide = root.slides.length - 1
    }

    focus: true  // Keep focus

    // Navigation through key events, too
    Keys.onSpacePressed: goToNextSlide()
    Keys.onRightPressed: goToNextSlide()
    Keys.onLeftPressed: goToPreviousSlide()

    // navigate with arrow keys
    Shortcut { sequence: StandardKey.MoveToNextLine; enabled: root.arrowNavigation; onActivated: goToNextSlide() }
    Shortcut { sequence: StandardKey.MoveToPreviousLine; enabled: root.arrowNavigation; onActivated: goToPreviousSlide() }
    Shortcut { sequence: StandardKey.MoveToNextChar; enabled: root.arrowNavigation; onActivated: goToNextSlide() }
    Shortcut { sequence: StandardKey.MoveToPreviousChar; enabled: root.arrowNavigation; onActivated: goToPreviousSlide() }

    // presentation-specific single-key shortcuts (which interfere with normal typing)
    Shortcut { sequence: " "; enabled: root.keyShortcutsEnabled; onActivated: goToNextSlide() }

    // standard shortcuts
    Shortcut { sequence: StandardKey.MoveToNextPage; onActivated: goToNextSlide() }
    Shortcut { sequence: StandardKey.MoveToPreviousPage; onActivated: goToPreviousSlide() }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton | Qt.RightButton
        onClicked: {
            if (mouse.button == Qt.RightButton)
                goToPreviousSlide()
            else
                goToNextSlide()
        }
        onPressAndHold: goToPreviousSlide(); //A back mechanism for touch only devices
    }

    Window {
        id: notesWindow;
        width: 400
        height: 300

        title: "QML Presentation: Notes"
        visible: root.showNotes

        Flickable {
            anchors.fill: parent
            contentWidth: parent.width
            contentHeight: textContainer.height

            Item {
                id: textContainer
                width: parent.width
                height: notesText.height + 2 * notesText.padding

                Text {
                    id: notesText

                    property real padding: 16;

                    x: padding
                    y: padding
                    width: parent.width - 2 * padding


                    font.pixelSize: 16
                    wrapMode: Text.WordWrap

                    property string notes: root.slides[root.currentSlide].notes;

                    onNotesChanged: {
                        var result = "";

                        var lines = notes.split("\n");
                        var beginNewLine = false
                        for (var i=0; i<lines.length; ++i) {
                            var line = lines[i].trim();
                            if (line.length == 0) {
                                beginNewLine = true;
                            } else {
                                if (beginNewLine && result.length) {
                                    result += "\n\n"
                                    beginNewLine = false
                                }
                                if (result.length > 0)
                                    result += " ";
                                result += line;
                            }
                        }

                        if (result.length == 0) {
                            font.italic = true;
                            text = "no notes.."
                        } else {
                            font.italic = false;
                            text = result;
                        }
                    }
                }
            }
        }
    }
}
