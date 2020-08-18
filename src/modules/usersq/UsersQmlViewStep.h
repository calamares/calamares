/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
 *   Copyright 2020, Camilo Higuita <milo.h@aol.com>
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

#ifndef USERSQMLVIEWSTEP_H
#define USERSQMLVIEWSTEP_H

#include <QObject>

#include <utils/PluginFactory.h>
#include <viewpages/QmlViewStep.h>

#include <DllMacro.h>

#include <QVariant>
#include "Config.h"

class PLUGINDLLEXPORT UsersQmlViewStep : public Calamares::QmlViewStep
{
    Q_OBJECT

public:
    explicit UsersQmlViewStep( QObject* parent = nullptr );

    QString prettyName() const override;

    bool isNextEnabled() const override;
    bool isBackEnabled() const override;

    bool isAtBeginning() const override;
    bool isAtEnd() const override;

    QList< Calamares::job_ptr > jobs() const override;

    void onActivate() override;
    void onLeave() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    QObject * getConfig() override
    {
        return m_config;
    }

private:
    Config *m_config;
    Calamares::JobList m_jobs;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( UsersQmlViewStepFactory )

#endif  // USERSQMLVIEWSTEP_H
