/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2022 Aditya Mehra <aix.m@outlook.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls 1.4 as QQC1
import QtQuick.Window 2.14
import QtQuick.Layouts 1.3

import org.kde.kirigami 2.7 as Kirigami

Item {
    width: partitionPage.width
    height: partitionPage.height

    function listProperty(item)
    {
        for (var p in item)
        console.log(p + ": " + item[p]);
    }

    Connections {
        target: choicePage
        onPartitionListModelInitialized: {
            // Need to wait for partition model to initialize
            // followed by partitionListModel
            // Requires further refactor to have partitionListModel ready
            // when choicePage is loaded instead of waiting for choicePage
            // to load partitionModel first.
            partitionView.model = choicePage.partitionListModel
        }
    }

    RowLayout {
        id: headerRowLayout
        anchors.top: parent.top
        width: parent.width
        height: Kirigami.Units.gridUnits * 2

        Item {
            id: partitionTypeBox
            Layout.preferredWidth: Kirigami.Units.gridUnit * 5
            Layout.fillHeight: true

            Item {
                id: partitionTypeIcon
                anchors.left: parent.left
                width: parent.width * 0.35
                height: parent.height

                Image {
                    anchors.centerIn: parent
                    width: Kirigami.Units.iconSizes.large
                    height: width
                    source: "images/partition-table.svg"
                }
            }
            Label {
                id: partitionTypeLabel
                anchors.left: partitionTypeIcon.right
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
            }
        }

        Kirigami.Separator {
            Layout.fillHeight: true
            Layout.preferredWidth: 1
        }

        Label {
            text: "Select Storage Device:"
            font.bold: true
            Layout.fillHeight: true
            verticalAlignment: Qt.AlignVCenter
            horizontalAlignment: Qt.AlignLeft
        }

        ComboBox {
            id: deviceComboBox

            Layout.fillWidth: true
            Layout.fillHeight: true

            model: core.deviceModel
            textRole: "display"
            currentIndex: core.currentDeviceIndex
            onCurrentIndexChanged: {
                core.currentDeviceIndex = currentIndex
                choicePage.setDeviceIndex(currentIndex)
            }

            Component.onCompleted: {
                choicePage.setupActions()
            }
        }

        Item {
            Layout.preferredWidth: Kirigami.Units.gridUnit * 5
            Layout.fillHeight: true
        }
    }

    Kirigami.Separator {
        id: headerBoxLine
        anchors.top: headerRowLayout.bottom
        width: parent.width
        height: 1
    }

    Item {
        anchors.top: headerBoxLine.bottom
        anchors.bottom: bottomSelectionBoxLine.top
        anchors.left: parent.left
        anchors.right: parent.right

        ColumnLayout {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: Kirigami.Units.smallSpacing

            ButtonGroup {
                id: buttonGroup
            }

            RadioButton {
                id: eraseBtn
                objectName: "eraseBtn"
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: choicePage.eraseButtonEnabled
                enabled: choicePage.eraseButtonEnabled
                ButtonGroup.group: buttonGroup
                text: choicePage.eraseButtonLabel;
                onClicked: {
                    choicePage.setInstallChoice(0)
                }
            }
            RadioButton {
                id: alongSideBtn
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: choicePage.alongSideButtonEnabled
                enabled: choicePage.alongSideButtonEnabled
                ButtonGroup.group: buttonGroup
                text: choicePage.alongSideButtonLabel;
                onClicked: {
                    choicePage.setInstallChoice(1)
                }
            }
            RadioButton {
                id: replaceBtn
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: choicePage.replaceButtonEnabled
                enabled: choicePage.replaceButtonEnabled
                ButtonGroup.group: buttonGroup
                text: choicePage.replaceButtonLabel;
                onClicked: {
                    choicePage.setInstallChoice(2)
                }
            }
            RadioButton {
                id: manualBtn
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: choicePage.manualButtonEnabled
                enabled: choicePage.manualButtonEnabled
                ButtonGroup.group: buttonGroup
                text: choicePage.somethingElseButtonLabel;
                onClicked: {
                    choicePage.setInstallChoice(3)
                }
            }

            RowLayout {
                id: partitionViewLayout

                Layout.fillWidth: true
                Layout.preferredHeight: Kirigami.Units.gridUnits * 3
                spacing: Kirigami.Units.smallSpacing

                Repeater {
                    id: partitionView

                    delegate: Item {
                        id: partitionItem
                        Layout.preferredWidth: Kirigami.Units.gridUnit * 4
                        Layout.preferredHeight: Kirigami.Units.gridUnit * 3
                        
                        ColumnLayout{
                            anchors.fill: parent
                            spacing: Kirigami.Units.smallSpacing

                            Rectangle {
                                Layout.fillWidth: true
                                Layout.preferredHeight: Kirigami.Units.gridUnit * 1.5

                                color: model.decoration

                                Label {
                                    anchors.centerIn: parent
                                    text: model.display
                                    fontSizeMode: Text.Fit
                                    font.pixelSize: parent.height * 0.25
                                    minimumPixelSize: 8
                                    color: Kirigami.Theme.textColor
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        listProperty(model)
                                    }
                                }
                            }

                            Label {                                
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                                fontSizeMode: Text.Fit
                                font.pixelSize: parent.height * 0.25
                                minimumPixelSize: 8
                                color: Kirigami.Theme.textColor
                                text: model.toolTip.replace(" ", "\n")
                            }
                        }
                    }

                    onCountChanged: {
                        partitionView.forceLayout()
                    }
                }
            }

            // ToDo: Partitioning Tree View Before and After View
        }
    }

    Kirigami.Separator {
        id: bottomSelectionBoxLine
        anchors.bottom: selectionBoxes.top
        width: parent.width
        height: 1
        visible: selectionBoxes.visible
    }

    Item {
        id: selectionBoxes
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height * 0.2
        visible: eraseBtn.checked || replaceBtn.checked || alongSideBtn.checked

        ColumnLayout {
            id: selectionBoxesLayout
            width: parent.width
            height: parent.height

            ComboBox {
                id: eraseSwapComboBox
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: choicePage.getEraseSwapChoices()
                textRole: "label"
                currentIndex: choicePage.getInitialSwapChoice()
                onCurrentIndexChanged: {
                    choicePage.setSwapChoice(currentIndex)
                }
                visible: eraseBtn.checked
            }

            RadioButton {
                id: encryptPartitionButton
                Layout.fillWidth: true
                Layout.fillHeight: true
                text: "Encrypt Partition"
                onClicked: {
                    if (encryptPartitionButton.checked) {
                        choicePage.setEncryptionSelected(true)
                    }
                }
            }

            TextField {
                id: encryptionPasswordField
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: encryptPartitionButton.checked
                onTextChanged: {
                    choicePage.setEncryptionPhrase(text)
                }
            }
        }
    }
}
