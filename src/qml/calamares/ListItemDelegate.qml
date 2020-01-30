import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import org.kde.mauikit 1.0 as Maui

ItemDelegate
{
    id: control


    property alias label1 : _label1
    property alias label2 : _label2

    hoverEnabled: true

    property bool isCurrentItem: ListView.isCurrentItem
    background: Rectangle
    {
        color: isCurrentItem || hovered ? Kirigami.Theme.highlightColor : Kirigami.Theme.backgroundColor
        opacity: isCurrentItem || hovered ? 0.7 : 0.1
    }

    width: parent.width
    height: 48

    contentItem: RowLayout
    {
        anchors.fill: parent
        anchors.margins: Kirigami.Units.largeSpacing

        Label
        {
            id: _label1
            Layout.fillHeight: true
            Layout.fillWidth: true
            horizontalAlignment: Qt.AlignLeft
            color: isCurrentItem ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor
        }

          Label
        {
            id: _label2
            visible: text.length
            Layout.fillHeight: true
            Layout.maximumWidth: parent.width * 0.4
            horizontalAlignment: Qt.AlignRight
            color: isCurrentItem ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor
            opacity: isCurrentItem ? 1 : 0.7
            font.weight: Font.Light
        }

        Kirigami.Icon
        {
            source: "checkmark"
            Layout.preferredWidth: 22
            Layout.preferredHeight: 22
            color: Kirigami.Theme.highlightedTextColor
            visible: isCurrentItem
        }
    }
}
