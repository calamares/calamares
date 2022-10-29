/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Evan James <dalto@fastmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "UserPkgList.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include <QFile>
#include <QProcess>

#include <unistd.h>


UserPkgListJob::UserPkgListJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

UserPkgListJob::~UserPkgListJob() {}

QString
UserPkgListJob::prettyName() const
{
    return QStringLiteral( " " );
}


Calamares::JobResult
UserPkgListJob::exec()
{
    return Calamares::JobResult::ok();
}


static QVariantMap
getNetinstallData( const QStringList& packages, const QVariantMap& map )
{
    return { { "source", "userPkgList" },
             { "name", CalamaresUtils::getString( map, "netinstall_name", "Custom Packages" ) },
             { "description", CalamaresUtils::getString( map, "netinstall_desc", "The custom packagelist defined" ) },
             { "hidden", false },
             { "selected", true },
             { "critical", false },
             { "packages", packages } };
}


void
UserPkgListJob::setConfigurationMap( const QVariantMap& map )
{
    // Get the file location from the configuration file
    QString fileLocation = CalamaresUtils::getString( map, "file_location" );

    // Open the file
    QFile packagesFile( fileLocation );
    if ( !packagesFile.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        cWarning() << "User packagelist file" << fileLocation << "not found";
        return;
    }

    QStringList packages;
    QTextStream packageStream( &packagesFile );
    while ( !packageStream.atEnd() )
    {
        QString line = packageStream.readLine();
        if ( !line.trimmed().isEmpty() && !line.trimmed().startsWith( "#" ) )
        {
            packages.append( line.trimmed() );
        }
    }

    // Turn the packages list into a structure suitable for netinstall and load it into global storage
    if ( !packages.isEmpty() )
    {
        cDebug() << "Loading custom user package list.  Packages: " << packages.join(" ");
        QVariantList netinstallList = { getNetinstallData( packages, map ) };
        Calamares::JobQueue::instance()->globalStorage()->insert( "netinstallAdd", netinstallList );
    }
}


CALAMARES_PLUGIN_FACTORY_DEFINITION( UserPkgListJobFactory, registerPlugin< UserPkgListJob >(); )
