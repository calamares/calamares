/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PLASMALNFPAGE_H
#define PLASMALNFPAGE_H

#include <QWidget>

namespace Ui
{
class PlasmaLnfPage;
}

class Config;

/** @brief Page for selecting a Plasma Look-and-Feel theme.
 *
 * You must call setEnabledThemes -- either overload -- once
 * to get the selection widgets. Note that calling that with
 * an empty list will result in zero (0) selectable themes.
 */
class PlasmaLnfPage : public QWidget
{
    Q_OBJECT
public:
    explicit PlasmaLnfPage( Config* config, QWidget* parent = nullptr );

private:
    Ui::PlasmaLnfPage* ui;
    Config* m_config;
};

#endif  //PLASMALNFPAGE_H
