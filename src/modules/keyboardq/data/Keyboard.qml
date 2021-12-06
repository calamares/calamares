/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import QtQuick 2.15
import QtQuick.XmlListModel 2.10

Item {
    id: keyboard

    width: 1024
    height: 640

    property int rows: 4;
    property int columns: 10;

    property string source: "generic.xml"
    property var target;

    property color backgroundColor: "black"

    property var keyImageLeft: ""
    property var keyImageRight: ""
    property var keyImageCenter: ""

    property color keyColor: "#404040"
    property color keyPressedColor: "grey"
    property int keyBounds: 2
    property var keyPressedColorOpacity: 1

    property var mainFontFamily: "Roboto"
    property color mainFontColor: "white"
    property int mainFontSize: 59

    property var secondaryFontFamily: "Roboto"
    property color secondaryFontColor: "white"
    property int secondaryFontSize: 30

    property bool secondaryLabelsVisible: false
    property bool doSwitchSource: true

    property bool allUpperCase: false

    signal keyClicked(string key)
    signal switchSource(string source)
    signal enterClicked()

    Rectangle {
        id: root
        anchors.fill: parent
        color: backgroundColor

        property int keyWidth: keyboard.width / columns;
        property int keyHeight: keyboard.height / rows;

        property int xmlIndex: 1

        Text {
            id: proxyMainTextItem
            color: keyboard.mainFontColor
            font.pixelSize: keyboard.mainFontSize
            font.weight: Font.Light
            font.family: keyboard.mainFontFamily
            font.capitalization: keyboard.allUpperCase ? Font.AllUppercase :
                                                     Font.MixedCase
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: proxySecondaryTextItem
            color: keyboard.secondaryFontColor
            font.pixelSize: keyboard.secondaryFontSize
            font.weight: Font.Light
            font.family: keyboard.secondaryFontFamily
            font.capitalization: keyboard.allUpperCase ? Font.AllUppercase :
                                                     Font.MixedCase
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        Column {
            id: column
            anchors.centerIn: parent

            Repeater {
                id: rowRepeater

                model: XmlListModel {
                    id: keyboardModel
                    source: keyboard.source
                    query: "/Keyboard/Row"

                    Behavior on source {
                        NumberAnimation {
                            easing.type: Easing.InOutSine
                            duration: 100
                        }
                    }
                }

                Row {
                    id: keyRow
                    property int rowIndex: index
                    anchors.horizontalCenter: if(parent) parent.horizontalCenter

                    Repeater {
                        id: keyRepeater

                        model: XmlListModel {
                            source: keyboard.source
                            query: "/Keyboard/Row[" + (rowIndex + 1) + "]/Key"

                            XmlRole { name: "labels"; query: "@labels/string()" }
                            XmlRole { name: "ratio"; query: "@ratio/number()" }
                            XmlRole { name: "icon"; query: "@icon/string()" }
                            XmlRole { name: "checkable"; query: "@checkable/string()" }
                        }

                        Key {
                            id: key
                            width: root.keyWidth * ratio
                            height: root.keyHeight
                            iconSource: icon
                            mainFontFamily: proxyMainTextItem.font
                            mainFontColor: proxyMainTextItem.color
                            secondaryFontFamily: proxySecondaryTextItem.font
                            secondaryFontColor: proxySecondaryTextItem.color
                            secondaryLabelVisible: keyboard.secondaryLabelsVisible
                            keyColor: keyboard.keyColor
                            keyImageLeft: keyboard.keyImageLeft
                            keyImageRight: keyboard.keyImageRight
                            keyImageCenter: keyboard.keyImageCenter
                            keyPressedColor: keyboard.keyPressedColor
                            keyPressedColorOpacity: keyboard.keyPressedColorOpacity
                            keyBounds: keyboard.keyBounds
                            isChekable: checkable
                            isChecked: isChekable &&
                                       command &&
                                       command === "shift" &&
                                       keyboard.allUpperCase
                            upperCase: keyboard.allUpperCase

                            property var command
                            property var params: labels

                            onParamsChanged: {
                                var labelSplit;

                                if(params[0] === '|')
                                {
                                    mainLabel = '|'
                                    labelSplit = params
                                }
                                else
                                {
                                    labelSplit = params.split(/[|]+/)

                                    if (labelSplit[0] === '!')
                                        mainLabel = '!';
                                    else
                                        mainLabel = params.split(/[!|]+/)[0].toString();
                                }

                                if (labelSplit[1]) secondaryLabels = labelSplit[1];

                                if (labelSplit[0] === '!')
                                    command = params.split(/[!|]+/)[1];
                                else
                                    command = params.split(/[!]+/)[1];
                            }

                            onClicked: {
                                if (command)
                                {
                                    var commandList = command.split(":");

                                    switch(commandList[0])
                                    {
                                        case "source":
                                            keyboard.switchSource(commandList[1])
                                            if(doSwitchSource) keyboard.source = commandList[1]
                                            return;
                                        case "shift":
                                            keyboard.allUpperCase = !keyboard.allUpperCase
                                            return;
                                        case "backspace":
                                            keyboard.keyClicked('\b');
                                            target.text = target.text.substring(0,target.text.length-1)
                                            return;
                                        case "enter":
                                            keyboard.enterClicked()
                                            return;
                                        case "tab":
                                            keyboard.keyClicked('\t');
                                            target.text = target.text + "   "
                                            return;
                                        default: return;
                                    }
                                }
                                if (mainLabel.length === 1)
                                    root.emitKeyClicked(mainLabel);
                            }
                            onAlternatesClicked: root.emitKeyClicked(symbol);
                        }
                    }
                }
            }
        }

        function emitKeyClicked(text) {
            var emitText = keyboard.allUpperCase ? text.toUpperCase() : text;
            keyClicked( emitText );
            target.text = target.text + emitText
        }
    }
}

