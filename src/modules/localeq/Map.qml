/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 - 2022 Anke Boersma <demm@kaosx.us>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

    // These are used by the map query to initially center the
    //   map on the user's likely location. They are updated by
    //   getIp() which does a more accurate GeoIP lookup than
    //   the default one in Calamares
    property var cityName: ""
    property var countryName: ""

    /* This is an extra GeoIP lookup, which will find better-accuracy
     * location data for the user's IP, and then sets the current timezone
     * and map location. Call it from Component.onCompleted so that
     * it happens "on time" before the page is shown.
     */
    function getIpOnline() {
        var xhr = new XMLHttpRequest

        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                var responseJSON = JSON.parse(xhr.responseText)
                var tz = responseJSON.timezone
                var ct = responseJSON.city
                var cy = responseJSON.country

                cityName = ct
                countryName = cy

                config.setCurrentLocation(tz)
            }
        }

        // Define the target of the request
        xhr.open("GET", "https://get.geojs.io/v1/ip/geo.json")
        // Execute the request
        xhr.send()
    }

    /* This is an "offline" GeoIP lookup -- it just follows what
     * Calamares itself has figured out with its GeoIP or configuration.
     * Call it from the **Component** onActivate() -- in localeq.qml --
     * so it happens as the page is shown.
     */
    function getIpOffline() {
        cityName = config.currentLocation.zone
        countryName = config.currentLocation.countryCode
    }

    /* This is an **accurate** TZ lookup method: it queries an
     * online service for the TZ at the given coordinates. It
     * requires an internet connection, though, and the distribution
     * will need to have an account with geonames to not hit the
     * daily query limit.
     *
     * See below, in MouseArea, for calling the right method.
     */
    function getTzOnline() {
        var xhr = new XMLHttpRequest
        var latC = map.center.latitude
        var lonC = map.center.longitude

        xhr.onreadystatechange = function() {
            if (xhr.readyState === XMLHttpRequest.DONE) {
                var responseJSON = JSON.parse(xhr.responseText)
                var tz2 = responseJSON.timezoneId

                config.setCurrentLocation(tz2)
            }
        }

        console.log("Online lookup", latC, lonC)
        // Needs to move to localeq.conf, each distribution will need their own account
        xhr.open("GET", "http://api.geonames.org/timezoneJSON?lat=" + latC + "&lng=" + lonC + "&username=SOME_USERNAME")
        xhr.send()
    }

    /* This is a quick TZ lookup method: it uses the existing
     * Calamares "closest TZ" code, which has lots of caveats.
     *
     * See below, in MouseArea, for calling the right method.
     */
    function getTzOffline() {
        var latC = map.center.latitude
        var lonC = map.center.longitude
        var tz = config.zonesModel.lookup(latC, lonC)
        console.log("Offline lookup", latC, lonC)
        config.setCurrentLocation(tz.region, tz.zone)
    }

    Rectangle {
        width: parent.width
        height: parent.height / 1.28

        Plugin {
            id: mapPlugin
            preferred: ["osm", "esri"] // "esri", "here", "itemsoverlay", "mapbox", "mapboxgl",  "osm"
        }

        Map {
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            activeMapType: supportedMapTypes[0]
            //might be desirable to set zoom level configurable?
            zoomLevel: 7
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

                onClicked: {
                    marker.coordinate = coordinate
                    map.center.latitude = coordinate.latitude
                    map.center.longitude = coordinate.longitude

                    // Pick a TZ lookup method here (quick:offline, accurate:online)
                    getTzOffline();
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
                    text: qsTr("Timezone: %1").arg(config.currentTimezoneName)
                    color: Kirigami.Theme.textColor
                    anchors.centerIn: parent
                }

                /* If you want an extra (and accurate) GeoIP lookup,
                 * enable this one and disable the offline lookup in
                 * onActivate().
                Component.onCompleted: getIpOnline();
                 */
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
