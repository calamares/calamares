/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "core/PartitionInfo.h"
#include "core/PartitionIterator.h"
#include "utils/Logger.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/util/report.h>

#include <QDir>
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

    const QString partitions = process.readAllStandardOutput();
    const QStringList partitionsList = partitions.simplified().split( ' ' );

    // Build a list of partitions of type 82 (Linux swap / Solaris).
    // We then need to clear them just in case they contain something resumable from a
    // previous suspend-to-disk.
    QStringList swapPartitions;
    process.start( "sfdisk", { "-d", m_device->deviceNode() } );
    process.waitForFinished();
    // Sample output:
    //    % sudo sfdisk -d /dev/sda
    //    label: dos
    //    label-id: 0x000ced89
    //    device: /dev/sda
    //    unit: sectors

    //    /dev/sda1 : start=          63, size=    29329345, type=83, bootable
    //    /dev/sda2 : start=    29331456, size=     2125824, type=82

    swapPartitions = QString::fromLocal8Bit( process.readAllStandardOutput() )
                        .split( '\n' );
    swapPartitions = swapPartitions.filter( "type=82" );
    for ( QStringList::iterator it = swapPartitions.begin();
          it != swapPartitions.end(); ++it )
    {
        *it = (*it).simplified().split( ' ' ).first();
    }

    const QStringList cryptoDevices = getCryptoDevices();
    for ( const QString &mapperPath : cryptoDevices )
    {
        tryUmount( mapperPath );
        QString news = tryCryptoClose( mapperPath );
        if ( !news.isEmpty() )
            goodNews.append( news );
    }

    // First we umount all LVM logical volumes we can find
    process.start( "lvscan", { "-a" } );
    process.waitForFinished();
    if ( process.exitCode() == 0 ) //means LVM2 tools are installed
    {
        const QStringList lvscanLines = QString::fromLocal8Bit( process.readAllStandardOutput() ).split( '\n' );
        for ( const QString& lvscanLine : lvscanLines )
        {
            QString lvPath = lvscanLine.simplified().split( ' ' ).value( 1 ); //second column
            lvPath = lvPath.replace( '\'', "" );

            QString news = tryUmount( lvPath );
            if ( !news.isEmpty() )
                goodNews.append( news );
        }
    }
    else
        cWarning() << "this system does not seem to have LVM2 tools.";

    // Then we go looking for volume groups that use this device for physical volumes
    process.start( "pvdisplay", { "-C", "--noheadings" } );
    process.waitForFinished();
    if ( process.exitCode() == 0 ) //means LVM2 tools are installed
    {
        QString pvdisplayOutput = process.readAllStandardOutput();
        if ( !pvdisplayOutput.simplified().isEmpty() ) //means there is at least one LVM PV
        {
            QSet< QString > vgSet;

            const QStringList pvdisplayLines = pvdisplayOutput.split( '\n' );
            for ( const QString& pvdisplayLine : pvdisplayLines )
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
        cWarning() << "this system does not seem to have LVM2 tools.";

    const QStringList cryptoDevices2 = getCryptoDevices();
    for ( const QString &mapperPath : cryptoDevices2 )
    {
        tryUmount( mapperPath );
        QString news = tryCryptoClose( mapperPath );
        if ( !news.isEmpty() )
            goodNews.append( news );
    }

    for ( const QString &p : partitionsList )
    {
        QString partPath = QString( "/dev/%1" ).arg( p );

        QString news = tryUmount( partPath );
        if ( !news.isEmpty() )
            goodNews.append( news );
    }

    foreach ( QString p, swapPartitions )
    {
        QString news = tryClearSwap( p );
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


QString
ClearMountsJob::tryClearSwap( const QString& partPath )
{
    QProcess process;
    process.start( "blkid", { "-s", "UUID", "-o", "value", partPath } );
    process.waitForFinished();
    QString swapPartUuid = QString::fromLocal8Bit( process.readAllStandardOutput() ).simplified();
    if ( process.exitCode() != 0 ||
         swapPartUuid.isEmpty() )
        return QString();

    process.start( "mkswap", { "-U", swapPartUuid, partPath } );
    process.waitForFinished();
    if ( process.exitCode() != 0 )
        return QString();

    return QString( "Successfully cleared swap %1." ).arg( partPath );
}


QString
ClearMountsJob::tryCryptoClose( const QString& mapperPath )
{
    QProcess process;
    process.start( "cryptsetup", { "close", mapperPath } );
    process.waitForFinished();
    if ( process.exitCode() == 0 )
        return QString( "Successfully closed mapper device %1." ).arg( mapperPath );

    return QString();
}


QStringList
ClearMountsJob::getCryptoDevices() const
{
    QDir mapperDir( "/dev/mapper" );
    const QFileInfoList fiList = mapperDir.entryInfoList( QDir::Files );
    QStringList list;
    QProcess process;
    for ( const QFileInfo &fi : fiList )
    {
        if ( fi.baseName() == "control" )
            continue;
        list.append( fi.absoluteFilePath() );
    }
    return list;
}
