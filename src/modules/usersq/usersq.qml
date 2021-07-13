/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 - 2021 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

import io.calamares.core 1.0
import io.calamares.ui 1.0

import QtQuick 2.15
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
                onTextChanged: config.setFullName(text)

                palette.base: _userNameField.text.length ? "#f0fff0" : "#FBFBFB"
                palette.highlight : _userNameField.text.length ? "#dcffdc" : "#FBFBFB"
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
                validator: RegularExpressionValidator { regularExpression: /[a-z_][a-z0-9_-]*[$]?$/ }

                onTextChanged: acceptableInput
                    ? ( _userLoginField.text === "root"
                    ? forbiddenMessage.visible=true
                    : ( config.setLoginName(text),
                    userMessage.visible = false,forbiddenMessage.visible=false ) )
                    : ( userMessage.visible = true,console.log("Invalid") )

                palette.base: _userLoginField.text.length
                    ? ( acceptableInput
                    ? ( _userLoginField.text === "root"
                    ? "#ffdae0" : "#f0fff0" ) : "#ffdae0" ) : "#FBFBFB"
                palette.highlight : _userLoginField.text.length ? "#dcffdc" : "#FBFBFB"
            }

            Label {
                width: parent.width
                text: qsTr("If more than one person will use this computer, you can create multiple accounts after installation.")
                font.weight: Font.Thin
                font.pointSize: 8
                color: "#6D6D6D"
            }
        }

        Kirigami.InlineMessage {
            id: userMessage
            Layout.fillWidth: true
            visible: false
            type: Kirigami.MessageType.Error
            text: qsTr("Only lowercase letters, numbers, underscore and hyphen are allowed.")
        }

        Kirigami.InlineMessage {
            id: forbiddenMessage
            Layout.fillWidth: true
            visible: false
            type: Kirigami.MessageType.Error
            text: qsTr("root is not allowed as username.")
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
                validator: RegularExpressionValidator { regularExpression: /[a-zA-Z0-9][-a-zA-Z0-9_]+/ }

                onTextChanged: acceptableInput
                    ? ( _hostName.text === "localhost"
                    ? forbiddenHost.visible=true
                    : ( config.setHostName(text),
                    hostMessage.visible = false,forbiddenHost.visible = false ) )
                    : hostMessage.visible = true

                palette.base: _hostName.text.length
                    ? ( acceptableInput
                    ? ( _hostName.text === "localhost" ? "#ffdae0" : "#f0fff0" )
                    : "#ffdae0")
                    : "#FBFBFB"
                palette.highlight : _hostName.text.length ? "#dcffdc" : "#FBFBFB"
            }

            Label {
                width: parent.width
                text: qsTr("This name will be used if you make the computer visible to others on a network.")
                font.weight: Font.Thin
                font.pointSize: 8
                color: "#6D6D6D"
            }
        }

        Kirigami.InlineMessage {
            id: hostMessage
            Layout.fillWidth: true
            visible: false
            type: Kirigami.MessageType.Error
            text: qsTr("Only letters, numbers, underscore and hyphen are allowed, minimal of two characters.")
        }

        Kirigami.InlineMessage {
            id: forbiddenHost
            Layout.fillWidth: true
            visible: false
            type: Kirigami.MessageType.Error
            text: qsTr("localhost is not allowed as hostname.")
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

                    palette.base: _passwordField.text.length ? "#f0fff0" : "#FBFBFB"
                    palette.highlight : _passwordField.text.length ? "#dcffdc" : "#FBFBFB"

                    echoMode: TextInput.Password
                    passwordMaskDelay: 300
                    inputMethodHints: Qt.ImhNoAutoUppercase
                }

                TextField {
                    id: _verificationPasswordField
                    width: parent.width / 2 - 10
                    placeholderText: qsTr("Repeat Password")
                    text: config.userPasswordSecondary

                    onTextChanged: _passwordField.text === _verificationPasswordField.text
                        ? ( config.setUserPasswordSecondary(text),
                        passMessage.visible = false,
                        validityMessage.visible = true )
                        : ( passMessage.visible = true,
                        validityMessage.visible = false )

                    palette.base: _verificationPasswordField.text.length
                        ? ( _passwordField.text === _verificationPasswordField.text
                        ? "#f0fff0" : "#ffdae0" )
                        : "#FBFBFB"
                    palette.highlight : _verificationPasswordField.text.length ? "#dcffdc" : "#FBFBFB"

                    echoMode: TextInput.Password
                    passwordMaskDelay: 300
                    inputMethodHints: Qt.ImhNoAutoUppercase
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

        Kirigami.InlineMessage {
            id: passMessage
            Layout.fillWidth: true
            showCloseButton: true
            visible: false
            type: Kirigami.MessageType.Error
            text: config.userPasswordMessage
        }

        Kirigami.InlineMessage {
            id: validityMessage
            Layout.fillWidth: true
            showCloseButton: true
            visible: false
            type:  config.userPasswordValidity
                ? ( config.requireStrongPasswords
                ? Kirigami.MessageType.Error : Kirigami.MessageType.Warning )
                : Kirigami.MessageType.Positive
            text: config.userPasswordMessage
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

                    palette.base: _rootPasswordField.text.length ? "#f0fff0" : "#FBFBFB"
                    palette.highlight : _rootPasswordField.text.length ? "#dcffdc" : "#FBFBFB"

                    echoMode: TextInput.Password
                    passwordMaskDelay: 300
                    inputMethodHints: Qt.ImhNoAutoUppercase
                }

                TextField {
                    id: _verificationRootPasswordField
                    width: parent.width / 2 -10
                    placeholderText: qsTr("Repeat Root Password")
                    text: config.rootPasswordSecondary

                    onTextChanged: _rootPasswordField.text === _verificationRootPasswordField.text
                        ? ( config.setRootPasswordSecondary(text),
                        rootPassMessage.visible = false,
                        rootValidityMessage.visible = true )
                        : ( rootPassMessage.visible = true,
                        rootValidityMessage.visible = false )

                    palette.base: _verificationRootPasswordField.text.length
                        ? ( _rootPasswordField.text === _verificationRootPasswordField.text
                        ? "#f0fff0" : "#ffdae0") : "#FBFBFB"
                    palette.highlight : _verificationRootPasswordField.text.length ? "#dcffdc" : "#FBFBFB"

                    echoMode: TextInput.Password
                    passwordMaskDelay: 300
                    inputMethodHints: Qt.ImhNoAutoUppercase
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

        Kirigami.InlineMessage {
            id: rootPassMessage
            Layout.fillWidth: true
            showCloseButton: true
            visible: false
            type: Kirigami.MessageType.Error
            text: config.rootPasswordMessage
        }

        Kirigami.InlineMessage {
            id: rootValidityMessage
            Layout.fillWidth: true
            showCloseButton: true
            visible: false
            type:  config.rootPasswordValidity
                ? ( config.requireStrongPasswords
                ? Kirigami.MessageType.Error : Kirigami.MessageType.Warning )
                : Kirigami.MessageType.Positive
            text: config.rootPasswordMessage
        }

        CheckBox {
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Log in automatically without asking for the password")
            checked: config.doAutoLogin
            onCheckedChanged: config.setAutoLogin(checked)
        }

        CheckBox {
            visible: config.permitWeakPasswords
            Layout.alignment: Qt.AlignCenter
            text: qsTr("Validate passwords quality")
            checked: config.requireStrongPasswords
            onCheckedChanged: config.setRequireStrongPasswords(checked),
                rootPassMessage.visible = false
        }

        Label {
            visible: config.permitWeakPasswords
            width: parent.width
            Layout.alignment: Qt.AlignCenter
            text: qsTr("When this box is checked, password-strength checking is done and you will not be able to use a weak password.")
            font.weight: Font.Thin
            font.pointSize: 8
            color: "#6D6D6D"
        }
    }
}
