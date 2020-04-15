/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2019-2020, Adriaan de Groot <groot@kde.org>
 *   Copyright 2020, Camilo Higuita <milo.h@aol.com>
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

#include "LCLocaleDialog.h"
#include "SetTimezoneJob.h"
#include "timezonewidget/timezonewidget.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"

#include "locale/Label.h"
#include "locale/TimeZone.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QDebug>
#include <QFile>
#include <QProcess>

Config::Config( QObject* parent )
    : QObject( parent )
    , m_regionList( CalamaresUtils::Locale::TZRegion::fromZoneTab() )
    , m_regionModel( new CalamaresUtils::Locale::CStringListModel( m_regionList ) )
    , m_zonesModel( new CalamaresUtils::Locale::CStringListModel() )
    , m_blockTzWidgetSet( false )
{
    connect( m_regionModel, &CalamaresUtils::Locale::CStringListModel::currentIndexChanged, [&]() {
        m_zonesModel->setList( static_cast< const CalamaresUtils::Locale::TZRegion* >(
                                   m_regionModel->item( m_regionModel->currentIndex() ) )
                                   ->zones() );
        updateLocaleLabels();
    } );

    connect(
        m_zonesModel, &CalamaresUtils::Locale::CStringListModel::currentIndexChanged, [&]() { updateLocaleLabels(); } );
}

Config::~Config()
{
    qDeleteAll( m_regionList );
}

CalamaresUtils::Locale::CStringListModel*
Config::zonesModel() const
{
    return m_zonesModel;
}

CalamaresUtils::Locale::CStringListModel*
Config::regionModel() const
{
    return m_regionModel;
}

void
Config::setLocaleInfo( const QString& initialRegion, const QString& initialZone, const QString& localeGenPath )
{
    using namespace CalamaresUtils::Locale;

    cDebug() << "REGION MODEL SIZE" << initialRegion << initialZone;
    auto* region = m_regionList.find< TZRegion >( initialRegion );
    if ( region && region->zones().find< TZZone >( initialZone ) )
    {
        this->m_regionModel->setCurrentIndex( m_regionModel->indexOf( initialRegion ) );
        m_zonesModel->setList( region->zones() );
        this->m_zonesModel->setCurrentIndex( m_zonesModel->indexOf( initialZone ) );
    }
    else
    {
        this->m_regionModel->setCurrentIndex( m_regionModel->indexOf( "America" ) );
        m_zonesModel->setList(
            static_cast< const TZRegion* >( m_regionModel->item( m_regionModel->currentIndex() ) )->zones() );
        this->m_zonesModel->setCurrentIndex( m_zonesModel->indexOf( "New_York" ) );
    }

    // Some distros come with a meaningfully commented and easy to parse locale.gen,
    // and others ship a separate file /usr/share/i18n/SUPPORTED with a clean list of
    // supported locales. We first try that one, and if it doesn't exist, we fall back
    // to parsing the lines from locale.gen
    m_localeGenLines.clear();
    QFile supported( "/usr/share/i18n/SUPPORTED" );
    QByteArray ba;

    if ( supported.exists() && supported.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        ba = supported.readAll();
        supported.close();

        const auto lines = ba.split( '\n' );
        for ( const QByteArray& line : lines )
        {
            m_localeGenLines.append( QString::fromLatin1( line.simplified() ) );
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

            m_localeGenLines.append( lineString );
        }
    }

    if ( m_localeGenLines.isEmpty() )
    {
        cWarning() << "cannot acquire a list of available locales."
                   << "The locale and localecfg modules will be broken as long as this "
                      "system does not provide"
                   << "\n\t  "
                   << "* a well-formed" << supported.fileName() << "\n\tOR"
                   << "* a well-formed"
                   << ( localeGenPath.isEmpty() ? QLatin1String( "/etc/locale.gen" ) : localeGenPath ) << "\n\tOR"
                   << "* a complete pre-compiled locale-gen database which allows complete locale -a output.";
        return;  // something went wrong and there's nothing we can do about it.
    }

    // Assuming we have a list of supported locales, we usually only want UTF-8 ones
    // because it's not 1995.
    for ( auto it = m_localeGenLines.begin(); it != m_localeGenLines.end(); )
    {
        if ( !it->contains( "UTF-8", Qt::CaseInsensitive ) && !it->contains( "utf8", Qt::CaseInsensitive ) )
        {
            it = m_localeGenLines.erase( it );
        }
        else
        {
            ++it;
        }
    }

    // We strip " UTF-8" from "en_US.UTF-8 UTF-8" because it's redundant redundant.
    for ( auto it = m_localeGenLines.begin(); it != m_localeGenLines.end(); ++it )
    {
        if ( it->endsWith( " UTF-8" ) )
        {
            it->chop( 6 );
        }
        *it = it->simplified();
    }
    updateGlobalStorage();
    updateLocaleLabels();
}

void
Config::updateGlobalLocale()
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();
    const QString bcp47 = m_selectedLocaleConfiguration.toBcp47();
    gs->insert( "locale", bcp47 );
}

void
Config::updateGlobalStorage()
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();

    const auto* location = currentLocation();
    bool locationChanged = ( location->region() != gs->value( "locationRegion" ) )
        || ( location->zone() != gs->value( "locationZone" ) );
#ifdef DEBUG_TIMEZONES
    if ( locationChanged )
    {
        cDebug() << "Location changed" << gs->value( "locationRegion" ) << ',' << gs->value( "locationZone" ) << "to"
                 << location->region() << ',' << location->zone();
    }
#endif
    gs->insert( "locationRegion", location->region() );
    gs->insert( "locationZone", location->zone() );

    updateGlobalLocale();

    // If we're in chroot mode (normal install mode), then we immediately set the
    // timezone on the live system. When debugging timezones, don't bother.
#ifndef DEBUG_TIMEZONES
    if ( locationChanged && Calamares::Settings::instance()->doChroot() )
    {
        QProcess::execute( "timedatectl",  // depends on systemd
                           { "set-timezone", location->region() + '/' + location->zone() } );
    }
#endif

    // Preserve those settings that have been made explicit.
    auto newLocale = guessLocaleConfiguration();
    if ( !m_selectedLocaleConfiguration.isEmpty() && m_selectedLocaleConfiguration.explicit_lang )
    {
        newLocale.setLanguage( m_selectedLocaleConfiguration.language() );
    }
    if ( !m_selectedLocaleConfiguration.isEmpty() && m_selectedLocaleConfiguration.explicit_lc )
    {
        newLocale.lc_numeric = m_selectedLocaleConfiguration.lc_numeric;
        newLocale.lc_time = m_selectedLocaleConfiguration.lc_time;
        newLocale.lc_monetary = m_selectedLocaleConfiguration.lc_monetary;
        newLocale.lc_paper = m_selectedLocaleConfiguration.lc_paper;
        newLocale.lc_name = m_selectedLocaleConfiguration.lc_name;
        newLocale.lc_address = m_selectedLocaleConfiguration.lc_address;
        newLocale.lc_telephone = m_selectedLocaleConfiguration.lc_telephone;
        newLocale.lc_measurement = m_selectedLocaleConfiguration.lc_measurement;
        newLocale.lc_identification = m_selectedLocaleConfiguration.lc_identification;
    }
    newLocale.explicit_lang = m_selectedLocaleConfiguration.explicit_lang;
    newLocale.explicit_lc = m_selectedLocaleConfiguration.explicit_lc;

    m_selectedLocaleConfiguration = newLocale;
    updateLocaleLabels();
}

void
Config::updateLocaleLabels()
{
    LocaleConfiguration lc
        = m_selectedLocaleConfiguration.isEmpty() ? guessLocaleConfiguration() : m_selectedLocaleConfiguration;
    auto labels = prettyLocaleStatus( lc );
    emit prettyStatusChanged();
}


std::pair< QString, QString >
Config::prettyLocaleStatus( const LocaleConfiguration& lc ) const
{
    using CalamaresUtils::Locale::Label;

    Label lang( lc.language(), Label::LabelFormat::AlwaysWithCountry );
    Label num( lc.lc_numeric, Label::LabelFormat::AlwaysWithCountry );

    return std::make_pair< QString, QString >(
        tr( "The system language will be set to %1." ).arg( lang.label() ),
        tr( "The numbers and dates locale will be set to %1." ).arg( num.label() ) );
}

Calamares::JobList
Config::createJobs()
{
    QList< Calamares::job_ptr > list;
    const CalamaresUtils::Locale::TZZone* location = currentLocation();

    Calamares::Job* j = new SetTimezoneJob( location->region(), location->zone() );
    list.append( Calamares::job_ptr( j ) );

    return list;
}

LocaleConfiguration
Config::guessLocaleConfiguration() const
{
    return LocaleConfiguration::fromLanguageAndLocation(
        QLocale().name(), m_localeGenLines, currentLocation() ? currentLocation()->country() : "" );
}

QMap< QString, QString >
Config::localesMap()
{
    return m_selectedLocaleConfiguration.isEmpty() ? guessLocaleConfiguration().toMap()
                                                   : m_selectedLocaleConfiguration.toMap();
}

QString
Config::prettyStatus() const
{
    QString status;
    status += tr( "Set timezone to %1/%2.<br/>" )
                  .arg( m_regionModel->item( m_regionModel->currentIndex() )->tr() )
                  .arg( m_zonesModel->item( m_zonesModel->currentIndex() )->tr() );

    LocaleConfiguration lc
        = m_selectedLocaleConfiguration.isEmpty() ? guessLocaleConfiguration() : m_selectedLocaleConfiguration;
    auto labels = prettyLocaleStatus( lc );
    status += labels.first + "<br/>";
    status += labels.second + "<br/>";

    return status;
}


const CalamaresUtils::Locale::TZZone*
Config::currentLocation() const
{
    return static_cast< const CalamaresUtils::Locale::TZZone* >( m_zonesModel->item( m_zonesModel->currentIndex() ) );
}
