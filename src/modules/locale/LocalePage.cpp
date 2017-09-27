/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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

#include "LocalePage.h"

#include "timezonewidget/timezonewidget.h"
#include "SetTimezoneJob.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "LCLocaleDialog.h"
#include "Settings.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QProcess>


LocalePage::LocalePage( QWidget* parent )
    : QWidget( parent )
    , m_blockTzWidgetSet( false )
{
    QBoxLayout* mainLayout = new QVBoxLayout;

    QBoxLayout* tzwLayout = new QHBoxLayout;
    mainLayout->addLayout( tzwLayout );
    m_tzWidget = new TimeZoneWidget( this );
    tzwLayout->addStretch();
    tzwLayout->addWidget( m_tzWidget );
    tzwLayout->addStretch();
    setMinimumWidth( m_tzWidget->width() );

    QBoxLayout* bottomLayout = new QHBoxLayout;
    mainLayout->addLayout( bottomLayout );

    m_regionLabel = new QLabel( this );
    bottomLayout->addWidget( m_regionLabel );

    m_regionCombo = new QComboBox( this );
    bottomLayout->addWidget( m_regionCombo );
    m_regionCombo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    m_regionLabel->setBuddy( m_regionCombo );

    bottomLayout->addSpacing( 20 );

    m_zoneLabel = new QLabel( this );
    bottomLayout->addWidget( m_zoneLabel );

    m_zoneCombo = new QComboBox( this );
    m_zoneCombo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    bottomLayout->addWidget( m_zoneCombo );
    m_zoneLabel->setBuddy( m_zoneCombo );

    mainLayout->addStretch();

    QBoxLayout* localeLayout = new QHBoxLayout;
    m_localeLabel = new QLabel( this );
    m_localeLabel->setWordWrap( true );
    m_localeLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    localeLayout->addWidget( m_localeLabel );

    m_localeChangeButton = new QPushButton( this );
    m_localeChangeButton->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    localeLayout->addWidget( m_localeChangeButton );
    mainLayout->addLayout( localeLayout );

    QBoxLayout* formatsLayout = new QHBoxLayout;
    m_formatsLabel = new QLabel( this );
    m_formatsLabel->setWordWrap( true );
    m_formatsLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    formatsLayout->addWidget( m_formatsLabel );

    m_formatsChangeButton = new QPushButton( this );
    m_formatsChangeButton->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    formatsLayout->addWidget( m_formatsChangeButton );
    mainLayout->addLayout( formatsLayout );

    setLayout( mainLayout );

    connect( m_regionCombo,
             static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
             [this]( int currentIndex )
    {
        Q_UNUSED( currentIndex );
        QHash< QString, QList< LocaleGlobal::Location > > regions = LocaleGlobal::getLocations();
        if ( !regions.contains( m_regionCombo->currentData().toString() ) )
            return;

        m_zoneCombo->blockSignals( true );

        m_zoneCombo->clear();

        const QList< LocaleGlobal::Location > zones = regions.value( m_regionCombo->currentData().toString() );
        for ( const LocaleGlobal::Location& zone : zones )
        {
            m_zoneCombo->addItem( LocaleGlobal::Location::pretty( zone.zone ), zone.zone );
        }

        m_zoneCombo->model()->sort( 0 );

        m_zoneCombo->blockSignals( false );

        m_zoneCombo->currentIndexChanged( m_zoneCombo->currentIndex() );
    } );

    connect( m_zoneCombo,
             static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
             [this]( int currentIndex )
    {
        Q_UNUSED( currentIndex )
        if ( !m_blockTzWidgetSet )
            m_tzWidget->setCurrentLocation( m_regionCombo->currentData().toString(),
                                            m_zoneCombo->currentData().toString() );

        updateGlobalStorage();
    } );

    connect( m_tzWidget, &TimeZoneWidget::locationChanged,
             [this]( LocaleGlobal::Location location )
    {
        m_blockTzWidgetSet = true;

        // Set region index
        int index = m_regionCombo->findData( location.region );
        if ( index < 0 )
            return;

        m_regionCombo->setCurrentIndex( index );

        // Set zone index
        index = m_zoneCombo->findData( location.zone );
        if ( index < 0 )
            return;

        m_zoneCombo->setCurrentIndex( index );

        m_blockTzWidgetSet = false;

        updateGlobalStorage();
    } );

    connect( m_localeChangeButton, &QPushButton::clicked,
             [this]
    {
        LCLocaleDialog* dlg =
                new LCLocaleDialog( m_selectedLocaleConfiguration.isEmpty() ?
                                        guessLocaleConfiguration().lang :
                                        m_selectedLocaleConfiguration.lang,
                                    m_localeGenLines,
                                    this );
        dlg->exec();
        if ( dlg->result() == QDialog::Accepted &&
             !dlg->selectedLCLocale().isEmpty() )
        {
            m_selectedLocaleConfiguration.lang = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.explicit_lang = true;
            this->updateLocaleLabels();
        }

        dlg->deleteLater();
    } );

    connect( m_formatsChangeButton, &QPushButton::clicked,
             [this]
    {
        LCLocaleDialog* dlg =
                new LCLocaleDialog( m_selectedLocaleConfiguration.isEmpty() ?
                                        guessLocaleConfiguration().lc_numeric :
                                        m_selectedLocaleConfiguration.lc_numeric,
                                    m_localeGenLines,
                                    this );
        dlg->exec();
        if ( dlg->result() == QDialog::Accepted &&
             !dlg->selectedLCLocale().isEmpty() )
        {
            // TODO: improve the granularity of this setting.
            m_selectedLocaleConfiguration.lc_numeric = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.lc_time = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.lc_monetary = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.lc_paper = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.lc_name = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.lc_address = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.lc_telephone = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.lc_measurement = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.lc_identification = dlg->selectedLCLocale();
            m_selectedLocaleConfiguration.explicit_lc = true;

            this->updateLocaleLabels();
        }

        dlg->deleteLater();

    } );

    CALAMARES_RETRANSLATE(
        m_regionLabel->setText( tr( "Region:" ) );
        m_zoneLabel->setText( tr( "Zone:" ) );

        updateLocaleLabels();

        m_localeChangeButton->setText( tr( "&Change..." ) );
        m_formatsChangeButton->setText( tr( "&Change..." ) );
    )
}


LocalePage::~LocalePage()
{}


void
LocalePage::updateLocaleLabels()
{
    LocaleConfiguration lc = m_selectedLocaleConfiguration.isEmpty() ?
                             guessLocaleConfiguration() :
                             m_selectedLocaleConfiguration;
    auto labels = prettyLocaleStatus( lc );
    m_localeLabel->setText( labels.first );
    m_formatsLabel->setText( labels.second );
}


void
LocalePage::init( const QString& initialRegion,
                  const QString& initialZone,
                  const QString& localeGenPath )
{
    m_regionCombo->blockSignals( true );
    m_zoneCombo->blockSignals( true );

    // Setup locations
    QHash< QString, QList< LocaleGlobal::Location > > regions = LocaleGlobal::getLocations();

    QStringList keys = regions.keys();
    keys.sort();

    foreach ( const QString& key, keys )
    {
        m_regionCombo->addItem( LocaleGlobal::Location::pretty( key ), key );
    }

    m_regionCombo->blockSignals( false );
    m_zoneCombo->blockSignals( false );

    m_regionCombo->currentIndexChanged( m_regionCombo->currentIndex() );

    // Default location
    auto containsLocation = []( const QList< LocaleGlobal::Location >& locations,
                                const QString& zone ) -> bool
    {
        for ( const LocaleGlobal::Location& location : locations )
        {
            if ( location.zone == zone )
                return true;
        }
        return false;
    };

    if ( keys.contains( initialRegion ) &&
         containsLocation( regions.value( initialRegion ), initialZone ) )
    {
        m_tzWidget->setCurrentLocation( initialRegion, initialZone );
    }
    else
    {
        m_tzWidget->setCurrentLocation( "America", "New_York" );
    }
    emit m_tzWidget->locationChanged( m_tzWidget->getCurrentLocation() );

    // Some distros come with a meaningfully commented and easy to parse locale.gen,
    // and others ship a separate file /usr/share/i18n/SUPPORTED with a clean list of
    // supported locales. We first try that one, and if it doesn't exist, we fall back
    // to parsing the lines from locale.gen
    m_localeGenLines.clear();
    QFile supported( "/usr/share/i18n/SUPPORTED" );
    QByteArray ba;

    if ( supported.exists() &&
         supported.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
        ba = supported.readAll();
        supported.close();

        const auto lines = ba.split( '\n' );
        for ( const QByteArray &line : lines )
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
            cDebug() << "Cannot open file" << localeGenPath
                     << ". Assuming the supported languages are already built into "
                        "the locale archive.";
            QProcess localeA;
            localeA.start( "locale", QStringList() << "-a" );
            localeA.waitForFinished();
            ba = localeA.readAllStandardOutput();
        }
        const auto lines = ba.split( '\n' );
        for ( const QByteArray &line : lines )
        {
            if ( line.startsWith( "## " ) ||
                 line.startsWith( "# " ) ||
                 line.simplified() == "#" )
                continue;

            QString lineString = QString::fromLatin1( line.simplified() );
            if ( lineString.startsWith( "#" ) )
                lineString.remove( '#' );
            lineString = lineString.simplified();

            if ( lineString.isEmpty() )
                continue;

            m_localeGenLines.append( lineString );
        }
    }

    if ( m_localeGenLines.isEmpty() )
    {
        cDebug() << "WARNING: cannot acquire a list of available locales."
                    << "The locale and localecfg modules will be broken as long as this "
                    "system does not provide"
                    << "\n\t  "
                    << "* a well-formed"
                    << supported.fileName()
                    << "\n\tOR"
                    << "* a well-formed"
                    << (localeGenPath.isEmpty() ? QLatin1Literal("/etc/locale.gen") : localeGenPath)
                    << "\n\tOR"
                    << "* a complete pre-compiled locale-gen database which allows complete locale -a output.";
        return; // something went wrong and there's nothing we can do about it.
    }

    // Assuming we have a list of supported locales, we usually only want UTF-8 ones
    // because it's not 1995.
    for ( auto it = m_localeGenLines.begin(); it != m_localeGenLines.end(); )
    {
        if ( !it->contains( "UTF-8", Qt::CaseInsensitive ) &&
             !it->contains( "utf8", Qt::CaseInsensitive ) )
            it = m_localeGenLines.erase( it );
        else
            ++it;
    }

    // We strip " UTF-8" from "en_US.UTF-8 UTF-8" because it's redundant redundant.
    for ( auto it = m_localeGenLines.begin(); it != m_localeGenLines.end(); ++it )
    {
        if ( it->endsWith( " UTF-8" ) )
            it->chop( 6 );
        *it = it->simplified();
    }
    updateGlobalStorage();
}

std::pair< QString, QString > LocalePage::prettyLocaleStatus( const LocaleConfiguration& lc ) const
{
    return std::make_pair< QString, QString >(
        tr( "The system language will be set to %1." )
            .arg( prettyLCLocale( lc.lang ) ),
        tr( "The numbers and dates locale will be set to %1." )
                            .arg( prettyLCLocale( lc.lc_numeric ) )
                                             );
}

QString
LocalePage::prettyStatus() const
{
    QString status;
    status += tr( "Set timezone to %1/%2.<br/>" )
              .arg( m_regionCombo->currentText() )
              .arg( m_zoneCombo->currentText() );

    LocaleConfiguration lc = m_selectedLocaleConfiguration.isEmpty() ?
                guessLocaleConfiguration() :
                m_selectedLocaleConfiguration;
    auto labels = prettyLocaleStatus(lc);
    status += labels.first + "<br/>";
    status += labels.second + "<br/>";

    return status;
}


QList< Calamares::job_ptr >
LocalePage::createJobs()
{
    QList< Calamares::job_ptr > list;
    LocaleGlobal::Location location = m_tzWidget->getCurrentLocation();

    Calamares::Job* j = new SetTimezoneJob( location.region, location.zone );
    list.append( Calamares::job_ptr( j ) );

    return list;
}


QMap< QString, QString >
LocalePage::localesMap()
{
    return m_selectedLocaleConfiguration.isEmpty() ?
                guessLocaleConfiguration().toMap() :
                m_selectedLocaleConfiguration.toMap();
}


void
LocalePage::onActivate()
{
    m_regionCombo->setFocus();
    if ( m_selectedLocaleConfiguration.isEmpty() ||
         !m_selectedLocaleConfiguration.explicit_lang )
    {
        auto newLocale = guessLocaleConfiguration();
        m_selectedLocaleConfiguration.lang = newLocale.lang;
        updateLocaleLabels();
    }
}


LocaleConfiguration
LocalePage::guessLocaleConfiguration() const
{
    QLocale myLocale;   // User-selected language

    // If we cannot say anything about available locales
    if ( m_localeGenLines.isEmpty() )
    {
        cDebug() << "WARNING: guessLocaleConfiguration can't guess from an empty list.";
        return LocaleConfiguration::createDefault();
    }

    QString myLanguageLocale = myLocale.name();
    if ( myLanguageLocale.isEmpty() )
        return LocaleConfiguration::createDefault();

    return LocaleConfiguration::fromLanguageAndLocation( myLanguageLocale,
                                                         m_localeGenLines,
                                                         m_tzWidget->getCurrentLocation().country );
}


QString
LocalePage::prettyLCLocale( const QString& lcLocale ) const
{
    QString localeString = lcLocale;
    if ( localeString.endsWith( " UTF-8" ) )
        localeString.remove( " UTF-8" );

    QLocale locale( localeString );
    //: Language (Country)
    return tr( "%1 (%2)" ).arg( QLocale::languageToString( locale.language() ) )
                          .arg( QLocale::countryToString( locale.country() ) );
}

void
LocalePage::updateGlobalStorage()
{
    LocaleGlobal::Location location = m_tzWidget->getCurrentLocation();
    Calamares::JobQueue::instance()->globalStorage()
            ->insert( "locationRegion", location.region );
    Calamares::JobQueue::instance()->globalStorage()
            ->insert( "locationZone", location.zone );
    Calamares::JobQueue::instance()->globalStorage()
            ->insert( "locale", m_selectedLocaleConfiguration.myLanguageLocaleBcp47);

    // If we're in chroot mode (normal install mode), then we immediately set the
    // timezone on the live system.
    if ( Calamares::Settings::instance()->doChroot() )
    {
        QProcess ::execute( "timedatectl",  // depends on systemd
                            { "set-timezone",
                              location.region + '/' + location.zone } );
    }

    // Preserve those settings that have been made explicit.
    auto newLocale = guessLocaleConfiguration();
    if ( !m_selectedLocaleConfiguration.isEmpty() &&
         m_selectedLocaleConfiguration.explicit_lang )
        newLocale.lang = m_selectedLocaleConfiguration.lang;
    if ( !m_selectedLocaleConfiguration.isEmpty() &&
         m_selectedLocaleConfiguration.explicit_lc )
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
