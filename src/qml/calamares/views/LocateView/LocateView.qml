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

            source: "file:Alt.jpg"

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
         width: _langList.width
        }
    }


    ColumnLayout
    {
        anchors.fill: parent
       spacing:  Kirigami.Units.largeSpacing * 3

//         Item
//         {
//
//             Layout.fillWidth: true
//             Layout.preferredHeight: 150
//
//             Image
//             {
//                 anchors.centerIn: parent
//                 source: "file:nxos_logo_large.png"
//                 height: parent.height
//                 width: height
//                 sourceSize.width: width
//                 sourceSize.height: height
//
//             }
//         }



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
            text: "Select system language"
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
            text: "Pick your correct system language to continue"
            color: "white"
            font.weight: Font.Light
            font.pointSize: 12
        }

            }



        ListView
        {
            id: _langList
            Layout.alignment: Qt.AlignCenter
            Layout.preferredWidth: Math.min(500, parent.width - 64)
            Layout.fillHeight: true
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

            model: ListModel
            {
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
                ListElement {label: "Espanol"; englishLabel: "Spanish"}
            }

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

    }

}
