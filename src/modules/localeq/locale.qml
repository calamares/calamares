import io.calamares.modules 1.0 as Modules
import io.calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0

ResponsiveBase
{
	id: control

	Modules.Locale //locale handler
	{
		id: _locale
	}

	title: stackView.currentItem.title
	subtitle: stackView.currentItem.subtitle
	message: stackView.currentItem.message

	stackView.initialItem: Item
	{
		id: _regionsListComponent

		property string title: qsTr("Region")
		property string subtitle: qsTr("Pick your preferred region or use the default one based on your current location")
		property string message:  qsTr("Select your preferred zone within your location to continue with the installation")

		ListViewTemplate
		{
			id: _regionListView
			anchors.centerIn: parent
			implicitWidth: Math.min(parent.width, 500)
			implicitHeight: Math.min(contentHeight, 500)
			currentIndex: model.currentIndex
			model: _locale.Config.regionModel

			delegate: ListItemDelegate
			{
				id: _delegate
				label1.text: model.label
				onClicked:
				{
					_regionListView.model.currentIndex = index
					_stackView.push(_zonesListComponent)
				}
			}

			footer:  RowLayout
			{
				width: parent.width
				z: 99999
				Button
				{
					Layout.fillWidth: true
					text: qsTr("Timezones")
					icon.name: "go-previous"
					onClicked: control.stackView.push(_zonesListComponent)
				}
			}
		}
	}


	Component
	{
		id: _zonesListComponent

		Item
		{
			property string title: qsTr("Timezone")
			property string subtitle: _locale.Config.prettyStatus
			property string message: ""
			ListViewTemplate
			{
				id: _zonesListView
				anchors.centerIn: parent
				implicitWidth: Math.min(parent.width, 500)
				implicitHeight: Math.min(contentHeight, 500)
				currentIndex: model.currentIndex
				model: _locale.Config.zonesModel

				delegate: ListItemDelegate
				{
					id: _delegate
					label1.text: model.label
					onClicked:
					{
						_zonesListView.model.currentIndex = index
						positionViewAtIndex(index, ListView.Center)
					}
				}

				footer: RowLayout
				{
					width: parent.width
					z: 99999

					Button
					{
						Layout.fillWidth: true
						icon.name: "go-previous"
						text: qsTr("Regions")
						onClicked: control.stackView.pop()
					}
				}
			}
		}
	}
}

