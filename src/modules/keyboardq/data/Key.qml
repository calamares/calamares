/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import QtQuick 2.15

Item {
    id: key

    property string mainLabel: "A"
    property var secondaryLabels: [];

    property var iconSource;

    property var keyImageLeft: ""
    property var keyImageRight: ""
    property var keyImageCenter: ""

    property color keyColor: "#404040"
    property color keyPressedColor: "grey"
    property int keyBounds: 2
    property var keyPressedColorOpacity: 1

    property var mainFontFamily: "Roboto"
    property color mainFontColor: "white"
    property int mainFontSize: 18

    property var secondaryFontFamily: "Roboto"
    property color secondaryFontColor: "white"
    property int secondaryFontSize: 10

    property bool secondaryLabelVisible: true

    property bool isChekable;
    property bool isChecked;

    property bool upperCase;

    signal clicked()
    signal alternatesClicked(string symbol)

    Item {
        anchors.fill: parent
        anchors.margins: key.keyBounds
        visible: key.keyImageLeft != "" || key.keyImageCenter != "" || key.keyImageRight != "" ? 1 : 0
        Image {
            id: backgroundImage_left
            anchors.left: parent.left
            height: parent.height
            fillMode: Image.PreserveAspectFit
            source: key.keyImageLeft
        }
        Image {
            id: backgroundImage_right
            anchors.right: parent.right
            height: parent.height
            fillMode: Image.PreserveAspectFit
            source: key.keyImageRight
        }
        Image {
            id: backgroundImage_center
            anchors.fill: parent
            anchors.leftMargin: backgroundImage_left.width - 1
            anchors.rightMargin: backgroundImage_right.width - 1
            height: parent.height
            fillMode: Image.Stretch
            source: key.keyImageCenter
        }
    }

    Rectangle {
        id: backgroundItem
        anchors.fill: parent
        anchors.margins: key.keyBounds
        color: key.isChecked || mouseArea.pressed ? key.keyPressedColor : key.keyColor;
        opacity: key.keyPressedColorOpacity
    }

    Column
    {
        anchors.centerIn: backgroundItem

        Text {
            id: secondaryLabelsItem
            smooth: true
            anchors.right: parent.right
            visible: true //secondaryLabelVisible
            text: secondaryLabels.length > 0 ? secondaryLabels : ""
            color: secondaryFontColor

            font.pixelSize: secondaryFontSize
            font.weight: Font.Light
            font.family: secondaryFontFamily
            font.capitalization: upperCase ? Font.AllUppercase :
                                                     Font.MixedCase
        }

        Row {
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: icon
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
                source: iconSource
                //sourceSize.width: key.width * 0.6
                sourceSize.height: key.height * 0.4
            }

            Text {
                id: mainLabelItem
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
                text: mainLabel
                color: mainFontColor
                visible: iconSource ? false : true

                font.pixelSize: mainFontSize
                font.weight: Font.Light
                font.family: mainFontFamily
                font.capitalization: upperCase ? Font.AllUppercase :
                                                         Font.MixedCase
            }
        }
    }

    Row {
        id: alternatesRow
        property int selectedIndex: -1
        visible: false
        anchors.bottom: backgroundItem.top
        anchors.left: backgroundItem.left

        Repeater {
            model: secondaryLabels.length

            Rectangle {
                property bool isSelected: alternatesRow.selectedIndex == index
                color: isSelected ? mainLabelItem.color : key.keyPressedColor
                height: backgroundItem.height
                width: backgroundItem.width

                Text {
                    anchors.centerIn: parent
                    text: secondaryLabels[ index ]
                    font: mainLabelItem.font
                    color: isSelected ? key.keyPressedColor : mainLabelItem.color
                }
            }
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onPressAndHold: alternatesRow.visible = true
        onClicked: {
            if (key.isChekable) key.isChecked = !key.isChecked
            key.clicked()
        }

        onReleased: {
            alternatesRow.visible = false
            if (alternatesRow.selectedIndex > -1)
                key.alternatesClicked(secondaryLabels[alternatesRow.selectedIndex])
        }

        onMouseXChanged: {
            alternatesRow.selectedIndex =
            (mouseY < 0 && mouseX > 0 && mouseY < alternatesRow.width) ?
                        Math.floor(mouseX / backgroundItem.width) :
                        -1;
        }
    }
}
