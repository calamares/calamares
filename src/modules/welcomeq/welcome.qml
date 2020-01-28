import io.calamares.modules.welcome 1.0 as Welcome
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import org.kde.mauikit 1.0 as Maui
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3


Page
{
	id: control
	width: Screen.width
	height: Screen.height

	Kirigami.Theme.backgroundColor: "#fafafa"
	Kirigami.Theme.textColor: "#333"

	background: Item
	{
		id: _background

		Image
		{
			id: _wallpaper
			height: parent.height
			width: parent.width

			sourceSize.height: height / 60
			sourceSize.width: width / 60

			fillMode: Image.PreserveAspectCrop
			antialiasing: false
			smooth: false
			asynchronous: true
			cache: true

			source: Branding.imagePath(Branding.ProductWallpaper)

		}

		FastBlur
		{
			id: fastBlur
			anchors.fill: parent
			source: _wallpaper
			radius: 130
			transparentBorder: false
			cached: true
		}
	}

	//     footer: Item
	//     {
	//         width: parent.width
	//         height: 200
	//
	//         Button
	//         {
	//             anchors.centerIn: parent
	//             text: Welcome.Config.countryCode
	//             width: _requirementsList.width
	//             height: implicitHeight
	//         }
	//     }

	footer: Item
	{
		height: 300
		width: parent.width

		Row
		{
			spacing: Kirigami.Units.largeSpacing
			anchors.centerIn: parent

			Button
			{
				text: qsTr("Next")
				enabled: Welcome.Config.isNextEnabled
				// 			width: _requirementsList.width
				onClicked: _stackView.push(_langComponent)
				height: implicitHeight
			}
		}
	}

	StackView
	{
		id:_stackView
		anchors.fill: parent
		anchors.margins: Kirigami.Units.largeSpacing * 5

		initialItem: ColumnLayout
		{
			width: parent.width
			spacing:  Kirigami.Units.largeSpacing * 5

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

			Label
			{
				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.NoWrap
				text: "Welcome to " + Branding.string(Branding.ProductName) + " " + Branding.string(Branding.Version)
				color: "white"
				font.bold: true
				font.weight: Font.Bold
				font.pointSize: 24
			}

			Label
			{
				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.NoWrap
				text: Welcome.Config.genericWelcomeMessage
				color: "white"
				font.weight: Font.Light
				font.pointSize: 12
			}


			Label
			{
				visible: !_requirementsList.model.satisfiedRequirements
				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.NoWrap
				text: Welcome.Config.warningMessage
				color: "white"
				font.weight: Font.Light
				font.pointSize: 10
			}


			ListView
			{
				id: _requirementsList

				Layout.alignment: Qt.AlignCenter
				Layout.preferredWidth: Math.min(500, parent.width - 64)
				Layout.preferredHeight: Math.min(contentHeight, 500)
				spacing: Kirigami.Units.smallSpacing
				clip: true
				boundsBehavior: Flickable.StopAtBounds

				Rectangle
				{
					z: parent.z - 1
					anchors.fill: parent
					color: Kirigami.Theme.backgroundColor
					radius: 5
					opacity: 0.5
				}

				model: Welcome.Config.requirementsModel

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
			}

			Row
			{
				Layout.preferredWidth: implicitWidth
				Layout.preferredHeight: 64
				spacing: Kirigami.Units.largeSpacing* 2
				Layout.alignment:Qt.AlignCenter

				Button
				{
					text: "About"
					icon.name: "documentinfo"
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"

					visible: Branding.string(Branding.ProductUrl).length
					onClicked: Qt.openUrlExternally(Branding.string(Branding.ProductUrl))
				}

				Button
				{
					text: qsTr("Support")
					icon.name: "help-contents"
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"
					visible: Branding.string(Branding.SupportUrl).length
					onClicked: Qt.openUrlExternally(Branding.string(Branding.SupportUrl))
				}

				Button
				{
					text: qsTr("Known issues")
					icon.name: "tools-report-bug"
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"
					visible: Branding.string(Branding.KnownIssuesUrl).length
					onClicked: Qt.openUrlExternally(Branding.string(Branding.KnownIssuesUrl))
				}

				Button
				{
					text: qsTr("Release notes")
					icon.name: "answer"
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"
					visible: Branding.string(Branding.ReleaseNotesUrl).length
					onClicked: Qt.openUrlExternally(Branding.string(Branding.ReleaseNotesUrl))
				}

			}
		}


		Component
		{
			id: _langComponent

			ColumnLayout
			{
				width: parent.width
				spacing:  Kirigami.Units.largeSpacing * 5

				Label
				{
					Layout.fillWidth: true
					Layout.preferredHeight: implicitHeight
					horizontalAlignment: Qt.AlignHCenter
					wrapMode: Text.NoWrap
					text: qsTr("Language")
					color: "white"
					font.bold: true
					font.weight: Font.Bold
					font.pointSize: 24
				}

				Label
				{
					Layout.fillWidth: true
					Layout.preferredHeight: implicitHeight
					horizontalAlignment: Qt.AlignHCenter
					wrapMode: Text.NoWrap
					text: qsTr("Select your preferred language to continue with the installation")
					color: "white"
					font.weight: Font.Light
					font.pointSize: 12
				}

				ListView
				{
					id: _langList
					Layout.alignment: Qt.AlignCenter
					Layout.preferredWidth: Math.min(500, parent.width - 64)
					Layout.preferredHeight: Math.min(contentHeight, parent.height - 200)
					spacing: Kirigami.Units.smallSpacing
					clip: true

					currentIndex: Welcome.Config.localeIndex

					Rectangle
					{
						z: parent.z - 1
						anchors.fill: parent
						color: Kirigami.Theme.backgroundColor
						radius: 5
						opacity: 0.3
					}

					model: Welcome.Config.languagesModel

					delegate: ItemDelegate
					{
						id: _delegate
						hoverEnabled: true

						property bool isCurrentItem: ListView.isCurrentItem
						background: Rectangle
						{
							color: isCurrentItem || hovered ? Kirigami.Theme.highlightColor : Kirigami.Theme.backgroundColor
							opacity: isCurrentItem || hovered ? 1 : 0.1
						}

						width: parent.width
						height: 48

						onClicked:
						{
							Welcome.Config.localeIndex = index
							positionViewAtIndex(index, ListView.Beginning)
						}

						contentItem: RowLayout
						{
							width: parent.width
							height: parent.height
							Label
							{
								Layout.fillWidth: true
								Layout.fillHeight: true
								horizontalAlignment: Qt.AlignLeft
								text: model.label
								color: isCurrentItem ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor
							}

							Label
							{
								Layout.fillWidth: true
								Layout.fillHeight: true
								horizontalAlignment: Qt.AlignRight
								text: model.englishLabel
								color: isCurrentItem ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor

								opacity: isCurrentItem ? 1 : 0.7
								font.weight: Font.Light
							}
						}
					}
				}
			}

		}
	}


}
