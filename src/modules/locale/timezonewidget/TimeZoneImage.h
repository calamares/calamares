/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef TIMEZONEIMAGE_H
#define TIMEZONEIMAGE_H

#include <QImage>
#include <QList>

using TimeZoneImage = QImage;

/** @brief All the timezone images
 *
 * There's one fixed list of timezone images that can be loaded
 * from the QRC, or from the source directory.
 */
class TimeZoneImageList : public QList< TimeZoneImage >
{
private:
    TimeZoneImageList();

public:
    /** @brief loads all the images from QRC.
     *
     * The images are assumed to be compiled into the Qt resource
     * system and are loaded from there.
     */
    static TimeZoneImageList fromQRC();
    /** @brief loads all the images from a specified directory.
     *
     * No error is returned if files are missing.
     */
    static TimeZoneImageList fromDirectory( const QString& dirName );

    /** @brief Map longitude and latitude to pixel positions
     *
     * The image is flat, and stretched at the poles and generally
     * a bit weird, so this maps the global coordinates (as found in
     * the zones table as a floating-point longitude and latitude value)
     * to an x,y position.
     */
    static QPoint getLocationPosition( double longitude, double latitude );

    /** @brief Find the index of the image claiming point @p p
     *
     * This maps a point (presumably from getLocationPosition(), so
     * originating from a longitude and latitude) to a specific zone
     * image index. Returns -1 if no image claims the point (e.g. if
     * it is out of bounds).
     */
    int index( QPoint p ) const;
    /** @brief Find the index of the image claiming point @p p
     *
     * As `index(p)`, but also fills in @p count with the number of
     * zones that claim the point.
     */
    int index( QPoint p, int& count ) const;
    /** @brief Get image of the zone claiming @p p
     *
     * Can return a null image, if the point is unclaimed or invalid.
     */
    QImage find( QPoint p ) const;

    /// @brief The **expected** number of zones in the list.
    static constexpr const int zoneCount = 37;
    /// @brief The expected size of each zone image.
    static constexpr const QSize imageSize = QSize( 780, 340 );
};

#endif
