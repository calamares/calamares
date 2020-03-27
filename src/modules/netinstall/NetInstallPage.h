/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
 *   Copyright 2017, Kyle Robbertze  <krobbertze@gmail.com>
 *   Copyright 2017-2018, 2020, Adriaan de Groot <groot@kde.org>
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

#ifndef NETINSTALLPAGE_H
#define NETINSTALLPAGE_H

#include "Config.h"
#include "PackageModel.h"
#include "PackageTreeItem.h"

#include "locale/TranslatableConfiguration.h"

#include <QString>
#include <QWidget>

#include <memory>

class QNetworkReply;

namespace Ui
{
class Page_NetInst;
}

class NetInstallPage : public QWidget
{
    Q_OBJECT
public:
    NetInstallPage( Config* config, QWidget* parent = nullptr );
    virtual ~NetInstallPage();

    /** @brief Sets the page title
     *
     * In situations where there is more than one netinstall page,
     * or you want some explanatory title above the treeview,
     * set the page title. This page takes ownership of the
     * TranslatedString object.
     *
     * Set to nullptr to remove the title.
     */
    void setPageTitle( CalamaresUtils::Locale::TranslatedString* );

    void onActivate();

public slots:
    void retranslate();
    void setStatus( QString s );

    /** @brief Expand entries that should be pre-expanded.
     *
     * Follows the *expanded* key / the startExpanded field in the
     * group entries of the model. Call this after filling up the model.
     */
    void expandGroups();

private:
    Config* m_config;
    Ui::Page_NetInst* ui;

    std::unique_ptr< CalamaresUtils::Locale::TranslatedString > m_title;  // Above the treeview
};

#endif  // NETINSTALLPAGE_H
