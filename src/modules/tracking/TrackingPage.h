/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#ifndef TRACKINGPAGE_H
#define TRACKINGPAGE_H

#include "TrackingType.h"

#include <QWidget>
#include <QUrl>

namespace Ui
{
class TrackingPage;
}

class TrackingPage : public QWidget
{
    Q_OBJECT
public:
    explicit TrackingPage( QWidget* parent = nullptr );

    /**
     * Enables or disables the tracking-option block for the given
     * tracking option @p t, and sets the initial state of the
     * checkbox to the @p user default.
     */
    void setTrackingOption( TrackingType t, bool setting, bool user );
    /**
     * Returns the state of the user checkbox for tracking option @p t.
     */
    bool getTrackingOption( TrackingType t );

    void setTrackingPolicy( TrackingType t, QString url );

private:
    Ui::TrackingPage* ui;
};

#endif //TRACKINGPAGE_H
