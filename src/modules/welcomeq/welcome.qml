import io.calamares.modules 1.0 as Modules
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import org.kde.mauikit 1.0 as Maui
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3

ResponsiveBase
{
	id: control

	Modules.Welcome
	{
		id: _welcome
	}

	nextButton.enabled: _welcome.Config.isNextEnabled
	onNextClicked:
	{
		if (stackView.depth === 2)
			return

		stackView.push(_langComponent)
	}

	title: stackView.currentItem.title
	subtitle: stackView.currentItem.subtitle
	message: stackView.currentItem.message

	Item
	{
		Layout.fillWidth: true
		Layout.preferredHeight: 100

		Image
		{
			anchors.centerIn: parent
			source: Branding.imagePath(Branding.ProductWelcome)
			height: Math.max(64, parent.height)
			width: height
			sourceSize.width: width
			sourceSize.height: height
		}
	}

	stackView.initialItem: Item
	{
		property string title: "Welcome to " + Branding.string(Branding.ProductName) + " " + Branding.string(Branding.Version)
		property string subtitle: _welcome.Config.genericWelcomeMessage
		property string message: _welcome.Config.warningMessage

		ListViewTemplate
		{
			id: _requirementsList
			anchors.centerIn: parent
			implicitWidth: Math.min(parent.width, 500)
			implicitHeight: Math.min(contentHeight, 500)

			model: _welcome.Config.requirementsModel

			delegate: ItemDelegate
			{
				id: _delegate

				background: Rectangle
				{
					color: model.satisfied ? Kirigami.Theme.positiveTextColor : Kirigami.Theme.negativeTextColor
					opacity: 0.2
				}

				width: parent.width
				height: 48

				contentItem: RowLayout
				{
					width: parent.width
					height: parent.height

					Item
					{
						Layout.fillHeight: true
						Layout.preferredWidth: height

						Kirigami.Icon
						{
							source: model.satisfied ? "checkmark" : (model.mandatory ? "error" : "dialog-warning-symbolic")
							height:  32
							width: height
							anchors.centerIn: parent
							color: background.color
						}
					}

					ColumnLayout
					{
						Layout.fillWidth: true
						Layout.fillHeight: true

						spacing: 0

						Label
						{
							Layout.fillWidth: true
							Layout.fillHeight: true
							horizontalAlignment: Qt.AlignLeft
							text: model.name
						}

						Label
						{
							Layout.fillWidth: true
							Layout.fillHeight: true
							horizontalAlignment: Qt.AlignLeft
							text: !model.satisfied ?  model.negatedText : model.details
							opacity: isCurrentItem ? 1 : 0.7
							font.weight: Font.Light
						}
					}
				}
			}

			footer: RowLayout
			{

				width: parent.width
				height: 64

				spacing: Kirigami.Units.largeSpacing* 2

				Button
				{
					Layout.fillWidth: true
					text: "About"
					icon.name: "documentinfo"
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"

					visible: Branding.string(Branding.ProductUrl).length
					onClicked: Qt.openUrlExternally(Branding.string(Branding.ProductUrl))
				}

				Button
				{
					Layout.fillWidth: true
					text: qsTr("Support")
					icon.name: "help-contents"
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"
					visible: Branding.string(Branding.SupportUrl).length
					onClicked: Qt.openUrlExternally(Branding.string(Branding.SupportUrl))
				}

				Button
				{
					Layout.fillWidth: true
					text: qsTr("Known issues")
					icon.name: "tools-report-bug"
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"
					visible: Branding.string(Branding.KnownIssuesUrl).length
					onClicked: Qt.openUrlExternally(Branding.string(Branding.KnownIssuesUrl))
				}

				Button
				{
					Layout.fillWidth: true
					text: qsTr("Release notes")
					icon.name: "answer"
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"
					visible: Branding.string(Branding.ReleaseNotesUrl).length
					onClicked: Qt.openUrlExternally(Branding.string(Branding.ReleaseNotesUrl))
				}

			}
		}
	}




	Component
	{
		id: _langComponent

		Item
		{
			property string title : qsTr("Language")
			property string subtitle:  qsTr("Select your preferred language to continue with the installation")

			ListViewTemplate
			{
				id: _langList
				anchors.centerIn: parent
				implicitWidth: Math.min(parent.width, 500)
				implicitHeight: Math.min(contentHeight, 500)

				currentIndex: _welcome.Config.localeIndex

				model: _welcome.Config.languagesModel

				delegate: ListItemDelegate
				{
					id: _delegate
					label1.text: model.label
					label2.text: model.englishLabel
				}
			}
		}

	}

}
