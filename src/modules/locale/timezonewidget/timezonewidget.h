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

class TimeZoneWidget : public QWidget
{
    Q_OBJECT
public:
    using TZZone = CalamaresUtils::Locale::TZZone;

    explicit TimeZoneWidget( QWidget* parent = nullptr );

    void setCurrentLocation( QString region, QString zone );
    void setCurrentLocation( const TZZone* location );
    const TZZone* currentLocation() { return m_currentLocation; }


signals:
    void locationChanged( const TZZone* location );

private:
    QFont font;
    QImage background, pin, currentZoneImage;
    TimeZoneImageList timeZoneImages;
    const TZZone* m_currentLocation = nullptr;  // Not owned by me

    QPoint getLocationPosition( const TZZone* l )
    {
        return timeZoneImages.getLocationPosition( l->longitude(), l->latitude() );
    }

    void paintEvent( QPaintEvent* event );
    void mousePressEvent( QMouseEvent* event );
};

#endif  // TIMEZONEWIDGET_H
