/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef SHELLPROCESSJOB_H
#define SHELLPROCESSJOB_H

#include "CppJob.h"
#include "DllMacro.h"

#include "locale/TranslatableConfiguration.h"
#include "utils/CommandList.h"
#include "utils/PluginFactory.h"

#include <QObject>
#include <QVariantMap>

#include <memory>

class PLUGINDLLEXPORT ShellProcessJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit ShellProcessJob( QObject* parent = nullptr );
    ~ShellProcessJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    std::unique_ptr< CalamaresUtils::CommandList > m_commands;
    std::unique_ptr< CalamaresUtils::Locale::TranslatedString > m_name;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( ShellProcessJobFactory )

#endif  // SHELLPROCESSJOB_H
