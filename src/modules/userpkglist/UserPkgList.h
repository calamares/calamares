/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Evan James <dalto@fastmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef USERPKGLISTJOB_H
#define USERPKGLISTJOB_H

#include <QObject>
#include <QStringList>
#include <QVariantMap>

#include "CppJob.h"

#include "utils/PluginFactory.h"

#include "DllMacro.h"

/** @brief Loads user packages into global storage
 *
 */
class PLUGINDLLEXPORT UserPkgListJob : public Calamares::CppJob
{
    Q_OBJECT

public:
    explicit UserPkgListJob( QObject* parent = nullptr );
    ~UserPkgListJob() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( UserPkgListJobFactory )

#endif  // USERPKGLISTJOB_H
