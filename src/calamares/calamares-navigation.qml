import io.calamares.ui 1.0
import io.calamares.core 1.0

import QtQuick 2.3
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

Row {
            id: buttonBar
            height: 64

            Button
            {
                Layout.fillWidth: true
                text: qsTr("Back")
                icon.name: "next"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: true
                onClicked: { }
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Next")
                icon.name: "next"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: true
                onClicked: { }
            }
            Button
            {
                Layout.fillWidth: true
                text: qsTr("Quit")
                icon.name: "quit"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: true
                onClicked: { }
            }

}
