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

	property string subtitle
	property string message

	default property alias content : _content.data
		property alias stackView: _stackView

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

		ColumnLayout
		{
			id: _content

			anchors.fill: parent
			spacing:  Kirigami.Units.largeSpacing * 5
			anchors.margins: Kirigami.Units.largeSpacing * 5

			Label
			{
				Layout.fillWidth: true
				Layout.preferredHeight: Math.min(implicitHeight, 200)
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.NoWrap
				elide: Text.ElideMiddle
				text: control.title
				color: "white"
				font.bold: true
				font.weight: Font.Bold
				font.pointSize: 24
			}

			Label
			{
				Layout.fillWidth: true
				Layout.preferredHeight: Math.min(implicitHeight, 200)
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.Wrap
				elide: Text.ElideMiddle
				text: control.subtitle
				color: "white"
				font.weight: Font.Light
				font.pointSize: 12
			}

			Label
			{
				Layout.fillWidth: true
				Layout.preferredHeight: Math.min(implicitHeight, 200)
				horizontalAlignment: Qt.AlignHCenter
				wrapMode: Text.Wrap
				elide: Text.ElideMiddle
				text: control.message
				color: "white"
				font.weight: Font.Light
				font.pointSize: 10
			}

			StackView
			{
				id: _stackView
				Layout.fillHeight: true
				Layout.preferredWidth: parent.width
				clip: true
			}
		}

		footer: Item
		{
			height: 100
			width: parent.width
			Kirigami.Theme.backgroundColor: "#fafafa"
			Kirigami.Theme.textColor: "#333"

			Row
			{
				spacing: Kirigami.Units.largeSpacing
				anchors.centerIn: parent

				Button
				{
					id: _backButton
					text: qsTr("Back")
					// 				enabled: _locale.isNextEnabled
					onClicked: control.backClicked()
					height: implicitHeight
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"

				}

				Button
				{
					id: _nextButton
					text: qsTr("Next")
					// 				enabled: _locale.isNextEnabled
					// 			width: _requirementsList.width
					onClicked: control.nextClicked()
					height: implicitHeight
					Kirigami.Theme.backgroundColor: Qt.rgba(Kirigami.Theme.backgroundColor.r, Kirigami.Theme.backgroundColor.g, Kirigami.Theme.backgroundColor.b, 0.4)
					Kirigami.Theme.textColor: "#fff"
				}
			}
		}
}
