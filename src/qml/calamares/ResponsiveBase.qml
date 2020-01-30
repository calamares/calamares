import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0
import io.calamares.ui 1.0

Page
{
	id: control
	width: parent.width
	height: parent.height

	Kirigami.Theme.backgroundColor: "#fafafa"
	Kirigami.Theme.textColor: "#333"

	signal backClicked()
	signal nextClicked()


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

	footer: Item
	{
		height: 100
		width: parent.width

		Row
		{
			spacing: Kirigami.Units.largeSpacing
			anchors.centerIn: parent

			Button
			{
				text: qsTr("Back")
				// 				enabled: _locale.isNextEnabled
				onClicked: control.backClicked()
				height: implicitHeight
			}

			Button
			{
				text: qsTr("Next")
				// 				enabled: _locale.isNextEnabled
				// 			width: _requirementsList.width
				onClicked: control.nextClicked()
				height: implicitHeight
			}
		}
	}
}
