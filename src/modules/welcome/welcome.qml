import io.calamares.modules.welcome 1.0;
import io.calamares.locale 1.0;
import io.calamares.ui 1.0;

import QtQuick 2.7
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import org.kde.mauikit 1.0 as Maui
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3


Page
{
    id: control
    width: 800
    height: Screen.height

    Kirigami.Theme.backgroundColor: "#fafafa"
    Kirigami.Theme.textColor: "#333"

    background: Item
    {
        id: _background

        Image
        {
            id: _wallpaper
            height: parent.height
            width: parent.width

            sourceSize.height: height / 20
            sourceSize.width: width / 20

            fillMode: Image.PreserveAspectCrop
            antialiasing: true
            smooth: true
            asynchronous: true
            cache: true

            source: "file:///home/camilo/coding/calamares/src/modules/welcome/Alt.jpg"

        }

        FastBlur
        {
            id: fastBlur
            anchors.fill: parent
            source: _wallpaper
            radius: 80
            transparentBorder: false
            cached: true
        }
    }

    footer: Item
    {

        width: parent.width
        height: 64

        Button
        {
            anchors.centerIn: parent
            text: "Next"
            width: implicitWidth * 2
        }
    }


    ColumnLayout
    {
        anchors.fill: parent
        spacing:  Kirigami.Units.largeSpacing * 3

        Item
        {

            Layout.fillWidth: true
            Layout.preferredHeight: 100

            Image
            {
                anchors.centerIn: parent
                source: "file:nxos_logo.png"
                height: Math.max(64, parent.height)
                width: height
                sourceSize.width: width
                sourceSize.height: height

            }
        }



        ColumnLayout
        {
            Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight

            Label
            {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                horizontalAlignment: Qt.AlignHCenter
                wrapMode: Text.NoWrap
                text: "Welcome to " /*+ Branding.productName*/
                color: "white"
                font.bold: true
                font.weight: Font.Bold
                font.pointSize: 24
            }

            Label
            {
                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                horizontalAlignment: Qt.AlignHCenter
                wrapMode: Text.NoWrap
                text: "This program will ask you some questions and set up your installation"
                color: "white"
                font.weight: Font.Light
                font.pointSize: 12
            }

        }


          Label
        {
                  Layout.fillWidth: true
            Layout.preferredHeight: implicitHeight
            horizontalAlignment: Qt.AlignHCenter
            wrapMode: Text.NoWrap
            text: "This computer does not satisfy the minimum requierments for installing Nitrux 1.0.\nInstallationcan not continue."
            color: "white"
            font.weight: Font.Light
            font.pointSize: 10
        }


        ListView
        {

        id: _langList

 Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Math.min(500, parent.width - 64)
            Layout.preferredHeight: Math.min(contentHeight, 500)
            spacing: Kirigami.Units.smallSpacing
            clip: true

          Rectangle
            {
                z: parent.z - 1
                anchors.fill: parent
                color: Kirigami.Theme.backgroundColor
                radius: 5
                opacity: 0.3
            }

        model: LocaleModel

        delegate: ItemDelegate
            {
                id: _delegate
                hoverEnabled: true

                property bool isCurrentItem: ListView.isCurrentItem
                background: Rectangle
                {
                    color: isCurrentItem || hovered ? Kirigami.Theme.highlightColor : Kirigami.Theme.backgroundColor
                    opacity: isCurrentItem || hovered ? 1 : 0.1
                }

                width: parent.width
                height: 48

                onClicked: _langList.currentIndex = index

                contentItem: RowLayout
                {
                    width: parent.width
                    height: parent.height
                    Label
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        horizontalAlignment: Qt.AlignLeft
                        text: model.label
                    }

                    Label
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        horizontalAlignment: Qt.AlignRight
                        text: model.englishLabel
                        opacity: isCurrentItem ? 1 : 0.7
                        font.weight: Font.Light
                    }
                }
                //             color: "red"

            }

        }



        Row
        {
            Layout.preferredWidth: implicitWidth
            Layout.preferredHeight: 64
            spacing: Kirigami.Units.largeSpacing* 2
            Layout.alignment:Qt.AlignCenter

            Button
            {
                text: "About"
                icon.name: "documentinfo"
            }

            Button
            {
                text: "Support"
                icon.name: "help-contents"
            }

            Button
            {
                text: "Known issues"
                icon.name: "tools-report-bug"
            }

            Button
            {
                text: "Release notes"
                icon.name: "answer"
            }

        }
    }

}
