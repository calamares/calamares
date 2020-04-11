import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

Page
{
    Map  {
        id: image
        anchors.horizontalCenter: parent.horizontalCenter
    }
    
    RowLayout {
 
        anchors.top: image.bottom
        anchors.topMargin: 5
        width: parent.width
        Kirigami.FormLayout {
            id: layout
            Layout.fillWidth: true

            ComboBox {
                Kirigami.FormData.label: qsTr("Region: ")
                currentIndex: model.currentIndex
                textRole: "label"
                model: config.regionModel
                onCurrentIndexChanged: console.debug(currentIndex)
            }
            Kirigami.Separator {
                Kirigami.FormData.isSection: true
                Kirigami.FormData.label: "System language set to American English"
            }
            
            Button {
                text: qsTr("Adjust Language")
                Layout.fillWidth: true
            }
        }
        
        Kirigami.FormLayout {
            id: zone
            Layout.fillWidth: true

            ComboBox {
                Kirigami.FormData.label: qsTr("Zone: ")
                currentIndex: model.currentIndex
                textRole: "label"
                model: config.zonesModel
                onCurrentIndexChanged: console.debug(currentIndex)
            }
            Kirigami.Separator {
                Kirigami.FormData.isSection: true
                Kirigami.FormData.label: "Numbers and dates locale set to American English"
            }
            Button {
                text: qsTr("Adjust Locale")
                Layout.fillWidth: true
            }
        }
    }
}
