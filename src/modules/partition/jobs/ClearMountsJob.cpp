/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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
#include <utils/Logger.h>

#include <QProcess>
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


QString
ClearMountsJob::prettyStatusMessage() const
{
    return tr( "Clearing mounts for partitioning operations on %1." )
            .arg( m_device->deviceNode() );
}


Calamares::JobResult
ClearMountsJob::exec()
{
    QStringList goodNews;

    QString deviceName = m_device->deviceNode().split( '/' ).last();

    QProcess process;
    process.setProgram( "sh" );
    process.setArguments( {
                              "-c",
                              QString( "echo $(awk '{print $4}' /proc/partitions | sed -e '/name/d' -e '/^$/d' -e '/[1-9]/!d' | grep %1)" )
                                      .arg( deviceName )
                          } );
    process.start();
    process.waitForFinished();

    QString partitions = process.readAllStandardOutput();
    QStringList partitionsList = partitions.simplified().split( ' ' );

    // First we umount all LVM logical volumes we can find
    process.start( "lvscan", { "-a" } );
    process.waitForFinished();
    if ( process.exitCode() == 0 ) //means LVM2 tools are installed
    {
        QStringList lvscanLines = QString::fromLocal8Bit( process.readAllStandardOutput() ).split( '\n' );
        foreach ( const QString& lvscanLine, lvscanLines )
        {
            QString lvPath = lvscanLine.simplified().split( ' ' ).value( 1 ); //second column
            lvPath = lvPath.replace( '\'', "" );

            QString news = tryUmount( lvPath );
            if ( !news.isEmpty() )
                goodNews.append( news );
        }
    }
    else
        cDebug() << "WARNING: this system does not seem to have LVM2 tools.";

    // Then we go looking for volume groups that use this device for physical volumes
    process.start( "pvdisplay", { "-C", "--noheadings" } );
    process.waitForFinished();
    if ( process.exitCode() == 0 ) //means LVM2 tools are installed
    {
        QString pvdisplayOutput = process.readAllStandardOutput();
        if ( !pvdisplayOutput.simplified().isEmpty() ) //means there is at least one LVM PV
        {
            QSet< QString > vgSet;

            QStringList pvdisplayLines = pvdisplayOutput.split( '\n' );
            foreach ( const QString& pvdisplayLine, pvdisplayLines )
            {
                QString pvPath = pvdisplayLine.simplified().split( ' ' ).value( 0 );
                QString vgName = pvdisplayLine.simplified().split( ' ' ).value( 1 );
                if ( !pvPath.contains( deviceName ) )
                    continue;

                vgSet.insert( vgName );
            }

            foreach ( const QString& vgName, vgSet )
            {
                process.start( "vgchange", { "-an", vgName } );
                process.waitForFinished();
                if ( process.exitCode() == 0 )
                    goodNews.append( QString( "Successfully disabled volume group %1." ).arg( vgName ) );
            }
        }
    }
    else
        cDebug() << "WARNING: this system does not seem to have LVM2 tools.";

    foreach ( QString p, partitionsList )
    {
        QString partPath = QString( "/dev/%1" ).arg( p );

        QString news = tryUmount( partPath );
        if ( !news.isEmpty() )
            goodNews.append( news );
    }

    Calamares::JobResult ok = Calamares::JobResult::ok();
    ok.setMessage( tr( "Cleared all mounts for %1" )
                        .arg( m_device->deviceNode() ) );
    ok.setDetails( goodNews.join( "\n" ) );

    cDebug() << "ClearMountsJob finished. Here's what was done:\n" << goodNews.join( "\n" );

    return ok;
}


QString
ClearMountsJob::tryUmount( const QString& partPath )
{
    QProcess process;
    process.start( "umount", { partPath } );
    process.waitForFinished();
    if ( process.exitCode() == 0 )
        return QString( "Successfully unmounted %1." ).arg( partPath );

    process.start( "swapoff", { partPath } );
    process.waitForFinished();
    if ( process.exitCode() == 0 )
        return QString( "Successfully disabled swap %1." ).arg( partPath );

    return QString();
}
