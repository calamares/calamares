/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2013-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Originally from Tomahawk, portions:
 *   SPDX-FileCopyrightText: 2010-2011 Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   SPDX-FileCopyrightText: 2010-2011 Leo Franchi <lfranchi@kde.org>
 *   SPDX-FileCopyrightText: 2010-2012 Jeff Mitchell <jeff@tomahawk-player.org>
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#include "Dirs.h"

#include "CalamaresConfig.h"
#include "Logger.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QLocale>
#include <QStandardPaths>
#include <QTranslator>

#include <iostream>

using std::cerr;

namespace CalamaresUtils
{

static QDir s_appDataDir( CMAKE_INSTALL_FULL_DATADIR );
static bool s_isAppDataDirOverridden = false;

static bool s_haveExtraDirs = false;
static QStringList s_extraConfigDirs;
static QStringList s_extraDataDirs;

static bool
isWritableDir( const QDir& dir )
{
    // We log with cerr here because we might be looking for the log dir
    QString path = dir.absolutePath();
    if ( !dir.exists() )
    {
        if ( !dir.mkpath( "." ) )
        {
            cerr << "warning: failed to create " << qPrintable( path ) << '\n';
            return false;
        }
        return true;
    }

    QFileInfo info( path );
    if ( !info.isDir() )
    {
        cerr << "warning: " << qPrintable( path ) << " is not a dir\n";
        return false;
    }
    if ( !info.isWritable() )
    {
        cerr << "warning: " << qPrintable( path ) << " is not writable\n";
        return false;
    }
    return true;
}


void
setAppDataDir( const QDir& dir )
{
    s_appDataDir = dir;
    s_isAppDataDirOverridden = true;
}

/* Split $ENV{@p name} on :, append to @p l, making sure each ends in / */
static void
mungeEnvironment( QStringList& l, const char* name, const char* defaultDirs )
{
    static const QString calamaresSubdir = QStringLiteral( "calamares/" );

    QStringList dirs = QString( qgetenv( name ) ).split( ':' );
    if ( dirs.isEmpty() )
    {
        dirs = QString( defaultDirs ).split( ':' );
    }

    for ( auto s : dirs )
    {
        if ( s.isEmpty() )
        {
            continue;
        }
        if ( s.endsWith( '/' ) )
        {
            l << ( s + calamaresSubdir ) << s;
        }
        else
        {
            l << ( s + '/' + calamaresSubdir ) << ( s + '/' );
        }
    }
}

void
setXdgDirs()
{
    mungeEnvironment( s_extraConfigDirs, "XDG_CONFIG_DIRS", "/etc/xdg" );
    mungeEnvironment( s_extraDataDirs, "XDG_DATA_DIRS", "/usr/local/share/:/usr/share/" );

    s_haveExtraDirs = !( s_extraConfigDirs.isEmpty() && s_extraDataDirs.isEmpty() );
}

QStringList
extraConfigDirs()
{
    if ( s_haveExtraDirs )
    {
        return s_extraConfigDirs;
    }
    return QStringList();
}

QStringList
extraDataDirs()
{
    if ( s_haveExtraDirs )
    {
        return s_extraDataDirs;
    }
    return QStringList();
}

bool
haveExtraDirs()
{
    return s_haveExtraDirs && ( !s_extraConfigDirs.isEmpty() || !s_extraDataDirs.isEmpty() );
}

bool
isAppDataDirOverridden()
{
    return s_isAppDataDirOverridden;
}


QDir
appDataDir()
{
    return s_appDataDir;
}


QDir
systemLibDir()
{
    QDir path( CMAKE_INSTALL_FULL_LIBDIR );
    return path;
}


QDir
appLogDir()
{
    QString path = QStandardPaths::writableLocation( QStandardPaths::CacheLocation );
    QDir dir( path );
    if ( isWritableDir( dir ) )
    {
        return dir;
    }

    cerr << "warning: Could not find a standard writable location for log dir, falling back to $HOME\n";
    dir = QDir::home();
    if ( isWritableDir( dir ) )
    {
        return dir;
    }

    cerr << "warning: Found no writable location for log dir, falling back to the temp dir\n";
    return QDir::temp();
}

}  // namespace CalamaresUtils
