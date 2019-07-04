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

#include "LuksBootKeyFileJob.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include "GlobalStorage.h"
#include "JobQueue.h"

LuksBootKeyFileJob::LuksBootKeyFileJob( QObject* parent )
    : Calamares::CppJob( parent )
{
}

LuksBootKeyFileJob::~LuksBootKeyFileJob() {}

QString
LuksBootKeyFileJob::prettyName() const
{
    return tr( "Configuring LUKS key file." );
}

struct LuksPassphrase
{
    QString device;
    QString passphrase;
};

struct GlobalSettings
{
    GlobalSettings( const QVariant& partitions )
        : valid( false )
    {
        if ( partitions.canConvert<QVariantList>() )
        {
            filesystems = getPartitionInfo( partitions.toList() );
            valid = true;
        }
    }

    /** @brief Extract the luks passphrases setup.
     *
     * Given a list of partitions (as set up by the partitioning module,
     * so there's maps with keys inside), returns just the list of
     * luks passphrases for each device.
     */
    static QList< LuksPassphrase > getPartitionInfo( const QVariantList& list )
    {
        int count = 0;
        for( const auto& p : list )
        {
            if ( p.canConvert< QVariantMap>() )
            {
                auto pinfo = p.toMap();
                QString device = pinfo["device"].toString();
                QString fs = pinfo["fs"].toString();
                QString mountPoint = pinfo["mountPoint"].toString();
                QString uuid = pinfo["uuid"].toString();

                cDebug() << count << "D=" << device << mountPoint << '(' << fs << ')';
            }
            count++;
        }
        return QList< LuksPassphrase >();
    }

    QList< LuksPassphrase > filesystems;
    bool valid;
};

Calamares::JobResult
LuksBootKeyFileJob::exec()
{
    const auto* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( !gs )
    {
        return Calamares::JobResult::internalError(
            "LukeBootKeyFile", "No GlobalStorage defined.", Calamares::JobResult::InvalidConfiguration );
    }
    if ( !gs->contains( "partitions" ) )
    {
        return Calamares::JobResult::internalError(
            "LukeBootKeyFile",
            tr( "No partitions are defined for LUKS to use." ).arg( "luksbootkeyfile" ),
            Calamares::JobResult::InvalidConfiguration );
    }

    GlobalSettings s( gs->value( "partitions" ) );
    return Calamares::JobResult::ok();
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( LuksBootKeyFileJobFactory, registerPlugin< LuksBootKeyFileJob >(); )
