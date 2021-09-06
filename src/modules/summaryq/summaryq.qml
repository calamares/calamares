/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
import QtQuick.Controls 2.13
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3

Kirigami.ScrollablePage {
    width: 860 //parent.width //860
    height: 640 //parent.height //640

    Kirigami.Theme.backgroundColor: "#EFF0F1"
    Kirigami.Theme.textColor: "#1F1F1F"

    header: Kirigami.Heading {
        Layout.fillWidth: true
        height: 100
        horizontalAlignment: Qt.AlignHCenter
        color: Kirigami.Theme.textColor
        font.weight: Font.Medium
        font.pointSize: 12
        text: config.message

    }

    RowLayout {
        width: parent.width

        Component {
            id: _delegate

            Rectangle {
                id: rect
                border.color: "#BDC3C7"
                width: parent.width - 80
                implicitHeight: message.implicitHeight + title.implicitHeight + 20
                anchors.horizontalCenter: parent.horizontalCenter

                Item {
                    width: parent.width - 80
                    implicitHeight: message.implicitHeight + title.implicitHeight + 20

                    Kirigami.FormLayout {

                        GridLayout {
                            anchors {
                                //left: parent.left
                                top: parent.top
                                right: parent.right
                            }
                            rowSpacing: Kirigami.Units.largeSpacing
                            columnSpacing: Kirigami.Units.largeSpacing
                            columns: width > Kirigami.Units.gridUnit * 20 ? 4 : 2

                            Image {
                                id: image
                                Layout.maximumHeight: Kirigami.Units.iconSizes.huge
                                Layout.preferredWidth: height
                                Layout.alignment: Qt.AlignTop
                                fillMode: Image.PreserveAspectFit
                                source: index === 0 ? "img/lokalize.svg"
                                    : ( index === 1 ? "img/keyboard.svg"
                                    : ( index === 2 ? "qrc:/data/images/partition-manual.svg"
                                    : "qrc:/data/images/partition-partition.svg" ) )
                            }
                            ColumnLayout {

                                Label {
                                    id: title
                                    Layout.fillWidth: true
                                    wrapMode: Text.WordWrap
                                    text: model.title
                                    font.weight: Font.Medium
                                    font.pointSize: 16
                                }
                                Rectangle {
                                    height: 2
                                    width: 200
                                    border.color: "#BDC3C7"
                                }
                                Label {
                                    id: message
                                    Layout.fillWidth: true
                                    text: model.message
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        spacing: 20
        model: config.summaryModel
        delegate: _delegate
    }
}
