/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CONTEXTUALPROCESSJOB_H
#define CONTEXTUALPROCESSJOB_H

#include <QObject>
#include <QVariantMap>

#include "CppJob.h"
#include "DllMacro.h"

#include "utils/PluginFactory.h"

class ContextualProcessBinding;

class PLUGINDLLEXPORT ContextualProcessJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit ContextualProcessJob( QObject* parent = nullptr );
    ~ContextualProcessJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

    /// The number of bindings
    int count();
    /// The number of value-checks for the named binding (-1 if binding doesn't exist)
    int count( const QString& variableName );

private:
    QList< ContextualProcessBinding* > m_commands;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ContextualProcessJobFactory )

#endif  // CONTEXTUALPROCESSJOB_H
