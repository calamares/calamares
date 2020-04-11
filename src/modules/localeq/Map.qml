import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Window 2.14
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

import QtLocation 5.14
import QtPositioning 5.14


Rectangle {
    width: parent.width
    height: 300

    Plugin {
        id: mapPlugin
        name: "esri" // "esri", "here", "itemsoverlay", "mapbox", "mapboxgl",  "osm"
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        activeMapType: supportedMapTypes[0]
        center: marker.coordinate
        zoomLevel: 5
        bearing: 0
        tilt: 0
        copyrightsVisible : true
        fieldOfView : 90

        MapQuickItem {
            id: marker
            anchorPoint.x: image.width/4
            anchorPoint.y: image.height
            coordinate: QtPositioning.coordinate(40.730610, -73.935242) // New York

            sourceItem: Image {
                id: image
                width: 48
                height: 48
                source: "pin.svg"
            }
        }
        MouseArea {
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            anchors.fill: map
            hoverEnabled: true
            property var coordinate: map.toCoordinate(Qt.point(mouseX, mouseY))
            Label {
                x: parent.mouseX - width
                y: parent.mouseY - height - 5
                text: "%1, %2".arg(parent.coordinate.latitude).arg(parent.coordinate.longitude)
            }
            
            onClicked: {
                marker.coordinate = coordinate
            }
        }
    }
    Column {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 10
        anchors.rightMargin: 10
        
        RoundButton {
            width: 25
            height:38
            text: "+"

            onClicked: map.zoomLevel++
        }
        RoundButton {
            width: 25
            height:38
            text: "-"
            font { pointSize: 20 }

            onClicked: map.zoomLevel--
        }
    }
}
