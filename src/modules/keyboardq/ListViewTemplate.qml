import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

ListView {

    id: control

    spacing: Kirigami.Units.smallSpacing
    clip: true
    boundsBehavior: Flickable.StopAtBounds

    Rectangle {

        z: parent.z - 1
        anchors.fill: parent
        color: Kirigami.Theme.backgroundColor
        radius: 5
        opacity: 0.7
    }
}
