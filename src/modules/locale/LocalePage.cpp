/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QProcess>


LocalePage::LocalePage( QWidget* parent )
    : QWidget()
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

        QList< LocaleGlobal::Location > zones = regions.value( m_regionCombo->currentData().toString() );
        foreach ( const LocaleGlobal::Location& zone, zones )
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
             [this]()
    {
        LCLocaleDialog* dlg = new LCLocaleDialog( lcLocale(),
                                                  m_localeGenLines,
                                                  this );
        dlg->exec();
        if ( dlg->result() == QDialog::Accepted &&
             !dlg->selectedLCLocale().isEmpty() )
        {
            m_selectedLocale = dlg->selectedLCLocale();
            m_localeLabel->setText( tr( "The system locale is set to %1." )
                                    .arg( prettyLCLocale( m_selectedLocale ) ) );
        }

        dlg->deleteLater();
    } );

    CALAMARES_RETRANSLATE(
        m_regionLabel->setText( tr( "Region:" ) );
        m_zoneLabel->setText( tr( "Zone:" ) );

        m_localeLabel->setText( tr( "The system locale is set to %1." )
                                .arg( prettyLCLocale( lcLocale() ) ) );

        m_localeChangeButton->setText( tr( "&Change..." ) );
    )
}


LocalePage::~LocalePage()
{}


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
        foreach ( const LocaleGlobal::Location& location, locations )
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
        m_tzWidget->setCurrentLocation( "Europe", "Berlin" );
    }
    emit m_tzWidget->locationChanged( m_tzWidget->getCurrentLocation() );

    // Fill in meaningful locale/charset lines from locale.gen
    m_localeGenLines.clear();
    QFile localeGen( localeGenPath );
    QByteArray ba;
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
    foreach ( QByteArray line, ba.split( '\n' ) )
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


QString
LocalePage::prettyStatus() const
{
    QString status;
    status += tr( "Set timezone to %1/%2.<br/>" )
              .arg( m_regionCombo->currentText() )
              .arg( m_zoneCombo->currentText() );

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


QString
LocalePage::lcLocale()
{
    return m_selectedLocale.isEmpty() ? guessLCLocale() : m_selectedLocale;
}


void
LocalePage::onActivate()
{
    m_regionCombo->setFocus();
}


QString
LocalePage::guessLCLocale()
{
    QLocale myLocale = QLocale();

    if ( m_localeGenLines.isEmpty() )
        return "en_US.UTF-8 UTF-8";

    QString myLanguage = myLocale.name().split( '_' ).first();
    QStringList linesForLanguage;
    foreach ( QString line, m_localeGenLines )
    {
        if ( line.startsWith( myLanguage ) )
            linesForLanguage.append( line );
    }

    if ( linesForLanguage.length() == 0 )
        return "en_US.UTF-8 UTF-8";
    else if ( linesForLanguage.length() == 1 )
        return linesForLanguage.first();
    else
    {
        QStringList linesForLanguageUtf;
        foreach ( QString line, linesForLanguage )
        {
            if ( line.contains( "UTF-8" ) )
                linesForLanguageUtf.append( line );
        }

        if ( linesForLanguageUtf.length() == 1 )
            return linesForLanguageUtf.first();
    }

    // FIXME: use reverse geocoding to guess the country
    QString prefix = myLocale.name();
    QStringList linesForLanguageAndCountry;
    foreach ( QString line, linesForLanguage )
    {
        if ( line.startsWith( prefix ) )
            linesForLanguageAndCountry.append( line );
    }

    if ( linesForLanguageAndCountry.length() == 0 )
        return "en_US.UTF-8 UTF-8";
    else if ( linesForLanguageAndCountry.length() == 1 )
        return linesForLanguageAndCountry.first();
    else
    {
        QStringList linesForLanguageAndCountryUtf;
        foreach ( QString line, linesForLanguageAndCountry )
        {
            if ( line.contains( "UTF-8" ) )
                linesForLanguageAndCountryUtf.append( line );
        }

        if ( linesForLanguageAndCountryUtf.length() == 1 )
            return linesForLanguageAndCountryUtf.first();
    }

    return "en_US.UTF-8 UTF-8";
}


QString
LocalePage::prettyLCLocale( const QString& lcLocale )
{
    QString localeString = lcLocale;
    if ( localeString.endsWith( " UTF-8" ) )
        localeString.remove( " UTF-8" );
    return localeString;
}

void
LocalePage::updateGlobalStorage()
{
    LocaleGlobal::Location location = m_tzWidget->getCurrentLocation();
    Calamares::JobQueue::instance()->globalStorage()
            ->insert( "locationRegion", location.region );
    Calamares::JobQueue::instance()->globalStorage()
            ->insert( "locationZone", location.zone );
}
