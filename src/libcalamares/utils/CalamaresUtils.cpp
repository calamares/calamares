/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2013-2016, Teo Mrnjavac <teo@kde.org>
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
static QDir s_qmlModulesDir( QString( CMAKE_INSTALL_FULL_DATADIR ) + "/qml" );
static bool s_isAppDataDirOverridden = false;

static QTranslator* s_brandingTranslator = nullptr;
static QTranslator* s_translator = nullptr;
static QString s_translatorLocaleName;


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


QDir
qmlModulesDir()
{
    return s_qmlModulesDir;
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
installTranslator( const QLocale& locale,
                   const QString& brandingTranslationsPrefix,
                   QObject* parent )
{
    QString localeName = locale.name();
    localeName.replace( "-", "_" );

    if ( localeName == "C" )
        localeName = "en";

    QTranslator* translator = nullptr;

    // Branding translations
    if ( !brandingTranslationsPrefix.isEmpty() )
    {
        QString brandingTranslationsDirPath( brandingTranslationsPrefix );
        brandingTranslationsDirPath.truncate( brandingTranslationsPrefix.lastIndexOf(
                                                  QDir::separator() ) );
        QDir brandingTranslationsDir( brandingTranslationsDirPath );
        if ( brandingTranslationsDir.exists() )
        {
            QString filenameBase( brandingTranslationsPrefix );
            filenameBase.remove( 0, brandingTranslationsPrefix.lastIndexOf(
                                        QDir::separator() ) + 1 );
            translator = new QTranslator( parent );
            if ( translator->load( locale,
                                   filenameBase,
                                   "_",
                                   brandingTranslationsDir.absolutePath() ) )
            {
                qDebug() << "Translation: Branding component: Using system locale:" << localeName;
            }
            else
            {
                qDebug() << "Translation: Branding component: Using default locale, system locale one not found:" << localeName;
                translator->load( brandingTranslationsPrefix + "en" );
            }

            if ( s_brandingTranslator )
            {
                QCoreApplication::removeTranslator( s_brandingTranslator );
                delete s_brandingTranslator;
            }

            QCoreApplication::installTranslator( translator );
            s_brandingTranslator = translator;
        }
    }

    // Calamares translations
    translator = new QTranslator( parent );
    if ( translator->load( QString( ":/lang/calamares_" ) + localeName ) )
    {
        qDebug() << "Translation: Calamares: Using system locale:" << localeName;
    }
    else
    {
        qDebug() << "Translation: Calamares: Using default locale, system locale one not found:" << localeName;
        translator->load( QString( ":/lang/calamares_en" ) );
    }

    if ( s_translator )
    {
        QCoreApplication::removeTranslator( s_translator );
        delete s_translator;
    }

    QCoreApplication::installTranslator( translator );
    s_translator = translator;

    s_translatorLocaleName = localeName;
}


QString
translatorLocaleName()
{
    return s_translatorLocaleName;
}


void
setQmlModulesDir( const QDir& dir )
{
    s_qmlModulesDir = dir;
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
        "žŞşĞğİıȚțȘ"
        "șĂăŐőŰűŘřĀ"
        "āĒēĪīŌōŪūŢ"
        "ţẀẁẂẃŴŵŶŷĎ"
        "ďĚěŇňŤťŮůŔ"
        "ŕĄąĘęŁłŃńŚ"
        "śŹźŻż"
    );
    const QStringList noDiacriticLetters = {
        "S", "OE", "Z", "s", "oe", "z", "Y", "Y", "u", "A",
        "A", "A", "A", "A", "AA", "AE", "C", "E", "E", "E",
        "E", "I", "I", "I", "I", "D", "N", "O", "O", "O",
        "O", "E", "OE", "U", "U", "U", "E", "Y", "s", "a",
        "a", "a", "a", "e", "aa", "ae", "c", "e", "e", "e",
        "e", "i", "i", "i", "i", "d", "n", "o", "o", "o",
        "o", "e", "oe", "u", "u", "u", "e", "y", "y", "TH",
        "th", "C", "c", "C", "c", "DJ", "dj", "S", "s", "Z",
        "z", "S", "s", "G", "g", "I", "i", "T", "t", "S",
        "s", "A", "a", "O", "o", "U", "u", "R", "r", "A",
        "a", "E", "e", "I", "i", "O", "o", "U", "u", "T",
        "t", "W", "w", "W", "w", "W", "w", "Y", "y", "D",
        "d", "E", "e", "N", "n", "T", "t", "U", "u", "R",
        "r", "A", "a", "E", "e", "L", "l", "N", "n", "S",
        "s", "Z", "z", "Z", "z"
    };

    QString output;
    for ( const QChar &c : string )
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


// Function CalamaresUtils::obscure based on KStringHandler::obscure,
// part of KDElibs by KDE, file kstringhandler.cpp.
// Original copyright statement follows.
/* This file is part of the KDE libraries
   Copyright (C) 1999 Ian Zepp (icszepp@islc.net)
   Copyright (C) 2006 by Dominic Battre <dominic@battre.de>
   Copyright (C) 2006 by Martin Pool <mbp@canonical.com>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
QString
obscure( const QString& string )
{
    QString result;
    const QChar *unicode = string.unicode();
    for ( int i = 0; i < string.length(); ++i )
        // yes, no typo. can't encode ' ' or '!' because
        // they're the unicode BOM. stupid scrambling. stupid.
        result += ( unicode[ i ].unicode() <= 0x21 ) ?
                      unicode[ i ] :
                      QChar( 0x1001F - unicode[ i ].unicode() );
    return result;
}


void
crash()
{
    volatile int* a = nullptr;
    *a = 1;
}


}
