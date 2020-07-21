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

#include "SetTimezoneJob.h"

#include "locale/Label.h"
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
Config::setCurrentLocation( const QString& regionName, const QString& zoneName )
{
    using namespace CalamaresUtils::Locale;
    auto* region = timezoneData().find< TZRegion >( regionName );
    auto* zone = region ? region->zones().find< TZZone >( zoneName ) : nullptr;
    if ( zone )
    {
        setCurrentLocation( zone );
    }
    else
    {
        // Recursive, but America/New_York always exists.
        setCurrentLocation( QStringLiteral( "America" ), QStringLiteral( "New_York" ) );
    }
}

void
Config::setCurrentLocation( const CalamaresUtils::Locale::TZZone* location )
{
    if ( location != m_currentLocation )
    {
        m_currentLocation = location;
        // Overwrite those settings that have not been made explicit.
        auto newLocale = automaticLocaleConfiguration();
        if ( !m_selectedLocaleConfiguration.explicit_lang )
        {
            m_selectedLocaleConfiguration.setLanguage( newLocale.language() );
        }
        if ( !m_selectedLocaleConfiguration.explicit_lc )
        {
            m_selectedLocaleConfiguration.lc_numeric = newLocale.lc_numeric;
            m_selectedLocaleConfiguration.lc_time = newLocale.lc_time;
            m_selectedLocaleConfiguration.lc_monetary = newLocale.lc_monetary;
            m_selectedLocaleConfiguration.lc_paper = newLocale.lc_paper;
            m_selectedLocaleConfiguration.lc_name = newLocale.lc_name;
            m_selectedLocaleConfiguration.lc_address = newLocale.lc_address;
            m_selectedLocaleConfiguration.lc_telephone = newLocale.lc_telephone;
            m_selectedLocaleConfiguration.lc_measurement = newLocale.lc_measurement;
            m_selectedLocaleConfiguration.lc_identification = newLocale.lc_identification;
        }
        emit currentLocationChanged( m_currentLocation );
    }
}


LocaleConfiguration
Config::automaticLocaleConfiguration() const
{
    return LocaleConfiguration::fromLanguageAndLocation(
        QLocale().name(), supportedLocales(), currentLocation()->country() );
}

LocaleConfiguration
Config::localeConfiguration() const
{
    return m_selectedLocaleConfiguration.isEmpty() ? automaticLocaleConfiguration() : m_selectedLocaleConfiguration;
}

void
Config::setLanguageExplicitly( const QString& language )
{
    m_selectedLocaleConfiguration.setLanguage( language );
    m_selectedLocaleConfiguration.explicit_lang = true;
}

void
Config::setLCLocaleExplicitly( const QString& locale )
{
    // TODO: improve the granularity of this setting.
    m_selectedLocaleConfiguration.lc_numeric = locale;
    m_selectedLocaleConfiguration.lc_time = locale;
    m_selectedLocaleConfiguration.lc_monetary = locale;
    m_selectedLocaleConfiguration.lc_paper = locale;
    m_selectedLocaleConfiguration.lc_name = locale;
    m_selectedLocaleConfiguration.lc_address = locale;
    m_selectedLocaleConfiguration.lc_telephone = locale;
    m_selectedLocaleConfiguration.lc_measurement = locale;
    m_selectedLocaleConfiguration.lc_identification = locale;
    m_selectedLocaleConfiguration.explicit_lc = true;
}

std::pair< QString, QString >
Config::prettyLocaleStatus() const
{
    using CalamaresUtils::Locale::Label;

    Label lang( m_selectedLocaleConfiguration.language(), Label::LabelFormat::AlwaysWithCountry );
    Label num( m_selectedLocaleConfiguration.lc_numeric, Label::LabelFormat::AlwaysWithCountry );

    return std::make_pair< QString, QString >(
        tr( "The system language will be set to %1." ).arg( lang.label() ),
        tr( "The numbers and dates locale will be set to %1." ).arg( num.label() ) );
}

QString
Config::prettyStatus() const
{
    QString br( QStringLiteral("<br/>"));
    QString status;
    status += tr( "Set timezone to %1/%2." ).arg( m_currentLocation->region(), m_currentLocation->zone() ) + br;

    auto labels = prettyLocaleStatus();
    status += labels.first + br;
    status += labels.second + br;

    return status;
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

Calamares::JobList
Config::createJobs()
{
    Calamares::JobList list;
    const CalamaresUtils::Locale::TZZone* location = currentLocation();

    if ( location )
    {
        Calamares::Job* j = new SetTimezoneJob( location->region(), location->zone() );
        list.append( Calamares::job_ptr( j ) );
    }

    return list;
}
