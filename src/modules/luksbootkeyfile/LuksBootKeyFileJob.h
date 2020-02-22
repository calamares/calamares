/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019, Adriaan de Groot <groot@kde.org>
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
    virtual ~LuksBootKeyFileJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( LuksBootKeyFileJobFactory )

#endif  // LUKSBOOTKEYFILEJOB_H
