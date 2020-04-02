import io.calamares.ui 1.0
import io.calamares.core 1.0

import QtQuick 2.3
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3

Rectangle {
    id: navigationBar;
    color: Branding.styleString( Branding.SidebarBackground );

    RowLayout {
        id: buttonBar
        height: 64;
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
            visible: true;
            onClicked: { ViewManager.back(); }
        }
        Button
        {
            text: ViewManager.nextLabel;
            icon.name: ViewManager.nextIcon;

            enabled: ViewManager.nextEnabled;
            visible: true;
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
