/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
