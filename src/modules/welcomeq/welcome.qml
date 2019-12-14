import io.calamares.modules.welcome 1.0 as Welcome
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
    width: Screen.width
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

            source: "file:///home/camilo/.local/share/wallpapers/wanderer_v02_5120x2880.png"

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
        height: 200

        Button
        {
            anchors.centerIn: parent
            text: Welcome.Config.countryCode
            width: _requirementsList.width
            height: implicitHeight
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
                text: "Welcome to " + Branding.string(Branding.ProductName) + " " + Branding.string(Branding.Version)
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
                text: Welcome.Config.genericWelcomeMessage
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

            id: _requirementsList

            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Math.min(500, parent.width - 64)
            Layout.preferredHeight: Math.min(contentHeight, 500)
            spacing: Kirigami.Units.smallSpacing
            clip: true

//             currentIndex: Welcome.Config.localeIndex

            Rectangle
            {
                z: parent.z - 1
                anchors.fill: parent
                color: Kirigami.Theme.backgroundColor
                radius: 5
                opacity: 0.3
            }

            model: Welcome.Config.requirementsModel

            delegate: ItemDelegate
            {
                id: _delegate

                background: Rectangle
                {
                    color: model.satisfied ? Kirigami.Theme.positiveTextColor : Kirigami.Theme.negativeTextColor
                    opacity: 0.2
                }

                width: parent.width
                height: 48

                contentItem: RowLayout
                {
                    width: parent.width
                    height: parent.height

                    Item
                    {
                        Layout.fillHeight: true
                        Layout.preferredWidth: height

                        Kirigami.Icon
                        {
                            source: model.satisfied ? "checkmark" : (model.mandatory ? "error" : "dialog-warning-symbolic")
                            height:  32
                            width: height
                            anchors.centerIn: parent
                            color: background.color
                        }
                    }

                     ColumnLayout
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: tru
                    Label
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        horizontalAlignment: Qt.AlignLeft
                        text: model.name
                    }

                    Label
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        horizontalAlignment: Qt.AlignLeft
                        text: !model.satisfied ?  model.negatedText : model.details
                        opacity: isCurrentItem ? 1 : 0.7
                        font.weight: Font.Light
                    }
                }
                }
            }
        }


         ListView
        {

            id: _langList
            visible: false
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Math.min(500, parent.width - 64)
            Layout.preferredHeight: Math.min(contentHeight, 500)
            spacing: Kirigami.Units.smallSpacing
            clip: true

//             currentIndex: Welcome.Config.localeIndex

            Rectangle
            {
                z: parent.z - 1
                anchors.fill: parent
                color: Kirigami.Theme.backgroundColor
                radius: 5
                opacity: 0.3
            }

            model: Welcome.Config.requirementsModel

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

                onClicked:
                {
                    Welcome.Config.localeIndex = index
                    positionViewAtIndex(index, ListView.Beginning)
                }

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

                visible: String(Welcome.Config.donateUrl).length
                onClicked: Qt.openUrlExternally(Welcome.Config.donateUrl)
            }

            Button
            {
                text: qsTr("Support")
                icon.name: "help-contents"

                visible: String(Welcome.Config.supportUrl).length
                onClicked: Qt.openUrlExternally(Welcome.Config.supportUrl)
            }

            Button
            {
                text: "Known issues"
                icon.name: "tools-report-bug"

                visible: String(Welcome.Config.knownIssuesUrl).length
                onClicked: Qt.openUrlExternally(Welcome.Config.knownIssuesUrl)
            }

            Button
            {
                text: "Release notes"
                icon.name: "answer"

                visible: String(Welcome.Config.releaseNotesUrl).length
                onClicked: Qt.openUrlExternally(Welcome.Config.releaseNotesUrl)
            }

        }
    }

}
