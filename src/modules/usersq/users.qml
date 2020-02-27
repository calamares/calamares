import io.calamares.modules 1.0 as Modules
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3

ResponsiveBase
{
	id: control

	Modules.Users //locale handler
	{
		id: _users
	}

	nextButton.enabled: _users.isNextEnabled

	title: qsTr("Users")
	subtitle: qsTr("Pick your user name and credentials to login and perform admin tasks")
	message:_users.Config.status.message

	Kirigami.Theme.textColor: "white"

	stackView.initialItem: Item
	{
		Kirigami.ScrollablePage
		{

			height: Math.min(parent.height, contentHeight+ 200)
			width: Math.min(parent.width, 500)
			anchors.centerIn: parent

			padding: 0
			background:  Rectangle
			{
				color: Kirigami.Theme.backgroundColor
				radius: 5
				opacity: 0.3
			}

			ColumnLayout
			{
				id: _formLayout
				spacing: Kirigami.Units.largeSpacing

				Column
				{
					Layout.fillWidth: true
					spacing: Kirigami.Units.smallSpacing

					Label
					{
						width: parent.width
						text: qsTr("What is your name?")
					}

					TextField
					{
						id: _userNameField
						width: parent.width
						placeholderText: qsTr("Your Full Name")
						onTextChanged: _users.Config.onFullNameTextEdited(text)
						background: Rectangle
						{
							color:  Kirigami.Theme.backgroundColor
							radius: 5
							opacity: 0.5
							border.color: _users.Config.fullNameReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor

						}
					}
				}

				Column
				{
					Layout.fillWidth: true
					spacing: Kirigami.Units.smallSpacing

					Label
					{
						width: parent.width
						text: qsTr("What name do you want to use to log in?")
					}

					TextField
					{
						width: parent.width
						placeholderText: qsTr("login")
						text: _users.Config.userName
						onTextEdited: _users.Config.onUsernameTextEdited(text)
						background: Rectangle
						{
							color:  Kirigami.Theme.backgroundColor
							radius: 5
							opacity: 0.5
							border.color: _users.Config.userNameReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor

						}
					}
				}

				Column
				{
					Layout.fillWidth: true
					spacing: Kirigami.Units.smallSpacing

					Label
					{
						width: parent.width
						text: qsTr("What is the name of this computer?")
					}

					TextField
					{
						width: parent.width
						placeholderText: qsTr("Computer Name")
						text: _users.Config.hostName
						onTextEdited: _users.Config.onHostnameTextEdited(text)
						background: Rectangle
						{
							color:  Kirigami.Theme.backgroundColor
							radius: 5
							opacity: 0.5
							border.color: _users.Config.hostNameReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor
						}
					}
				}

				Column
				{
					visible: !_users.Config.resusePassword
					Layout.fillWidth: true
					spacing: Kirigami.Units.smallSpacing

					Label
					{
						width: parent.width
						text: qsTr("Choose a root password to keep your account safe.")
					}

					TextField
					{
						id: _rootPasswordField
						width: parent.width
						placeholderText: qsTr("Root Password")
						echoMode: TextInput.Password
						passwordMaskDelay: 300
						inputMethodHints: Qt.ImhNoAutoUppercase
						onTextChanged: _users.Config.onRootPasswordTextChanged(text, _verificationRootPasswordField.text)

						background: Rectangle
						{
							color:  Kirigami.Theme.backgroundColor
							radius: 5
							opacity: 0.5
							border.color: _users.Config.rootPasswordReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor

						}
					}

					TextField
					{
						id: _verificationRootPasswordField
						width: parent.width
						placeholderText: qsTr("Repeat Root Password")
						echoMode: TextInput.Password
						passwordMaskDelay: 300
						inputMethodHints: Qt.ImhNoAutoUppercase
						onTextChanged: _users.Config.onPasswordTextChanged(_rootPasswordField.text, text)

						background: Rectangle
						{
							color:  Kirigami.Theme.backgroundColor
							radius: 5
							opacity: 0.5
							border.color: _users.Config.rootPasswordReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor
						}
					}
				}

				Column
				{
					Layout.fillWidth: true
					spacing: Kirigami.Units.smallSpacing

					Label
					{
						width: parent.width
						text: qsTr("Choose a password to keep your account safe.")
					}

					TextField
					{
						id: _passwordField
						width: parent.width
						placeholderText: qsTr("Password")
						echoMode: TextInput.Password
						passwordMaskDelay: 300
						inputMethodHints: Qt.ImhNoAutoUppercase
						onTextChanged: _users.Config.onPasswordTextChanged(text, _verificationPasswordField.text)

						background: Rectangle
						{
							color:  Kirigami.Theme.backgroundColor
							radius: 5
							opacity: 0.5
							border.color: _users.Config.passwordReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor
						}
					}

					TextField
					{
						id: _verificationPasswordField
						width: parent.width
						placeholderText: qsTr("Repeat Password")
						echoMode: TextInput.Password
						passwordMaskDelay: 300
						inputMethodHints: Qt.ImhNoAutoUppercase
						onTextChanged: _users.Config.onPasswordTextChanged(_passwordField.text, text)

						background: Rectangle
						{
							color:  Kirigami.Theme.backgroundColor
							radius: 5
							opacity: 0.5
							border.color: _users.Config.passwordReady ? Kirigami.Theme.backgroundColor : Kirigami.Theme.negativeTextColor

						}
					}
				}
				CheckBox
				{
					visible: _users.Config.validatePasswordsVisible
					text: qsTr("Validate passwords quality")
					checked: _users.Config.validatePasswords
					onToggled:  _users.Config.validatePasswords = !_users.Config.validatePasswords
				}


				CheckBox
				{
					visible: _users.Config.resusePasswordVisible
					text: qsTr("Reuse user password as root password")
					checked: _users.Config.resusePassword
					onToggled:  _users.Config.resusePassword = !_users.Config.resusePassword
				}


				CheckBox
				{
					text: qsTr("Log in automatically withouth asking for the password")
					checked: _users.Config.autologin
					onToggled:  _users.Config.autologin = !_users.Config.autologin
				}
			}
		}
	}

}
