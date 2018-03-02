/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#ifndef CONTEXTUALPROCESSJOB_H
#define CONTEXTUALPROCESSJOB_H

#include <QObject>
#include <QVariantMap>

#include "CppJob.h"
#include "PluginDllMacro.h"

#include "utils/PluginFactory.h"

struct ContextualProcessBinding;

class PLUGINDLLEXPORT ContextualProcessJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit ContextualProcessJob( QObject* parent = nullptr );
    virtual ~ContextualProcessJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    /// The number of bindings
    int count();
    /// The number of value-checks for the named binding (-1 if binding doesn't exist)
    int count( const QString& variableName );

private:
    QList<ContextualProcessBinding*> m_commands;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ContextualProcessJobFactory )

#endif // CONTEXTUALPROCESSJOB_H
