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
    /** @brief enable only the listed themes.
     *
     * Shows the listed @p themes with full information (e.g. screenshot).
     * If @p showAll is true, then also show all installed themes
     * not explicitly listed (without a screenshot).
     */
    void setEnabledThemes( const ThemeInfoList& themes, bool showAll );
    /** @brief enable all installed plasma themes. */
    void setEnabledThemesAll();
    /** @brief set which theme is to be preselected. */
    void setPreselect( const QString& id );

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
    QString m_preselect;
    bool m_showAll;  // If true, don't winnow according to enabledThemes
    ThemeInfoList m_enabledThemes;

    QButtonGroup* m_buttonGroup;
    QList< ThemeWidget* > m_widgets;
};

#endif  //PLASMALNFPAGE_H
