/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "ClearMountsJob.h"

#include <core/device.h>
#include <core/partition.h>
#include <core/PartitionInfo.h>
#include <core/PartitionIterator.h>
#include <util/report.h>

#include <QStringList>


ClearMountsJob::ClearMountsJob( Device* device )
    : Calamares::Job()
    , m_device( device )
{
}


QString
ClearMountsJob::prettyName() const
{
    return tr( "Clear mounts for partitioning operations on %1" )
            .arg( m_device->deviceNode() );
}


Calamares::JobResult
ClearMountsJob::exec()
{
    QStringList goodNews;
    for ( auto it = PartitionIterator::begin( m_device );
          it != PartitionIterator::end( m_device ); ++it )
    {
        if ( (*it)->isMounted() )
        {
            if ( (*it)->canUnmount() )
            {
                Report report( 0, QString() );
                (*it)->unmount( report );
                goodNews.append( report.toText() );
            }
            else
            {
                return Calamares::JobResult::error( tr( "Cannot umount partition %1" )
                                                        .arg( (*it)->deviceNode() ),
                                                    tr( "Cannot proceed with partitioning operations "
                                                        "because some partitions are still mounted." ) );
            }
        }
    }
    Calamares::JobResult ok = Calamares::JobResult::ok();
    ok.setMessage( tr( "Cleared all mounts for %1" )
                        .arg( m_device->deviceNode() ) );
    ok.setDetails( goodNews.join( "\n" ) );
    return ok;
}
