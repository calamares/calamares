/* === This file is part of Calamares - <https://github.com/calamares> ===
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
     *
     * Call this in ascending order of tracking type.
     */
    void enableTrackingOption( TrackingType t, bool enabled );
    /**
     * Returns whether tracking type @p is selected by the user
     * (i.e. is the radio button for that level, or for a higher
     * tracking level, enabled).
     */
    bool getTrackingOption( TrackingType t );

    /* URL for given level @p t */
    void setTrackingPolicy( TrackingType t, QString url );
    /* URL for the global link */
    void setGeneralPolicy( QString url );
    /* Select one of the four levels by name */
    void setTrackingLevel( const QString& level );

private:
    Ui::TrackingPage* ui;
};

#endif //TRACKINGPAGE_H
