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

	title: qsTr("Users")
	subtitle: qsTr("Pick your user name and credentials to login and perform admin tasks")

	stackView.initialItem: Flickable
	{
		clip: true

		contentWidth: width
		contentHeight: _formLayout.implicitHeight

		ColumnLayout
		{
			id: _formLayout
			anchors.centerIn: parent
			width: parent.width

			TextField
			{
				Layout.fillWidth: true
				placeholderText: qsTr("User name")
			}


			TextField
			{
				Layout.fillWidth: true
				placeholderText: qsTr("User name")
			}


			TextField
			{
				Layout.fillWidth: true
				placeholderText: qsTr("User name")
			}


			TextField
			{
				Layout.fillWidth: true
				placeholderText: qsTr("User name")
			}


			TextField
			{
				Layout.fillWidth: true
				placeholderText: qsTr("User name")
			}
		}
	}

}
