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

#ifndef PLASMALNFPAGE_H
#define PLASMALNFPAGE_H

#include <QButtonGroup>
#include <QList>
#include <QString>
#include <QStringList>
#include <QWidget>

#include "ThemeInfo.h"
#include "ThemeWidget.h"

namespace Ui
{
class PlasmaLnfPage;
}

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
    explicit PlasmaLnfPage( QWidget* parent = nullptr );

    void setLnfPath( const QString& path );
    /** @brief enable only the listed themes. */
    void setEnabledThemes( const ThemeInfoList& themes );
    /** @brief enable all installed plasma themes. */
    void setEnabledThemesAll();

signals:
    void plasmaThemeSelected( const QString& id );

private:
    /** @brief Intersect the list of enabled themes with the installed ones. */
    void winnowThemes();
    /** @brief Get the translated names for all enabled themes. */
    void updateThemeNames();
    /** @brief show enabled themes in the UI. */
    void fillUi();

    Ui::PlasmaLnfPage* ui;
    QString m_lnfPath;
    ThemeInfoList m_enabledThemes;

    QButtonGroup *m_buttonGroup;
    QList< ThemeWidget* > m_widgets;
};

#endif //PLASMALNFPAGE_H
