/* Sample of QML progress tree.

   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
   SPDX-License-Identifier: GPL-3.0-or-later


   The progress tree (actually a list) is generally "vertical" in layout,
   with the steps going "down", but it could also be a more compact
   horizontal layout with suitable branding settings.

   This example emulates the layout and size of the widgets progress tree.
*/
import io.calamares.ui 1.0
import io.calamares.core 1.0

import QtQuick 2.3
import QtQuick.Layouts 1.3

Rectangle {
    id: sideBar;
    color: Branding.styleString( Branding.SidebarBackground );
    anchors.fill: parent;

    ColumnLayout {
        anchors.fill: parent;
        spacing: 0;

        Image {
            Layout.topMargin: 12;
            Layout.bottomMargin: 12;
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            id: logo;
            width: 80;
            height: width;  // square
            source: "file:/" + Branding.imagePath(Branding.ProductLogo);
            sourceSize.width: width;
            sourceSize.height: height;
        }

        Repeater {
            model: ViewManager
            Rectangle {
                Layout.leftMargin: 6;
                Layout.rightMargin: 6;
                Layout.fillWidth: true;
                height: 35;
                radius: 6;
                color: Branding.styleString( index == ViewManager.currentStepIndex ? Branding.SidebarBackgroundCurrent : Branding.SidebarBackground );

                Text {
                    anchors.verticalCenter: parent.verticalCenter;
                    anchors.horizontalCenter: parent.horizontalCenter;
                    color: Branding.styleString( index == ViewManager.currentStepIndex ? Branding.SidebarTextCurrent : Branding.SidebarText );
                    text: display;
                }
            }
        }

        Item {
            Layout.fillHeight: true;
        }

        Rectangle {
            id: metaArea
            Layout.fillWidth: true;
            height: 35
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            color: Branding.styleString( Branding.SidebarBackground );
            visible: true;

            Rectangle {
                id: aboutArea
                height: 35
                width: parent.width / 2;
                anchors.left: parent.left
                color: Branding.styleString( Branding.SidebarBackgroundCurrent );
                visible: true;

                MouseArea {
                    id: mouseAreaAbout
                    anchors.fill: parent;
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    Text {
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        x: parent.x + 4;
                        text: qsTr("About")
                        color: Branding.styleString( Branding.SidebarTextCurrent );
                        font.pointSize : 9
                    }

                    onClicked: debug.about()
                }
            }

            Rectangle {
                id: debugArea
                height: 35
                width: parent.width / 2;
                anchors.right: parent.right
                color: Branding.styleString( Branding.SidebarBackgroundCurrent );
                visible: debug.enabled

                MouseArea {
                    id: mouseAreaDebug
                    anchors.fill: parent;
                    cursorShape: Qt.PointingHandCursor
                    hoverEnabled: true
                    Text {
                        anchors.verticalCenter: parent.verticalCenter;
                        anchors.horizontalCenter: parent.horizontalCenter;
                        x: parent.x + 4;
                        text: qsTr("Debug")
                        color: Branding.styleString( Branding.SidebarTextCurrent );
                        font.pointSize : 9
                    }

                    onClicked: debug.toggle()
                }
            }
        }
    }
}
