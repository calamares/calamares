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

    Kirigami.Theme.backgroundColor: "#FAFAFA"
    Kirigami.Theme.textColor: "#1F1F1F"

    property string subtitle
    property string message

    default property alias content : _content.data
    property alias stackView: _stackView

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
            color: Kirigami.Theme.textColor
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
            color: Kirigami.Theme.textColor
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
            color: Kirigami.Theme.textColor
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
