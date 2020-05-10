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

    //Needs to come from .conf/geoip
    property var configCity: "New York"
    property var configCountry: "USA"
    property var configTimezone: "America/New York"
    property var geoipCity: "" //"Amsterdam"
    property var geoipCountry: "" //"Netherlands"
    property var geoipTimezone: "" //"Europe/Amsterdam"
    // vars that will stay once connected
    property var cityName: (geoipCity != "") ? geoipCity : configCity
    property var countryName: (geoipCountry != "") ? geoipCountry : configCountry
    property var timeZone: (geoipTimezone != "") ? geoipTimezone : configTimezone

    function getIp() {
        var xhr = new XMLHttpRequest

        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                var responseJSON = JSON.parse(xhr.responseText)
                var tz = responseJSON.timezone
                var ct = responseJSON.city
                var cy = responseJSON.country

                tzText.text = "Timezone: " + tz
                cityName = ct
                countryName = cy
            }
        }

        // Define the target of the request
        xhr.open("GET", "https://get.geojs.io/v1/ip/geo.json")
        // Execute the request
        xhr.send()
    }

    function getTz() {
        var xhr = new XMLHttpRequest
        var latC = map.center.latitude
        var lonC = map.center.longitude

        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                var responseJSON = JSON.parse(xhr.responseText)
                var tz2 = responseJSON.timezoneId

                tzText.text = "Timezone: " + tz2
            }
        }

        // Needs to move to localeq.conf, each distribution will need their own account
        xhr.open("GET", "http://api.geonames.org/timezoneJSON?lat=" + latC + "&lng=" + lonC + "&username=SOME_USERNAME")
        xhr.send()
    }

    Rectangle {
        width: parent.width
        height: parent.height / 1.28

        Plugin {
            id: mapPlugin
            name: "esri" // "esri", "here", "itemsoverlay", "mapbox", "mapboxgl",  "osm"
        }

        Map {
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            activeMapType: supportedMapTypes[0]
            //might be desirable to set zoom level configurable?
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
                    city: cityName
                    country: countryName
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
                    width: 32
                    height: 32
                    source: "img/pin.svg"
                }
            }

            MouseArea {
                acceptedButtons: Qt.LeftButton
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

                    getTz();
                        
                    console.log(coordinate.latitude, coordinate.longitude)
                }
            }
        }

        Column {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.bottomMargin: 5
            anchors.rightMargin: 10

            MouseArea {
                width: 32
                height:32
                cursorShape: Qt.PointingHandCursor
                Image {
                    source: "img/plus.png"
                    anchors.centerIn: parent
                    width: 36
                    height: 36
                }

                onClicked: map.zoomLevel++
            }

            MouseArea {
                width: 32
                height:32
                cursorShape: Qt.PointingHandCursor
                Image {
                    source: "img/minus.png"
                    anchors.centerIn: parent
                    width: 32
                    height: 32
                }

                onClicked: map.zoomLevel--
            }
        }
    }

    Rectangle {
        width: parent.width 
        height: 100
        anchors.horizontalCenter: parent.horizontalCenter

        Item {
            id: location
            Kirigami.Theme.inherit: false
            Kirigami.Theme.colorSet: Kirigami.Theme.Complementary
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                anchors.centerIn: parent
                width: 300
                height: 30
                color: Kirigami.Theme.backgroundColor

                Text {
                    id: tzText
                    text: tzText.text
                    //text: qsTr("Timezone: %1").arg(timeZone)
                    color: Kirigami.Theme.textColor
                    anchors.centerIn: parent
                }

                Component.onCompleted: getIp();
            }
        }

        Text {
            anchors.top: location.bottom
            anchors.topMargin: 20
            padding: 10
            width: parent.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            Kirigami.Theme.backgroundColor: Kirigami.Theme.backgroundColor
            text: qsTr("Please select your preferred location on the map so the installer can suggest the locale
            and timezone settings for you. You can fine-tune the suggested settings below. Search the map by dragging
            to move and using the +/- buttons to zoom in/out or use mouse scrolling for zooming.")
        }
    }
}
