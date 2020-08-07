/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020 Adriaan de Groot <groot@kde.org>
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

#ifndef LOCALE_QMLVIEWSTEP_H
#define LOCALE_QMLVIEWSTEP_H

#include "Config.h"

#include "DllMacro.h"
#include "utils/PluginFactory.h"
#include "viewpages/QmlViewStep.h"

#include <memory>

class PLUGINDLLEXPORT LocaleQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit LocaleQmlViewStep( QObject* parent = nullptr );

    QString prettyName() const override;
    QString prettyStatus() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    virtual void onActivate() override;
    virtual void onLeave() override;

    Calamares::JobList jobs() const override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;
    QObject* getConfig() override;

private:
    std::unique_ptr< Config > m_config;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( LocaleQmlViewStepFactory )

#endif
