/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Kevin Kofler <kevin.kofler@chello.at>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ClearMountsJob.h"

#include "core/PartitionInfo.h"

#include "partition/PartitionIterator.h"
#include "partition/Sync.h"
#include "utils/Logger.h"
#include "utils/String.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/util/report.h>

#include <QCoreApplication>
#include <QDir>
#include <QProcess>
#include <QStringList>

using CalamaresUtils::Partition::PartitionIterator;


/** @brief Returns list of partitions on a given @p deviceName
 *
 * The @p deviceName is a (whole-block) device, like "sda", and the partitions
 * returned are then "sdaX". The whole-block device itself is ignored, if
 * present. Partitions are returned with their full /dev/ path (e.g. /dev/sda1).
 *
 * The format for /etc/partitions is, e.g.
 *      major minor #blocks name
 *      8     0     33554422 sda
 *      8     1     33554400 sda1
 */
STATICTEST QStringList
getPartitionsForDevice( const QString& deviceName )
{
    QStringList partitions;

    QFile dev_partitions( "/proc/partitions" );
    if ( dev_partitions.open( QFile::ReadOnly ) )
    {
        cDebug() << "Reading from" << dev_partitions.fileName() << "looking for" << deviceName;
        QTextStream in( &dev_partitions );
        (void)in.readLine();  // That's the header line, skip it
        while ( !in.atEnd() )
        {
            // The fourth column (index from 0, so index 3) is the name of the device;
            // keep it if it is followed by something.
            QStringList columns = in.readLine().split( ' ', SplitSkipEmptyParts );
            if ( ( columns.count() >= 4 ) && ( columns[ 3 ].startsWith( deviceName ) )
                 && ( columns[ 3 ] != deviceName ) )
            {
                partitions.append( QStringLiteral( "/dev/" ) + columns[ 3 ] );
            }
        }
    }
    else
    {
        cDebug() << "Could not open" << dev_partitions.fileName();
    }

    return partitions;
}

STATICTEST QStringList
getSwapsForDevice( const QString& deviceName )
{
    QProcess process;

    // Build a list of partitions of type 82 (Linux swap / Solaris).
    // We then need to clear them just in case they contain something resumable from a
    // previous suspend-to-disk.
    QStringList swapPartitions;
    process.start( "sfdisk", { "-d", deviceName } );
    process.waitForFinished();
    // Sample output:
    //    % sudo sfdisk -d /dev/sda
    //    label: dos
    //    label-id: 0x000ced89
    //    device: /dev/sda
    //    unit: sectors

    //    /dev/sda1 : start=          63, size=    29329345, type=83, bootable
    //    /dev/sda2 : start=    29331456, size=     2125824, type=82

    swapPartitions = QString::fromLocal8Bit( process.readAllStandardOutput() ).split( '\n' );
    swapPartitions = swapPartitions.filter( "type=82" );
    for ( QStringList::iterator it = swapPartitions.begin(); it != swapPartitions.end(); ++it )
    {
        *it = ( *it ).simplified().split( ' ' ).first();
    }

    return swapPartitions;
}

static inline bool
isControl( const QString& baseName )
{
    return baseName == "control";
}

static inline bool
isFedoraSpecial( const QString& baseName )
{
    // Fedora live images use /dev/mapper/live-* internally. We must not
    // unmount those devices, because they are used by the live image and
    // because we need /dev/mapper/live-base in the unpackfs module.
    return baseName.startsWith( "live-" );
}

/** @brief Returns a list of unneeded crypto devices
 *
 * These are the crypto devices to unmount and close; some are "needed"
 * for system operation: on Fedora, the live- mappers are special.
 * Some other devices are special, too, so those do not end up in
 * the list.
 */
STATICTEST QStringList
getCryptoDevices( const QStringList& mapperExceptions )
{
    QDir mapperDir( "/dev/mapper" );
    const QFileInfoList fiList = mapperDir.entryInfoList( QDir::Files );
    QStringList list;
    for ( const QFileInfo& fi : fiList )
    {
        QString baseName = fi.baseName();
        if ( isControl( baseName ) || isFedoraSpecial( baseName ) || mapperExceptions.contains( baseName ) )
        {
            continue;
        }
        list.append( fi.absoluteFilePath() );
    }
    return list;
}

STATICTEST QStringList
getLVMVolumes()
{
    QProcess process;

    // First we umount all LVM logical volumes we can find
    process.start( "lvscan", { "-a" } );
    process.waitForFinished();
    if ( process.exitCode() == 0 )  //means LVM2 tools are installed
    {
        QStringList lvscanLines = QString::fromLocal8Bit( process.readAllStandardOutput() ).split( '\n' );
        // Get the second column (`value(1)`) sinec that is the device name,
        // remove quoting.
        std::transform( lvscanLines.begin(),
                        lvscanLines.end(),
                        lvscanLines.begin(),
                        []( const QString& lvscanLine )
                        { return lvscanLine.simplified().split( ' ' ).value( 1 ).replace( '\'', "" ); } );
        return lvscanLines;
    }
    else
    {
        cWarning() << "this system does not seem to have LVM2 tools.";
    }
    return QStringList();
}
STATICTEST QStringList
getPVGroups( const QString& deviceName )
{
    QProcess process;
    // Then we go looking for volume groups that use this device for physical volumes
    process.start( "pvdisplay", { "-C", "--noheadings" } );
    process.waitForFinished();
    if ( process.exitCode() == 0 )  //means LVM2 tools are installed
    {
        QString pvdisplayOutput = process.readAllStandardOutput();
        if ( !pvdisplayOutput.simplified().isEmpty() )  //means there is at least one LVM PV
        {
            QSet< QString > vgSet;

            const QStringList pvdisplayLines = pvdisplayOutput.split( '\n' );
            for ( const QString& pvdisplayLine : pvdisplayLines )
            {
                QString pvPath = pvdisplayLine.simplified().split( ' ' ).value( 0 );
                QString vgName = pvdisplayLine.simplified().split( ' ' ).value( 1 );
                if ( !pvPath.contains( deviceName ) )
                {
                    continue;
                }

                vgSet.insert( vgName );
            }
// toList() was deprecated, but old-old versions don't support QStringList construction like this
#if QT_VERSION < QT_VERSION_CHECK( 5, 15, 0 )
            return vgSet.toList();
#else
            return QStringList { vgSet.cbegin(), vgSet.cend() };
#endif
        }
    }
    else
    {
        cWarning() << "this system does not seem to have LVM2 tools.";
    }
    return QStringList();
}

/*
 * The tryX() free functions, below, return an empty QString on
 * failure, or a non-empty QString on success. The string is
 * meant **only** for debugging and is not displayed to the user,
 * which is why no translation is applied.
 *
 * The MessageAndPath class stores a C-style pointer to a character
 * array -- from QT_TRANSLATE_NOOP() -- and a path to substitute into it.
 *
 * When the tryX() functions return an "empty string", it is an
 * empty MessageAndPath which acts like an empty string (in particular,
 * isEmpty() is true).
 */

class MessageAndPath
{
public:
    ///@brief An unsuccessful attempt at something
    MessageAndPath() {}
    ///@brief A success at doing @p thing to @p path
    MessageAndPath( const char* thing, const QString& path )
        : m_message( thing )
        , m_path( path )
    {
    }

    bool isEmpty() const { return !m_message; }

    explicit operator QString() const
    {
        return isEmpty() ? QString() : QCoreApplication::translate( "ClearMountsJob", m_message ).arg( m_path );
    }

private:
    const char* m_message = nullptr;
    QString m_path;
};

STATICTEST inline QDebug&
operator<<( QDebug& s, const MessageAndPath& m )
{
    if ( m.isEmpty() )
    {
        return s;
    }
    return s << QString( m );
}


///@brief Returns a debug-string if @p partPath could be unmounted
STATICTEST MessageAndPath
tryUmount( const QString& partPath )
{
    QProcess process;
    process.start( "umount", { partPath } );
    process.waitForFinished();
    if ( process.exitCode() == 0 )
    {
        return { QT_TRANSLATE_NOOP( "ClearMountsJob", "Successfully unmounted %1." ), partPath };
    }

    process.start( "swapoff", { partPath } );
    process.waitForFinished();
    if ( process.exitCode() == 0 )
    {
        return { QT_TRANSLATE_NOOP( "ClearMountsJob", "Successfully disabled swap %1." ), partPath };
    }

    return {};
}

///@brief Returns a debug-string if @p partPath was swap and could be cleared
STATICTEST MessageAndPath
tryClearSwap( const QString& partPath )
{
    QProcess process;
    process.start( "blkid", { "-s", "UUID", "-o", "value", partPath } );
    process.waitForFinished();
    QString swapPartUuid = QString::fromLocal8Bit( process.readAllStandardOutput() ).simplified();
    if ( process.exitCode() != 0 || swapPartUuid.isEmpty() )
    {
        return {};
    }

    process.start( "mkswap", { "-U", swapPartUuid, partPath } );
    process.waitForFinished();
    if ( process.exitCode() != 0 )
    {
        return {};
    }

    return { QT_TRANSLATE_NOOP( "ClearMountsJob", "Successfully cleared swap %1." ), partPath };
}

///@brief Returns a debug-string if @p mapperPath could be closed
STATICTEST MessageAndPath
tryCryptoClose( const QString& mapperPath )
{
    /* ignored */ tryUmount( mapperPath );

    QProcess process;
    process.start( "cryptsetup", { "close", mapperPath } );
    process.waitForFinished();
    if ( process.exitCode() == 0 )
    {
        return { QT_TRANSLATE_NOOP( "ClearMountsJob", "Successfully closed mapper device %1." ), mapperPath };
    }

    return {};
}

STATICTEST MessageAndPath
tryVGDisable( const QString& vgName )
{
    QProcess vgProcess;
    vgProcess.start( "vgchange", { "-an", vgName } );
    vgProcess.waitForFinished();
    return ( vgProcess.exitCode() == 0 )
        ? MessageAndPath { QT_TRANSLATE_NOOP( "ClearMountsJob", "Successfully disabled volume group %1." ), vgName }
        : MessageAndPath {};
}

///@brief Apply @p f to all the @p paths, appending successes to @p news
template < typename F >
void
apply( const QStringList& paths, F f, QList< MessageAndPath >& news )
{
    for ( const QString& p : qAsConst( paths ) )
    {
        auto n = f( p );
        if ( !n.isEmpty() )
        {
            news.append( n );
        }
    }
}

STATICTEST QStringList
stringify( const QList< MessageAndPath >& news )
{
    QStringList l;
    for ( const auto& m : qAsConst( news ) )
    {
        l << QString( m );
    }
    return l;
}

ClearMountsJob::ClearMountsJob( Device* device )
    : Calamares::Job()
    , m_deviceNode( device->deviceNode() )
{
}

QString
ClearMountsJob::prettyName() const
{
    return tr( "Clear mounts for partitioning operations on %1" ).arg( m_deviceNode );
}

QString
ClearMountsJob::prettyStatusMessage() const
{
    return tr( "Clearing mounts for partitioning operations on %1." ).arg( m_deviceNode );
}

Calamares::JobResult
ClearMountsJob::exec()
{
    const QString deviceName = m_deviceNode.split( '/' ).last();
    CalamaresUtils::Partition::Syncer s;
    QList< MessageAndPath > goodNews;

    apply( getCryptoDevices( m_mapperExceptions ), tryCryptoClose, goodNews );
    apply( getLVMVolumes(), tryUmount, goodNews );
    apply( getPVGroups( deviceName ), tryVGDisable, goodNews );

    apply( getCryptoDevices( m_mapperExceptions ), tryCryptoClose, goodNews );
    apply( getPartitionsForDevice( deviceName ), tryUmount, goodNews );
    apply( getSwapsForDevice( m_deviceNode ), tryClearSwap, goodNews );

    Calamares::JobResult ok = Calamares::JobResult::ok();
    ok.setMessage( tr( "Cleared all mounts for %1" ).arg( m_deviceNode ) );
    ok.setDetails( stringify( goodNews ).join( "\n" ) );
    cDebug() << "ClearMountsJob finished. Here's what was done:" << Logger::DebugListT< MessageAndPath >( goodNews );

    return ok;
}
