/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "timezonewidget.h"

TimeZoneWidget::TimeZoneWidget(QWidget* parent) :
    QWidget(parent)
{
    setMouseTracking(false);
    setCursor(Qt::PointingHandCursor);

    // Font
    font.setPointSize(12);
    font.setBold(false);

    // Images
    background = QImage(":/images/bg.png").scaled(X_SIZE, Y_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    pin = QImage(":/images/pin.png");

    // Set size
    setMinimumSize(background.size());
    setMaximumSize(background.size());

    // Zone images
    QStringList zones = QString(ZONES).split(" ", QString::SkipEmptyParts);
    for (int i = 0; i < zones.size(); ++i)
        timeZoneImages.append(QImage(":/images/timezone_" + zones.at(i) + ".png").scaled(X_SIZE, Y_SIZE, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}


void TimeZoneWidget::setCurrentLocation(QString region, QString zone) {
    QHash<QString, QList<LocaleGlobal::Location> > hash = LocaleGlobal::getLocations();

    if (!hash.contains(region))
        return;

    QList<LocaleGlobal::Location> locations = hash.value(region);
    for (int i = 0; i < locations.size(); ++i) {
        if (locations.at(i).zone == zone) {
            setCurrentLocation(locations.at(i));
            break;
        }
    }
}



void TimeZoneWidget::setCurrentLocation(LocaleGlobal::Location location) {
    currentLocation = location;

    // Set zone
    QPoint pos = getLocationPosition(currentLocation.longitude, currentLocation.latitude);

    for (int i = 0; i < timeZoneImages.size(); ++i) {
        QImage zone = timeZoneImages[i];

        // If not transparent set as current
        if (zone.pixel(pos) != RGB_TRANSPARENT) {
            currentZoneImage = zone;
            break;
        }
    }

    // Repaint widget
    repaint();
}



//###
//### Private
//###


QPoint TimeZoneWidget::getLocationPosition(double longitude, double latitude) {
    const int width = this->width();
    const int height = this->height();

    double x = (width / 2.0 + (width / 2.0) * longitude / 180.0) + MAP_X_OFFSET * width;
    double y = (height / 2.0 - (height / 2.0) * latitude / 90.0) + MAP_Y_OFFSET * height;

    if (x < 0)
        x = width+x;
    if (x >= width)
        x -= width;
    if (y < 0)
        y = height+y;
    if (y >= height)
        y -= height;

    return QPoint( int(x), int(y) );
}



void TimeZoneWidget::paintEvent(QPaintEvent*) {
    const int width = this->width();
    const int height = this->height();
    QFontMetrics fontMetrics(font);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(font);

    // Draw background
    painter.drawImage(0, 0, background);

    // Draw zone image
    painter.drawImage(0, 0, currentZoneImage);

    // Draw pin
    QPoint point = getLocationPosition(currentLocation.longitude, currentLocation.latitude);
    painter.drawImage(point.x() - pin.width()/2, point.y() - pin.height()/2, pin);

    // Draw text and box
    const int textWidth = fontMetrics.width(LocaleGlobal::Location::pretty(currentLocation.zone));
    const int textHeight = fontMetrics.height();

    QRect rect = QRect(point.x() - textWidth/2 - 5, point.y() - textHeight - 8, textWidth + 10, textHeight - 2);

    if (rect.x() <= 5)
        rect.moveLeft(5);
    if (rect.right() >= width-5)
        rect.moveRight(width - 5);
    if (rect.y() <= 5)
        rect.moveTop(5);
    if (rect.y() >= height-5)
        rect.moveBottom(height-5);

    painter.setPen(QPen()); // no pen
    painter.setBrush(QColor(40, 40, 40));
    painter.drawRoundedRect(rect, 3, 3);
    painter.setPen(Qt::white);
    painter.drawText(rect.x() + 5, rect.bottom() - 4, LocaleGlobal::Location::pretty(currentLocation.zone));

    painter.end();
}



void TimeZoneWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() != Qt::LeftButton)
        return;

    // Set nearest location
    int nX = 999999, mX = event->pos().x();
    int nY = 999999, mY = event->pos().y();
    QHash<QString, QList<LocaleGlobal::Location> > hash = LocaleGlobal::getLocations();
    QHash<QString, QList<LocaleGlobal::Location> >::iterator iter = hash.begin();

    while (iter != hash.end()) {
        QList<LocaleGlobal::Location> locations = iter.value();

        for (int i = 0; i < locations.size(); ++i) {
            LocaleGlobal::Location loc = locations[i];
            QPoint locPos = getLocationPosition(loc.longitude, loc.latitude);

            if ((abs(mX - locPos.x()) + abs(mY - locPos.y())  <  abs(mX - nX) + abs(mY - nY))) {
                currentLocation = loc;
                nX = locPos.x();
                nY = locPos.y();
            }
        }

        ++iter;
    }

    // Set zone image and repaint widget
    setCurrentLocation(currentLocation);

    // Emit signal
    emit locationChanged(currentLocation);
}
