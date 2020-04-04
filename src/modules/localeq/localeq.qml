import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0

RowLayout
{
    Rectangle {
        width: parent.width / 3
        Layout.fillWidth: true
        ColumnLayout {
            id: regions
            Repeater {
                model: config.regionModel
                Text {
                    text: label
                }
            }
        }
    }
    Rectangle {
        width: parent.width / 3
        Layout.fillWidth: true
        ColumnLayout {
            id: zones
            ListView {
                model: config.zonesModel
                delegate: Text { 
                    text: label
                }
            }
        }
    }
}

