/*
 *   Copyright 2016, Luca Giambonini <almack@chakraos.org>
 *   Copyright 2016, Lisa Vitolo     <shainer@chakraos.org>
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

#ifndef NETINSTALLVIEWSTEP_H
#define NETINSTALLVIEWSTEP_H

#include "Config.h"

#include "DllMacro.h"
#include "locale/TranslatableConfiguration.h"
#include "utils/PluginFactory.h"
#include "viewpages/ViewStep.h"

#include <QVariant>

class NetInstallPage;

class PLUGINDLLEXPORT NetInstallViewStep : public Calamares::ViewStep
{
    Q_OBJECT

public:
    explicit NetInstallViewStep( QObject* parent = nullptr );
    virtual ~NetInstallViewStep() override;

    QString prettyName() const override;

    QWidget* widget() override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    Calamares::JobList jobs() const override;

    void onActivate() override;

    // Leaving the page; store all selected packages for later installation.
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

public slots:
    void nextIsReady();

private:
    Config m_config;

    NetInstallPage* m_widget;
    CalamaresUtils::Locale::TranslatedString* m_sidebarLabel;  // As it appears in the sidebar
    bool m_nextEnabled = false;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( NetInstallViewStepFactory )

#endif  // NETINSTALLVIEWSTEP_H
