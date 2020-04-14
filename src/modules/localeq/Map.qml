/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Anke Boersma <demm@kaosx.us>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.10
import QtQuick.Controls 2.10
import QtQuick.Window 2.14
import QtQuick.Layouts 1.3
import org.kde.kirigami 2.7 as Kirigami

import QtLocation 5.14
import QtPositioning 5.14

Column {
    width: parent.width
    
    Rectangle {
        width: parent.width
        height: 270
        
        Plugin {
            id: mapPlugin
            name: "esri" // "esri", "here", "itemsoverlay", "mapbox", "mapboxgl",  "osm"
        }

        Map {
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            activeMapType: supportedMapTypes[0]
            zoomLevel: 5
            bearing: 0
            tilt: 0
            copyrightsVisible : true
            fieldOfView : 0

            GeocodeModel {
                id: geocodeModel
                plugin: mapPlugin
                autoUpdate: true
                query: Address {
                    id: address
                    //street: "14th Street"
                    city: zoneIndex.currentIndex
                    country: regionIndex.currentIndex
                    //countryCode: "US"
                }
                
                onLocationsChanged: {
                    if (count == 1) {
                        map.center.latitude = get(0).coordinate.latitude
                        map.center.longitude = get(0).coordinate.longitude
                    }
                }
            }
            
            MapQuickItem {
                id: marker
                anchorPoint.x: image.width/4
                anchorPoint.y: image.height
                coordinate: QtPositioning.coordinate(
                    map.center.latitude, 
                    map.center.longitude)
                //coordinate: QtPositioning.coordinate(40.730610, -73.935242) // New York

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
                    text: "%1, %2".arg(
                        parent.coordinate.latitude).arg(parent.coordinate.longitude)
                }
                
                onClicked: {
                    marker.coordinate = coordinate
                    map.center.latitude = coordinate.latitude
                    map.center.longitude = coordinate.longitude
                    console.log(coordinate.latitude, coordinate.longitude)
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

                onClicked: map.zoomLevel--
            }
        }
    }

    Rectangle {
        width: parent.width / 1.2
        height: 70
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            width: parent.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Please select your preferred location on the map so the installer can suggest the locale and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.")
        }
    }
}
