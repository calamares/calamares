/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "PreserveFiles.h"

#include "permissions.h"

#include "CalamaresVersion.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

#include "utils/CalamaresUtilsSystem.h"
#include "utils/CommandList.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <QFile>

using CalamaresUtils::operator""_MiB;

QString targetPrefix()
{
    if ( CalamaresUtils::System::instance()->doChroot() )
    {
        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
        if ( gs && gs->contains( "rootMountPoint" ) )
        {
            QString r = gs->value( "rootMountPoint" ).toString();
            if ( !r.isEmpty() )
                return r;
            else
                cDebug() << "RootMountPoint is empty";
        }
        else
        {
            cDebug() << "No rootMountPoint defined, preserving files to '/'";
        }
    }

    return QLatin1String( "/" );
}

QString atReplacements( QString s )
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QString root( "/" );
    QString user;

    if ( gs && gs->contains( "rootMountPoint" ) )
        root = gs->value( "rootMountPoint" ).toString();
    if ( gs && gs->contains( "username" ) )
        user = gs->value( "username" ).toString();

    return s.replace( "@@ROOT@@", root ).replace( "@@USER@@", user );
}

PreserveFiles::PreserveFiles( QObject* parent )
    : Calamares::CppJob( parent )
{
}

PreserveFiles::~PreserveFiles()
{
}

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
    }
    while ( b.count() > 0 );

    sourcef.close();
    destf.close();

    return true;
}

Calamares::JobResult PreserveFiles::exec()
{
    if ( m_items.isEmpty() )
        return Calamares::JobResult::error( tr( "No files configured to save for later." ) );

    QString prefix = targetPrefix();
    if ( !prefix.endsWith( '/' ) )
        prefix.append( '/' );

    int count = 0;
    for ( const auto& it : m_items )
    {
        QString source = it.source;
        QString bare_dest = atReplacements( it.dest );
        QString dest = prefix + bare_dest;

        if ( it.type == ItemType::Log )
            source = Logger::logFile();
        if ( it.type == ItemType::Config )
        {
            if ( Calamares::JobQueue::instance()->globalStorage()->save( dest ) )
                cWarning() << "Could not write config for" << dest;
            else
                ++count;
        }
        else if ( source.isEmpty() )
            cWarning() << "Skipping unnamed source file for" << dest;
        else
        {
            if ( copy_file( source, dest ) )
            {
                if ( it.perm.isValid() )
                {
                    auto s_p = CalamaresUtils::System::instance();

                    int r;

                    r = s_p->targetEnvCall( QStringList{ "chown", it.perm.username(), bare_dest } );
                    if ( r )
                        cWarning() << "Could not chown target" << bare_dest;

                    r = s_p->targetEnvCall( QStringList{ "chgrp", it.perm.group(), bare_dest } );
                    if ( r )
                        cWarning() << "Could not chgrp target" << bare_dest;

                    r = s_p->targetEnvCall( QStringList{ "chmod", it.perm.octal(), bare_dest } );
                    if ( r )
                        cWarning() << "Could not chmod target" << bare_dest;
                }

                ++count;
            }
        }
    }

    return count == m_items.count() ?
        Calamares::JobResult::ok() :
        Calamares::JobResult::error( tr( "Not all of the configured files could be preserved." ) );
}

void PreserveFiles::setConfigurationMap(const QVariantMap& configurationMap)
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
        defaultPermissions = QStringLiteral( "root:root:0400" );

    QVariantList l = files.toList();
    unsigned int c = 0;
    for ( const auto& li : l )
    {
        if ( li.type() == QVariant::String )
        {
            QString filename = li.toString();
            if ( !filename.isEmpty() )
                m_items.append( Item{ filename, filename, Permissions( defaultPermissions ), ItemType::Path } );
            else
                cDebug() << "Empty filename for preservefiles, item" << c;
        }
        else if ( li.type() == QVariant::Map )
        {
            const auto map = li.toMap();
            QString dest = map[ "dest" ].toString();
            QString from = map[ "from" ].toString();
            ItemType t =
                ( from == "log" ) ? ItemType::Log :
                ( from == "config" ) ? ItemType::Config :
                ItemType::None;
            QString perm = map[ "perm" ].toString();
            if ( perm.isEmpty() )
                perm = defaultPermissions;

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
                m_items.append( Item{ QString(), dest, Permissions( perm ), t } );
            }
        }
        else
            cDebug() << "Invalid type for preservefiles, item" << c;

        ++c;
    }
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( PreserveFilesFactory, registerPlugin<PreserveFiles>(); )

