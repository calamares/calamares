/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *  SPDX-FileCopyrightText: 2018 Scott Harvey <scott@spharvey.me>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *  License-Filename: LICENSE
 *
 */

#include "Permissions.h"

#include <QString>
#include <QStringList>

Permissions::Permissions()
    : m_username()
    , m_group()
    , m_valid( false )
    , m_value( 0 )
{
}


Permissions::Permissions( QString p )
    : Permissions()
{
    parsePermissions( p );
}

void
Permissions::parsePermissions( const QString& p )
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
