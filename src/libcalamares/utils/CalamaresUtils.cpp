/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2013-2014, Teo Mrnjavac <teo@kde.org>
 *
 *   Originally from Tomahawk, portions:
 *   Copyright 2010-2011, Christian Muehlhaeuser <muesli@tomahawk-player.org>
 *   Copyright 2010-2011, Leo Franchi <lfranchi@kde.org>
 *   Copyright 2010-2012, Jeff Mitchell <jeff@tomahawk-player.org>
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

#include "CalamaresUtils.h"

#include "CalamaresConfig.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QLocale>
#include <QStandardPaths>
#include <QTranslator>


// stdc++
#include <iostream>

using namespace std;

namespace CalamaresUtils
{

static QDir s_appDataDir( CMAKE_INSTALL_FULL_DATADIR );
static bool s_isAppDataDirOverridden = false;

static bool
isWritableDir( const QDir& dir )
{
    // We log with cerr here because we might be looking for the log dir
    QString path = dir.absolutePath();
    if ( !dir.exists() )
    {
        if ( !dir.mkpath( "." ) )
        {
            cerr << "warning: failed to create " << qPrintable( path ) << endl;
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
        return dir;

    cerr << "warning: Could not find a standard writable location for log dir, falling back to $HOME\n";
    dir = QDir::home();
    if ( isWritableDir( dir ) )
        return dir;

    cerr << "warning: Found no writable location for log dir, falling back to the temp dir\n";
    return QDir::temp();
}


void
installTranslator( QObject* parent )
{
    QString locale = QLocale::system().uiLanguages().first().replace( "-", "_" );

    if ( locale == "C" )
        locale = "en";

    // Calamares translations
    QTranslator* translator = new QTranslator( parent );
    if ( translator->load( QString( ":/lang/calamares_" ) + locale ) )
    {
        qDebug() << "Translation: Calamares: Using system locale:" << locale;
    }
    else
    {
        qDebug() << "Translation: Calamares: Using default locale, system locale one not found:" << locale;
        translator->load( QString( ":/lang/calamares_en" ) );
    }

    QCoreApplication::installTranslator( translator );

    // Qt translations
    translator = new QTranslator( parent );
    if ( translator->load( QString( ":/lang/qt_" ) + locale ) )
    {
        qDebug() << "Translation: Qt: Using system locale:" << locale;
    }
    else
    {
        qDebug() << "Translation: Qt: Using default locale, system locale one not found:" << locale;
    }

    QCoreApplication::installTranslator( translator );
}


QString
removeDiacritics( const QString& string )
{
    const QString diacriticLetters = QString::fromUtf8(
        "ŠŒŽšœžŸ¥µÀ"
        "ÁÂÃÄÅÆÇÈÉÊ"
        "ËÌÍÎÏÐÑÒÓÔ"
        "ÕÖØÙÚÛÜÝßà"
        "áâãäåæçèéê"
        "ëìíîïðñòóô"
        "õöøùúûüýÿÞ"
        "þČčĆćĐđŠšŽ"
        "ž"
    );
    const QStringList noDiacriticLetters = {
        "S", "OE", "Z", "s", "oe", "z", "Y", "Y", "u", "A",
        "A", "A", "A", "A", "A", "AE", "C", "E", "E", "E",
        "E", "I", "I", "I", "I", "DH", "N", "O", "O", "O",
        "O", "O", "O", "U", "U", "U", "U", "Y", "s", "a",
        "a", "a", "a", "a", "a", "ae", "c", "e", "e", "e",
        "e", "i", "i", "i", "i", "dh", "n", "o", "o", "o",
        "o", "o", "o", "u", "u", "u", "u", "y", "y", "TH",
        "th", "C", "c", "C", "c", "DJ", "dj", "S", "s", "Z",
        "z"
    };

    QString output;
    foreach ( QChar c, string )
    {
        int i = diacriticLetters.indexOf( c );
        if ( i < 0 )
        {
            output.append( c );
        }
        else
        {
            QString replacement = noDiacriticLetters[ i ];
            output.append( replacement );
        }
    }

    return output;
}


}
