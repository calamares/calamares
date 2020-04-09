import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

import org.kde.marble.private.plasma 0.20



Rectangle {
    id: screen
    width: parent.width
    height: 300

    PositionSource {
        id: gpsd
        active: true
    }

    MarbleItem {
        id: map
        anchors.fill: parent

        property bool autoCenter: true
        readonly property double locationLongitude: geolocationDataSource.data.longitude
        radius: 200
        
        Coordinate { longitude: -73.935242; latitude: 40.730610 }

        mapThemeId: "earth/srtm/srtm.dgml"
        //projection: "Mercator"
        //activeFloatItems: [ "compass", "scalebar", "progress" ]
        //showScaleBar: true
        //showClouds: true
        //showGrid: true
        showCrosshairs: true
        showAtmosphere: true
        //setCenterLatitude: 35.0

        property Tracking tracking: Tracking {
            positionSource: gpsd
            map: map
            positionMarkerType: Tracking.Arrow
            showTrack: true
        }
    }
    
    Column {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.rightMargin: 10
        
        Button {
            width: 40
            icon.name: "arrow-up"

            onClicked: map.zoomIn()
        }
        Button {
            width: 40
            icon.name: "arrow-down"

            onClicked: map.zoomOut()
        }
    }
}
