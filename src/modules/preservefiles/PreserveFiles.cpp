/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "PreserveFiles.h"

#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/CommandList.h"
#include "utils/Logger.h"
#include "utils/Permissions.h"
#include "utils/Units.h"

#include <QFile>

using namespace CalamaresUtils::Units;

QString
targetPrefix()
{
    if ( CalamaresUtils::System::instance()->doChroot() )
    {
        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        if ( gs && gs->contains( "rootMountPoint" ) )
        {
            QString r = gs->value( "rootMountPoint" ).toString();
            if ( !r.isEmpty() )
            {
                return r;
            }
            else
            {
                cDebug() << "RootMountPoint is empty";
            }
        }
        else
        {
            cDebug() << "No rootMountPoint defined, preserving files to '/'";
        }
    }

    return QLatin1String( "/" );
}

QString
atReplacements( QString s )
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QString root( "/" );
    QString user;

    if ( gs && gs->contains( "rootMountPoint" ) )
    {
        root = gs->value( "rootMountPoint" ).toString();
    }
    if ( gs && gs->contains( "username" ) )
    {
        user = gs->value( "username" ).toString();
    }

    return s.replace( "@@ROOT@@", root ).replace( "@@USER@@", user );
}

PreserveFiles::PreserveFiles( QObject* parent )
    : Calamares::CppJob( parent )
{
}

PreserveFiles::~PreserveFiles() {}

QString
PreserveFiles::prettyName() const
{
    return tr( "Saving files for later ..." );
}

static bool
copy_file( const QString& source, const QString& dest )
{
    QFile sourcef( source );
    if ( !sourcef.open( QFile::ReadOnly ) )
    {
        cWarning() << "Could not read" << source;
        return false;
    }

    QFile destf( dest );
    if ( !destf.open( QFile::WriteOnly ) )
    {
        sourcef.close();
        cWarning() << "Could not open" << destf.fileName() << "for writing; could not copy" << source;
        return false;
    }

    QByteArray b;
    do
    {
        b = sourcef.read( 1_MiB );
        destf.write( b );
    } while ( b.count() > 0 );

    sourcef.close();
    destf.close();

    return true;
}

Calamares::JobResult
PreserveFiles::exec()
{
    if ( m_items.isEmpty() )
    {
        return Calamares::JobResult::error( tr( "No files configured to save for later." ) );
    }

    QString prefix = targetPrefix();
    if ( !prefix.endsWith( '/' ) )
    {
        prefix.append( '/' );
    }

    int count = 0;
    for ( const auto& it : m_items )
    {
        QString source = it.source;
        QString bare_dest = atReplacements( it.dest );
        QString dest = prefix + bare_dest;

        if ( it.type == ItemType::Log )
        {
            source = Logger::logFile();
        }
        if ( it.type == ItemType::Config )
        {
            if ( !Calamares::JobQueue::instance()->globalStorage()->saveJson( dest ) )
            {
                cWarning() << "Could not write a JSON dump of global storage to" << dest;
            }
            else
            {
                ++count;
            }
        }
        else if ( source.isEmpty() )
        {
            cWarning() << "Skipping unnamed source file for" << dest;
        }
        else
        {
            if ( copy_file( source, dest ) )
            {
                if ( it.perm.isValid() )
                {
                    if ( !it.perm.apply( CalamaresUtils::System::instance()->targetPath( bare_dest ) ) )
                    {
                        cWarning() << "Could not set attributes of" << bare_dest;
                    }
                }

                ++count;
            }
        }
    }

    return count == m_items.count()
        ? Calamares::JobResult::ok()
        : Calamares::JobResult::error( tr( "Not all of the configured files could be preserved." ) );
}

void
PreserveFiles::setConfigurationMap( const QVariantMap& configurationMap )
{
    auto files = configurationMap[ "files" ];
    if ( !files.isValid() )
    {
        cDebug() << "No 'files' key for preservefiles.";
        return;
    }

    if ( files.type() != QVariant::List )
    {
        cDebug() << "Configuration key 'files' is not a list for preservefiles.";
        return;
    }

    QString defaultPermissions = configurationMap[ "perm" ].toString();
    if ( defaultPermissions.isEmpty() )
    {
        defaultPermissions = QStringLiteral( "root:root:0400" );
    }

    QVariantList l = files.toList();
    unsigned int c = 0;
    for ( const auto& li : l )
    {
        if ( li.type() == QVariant::String )
        {
            QString filename = li.toString();
            if ( !filename.isEmpty() )
                m_items.append(
                    Item { filename, filename, CalamaresUtils::Permissions( defaultPermissions ), ItemType::Path } );
            else
            {
                cDebug() << "Empty filename for preservefiles, item" << c;
            }
        }
        else if ( li.type() == QVariant::Map )
        {
            const auto map = li.toMap();
            QString dest = map[ "dest" ].toString();
            QString from = map[ "from" ].toString();
            ItemType t = ( from == "log" ) ? ItemType::Log : ( from == "config" ) ? ItemType::Config : ItemType::None;
            QString perm = map[ "perm" ].toString();
            if ( perm.isEmpty() )
            {
                perm = defaultPermissions;
            }

            if ( dest.isEmpty() )
            {
                cDebug() << "Empty dest for preservefiles, item" << c;
            }
            else if ( t == ItemType::None )
            {
                cDebug() << "Invalid type for preservefiles, item" << c;
            }
            else
            {
                m_items.append( Item { QString(), dest, CalamaresUtils::Permissions( perm ), t } );
            }
        }
        else
        {
            cDebug() << "Invalid type for preservefiles, item" << c;
        }

        ++c;
    }
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( PreserveFilesFactory, registerPlugin< PreserveFiles >(); )
