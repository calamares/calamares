/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3

Page
{
    id: welcome

    header: Item {
        width: parent.width
        height: parent.height

        Text {
            id: welcomeTopText
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            padding: 40
            // In QML, QString::arg() only takes one argument
            text: qsTr("<h3>Welcome to the %1 <quote>%2</quote> installer</h3>
            <p>This program will ask you some questions and set up %1 on your computer.</p>").arg(Branding.string(Branding.ProductName)).arg(Branding.string(Branding.Version))
        }
        Image {
            id: welcomeImage
            anchors.centerIn: parent
            // imagePath() returns a full pathname, so make it refer to the filesystem
            // .. otherwise the path is interpreted relative to the "call site", which
            // .. might be the QRC file.
            source: "file:/" + Branding.imagePath(Branding.ProductWelcome)
            sourceSize.width: width
            sourceSize.height: height
            fillMode: Image.PreserveAspectFit
        }

        Requirements {
            visible: !config.requirementsModel.satisfiedRequirements
        }

        RowLayout {
            id: buttonBar
            width: parent.width / 1.5
            height: 64

            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            spacing: Kirigami.Units.largeSpacing* 2

            Button {
                Layout.fillWidth: true
                text: qsTr("Support")
                icon.name: "system-help"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: config.supportUrl !== ""
                onClicked: Qt.openUrlExternally(config.supportUrl)
            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Known issues")
                icon.name: "tools-report-bug"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: config.knownIssuesUrl !== ""
                onClicked: Qt.openUrlExternally(config.knownIssuesUrl)
            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Release notes")
                icon.name: "folder-text"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: config.releaseNotesUrl !== ""
                onClicked: load.source = "release_notes.qml"
                //onClicked: load.source = "file:/usr/share/calamares/release_notes.qml"
            }

            Button {
                Layout.fillWidth: true
                text: qsTr("Donate")
                icon.name: "taxes-finances"
                Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
                Kirigami.Theme.textColor: Kirigami.Theme.textColor

                visible: config.donateUrl !== ""
                onClicked: Qt.openUrlExternally(config.donateUrl)
            }
        }

        RowLayout {
            id: languageBar
            width: parent.width /1.2
            height: 48

            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height /7
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: Kirigami.Units.largeSpacing* 4

            Rectangle {
                width: parent.width
                Layout.fillWidth: true
                focus: true

                Loader {
                    id: imLoader

                    Component {
                        id: icon
                        Kirigami.Icon {
                            source: config.languageIcon
                            height: 48
                            width: 48
                        }
                    }

                    Component {
                        id: image
                        Image {
                            height: 48
                            fillMode: Image.PreserveAspectFit
                            source: "img/language-icon-48px.png"
                        }
                    }

                    sourceComponent: (config.languageIcon != "")  ? icon : image
                }

                ComboBox {
                    id: languages
                    anchors.left: imLoader.right
                    width: languageBar.width /1.1
                    textRole: "label"
                    currentIndex: config.localeIndex
                    model: config.languagesModel
                    onCurrentIndexChanged: config.localeIndex = currentIndex
                }
            }
        }

        Loader {
            id:load
            anchors.fill: parent
        }
    }
}
