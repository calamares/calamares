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
				text: qsTr("Back")
// 				enabled: Locale.Config.isNextEnabled
				onClicked:
				{
					if(_stackView.depth === 0)
						return;

					_stackView.pop()
				}
				height: implicitHeight
			}

			Button
			{
				text: qsTr("Next")
// 				enabled: Locale.Config.isNextEnabled
				// 			width: _requirementsList.width
				onClicked:
				{
					if(_stackView.depth >=2)
						return;

					_stackView.push(_zonesListComponent)
				}
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
			id: _regionsListComponent
			width: parent.width
			spacing:  Kirigami.Units.largeSpacing * 5

			Label
			{
				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.NoWrap
				text: qsTr("Region")
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
				text: qsTr("Pick your preferred region or use the default one based on your current location")
				color: "white"
				font.weight: Font.Light
				font.pointSize: 12
			}

			Label
			{

				Layout.fillWidth: true
				Layout.preferredHeight: implicitHeight
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.NoWrap
				text: qsTr("Select your preferred zone within your location to continue with the installation")
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
				currentIndex: model.currentIndex

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

					hoverEnabled: true

					property bool isCurrentItem: ListView.isCurrentItem
					background: Rectangle
					{
						color: isCurrentItem || hovered ? Kirigami.Theme.highlightColor : Kirigami.Theme.backgroundColor
						opacity: isCurrentItem || hovered ? 0.7 : 0.1
					}

					width: parent.width
					height: 48

					contentItem: Label
					{
						anchors.fill: parent
						anchors.margins: Kirigami.Units.largeSpacing
						horizontalAlignment: Qt.AlignLeft
						text: model.label
						color: isCurrentItem ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor
					}

					onClicked:
					{
						_regionListView.model.currentIndex = index
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
					text: qsTr("Timezone")
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
					text: Locale.Config.prettyStatus
					color: "white"
					font.weight: Font.Light
					font.pointSize: 12
				}

				ListView
				{
					id: _zonesListView
					Layout.alignment: Qt.AlignCenter
					Layout.preferredWidth: Math.min(500, parent.width - 64)
					Layout.preferredHeight: Math.min(contentHeight, parent.height - 200)
					spacing: Kirigami.Units.smallSpacing
					clip: true

					currentIndex: model.currentIndex

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
							opacity: isCurrentItem || hovered ? 0.7 : 0.1
						}

						width: parent.width
						height: 48

						onClicked:
						{
							_zonesListView.model.currentIndex = index
							positionViewAtIndex(index, ListView.Center)
						}

						contentItem: Label
						{
							anchors.fill: parent
							anchors.margins: Kirigami.Units.largeSpacing
							horizontalAlignment: Qt.AlignLeft
							text: model.label
							color: isCurrentItem ? Kirigami.Theme.highlightedTextColor : Kirigami.Theme.textColor
						}
					}
				}
			}

		}

	}
}
