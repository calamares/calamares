/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "PreserveFiles.h"

#include "Item.h"

#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/CommandList.h"
#include "utils/Logger.h"
#include "utils/Units.h"

#include <QFile>

using namespace CalamaresUtils::Units;

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

Calamares::JobResult
PreserveFiles::exec()
{
    if ( m_items.empty() )
    {
        return Calamares::JobResult::error( tr( "No files configured to save for later." ) );
    }

    int count = 0;
    for ( const auto& it : qAsConst( m_items ) )
    {
        if ( !it )
        {
            // Invalid entries are nullptr, ignore them but count as a success
            // because they shouldn't block the installation. There are
            // warnings in the log showing what the configuration problem is.
            ++count;
            continue;
        }
        // Try to preserve the file. If it's marked as optional, count it
        // as a success regardless.
        if ( it.exec( atReplacements ) || it.isOptional() )
        {
            ++count;
        }
    }

    return count == m_items.size()
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
    CalamaresUtils::Permissions perm( defaultPermissions );

    for ( const auto& li : files.toList() )
    {
        m_items.push_back( Item::fromVariant( li, perm ) );
    }
}

CALAMARES_PLUGIN_FACTORY_DEFINITION( PreserveFilesFactory, registerPlugin< PreserveFiles >(); )
