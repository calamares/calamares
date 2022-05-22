/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "Config.h"

#include "SetTimezoneJob.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "locale/Global.h"
#include "locale/Translation.h"
#include "modulesystem/ModuleManager.h"
#include "network/Manager.h"
#include "utils/Logger.h"
#include "utils/Variant.h"

#include <QFile>
#include <QProcess>
#include <QTimeZone>

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
    auto notUtf8 = []( const QString& s )
    { return !s.contains( "UTF-8", Qt::CaseInsensitive ) && !s.contains( "utf8", Qt::CaseInsensitive ); };
    auto it = std::remove_if( localeGenLines.begin(), localeGenLines.end(), notUtf8 );
    localeGenLines.erase( it, localeGenLines.end() );

    // We strip " UTF-8" from "en_US.UTF-8 UTF-8" because it's redundant redundant.
    // Also simplify whitespace.
    auto unredundant = []( QString& s )
    {
        if ( s.endsWith( " UTF-8" ) )
        {
            s.chop( 6 );
        }
        s = s.simplified();
    };
    std::for_each( localeGenLines.begin(), localeGenLines.end(), unredundant );

    return localeGenLines;
}

static bool
updateGSLocation( Calamares::GlobalStorage* gs, const CalamaresUtils::Locale::TimeZoneData* location )
{
    const QString regionKey = QStringLiteral( "locationRegion" );
    const QString zoneKey = QStringLiteral( "locationZone" );

    if ( !location )
    {
        if ( gs->contains( regionKey ) || gs->contains( zoneKey ) )
        {
            gs->remove( regionKey );
            gs->remove( zoneKey );
            return true;
        }
        return false;
    }

    // Update the GS region and zone (and possibly the live timezone)
    bool locationChanged
        = ( location->region() != gs->value( regionKey ) ) || ( location->zone() != gs->value( zoneKey ) );

    gs->insert( regionKey, location->region() );
    gs->insert( zoneKey, location->zone() );

    return locationChanged;
}

static void
updateGSLocale( Calamares::GlobalStorage* gs, const LocaleConfiguration& locale )
{
    CalamaresUtils::Locale::insertGS( *gs, locale.toMap(), CalamaresUtils::Locale::InsertMode::Overwrite );
}

Config::Config( QObject* parent )
    : QObject( parent )
    , m_regionModel( std::make_unique< CalamaresUtils::Locale::RegionsModel >() )
    , m_zonesModel( std::make_unique< CalamaresUtils::Locale::ZonesModel >() )
    , m_regionalZonesModel( std::make_unique< CalamaresUtils::Locale::RegionalZonesModel >( m_zonesModel.get() ) )
{
    // Slightly unusual: connect to our *own* signals. Wherever the language
    // or the location is changed, these signals are emitted, so hook up to
    // them to update global storage accordingly. This simplifies code:
    // we don't need to call an update-GS method, or introduce an intermediate
    // update-thing-and-GS method. And everywhere where we **do** change
    // language or location, we already emit the signal.
    connect( this,
             &Config::currentLanguageCodeChanged,
             [ & ]()
             {
                 auto* gs = Calamares::JobQueue::instance()->globalStorage();
                 gs->insert( "locale", m_selectedLocaleConfiguration.toBcp47() );
             } );

    connect( this,
             &Config::currentLCCodeChanged,
             [ & ]() { updateGSLocale( Calamares::JobQueue::instance()->globalStorage(), localeConfiguration() ); } );

    connect( this,
             &Config::currentLocationChanged,
             [ & ]()
             {
                 const bool locationChanged
                     = updateGSLocation( Calamares::JobQueue::instance()->globalStorage(), currentLocation() );

                 if ( locationChanged && m_adjustLiveTimezone )
                 {
                     QProcess::execute( "timedatectl",  // depends on systemd
                                        { "set-timezone", currentTimezoneCode() } );
                 }

                 emit currentTimezoneCodeChanged( currentTimezoneCode() );
                 emit currentTimezoneNameChanged( currentTimezoneName() );
             } );

    auto prettyStatusNotify = [ & ]() { emit prettyStatusChanged( prettyStatus() ); };
    connect( this, &Config::currentLanguageStatusChanged, prettyStatusNotify );
    connect( this, &Config::currentLCStatusChanged, prettyStatusNotify );
    connect( this, &Config::currentLocationStatusChanged, prettyStatusNotify );
}

Config::~Config() {}

void
Config::setCurrentLocation()
{
    if ( !m_currentLocation && m_startingTimezone.isValid() )
    {
        setCurrentLocation( m_startingTimezone.first, m_startingTimezone.second );
    }
    if ( !m_selectedLocaleConfiguration.explicit_lang )
    {
        auto newLocale = automaticLocaleConfiguration();
        setLanguage( newLocale.language() );
    }
}

void
Config::setCurrentLocation( const QString& regionzone )
{
    auto r = CalamaresUtils::GeoIP::splitTZString( regionzone );
    if ( r.isValid() )
    {
        setCurrentLocation( r.first, r.second );
    }
}

void
Config::setCurrentLocation( const QString& regionName, const QString& zoneName )
{
    using namespace CalamaresUtils::Locale;
    auto* zone = m_zonesModel->find( regionName, zoneName );
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
Config::setCurrentLocation( const CalamaresUtils::Locale::TimeZoneData* location )
{
    const bool updateLocation = ( location != m_currentLocation );
    if ( updateLocation )
    {
        m_currentLocation = location;
    }

    // lang should be always be updated
    auto newLocale = automaticLocaleConfiguration();
    if ( !m_selectedLocaleConfiguration.explicit_lang )
    {
        setLanguage( newLocale.language() );
    }

    if ( updateLocation )
    {
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

            emit currentLCStatusChanged( currentLCStatus() );
        }
        emit currentLocationChanged( m_currentLocation );
        // Other signals come from the LocationChanged signal
    }
}

LocaleConfiguration
Config::automaticLocaleConfiguration() const
{
    // Special case: no location has been set at **all**
    if ( !currentLocation() )
    {
        return LocaleConfiguration();
    }
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
    m_selectedLocaleConfiguration.explicit_lang = true;
    setLanguage( language );
}

void
Config::setLanguage( const QString& language )
{
    if ( language != m_selectedLocaleConfiguration.language() )
    {
        m_selectedLocaleConfiguration.setLanguage( language );

        emit currentLanguageStatusChanged( currentLanguageStatus() );
        emit currentLanguageCodeChanged( currentLanguageCode() );
    }
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

    emit currentLCStatusChanged( currentLCStatus() );
    emit currentLCCodeChanged( currentLCCode() );
}

QString
Config::currentLocationStatus() const
{
    return tr( "Set timezone to %1/%2." )
        .arg( m_currentLocation ? m_currentLocation->region() : QString(),
              m_currentLocation ? m_currentLocation->zone() : QString() );
}

QString
Config::currentTimezoneCode() const
{
    if ( m_currentLocation )
    {
        return m_currentLocation->region() + '/' + m_currentLocation->zone();
    }
    return QString();
}

QString
Config::currentTimezoneName() const
{
    if ( m_currentLocation )
    {
        return m_regionModel->tr( m_currentLocation->region() ) + '/' + m_currentLocation->tr();
    }
    return QString();
}


static inline QString
localeLabel( const QString& s )
{
    using CalamaresUtils::Locale::Translation;

    Translation lang( { s }, Translation::LabelFormat::AlwaysWithCountry );
    return lang.label();
}

QString
Config::currentLanguageStatus() const
{
    return tr( "The system language will be set to %1." )
        .arg( localeLabel( m_selectedLocaleConfiguration.language() ) );
}

QString
Config::currentLCStatus() const
{
    return tr( "The numbers and dates locale will be set to %1." )
        .arg( localeLabel( m_selectedLocaleConfiguration.lc_numeric ) );
}

QString
Config::prettyStatus() const
{
    QStringList l { currentLocationStatus(), currentLanguageStatus(), currentLCStatus() };
    return l.join( QStringLiteral( "<br/>" ) );
}

static inline void
getLocaleGenLines( const QVariantMap& configurationMap, QStringList& localeGenLines )
{
    QString localeGenPath = CalamaresUtils::getString( configurationMap, "localeGenPath" );
    if ( localeGenPath.isEmpty() )
    {
        localeGenPath = QStringLiteral( "/etc/locale.gen" );
    }
    localeGenLines = loadLocales( localeGenPath );
}

static inline void
getAdjustLiveTimezone( const QVariantMap& configurationMap, bool& adjustLiveTimezone )
{
    adjustLiveTimezone = CalamaresUtils::getBool(
        configurationMap, "adjustLiveTimezone", Calamares::Settings::instance()->doChroot() );
#ifdef DEBUG_TIMEZONES
    if ( adjustLiveTimezone )
    {
        cWarning() << "Turning off live-timezone adjustments because debugging is on.";
        adjustLiveTimezone = false;
    }
#endif
#ifdef __FreeBSD__
    if ( adjustLiveTimezone )
    {
        cWarning() << "Turning off live-timezone adjustments on FreeBSD.";
        adjustLiveTimezone = false;
    }
#endif
}

static inline void
getStartingTimezone( const QVariantMap& configurationMap, CalamaresUtils::GeoIP::RegionZonePair& startingTimezone )
{
    QString region = CalamaresUtils::getString( configurationMap, "region" );
    QString zone = CalamaresUtils::getString( configurationMap, "zone" );
    if ( !region.isEmpty() && !zone.isEmpty() )
    {
        startingTimezone = CalamaresUtils::GeoIP::RegionZonePair( region, zone );
    }
    else
    {
        startingTimezone
            = CalamaresUtils::GeoIP::RegionZonePair( QStringLiteral( "America" ), QStringLiteral( "New_York" ) );
    }

    if ( CalamaresUtils::getBool( configurationMap, "useSystemTimezone", false ) )
    {
        auto systemtz = CalamaresUtils::GeoIP::splitTZString( QTimeZone::systemTimeZoneId() );
        if ( systemtz.isValid() )
        {
            cDebug() << "Overriding configured timezone" << startingTimezone << "with system timezone" << systemtz;
            startingTimezone = systemtz;
        }
    }
}

static inline void
getGeoIP( const QVariantMap& configurationMap, std::unique_ptr< CalamaresUtils::GeoIP::Handler >& geoip )
{
    bool ok = false;
    QVariantMap map = CalamaresUtils::getSubMap( configurationMap, "geoip", ok );
    if ( ok )
    {
        QString url = CalamaresUtils::getString( map, "url" );
        QString style = CalamaresUtils::getString( map, "style" );
        QString selector = CalamaresUtils::getString( map, "selector" );

        geoip = std::make_unique< CalamaresUtils::GeoIP::Handler >( style, url, selector );
        if ( !geoip->isValid() )
        {
            cWarning() << "GeoIP Style" << style << "is not recognized.";
        }
    }
}

void
Config::setConfigurationMap( const QVariantMap& configurationMap )
{
    getLocaleGenLines( configurationMap, m_localeGenLines );
    getAdjustLiveTimezone( configurationMap, m_adjustLiveTimezone );
    getStartingTimezone( configurationMap, m_startingTimezone );
    getGeoIP( configurationMap, m_geoip );

#ifndef BUILD_AS_TEST
    if ( m_geoip && m_geoip->isValid() )
    {
        connect(
            Calamares::ModuleManager::instance(), &Calamares::ModuleManager::modulesLoaded, this, &Config::startGeoIP );
    }
#endif
}

Calamares::JobList
Config::createJobs()
{
    Calamares::JobList list;
    const auto* location = currentLocation();

    if ( location )
    {
        Calamares::Job* j = new SetTimezoneJob( location->region(), location->zone() );
        list.append( Calamares::job_ptr( j ) );
    }

    return list;
}

void
Config::finalizeGlobalStorage() const
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();
    updateGSLocale( gs, localeConfiguration() );
    updateGSLocation( gs, currentLocation() );
}


void
Config::startGeoIP()
{
    if ( m_geoip && m_geoip->isValid() )
    {
        auto& network = CalamaresUtils::Network::Manager::instance();
        if ( network.hasInternet() || network.synchronousPing( m_geoip->url() ) )
        {
            using Watcher = QFutureWatcher< CalamaresUtils::GeoIP::RegionZonePair >;
            m_geoipWatcher = std::make_unique< Watcher >();
            m_geoipWatcher->setFuture( m_geoip->query() );
            connect( m_geoipWatcher.get(), &Watcher::finished, this, &Config::completeGeoIP );
        }
    }
}

void
Config::completeGeoIP()
{
    if ( !currentLocation() )
    {
        auto r = m_geoipWatcher->result();
        if ( r.isValid() )
        {
            m_startingTimezone = r;
        }
        else
        {
            cWarning() << "GeoIP returned invalid result.";
        }
    }
    else
    {
        cWarning() << "GeoIP result ignored because a location is already set.";
    }
    m_geoipWatcher.reset();
    m_geoip.reset();
}
