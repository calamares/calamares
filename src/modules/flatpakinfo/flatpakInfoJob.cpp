/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Evan James <dalto@fastmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "flatpakInfoJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include <QProcess>

#include <unistd.h>

#include "PackagePool.h"

FlatpakInfoJob::FlatpakInfoJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

FlatpakInfoJob::~FlatpakInfoJob() {}

QString
FlatpakInfoJob::prettyName() const
{
    return tr( "Fill netinstall with flatpak packages" );
}


Calamares::JobResult
FlatpakInfoJob::exec()
{
    QVariantList partitions;
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();


    downloadPackagesInfo();

    return Calamares::JobResult::ok();
}


void
FlatpakInfoJob::setConfigurationMap( const QVariantMap& map )
{

}

CALAMARES_PLUGIN_FACTORY_DEFINITION( FlatpakInfoJobFactory, registerPlugin< FlatpakInfoJob >(); )
