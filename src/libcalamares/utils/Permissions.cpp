/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2018 Scott Harvey <scott@spharvey.me>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include "Permissions.h"

#include "CalamaresUtilsSystem.h"
#include "Logger.h"

#include <QString>
#include <QStringList>

#include <sys/stat.h>

namespace CalamaresUtils
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

    bool ok;
    int octal = segments[ 2 ].toInt( &ok, 8 );
    if ( !ok || octal == 0 )
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
Permissions::apply( const QString& path, const CalamaresUtils::Permissions& p )
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
        if ( CalamaresUtils::System::runCommand( { "chown", p.username() + ':' + p.group(), path },
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


}  // namespace CalamaresUtils
