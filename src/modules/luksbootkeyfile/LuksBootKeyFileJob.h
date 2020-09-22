/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef LUKSBOOTKEYFILEJOB_H
#define LUKSBOOTKEYFILEJOB_H

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/PluginFactory.h"

#include <QObject>
#include <QVariantMap>

/** @brief Creates the LUKS boot key file and adds it to the cryptsetup.
 *
 * This job has no configuration, because it takes everything
 * from the global storage settings set by others.
 */
class PLUGINDLLEXPORT LuksBootKeyFileJob : public Calamares::CppJob
{
    Q_OBJECT
public:
    explicit LuksBootKeyFileJob( QObject* parent = nullptr );
    ~LuksBootKeyFileJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( LuksBootKeyFileJobFactory )

#endif  // LUKSBOOTKEYFILEJOB_H
