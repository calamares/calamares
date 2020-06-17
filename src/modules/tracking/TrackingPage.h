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

#include <QCheckBox>
#include <QUrl>
#include <QWidget>

namespace Ui
{
class TrackingPage;
}

class Config;
class TrackingStyleConfig;

class TrackingPage : public QWidget
{
    Q_OBJECT
public:
    explicit TrackingPage( Config* config, QWidget* parent = nullptr );

    /** @brief is any of the enable-tracking buttons checked?
     *
     * Returns true if any one or more of install, machine or user
     * tracking is enabled.
     */
    bool anyOtherChecked() const;

public Q_SLOTS:
    void retranslate();

    /** @brief When the *no tracking* checkbox is changed
     *
     * @p state will be non-zero when the box is checked; this
     * **unchecks** all the other boxes.
     */
    void buttonNoneChecked( int state );

    /** @brief Some other checkbox changed
     *
     * This may check the *none* button if all the others are
     * now unchecked.
     */
    void buttonChecked( int state );

private:
    /** @brief Apply the tracking configuration to the UI
     *
     * If the config cannot be changed (disabled in config) then
     * hide the UI parts on the @p panel; otherwise show it
     * and set @p check state to whether the user has enabled it.
     */
    void trackerChanged( TrackingStyleConfig* subconfig, QWidget* panel, QCheckBox* check );

    Ui::TrackingPage* ui;
};

#endif  //TRACKINGPAGE_H
