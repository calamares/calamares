/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *
 *   Originally from the Manjaro Installation Framework
 *   by Roland Singer <roland@manjaro.org>
 *   Copyright (C) 2007 Free Software Foundation, Inc.
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

#include "localeglobal.h"

#include "locale/TimeZone.h"

#include <QTimeZone>

//###
//### Private variables
//###

QHash< QString, QHash< QString, QList< LocaleGlobal::Locale > > > LocaleGlobal::locales;


//###
//### Public methods
//###


void
LocaleGlobal::init()
{
    // TODO: Error handling
    initLocales();
}


QHash< QString, QHash< QString, QList< LocaleGlobal::Locale > > >
LocaleGlobal::getLocales()
{
    return locales;
}


//###
//### Private methods
//###


void
LocaleGlobal::initLocales()
{
    static const char LOCALESDIR[] = "/usr/share/i18n/locales";

    locales.clear();

    QStringList files = QDir( LOCALESDIR ).entryList( QDir::Files, QDir::Name );

    for ( int i = 0; i < files.size(); ++i )
    {
        QString filename = files.at( i );
        QFile file( QString( LOCALESDIR ) + "/" + filename );
        if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            continue;
        }

        QTextStream in( &file );
        QString commentChar = "%";
        Locale locale;
        QString lang, territory;

        locale.locale = filename;

        while ( !in.atEnd() )
        {
            QString line = in.readLine().trimmed();
            QStringList split = line.split( commentChar, QString::KeepEmptyParts )
                                    .first()
                                    .split( QRegExp( " (?=[^\"]*(\"[^\"]*\"[^\"]*)*$)" ), QString::SkipEmptyParts );

            if ( split.size() < 2 )
            {
                continue;
            }

            QString sub1 = QString( split.at( 0 ) ).remove( "\"" );
            QString sub2 = QString( split.at( 1 ) ).remove( "\"" );

            if ( sub1 == "comment_char" )
            {
                commentChar = sub2;
            }
            else if ( sub1 == "title" )
            {
                locale.description = sub2;
            }
            else if ( sub1 == "territory" )
            {
                territory = sub2;
            }
            else if ( sub1 == "language" )
            {
                lang = sub2;
            }
        }

        if ( lang.isEmpty() || territory.isEmpty() )
        {
            continue;
        }

        locales[ lang ][ territory ].append( locale );
    }
}
