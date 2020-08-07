/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
 *
 *   Originally from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
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

#ifndef TIMEZONEWIDGET_H
#define TIMEZONEWIDGET_H

#include "TimeZoneImage.h"

#include "locale/TimeZone.h"

#include <QFont>
#include <QWidget>

/** @brief The TimeZoneWidget shows a map and reports where clicks happen
 *
 * This widget shows a map (unspecified whether it's a whole world map
 * or can show regionsvia some kind of internal state). Mouse clicks are
 * translated into timezone locations (e.g. the zone for America/New_York).
 *
 * The current location can be changed programmatically, by name
 * or through a pointer to a location. If a pointer is used, take care
 * that the pointer is to a zone in the same model as used by the
 * widget.
 *
 * When a location is chosen -- by mouse click or programmatically --
 * the locationChanged() signal is emitted with the new location.
 *
 * NOTE: the widget currently uses the globally cached TZRegion::fromZoneTab()
 */
class TimeZoneWidget : public QWidget
{
    Q_OBJECT
public:
    using TimeZoneData = CalamaresUtils::Locale::TimeZoneData;

    explicit TimeZoneWidget( const CalamaresUtils::Locale::ZonesModel* zones, QWidget* parent = nullptr );

public Q_SLOTS:
    /** @brief Sets a location by pointer
     *
     * Pointer should be within the same model as the widget uses.
     */
    void setCurrentLocation( const TimeZoneData* location );

signals:
    /** @brief The location has changed by mouse click */
    void locationChanged( const TimeZoneData* location );

private:
    QFont font;
    QImage background, pin, currentZoneImage;
    TimeZoneImageList timeZoneImages;

    const CalamaresUtils::Locale::ZonesModel* m_zonesData;
    const TimeZoneData* m_currentLocation = nullptr;  // Not owned by me

    void paintEvent( QPaintEvent* event );
    void mousePressEvent( QMouseEvent* event );
};

#endif  // TIMEZONEWIDGET_H
