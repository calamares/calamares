import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

ResponsiveBase {

    id: control

    title: stackView.currentItem.title
    subtitle: stackView.currentItem.subtitle


    stackView.initialItem:  Item {

        id: _keyboardModelsComponet

        property string title: qsTr("Keyboard Model")
        property string subtitle: qsTr("Pick your preferred keyboard model or use the default one based on the detected hardware")

        ListViewTemplate {

            id: _keyboardModelListView

            anchors.centerIn: parent
            implicitWidth: Math.min(parent.width, 500)
            implicitHeight: Math.min(contentHeight, 300)
            currentIndex: model.currentIndex

            model: config.keyboardModelsModel

            delegate: ListItemDelegate {

                id: _delegate
                label1.text: model.label
                onClicked: {

                    _keyboardModelListView.model.currentIndex = index
                    control.stackView.push(_keyboardLayoutsComponent)
                }
            }
        }

        ColumnLayout{

            spacing: 2
            anchors.verticalCenter: parent.verticalCenter

            Button {

                icon.name: "view-refresh"
                width: parent.width
                onClicked: control.stackView.pop()
                text: qsTr("Refresh")
            }

            Button {

                Layout.fillWidth: true
                text: qsTr("Layouts")
                icon.name: "go-next"
                onClicked: control.stackView.push(_keyboardLayoutsComponent)
            }
        }
    }

    Component {

        id: _keyboardLayoutsComponent

        Item {
            
            property string title: qsTr("Keyboard Layout")
            property string subtitle: config.prettyStatus

            ListViewTemplate {

                id: _layoutsListView

                anchors.centerIn: parent

                implicitWidth: Math.min(parent.width, 500)
                implicitHeight: Math.min(contentHeight, 300)

                currentIndex: model.currentIndex

                model: config.keyboardLayoutsModel

                delegate: ListItemDelegate {

                    id: _delegate
                    label1.text: model.label
                    onClicked: {

                        _layoutsListView.model.currentIndex = index
                        _layoutsListView.positionViewAtIndex(index, ListView.Center)
                        control.stackView.push(_keyboardVariantsComponent)
                    }
                }
            }

            ColumnLayout{

                spacing: 2
                anchors.verticalCenter: parent.verticalCenter

                Button {

                    Layout.fillWidth: true
                    icon.name: "go-previous"
                    text: qsTr("Models")
                    onClicked: control.stackView.pop()
                }

                Button {

                    Layout.fillWidth: true
                    icon.name: "go-next"
                    text: qsTr("Variants")
                    onClicked: control.stackView.push(_keyboardVariantsComponent)
                }
            }
        }
    }

    Component {

        id: _keyboardVariantsComponent

        Item {

            property string title: qsTr("Keyboard Layout")
            property string subtitle: config.prettyStatus

            ListViewTemplate {

                id: _variantsListView

                anchors.centerIn: parent

                implicitWidth: Math.min(parent.width, 500)
                implicitHeight: Math.min(contentHeight, 300)

                currentIndex: model.currentIndex

                model: config.keyboardVariantsModel

                delegate: ListItemDelegate {

                    id: _delegate
                    label1.text: model.label
                    onClicked: {

                        _variantsListView.model.currentIndex = index
                        _variantsListView.positionViewAtIndex(index, ListView.Center)
                    }
                }
            }

            ColumnLayout{

                anchors.verticalCenter: parent.verticalCenter
            
                Button {

                    Layout.fillWidth: true
                    text: qsTr("Layouts")
                    icon.name: "go-previous"
                    onClicked: control.stackView.pop()
                }
            }
        }

    }

    TextField {

        placeholderText: qsTr("Test your keyboard")
        Layout.preferredHeight: 48
        Layout.maximumWidth:  500
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignCenter

        background:Rectangle {

            z: parent.z - 1
            anchors.fill: parent
            color: control.Kirigami.Theme.backgroundColor
            radius: 5
            opacity: 0.8
        }
    }
}
