/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
