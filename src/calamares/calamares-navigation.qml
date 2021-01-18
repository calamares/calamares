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
        }
        Button
        {
            Layout.leftMargin: 3 * buttonBar.spacing;  // little gap from back/next
            Layout.rightMargin: 2 * buttonBar.spacing
            text: ViewManager.quitLabel;
            icon.name: ViewManager.quitIcon;

            ToolTip.visible: hovered
            ToolTip.timeout: 5000
            ToolTip.delay: 1000
            ToolTip.text: ViewManager.quitTooltip;

            enabled: ViewManager.quitEnabled;
            visible: ViewManager.quitVisible;
            onClicked: { ViewManager.quit(); }
        }
    }
}
