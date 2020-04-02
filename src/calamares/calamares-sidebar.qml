import io.calamares.ui 1.0
import io.calamares.core 1.0

import QtQuick 2.3
import QtQuick.Layouts 1.3

Rectangle {
    id: sideBar;
    color: Branding.styleString( Branding.SidebarBackground );

    ColumnLayout {
        anchors.fill: parent;
        spacing: 0;

        Image {
            id: logo
            width: 80;
            height: width;  // square
            anchors.horizontalCenter: parent.horizontalCenter;
            source: "file:/" + Branding.imagePath(Branding.ProductLogo);
            sourceSize.width: width;
            sourceSize.height: height;
        }

        Repeater {
            model: ViewManager
            Rectangle {
                width: 200;
                height: 75;
                color: Branding.styleString( index == ViewManager.currentStepIndex ? Branding.SidebarTextHighlight : Branding.SidebarBackground );

                Text {
                    anchors.centerIn: parent;
                    color: Branding.styleString( index == ViewManager.currentStepIndex ? Branding.SidebarTextSelect : Branding.SidebarText );
                    text: display;
                }
            }
        }

        Item {
            Layout.fillHeight: true;
        }
    }
}
