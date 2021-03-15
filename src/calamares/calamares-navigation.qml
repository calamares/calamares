/* Sample of QML navigation.

   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
   SPDX-License-Identifier: GPL-3.0-or-later


   The navigation panel is generally "horizontal" in layout, with
   buttons for next and previous; this particular one copies
   the layout and size of the widgets panel.
*/
import io.calamares.ui 1.0
import io.calamares.core 1.0

import QtQuick 2.3
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3

Rectangle {
    id: navigationBar;
    color: Branding.styleString( Branding.SidebarBackground );
    height: 48;

    RowLayout {
        id: buttonBar
        anchors.fill: parent;

        Item
        {
            Layout.fillWidth: true;
        }

        Button
        {
            text: ViewManager.backLabel;
            icon.name: ViewManager.backIcon;

            enabled: ViewManager.backEnabled;
            visible: ViewManager.backAndNextVisible;
            onClicked: { ViewManager.back(); }
        }
        Button
        {
            text: ViewManager.nextLabel;
            icon.name: ViewManager.nextIcon;

            enabled: ViewManager.nextEnabled;
            visible: ViewManager.backAndNextVisible;
            onClicked: { ViewManager.next(); }
            // This margin goes in the "next" button, because the "quit"
            // button can vanish and we want to keep the margin to
            // the next-thing-in-the-navigation-panel around.
            Layout.rightMargin: 3 * buttonBar.spacing;
        }
        Button
        {
            Layout.rightMargin: 2 * buttonBar.spacing
            text: ViewManager.quitLabel;
            icon.name: ViewManager.quitIcon;

            ToolTip.visible: hovered
            ToolTip.timeout: 5000
            ToolTip.delay: 1000
            ToolTip.text: ViewManager.quitTooltip;

            /*
             * The ViewManager has settings -- user-controlled via the
             * branding component, and party based on program state --
             * whether the quit button should be enabled and visible.
             *
             * QML navigation *should* follow this pattern, but can also
             * add other qualifications. For instance, you may have a
             * "finished" module that handles quit in its own way, and
             * want to hide the quit button then. The ViewManager has a
             * current step and a total count, so compare them:
             *
             * visible: ViewManager.quitVisible && ( ViewManager.currentStepIndex < ViewManager.rowCount()-1);
             */
            enabled: ViewManager.quitEnabled;
            visible: ViewManager.quitVisible;
            onClicked: { ViewManager.quit(); }
        }
    }
}
