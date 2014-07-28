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
#include <QTranslator>

namespace CalamaresUtils
{

static QDir s_appDataDir( CMAKE_INSTALL_FULL_DATADIR );

void
setAppDataDir( const QDir& dir )
{
    s_appDataDir = dir;
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
    return appDataDir();
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

}
