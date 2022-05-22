/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Luca Giambonini <almack@chakraos.org>
 *   SPDX-FileCopyrightText: 2016 Lisa Vitolo     <shainer@chakraos.org>
 *   SPDX-FileCopyrightText: 2017 Kyle Robbertze  <krobbertze@gmail.com>
 *   SPDX-FileCopyrightText: 2017-2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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
    ~NetInstallPage() override;

    void onActivate();

    /** @brief Expand entries that should be pre-expanded.
     *
     * Follows the *expanded* key / the startExpanded field in the
     * group entries of the model. Call this after filling up the model.
     */
    void expandGroups();

private:
    Config* m_config;
    Ui::Page_NetInst* ui;
};

#endif  // NETINSTALLPAGE_H
