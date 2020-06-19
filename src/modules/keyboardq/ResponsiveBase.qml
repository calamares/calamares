import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0

import io.calamares.ui 1.0
import io.calamares.core 1.0

Page {

    id: control
    width: 800 //parent.width
    height: 550 //parent.height

    Kirigami.Theme.backgroundColor: "#fafafa"
    Kirigami.Theme.textColor: "#333"

    property string subtitle
    property string message

    default property alias content : _content.data
    property alias stackView: _stackView

    background: Item {

        id: _background

        Image {

            id: _wallpaper
            height: parent.height
            width: parent.width

            sourceSize.width: 800
            sourceSize.height: 550

            fillMode: Image.PreserveAspectCrop
            antialiasing: false
            smooth: false
            asynchronous: true
            cache: true

            source: "keyboard.jpg"
        }

        FastBlur {

            id: fastBlur
            anchors.fill: parent
            source: _wallpaper
            radius: 32
            transparentBorder: false
            cached: true
        }
    }
    
    ColumnLayout {

        id: _content

        anchors.fill: parent
        spacing:  Kirigami.Units.smallSpacing * 5
        anchors.margins: Kirigami.Units.smallSpacing * 5
        anchors.bottomMargin: 20
        
        Label {
            
            Layout.fillWidth: true
            Layout.preferredHeight: Math.min(implicitHeight, 200)
            horizontalAlignment: Qt.AlignHCenter
            wrapMode: Text.NoWrap
            elide: Text.ElideMiddle
            text: control.title
            color: "white"
            font.bold: true
            font.weight: Font.Bold
            font.pointSize: 24
        }

        Label {

            Layout.fillWidth: true
            Layout.preferredHeight: Math.min(implicitHeight, 200)
            horizontalAlignment: Qt.AlignHCenter
            wrapMode: Text.Wrap
            elide: Text.ElideMiddle
            text: control.subtitle
            color: "white"
            font.weight: Font.Light
            font.pointSize: 12
        }

        Label {

            Layout.fillWidth: true
            Layout.preferredHeight: Math.min(implicitHeight, 200)
            horizontalAlignment: Qt.AlignHCenter
            wrapMode: Text.Wrap
            elide: Text.ElideMiddle
            text: control.message
            color: "white"
            font.weight: Font.Light
            font.pointSize: 10
        }

        StackView {

            id: _stackView
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width
            clip: true
        }	
        
    }
}
