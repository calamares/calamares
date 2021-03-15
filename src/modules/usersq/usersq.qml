/* === This file is part of Calamares - <https://calamares.io> ===
 *
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

Kirigami.ScrollablePage {

    width: parent.width
    height: parent.height

    Kirigami.Theme.backgroundColor: "#EFF0F1"
    Kirigami.Theme.textColor: "#1F1F1F"

	header: Kirigami.Heading {

        Layout.fillWidth: true
        height: 50
        horizontalAlignment: Qt.AlignHCenter
        color: Kirigami.Theme.textColor
        font.weight: Font.Medium
        font.pointSize: 12
        text: qsTr("Pick your user name and credentials to login and perform admin tasks")
    }

    ColumnLayout {

        id: _formLayout
        spacing: Kirigami.Units.smallSpacing

        Column {

            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Label {

                width: parent.width
                text: qsTr("What is your name?")
            }

            TextField {

                id: _userNameField
                width: parent.width
                enabled: config.isEditable("fullName")
                placeholderText: qsTr("Your Full Name")
                text: config.fullName
                onTextChanged: config.setFullName(text);

                background: Rectangle {
                    color: "#FBFBFB" // Kirigami.Theme.backgroundColor
                    radius: 2
                    opacity: 0.9
                    //border.color: _userNameField.text === "" ? Kirigami.Theme.backgroundColor : ( config.fullNameReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor)
                    border.color: _userNameField.text === "" ? "#FBFBFB" : ( config.fullNameChanged ? "#FBFBFB" : Kirigami.Theme.negativeTextColor)
                }
            }
        }

        Column {

            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Label {

                width: parent.width
                text: qsTr("What name do you want to use to log in?")
            }

            TextField {

                id: _userLoginField
                width: parent.width
                enabled: config.isEditable("loginName")
                placeholderText: qsTr("Login Name")
                text: config.loginName
                onTextChanged: config.setLoginName(text)

                background: Rectangle {

                    color: "#FBFBFB" // Kirigami.Theme.backgroundColor
                    opacity: 0.9
                    //border.color: _userLoginField.text === "" ? Kirigami.Theme.backgroundColor : ( config.userNameReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor)
                    border.color: _userLoginField.text === "" ? "#FBFBFB" : ( config.loginNameStatusChanged ? "#FBFBFB" : Kirigami.Theme.negativeTextColor)
                }
            }

            Label {

                width: parent.width
                text: qsTr("If more than one person will use this computer, you can create multiple accounts after installation.")
                font.weight: Font.Thin
                font.pointSize: 8
                color: "#6D6D6D"
            }
        }

        Column {

            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Label {

                width: parent.width
                text: qsTr("What is the name of this computer?")
            }

            TextField {

                id: _hostName
                width: parent.width
                placeholderText: qsTr("Computer Name")
                text: config.hostName
                onTextChanged: config.setHostName(text)

                background: Rectangle {

                    color: "#FBFBFB" // Kirigami.Theme.backgroundColor
                    opacity: 0.9
                    //border.color: _hostName.text === "" ? Kirigami.Theme.backgroundColor : ( config.hostNameStatusChanged ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor)
                    border.color: _hostName.text === "" ? "#FBFBFB" : ( config.hostNameStatusChanged ? "#FBFBFB" : Kirigami.Theme.negativeTextColor)
                }
            }

            Label {

                width: parent.width
                text: qsTr("This name will be used if you make the computer visible to others on a network.")
                font.weight: Font.Thin
                font.pointSize: 8
                color: "#6D6D6D"
            }
        }

        Column {

            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Label {

                width: parent.width
                text: qsTr("Choose a password to keep your account safe.")
            }

            Row {
                width: parent.width
                spacing: 20

                TextField {

                    id: _passwordField
                    width: parent.width / 2 - 10
                    placeholderText: qsTr("Password")
                    text: config.userPassword
                    onTextChanged: config.setUserPassword(text)

                    echoMode: TextInput.Password
                    passwordMaskDelay: 300
                    inputMethodHints: Qt.ImhNoAutoUppercase

                    background: Rectangle {

                        color: "#FBFBFB" // Kirigami.Theme.backgroundColor
                        opacity: 0.9
                        //border.color: _passwordField.text === "" ? Kirigami.Theme.backgroundColor : ( config.passwordReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor)
                        border.color: _passwordField.text === "" ? "#FBFBFB" : ( config.userPasswordStatusChanged ? "#FBFBFB" : Kirigami.Theme.negativeTextColor)
                    }
                }

                TextField {

                    id: _verificationPasswordField
                    width: parent.width / 2 - 10
                    placeholderText: qsTr("Repeat Password")
                    text: config.userPasswordSecondary
                    onTextChanged: config.setUserPasswordSecondary(text)

                    echoMode: TextInput.Password
                    passwordMaskDelay: 300
                    inputMethodHints: Qt.ImhNoAutoUppercase

                    background: Rectangle {

                        color: "#FBFBFB" //Kirigami.Theme.backgroundColor
                        opacity: 0.9
                        //border.color: _verificationpasswordField.text === "" ? Kirigami.Theme.backgroundColor : ( config.passwordReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor)
                        border.color: _verificationPasswordField.text === "" ? "#FBFBFB" : ( config.userPasswordSecondaryChanged ? "#FBFBFB" : Kirigami.Theme.negativeTextColor)
                    }
                }
            }

            Label {

                width: parent.width
                text: qsTr("Enter the same password twice, so that it can be checked for typing errors. A good password will contain a mixture of letters, numbers and punctuation, should be at least eight characters long, and should be changed at regular intervals.")
                font.weight: Font.Thin
                font.pointSize: 8
                wrapMode: Text.WordWrap
                color: "#6D6D6D"
            }
        }

        CheckBox {

            visible: config.permitWeakPasswords
            text: qsTr("Validate passwords quality")
            checked: config.requireStrongPasswords
            onCheckedChanged: config.setRequireStrongPasswords(checked)
        }

        Label {
            visible: config.permitWeakPasswords
            width: parent.width
            text: qsTr("When this box is checked, password-strength checking is done and you will not be able to use a weak password.")
            font.weight: Font.Thin
            font.pointSize: 8
            color: "#6D6D6D"
        }

        CheckBox {
            text: qsTr("Log in automatically without asking for the password")
            checked: config.doAutoLogin
            onCheckedChanged: config.setAutoLogin(checked)
        }

        CheckBox {
            id: root
            visible: config.writeRootPassword
            text: qsTr("Reuse user password as root password")
            checked: config.reuseUserPasswordForRoot
            onCheckedChanged: config.setReuseUserPasswordForRoot(checked)
        }

        Label {
            visible: root.checked
            width: parent.width
            text: qsTr("Use the same password for the administrator account.")
            font.weight: Font.Thin
            font.pointSize: 8
            color: "#6D6D6D"
        }

        Column {

            visible: ! root.checked
            Layout.fillWidth: true
            spacing: Kirigami.Units.smallSpacing

            Label {

                width: parent.width
                text: qsTr("Choose a root password to keep your account safe.")
            }

            Row {
                width: parent.width
                spacing: 20

                TextField {

                    id: _rootPasswordField
                    width: parent.width / 2 -10
                    placeholderText: qsTr("Root Password")
                    text: config.rootPassword
                    onTextChanged: config.setRootPassword(text)

                    echoMode: TextInput.Password
                    passwordMaskDelay: 300
                    inputMethodHints: Qt.ImhNoAutoUppercase

                    background: Rectangle {

                        color: "#FBFBFB" // Kirigami.Theme.backgroundColor
                        opacity: 0.9
                        //border.color: _rootPasswordField.text === "" ? Kirigami.Theme.backgroundColor : ( config.rootPasswordReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor)
                        border.color: _rootPasswordField.text === "" ? "#FBFBFB" : ( config.rootPasswordReady ? "#FBFBFB" : Kirigami.Theme.negativeTextColor)
                    }
                }

                TextField {

                    id: _verificationRootPasswordField
                    width: parent.width / 2 -10
                    placeholderText: qsTr("Repeat Root Password")
                    text: config.rootPasswordSecondary
                    onTextChanged: config.setRootPasswordSecondary(text)

                    echoMode: TextInput.Password
                    passwordMaskDelay: 300
                    inputMethodHints: Qt.ImhNoAutoUppercase

                    background: Rectangle {

                        color: "#FBFBFB" // Kirigami.Theme.backgroundColor
                        opacity: 0.9
                        //border.color: _verificationRootPasswordField.text === "" ? Kirigami.Theme.backgroundColor : ( config.rootPasswordReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor)
                        border.color: _verificationRootPasswordField.text === "" ? "#FBFBFB" : ( config.rootPasswordReady ? "#FBFBFB" : Kirigami.Theme.negativeTextColor)
                    }
                }
            }

            Label {

                visible: ! root.checked
                width: parent.width
                text: qsTr("Enter the same password twice, so that it can be checked for typing errors.")
                font.weight: Font.Thin
                font.pointSize: 8
                color: "#6D6D6D"
            }
        }
    }
}
