/* === This file is part of Calamares - <https://calamares.io> ===
 *
 * Tags from the Python version of this module:
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2016 Anke Boersma <demm@kaosx.us>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 * Tags for the C++ version of this module:
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "UmountJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QFile>


UmountJob::UmountJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

UmountJob::~UmountJob() {}

QString
UmountJob::prettyName() const
{
    return tr( "Unmount file systems." );
}

Calamares::JobResult
UmountJob::exec()
{
    return Calamares::JobResult::ok();
}

void
UmountJob::setConfigurationMap( const QVariantMap& map )
{
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( UmountJobFactory, registerPlugin< UmountJob >(); )
