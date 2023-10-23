/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2018, 2021 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "Item.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "compat/Variant.h"
#include "utils/Logger.h"
#include "utils/System.h"
#include "utils/Units.h"
#include "utils/Variant.h"

#include <QFile>

using namespace Calamares::Units;

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
    } while ( b.size() > 0 );

    sourcef.close();
    destf.close();

    return true;
}

Item
Item::fromVariant( const QVariant& v, const Calamares::Permissions& defaultPermissions )
{
    if ( Calamares::typeOf( v ) == Calamares::StringVariantType )
    {
        QString filename = v.toString();
        if ( !filename.isEmpty() )
        {
            return { filename, filename, defaultPermissions, ItemType::Path, false };
        }
        else
        {
            cWarning() << "Empty filename for preservefiles, item" << v;
            return {};
        }
    }
    else if ( Calamares::typeOf( v ) == Calamares::MapVariantType )
    {
        const auto map = v.toMap();

        Calamares::Permissions perm( defaultPermissions );
        ItemType t = ItemType::None;
        bool optional = Calamares::getBool( map, "optional", false );

        {
            QString perm_string = map[ "perm" ].toString();
            if ( !perm_string.isEmpty() )
            {
                perm = Calamares::Permissions( perm_string );
            }
        }

        {
            QString from = map[ "from" ].toString();
            t = ( from == "log" ) ? ItemType::Log : ( from == "config" ) ? ItemType::Config : ItemType::None;

            if ( t == ItemType::None && !map[ "src" ].toString().isEmpty() )
            {
                t = ItemType::Path;
            }
        }

        QString dest = map[ "dest" ].toString();
        if ( dest.isEmpty() )
        {
            cWarning() << "Empty dest for preservefiles, item" << v;
            return {};
        }

        switch ( t )
        {
        case ItemType::Config:
            return { QString(), dest, perm, t, optional };
        case ItemType::Log:
            return { QString(), dest, perm, t, optional };
        case ItemType::Path:
            return { map[ "src" ].toString(), dest, perm, t, optional };
        case ItemType::None:
            cWarning() << "Invalid type for preservefiles, item" << v;
            return {};
        }
    }
    cWarning() << "Invalid type for preservefiles, item" << v;
    return {};
}

bool
Item::exec( const std::function< QString( QString ) >& replacements ) const
{
    QString expanded_dest = replacements( dest );
    QString full_dest = Calamares::System::instance()->targetPath( expanded_dest );

    bool success = false;
    switch ( m_type )
    {
    case ItemType::None:
        cWarning() << "Invalid item for preservefiles skipped.";
        return false;
    case ItemType::Config:
        if ( !( success = Calamares::JobQueue::instance()->globalStorage()->saveJson( full_dest ) ) )
        {
            cWarning() << "Could not write a JSON dump of global storage to" << full_dest;
        }
        break;
    case ItemType::Log:
        if ( !( success = copy_file( Logger::logFile(), full_dest ) ) )
        {
            cWarning() << "Could not preserve log file to" << full_dest;
        }
        break;
    case ItemType::Path:
        if ( !( success = copy_file( source, full_dest ) ) )
        {
            cWarning() << "Could not preserve" << source << "to" << full_dest;
        }
        break;
    }
    if ( !success )
    {
        Calamares::System::instance()->removeTargetFile( expanded_dest );
        return false;
    }
    else
    {
        return perm.apply( full_dest );
    }
}
