/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "IDJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include "utils/Logger.h"

#include <QDir>
#include <QFile>

IDJob::IDJob( const QString& id, QObject* parent )
    : Job( parent )
    , m_batchIdentifier( id )
{
}

QString
IDJob::prettyName() const
{
    return tr( "OEM Batch Identifier" );
}

Calamares::JobResult
IDJob::writeId( const QString& dirs, const QString& filename, const QString& contents )
{
    if ( !QDir().mkpath( dirs ) )
    {
        cError() << "Could not create directories" << dirs;
        return Calamares::JobResult::error( tr( "OEM Batch Identifier" ),
                                            tr( "Could not create directories <code>%1</code>." ).arg( dirs ) );
    }

    QFile output( QDir( dirs ).filePath( filename ) );
    if ( output.exists() )
    {
        cWarning() << "Existing OEM Batch ID" << output.fileName() << "overwritten.";
    }

    if ( !output.open( QIODevice::WriteOnly ) )
    {
        cError() << "Could not write to" << output.fileName();
        return Calamares::JobResult::error( tr( "OEM Batch Identifier" ),
                                            tr( "Could not open file <code>%1</code>." ).arg( output.fileName() ) );
    }

    if ( output.write( contents.toUtf8() ) < 0 )
    {
        cError() << "Write error on" << output.fileName();
        return Calamares::JobResult::error( tr( "OEM Batch Identifier" ),
                                            tr( "Could not write to file <code>%1</code>." ).arg( output.fileName() ) );
    }
    output.write( "\n" );  // Ignore error on this one

    return Calamares::JobResult::ok();
}

Calamares::JobResult
IDJob::exec()
{
    cDebug() << "Setting OEM Batch ID to" << m_batchIdentifier;

    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    QString targetDir = QStringLiteral( "/var/log/installer/" );
    QString targetFile = QStringLiteral( "oem-id" );
    QString rootMount = gs->value( "rootMountPoint" ).toString();

    // Don't bother translating internal errors
    if ( rootMount.isEmpty() && Calamares::Settings::instance()->doChroot() )
        return Calamares::JobResult::internalError( "OEM Batch Identifier",
                                                    "No rootMountPoint is set, but a chroot is required. "
                                                    "Is there a module before oemid that sets up the partitions?",
                                                    Calamares::JobResult::InvalidConfiguration );
    return writeId( Calamares::Settings::instance()->doChroot() ? rootMount + targetDir : targetDir,
                    targetFile,
                    m_batchIdentifier );
}
