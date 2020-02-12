import calamares.ui 1.0

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami
import QtGraphicalEffects 1.0
import QtQuick.Window 2.3

Page
{
	id: welcome

	header: Item
	{
		width: parent.width
		height: 150

		Image
		{
			anchors.centerIn: parent
			source: Branding.imagePath(Branding.ProductWelcome)
			height: Math.min(100, parent.height)
			width: height
			sourceSize.width: width
			sourceSize.height: height
		}
	}
}
