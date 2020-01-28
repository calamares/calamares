import io.calamares.modules.locale 1.0 as Locale
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
				enabled: Locale.Config.isNextEnabled
				// 			width: _requirementsList.width
				onClicked: _stackView.push(_zonesListComponent)
				height: implicitHeight
			}
		}
	}

	StackView
	{
		id:_stackView
		anchors.fill: parent
		anchors.margins: Kirigami.Units.largeSpacing * 5

		initialItem:  ColumnLayout
		{
			width: parent.width
			spacing:  Kirigami.Units.largeSpacing * 5


			Label
			{
				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.NoWrap
				text: qsTr("Location")
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
				text: qsTr("Pick your preferred location")
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
				text: _regionListView.count
				color: "white"
				font.weight: Font.Light
				font.pointSize: 10
			}

			ListView
			{
				id: _regionListView
				Layout.alignment: Qt.AlignCenter
				Layout.preferredWidth: Math.min(500, parent.width - 64)
				Layout.preferredHeight: Math.min(contentHeight, 500)
				spacing: Kirigami.Units.smallSpacing
				clip: true
				boundsBehavior: Flickable.StopAtBounds
				currentIndex: Locale.Config.currentRegion

				Rectangle
				{
					z: parent.z - 1
					anchors.fill: parent
					color: Kirigami.Theme.backgroundColor
					radius: 5
					opacity: 0.5
				}

				model: Locale.Config.regionModel

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

					text: model.label
					onClicked:
					{
						Locale.Config.currentRegion = index
						_stackView.push(_zonesListComponent)
					}


				}
			}
		}

		Component
		{
			id: _zonesListComponent

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
					text: qsTr("Zone")
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
					text: qsTr("Select your preferred zone to continue with the installation")
					color: "white"
					font.weight: Font.Light
					font.pointSize: 12
				}

				ListView
				{
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

					model: Locale.Config.zonesModel

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

						text: model.label
// 						color: isCurrentItem ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor
					}
				}
			}

		}

	}
}
