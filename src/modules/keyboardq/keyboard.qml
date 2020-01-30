import io.calamares.modules 1.0 as Modules
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import org.kde.mauikit 1.0 as Maui

ResponsiveBase
{
	id: control
	Modules.Keyboard //locale handler
	{
		id: _keyboard
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
				text: qsTr("Keyboard Model")
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
				text: qsTr("Pick your preferred keyboard model or use the default one based on the detected hardware")
				color: "white"
				font.weight: Font.Light
				font.pointSize: 12
			}

			ListView
			{
				id: _keyboardModelListView
				Layout.alignment: Qt.AlignCenter
				Layout.preferredWidth: Math.min(500, parent.width - 64)
				Layout.preferredHeight: Math.min(contentHeight, 500)
				spacing: Kirigami.Units.smallSpacing
				clip: true
				boundsBehavior: Flickable.StopAtBounds
				currentIndex: model.currentIndex

				footerPositioning: ListView.OverlayFooter
				footer: ToolButton
				{
					icon.name: "view-refresh"
					onClicked: model.refresh()
					text: qsTr("Refresh")
				}

				Rectangle
				{
					z: parent.z - 1
					anchors.fill: parent
					color: Kirigami.Theme.backgroundColor
					radius: 5
					opacity: 0.5
				}

				model: _keyboard.Config.keyboardModelsModel

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
						_keyboardModelListView.model.currentIndex = index
						_stackView.push(_keyboardLayoutsComponent)
					}
				}
			}
		}

		Component
		{
			id: _keyboardLayoutsComponent

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
					text: qsTr("Keyboard Layout")
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
					text: _keyboard.Config.prettyStatus
					color: "white"
					font.weight: Font.Light
					font.pointSize: 12
				}

				ListView
				{
					id: _layoutsListView
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

					model: _keyboard.Config.keyboardLayoutsModel

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
							_layoutsListView.model.currentIndex = index
							_layoutsListView.positionViewAtIndex(index, ListView.Center)
							_stackView.push(_keyboardVariantsComponent)
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

		Component
		{
			id: _keyboardVariantsComponent

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
					text: qsTr("Keyboard Variant")
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
					text: _keyboard.Config.prettyStatus
					color: "white"
					font.weight: Font.Light
					font.pointSize: 12
				}

				ListView
				{
					id: _variantsListView
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

					model: _keyboard.Config.keyboardVariantsModel

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
							_variantsListView.model.currentIndex = index
							_variantsListView.positionViewAtIndex(index, ListView.Center)
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
