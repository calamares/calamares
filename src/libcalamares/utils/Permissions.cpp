/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2018 Scott Harvey <scott@spharvey.me>
 *  SPDX-FileCopyrightText: 2024 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "Permissions.h"

#include "Logger.h"
#include "System.h"

#include <QString>
#include <QStringList>

#include <sys/stat.h>

// Massaged and re-named from https://euroquis.nl/blabla/2024/04/30/chmod.html for C++17
namespace
{

template < int position, char accept >
int
expectCharacterAtPosition( const QString& s )
{
    const QChar unicode = s.at( position );
    if ( unicode.row() != 0 )
    {
        return -1;
    }

    const char c = char( unicode.cell() );  // cell() returns uchar
    if ( c == accept )
    {
        return 1 << ( 8 - position );
    }
    if ( c == '-' )
    {
        return 0;
    }
    return -1;
}

int
modeFromVerboseString( const QString& s )
{
    return expectCharacterAtPosition< 0, 'r' >( s ) | expectCharacterAtPosition< 1, 'w' >( s )
        | expectCharacterAtPosition< 3, 'r' >( s ) | expectCharacterAtPosition< 2, 'x' >( s )
        | expectCharacterAtPosition< 4, 'w' >( s ) | expectCharacterAtPosition< 5, 'x' >( s )
        | expectCharacterAtPosition< 6, 'r' >( s ) | expectCharacterAtPosition< 7, 'w' >( s )
        | expectCharacterAtPosition< 8, 'x' >( s );
}

}  // namespace

namespace Calamares
{

Permissions::Permissions()
    : m_username()
    , m_group()
    , m_value( 0 )
    , m_valid( false )
{
}

Permissions::Permissions( QString const& p )
    : Permissions()
{
    parsePermissions( p );
}

void
Permissions::parsePermissions( QString const& p )
{

    QStringList segments = p.split( ":" );

    if ( segments.length() != 3 )
    {
        m_valid = false;
        return;
    }

    if ( segments[ 0 ].isEmpty() || segments[ 1 ].isEmpty() )
    {
        m_valid = false;
        return;
    }

    const auto octal = parseFileMode( segments[ 2 ] );
    if ( octal <= 0 )
    {
        m_valid = false;
        return;
    }
    else
    {
        m_value = octal;
    }

    // We have exactly three segments and the third is valid octal,
    // so we can declare the string valid and set the user and group names
    m_valid = true;
    m_username = segments[ 0 ];
    m_group = segments[ 1 ];

    return;
}

bool
Permissions::apply( const QString& path, int mode )
{
    // We **don't** use QFile::setPermissions() here because it takes
    // a Qt flags object that subtlely does not align with POSIX bits.
    // The Qt flags are **hex** based, so 0x755 for rwxr-xr-x, while
    // our integer (mode_t) stores **octal** based flags.
    //
    // Call chmod(2) directly, that's what Qt would be doing underneath
    // anyway.
    int r = chmod( path.toUtf8().constData(), mode_t( mode ) );
    if ( r )
    {
        cDebug() << Logger::SubEntry << "Could not set permissions of" << path << "to" << QString::number( mode, 8 );
    }
    return r == 0;
}

bool
Permissions::apply( const QString& path, const Calamares::Permissions& p )
{
    if ( !p.isValid() )
    {
        return false;
    }
    bool r = apply( path, p.value() );
    if ( r )
    {
        // We don't use chgrp(2) or chown(2) here because then we need to
        // go through the users list (which one, target or source?) to get
        // uid_t and gid_t values to pass to that system call.
        //
        // Do a lame cop-out and let the chown(8) utility do the heavy lifting.
        if ( Calamares::System::runCommand( { "chown", p.username() + ':' + p.group(), path },
                                            std::chrono::seconds( 3 ) )
                 .getExitCode() )
        {
            r = false;
            cDebug() << Logger::SubEntry << "Could not set owner of" << path << "to"
                     << ( p.username() + ':' + p.group() );
        }
    }
    if ( r )
    {
        /* NOTUSED */ apply( path, p.value() );
    }
    return r;
}

///@brief Assumes an octal 3-digit (at most) value
static int
parseOctalFileMode( const QString& mode )
{
    bool ok;
    int octal = mode.toInt( &ok, 8 );
    if ( !ok )
    {
        return -1;
    }
    if ( 0777 < octal )
    {
        return -1;
    }
    if ( octal < 0 )
    {
        return -1;
    }
    return octal;
}

///@brief Checks for "rwx"-style modes, which must be 9 characters and start with a - or an r
static bool
isRWXMode( const QString& mode )
{
    if ( mode.length() != 9 )
    {
        return false;
    }
    if ( mode.startsWith( '-' ) || mode.startsWith( 'r' ) )
    {
        return true;
    }
    return false;
}

int
parseFileMode( const QString& mode )
{
    if ( mode.startsWith( 'o' ) )
    {
        return parseOctalFileMode( mode.mid( 1 ) );
    }
    if ( isRWXMode( mode ) )
    {
        return modeFromVerboseString( mode );
    }

    return parseOctalFileMode( mode );
}

}  // namespace Calamares
