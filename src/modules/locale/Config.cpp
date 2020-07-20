/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
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

#include "Config.h"

#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QFile>
#include <QProcess>

/** @brief Load supported locale keys
 *
 * If i18n/SUPPORTED exists, read the lines from that and return those
 * as supported locales; otherwise, try the file at @p localeGenPath
 * and get lines from that. Failing both, try the output of `locale -a`.
 *
 * This gives us a list of locale identifiers (e.g. en_US.UTF-8), which
 * are not particularly human-readable.
 *
 * Only UTF-8 locales are returned (even if the system claims to support
 * other, non-UTF-8, locales).
 */
static QStringList
loadLocales( const QString& localeGenPath )
{
    QStringList localeGenLines;

    // Some distros come with a meaningfully commented and easy to parse locale.gen,
    // and others ship a separate file /usr/share/i18n/SUPPORTED with a clean list of
    // supported locales. We first try that one, and if it doesn't exist, we fall back
    // to parsing the lines from locale.gen
    localeGenLines.clear();
    QFile supported( "/usr/share/i18n/SUPPORTED" );
    QByteArray ba;

    if ( supported.exists() && supported.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        ba = supported.readAll();
        supported.close();

        const auto lines = ba.split( '\n' );
        for ( const QByteArray& line : lines )
        {
            localeGenLines.append( QString::fromLatin1( line.simplified() ) );
        }
    }
    else
    {
        QFile localeGen( localeGenPath );
        if ( localeGen.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
            ba = localeGen.readAll();
            localeGen.close();
        }
        else
        {
            cWarning() << "Cannot open file" << localeGenPath
                       << ". Assuming the supported languages are already built into "
                          "the locale archive.";
            QProcess localeA;
            localeA.start( "locale", QStringList() << "-a" );
            localeA.waitForFinished();
            ba = localeA.readAllStandardOutput();
        }
        const auto lines = ba.split( '\n' );
        for ( const QByteArray& line : lines )
        {
            if ( line.startsWith( "## " ) || line.startsWith( "# " ) || line.simplified() == "#" )
            {
                continue;
            }

            QString lineString = QString::fromLatin1( line.simplified() );
            if ( lineString.startsWith( "#" ) )
            {
                lineString.remove( '#' );
            }
            lineString = lineString.simplified();

            if ( lineString.isEmpty() )
            {
                continue;
            }

            localeGenLines.append( lineString );
        }
    }

    if ( localeGenLines.isEmpty() )
    {
        cWarning() << "cannot acquire a list of available locales."
                   << "The locale and localecfg modules will be broken as long as this "
                      "system does not provide"
                   << "\n\t  "
                   << "* a well-formed" << supported.fileName() << "\n\tOR"
                   << "* a well-formed"
                   << ( localeGenPath.isEmpty() ? QLatin1String( "/etc/locale.gen" ) : localeGenPath ) << "\n\tOR"
                   << "* a complete pre-compiled locale-gen database which allows complete locale -a output.";
        return localeGenLines;  // something went wrong and there's nothing we can do about it.
    }

    // Assuming we have a list of supported locales, we usually only want UTF-8 ones
    // because it's not 1995.
    auto notUtf8 = []( const QString& s ) {
        return !s.contains( "UTF-8", Qt::CaseInsensitive ) && !s.contains( "utf8", Qt::CaseInsensitive );
    };
    auto it = std::remove_if( localeGenLines.begin(), localeGenLines.end(), notUtf8 );
    localeGenLines.erase( it, localeGenLines.end() );

    // We strip " UTF-8" from "en_US.UTF-8 UTF-8" because it's redundant redundant.
    // Also simplify whitespace.
    auto unredundant = []( QString& s ) {
        if ( s.endsWith( " UTF-8" ) )
        {
            s.chop( 6 );
        }
        s = s.simplified();
    };
    std::for_each( localeGenLines.begin(), localeGenLines.end(), unredundant );

    return localeGenLines;
}

static inline const CalamaresUtils::Locale::CStringPairList&
timezoneData()
{
    return CalamaresUtils::Locale::TZRegion::fromZoneTab();
}


Config::Config( QObject* parent )
    : QObject( parent )
    , m_regionModel( std::make_unique< CalamaresUtils::Locale::CStringListModel >( ::timezoneData() ) )
    , m_zonesModel( std::make_unique< CalamaresUtils::Locale::CStringListModel >() )
{
}

Config::~Config() {}

const CalamaresUtils::Locale::CStringPairList&
Config::timezoneData() const
{
    return ::timezoneData();
}


void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    QString localeGenPath = CalamaresUtils::getString( configurationMap, "localeGenPath" );
    if ( localeGenPath.isEmpty() )
    {
        localeGenPath = QStringLiteral( "/etc/locale.gen" );
    }
    m_localeGenLines = loadLocales( localeGenPath );
}
