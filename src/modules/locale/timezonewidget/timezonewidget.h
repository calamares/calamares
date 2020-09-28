/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2007 Free Software Foundation, Inc.
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Originally from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

    void paintEvent( QPaintEvent* event ) override;
    void mousePressEvent( QMouseEvent* event ) override;
};

#endif  // TIMEZONEWIDGET_H
