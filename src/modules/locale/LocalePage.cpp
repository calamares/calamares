/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
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

#include "Config.h"
#include "SetTimezoneJob.h"
#include "timezonewidget/timezonewidget.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "LCLocaleDialog.h"
#include "Settings.h"
#include "locale/Label.h"
#include "locale/TimeZone.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/Retranslator.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QFile>
#include <QLabel>
#include <QProcess>
#include <QPushButton>

LocalePage::LocalePage( Config* config, QWidget* parent )
    : QWidget( parent )
    , m_config( config )
    , m_blockTzWidgetSet( false )
{
    QBoxLayout* mainLayout = new QVBoxLayout;

    QBoxLayout* tzwLayout = new QHBoxLayout;
    m_tzWidget = new TimeZoneWidget( config->timezoneData(), this );
    tzwLayout->addStretch();
    tzwLayout->addWidget( m_tzWidget );
    tzwLayout->addStretch();
    // Adjust for margins and spacing in this page
    m_tzWidget->setMinimumHeight( m_tzWidget->minimumHeight() + 12 );  // 2 * spacing

    QBoxLayout* zoneAndRegionLayout = new QHBoxLayout;
    m_regionLabel = new QLabel( this );
    zoneAndRegionLayout->addWidget( m_regionLabel );

    m_regionCombo = new QComboBox( this );
    zoneAndRegionLayout->addWidget( m_regionCombo );
    m_regionCombo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    m_regionLabel->setBuddy( m_regionCombo );

    zoneAndRegionLayout->addSpacing( 20 );

    m_zoneLabel = new QLabel( this );
    zoneAndRegionLayout->addWidget( m_zoneLabel );

    m_zoneCombo = new QComboBox( this );
    m_zoneCombo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    zoneAndRegionLayout->addWidget( m_zoneCombo );
    m_zoneLabel->setBuddy( m_zoneCombo );


    QBoxLayout* localeLayout = new QHBoxLayout;
    m_localeLabel = new QLabel( this );
    m_localeLabel->setWordWrap( true );
    m_localeLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    localeLayout->addWidget( m_localeLabel );

    m_localeChangeButton = new QPushButton( this );
    m_localeChangeButton->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    localeLayout->addWidget( m_localeChangeButton );

    QBoxLayout* formatsLayout = new QHBoxLayout;
    m_formatsLabel = new QLabel( this );
    m_formatsLabel->setWordWrap( true );
    m_formatsLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    formatsLayout->addWidget( m_formatsLabel );

    m_formatsChangeButton = new QPushButton( this );
    m_formatsChangeButton->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    formatsLayout->addWidget( m_formatsChangeButton );

    mainLayout->addLayout( tzwLayout );
    mainLayout->addStretch();
    mainLayout->addLayout( zoneAndRegionLayout );
    mainLayout->addStretch();
    mainLayout->addLayout( localeLayout );
    mainLayout->addLayout( formatsLayout );
    setMinimumWidth( m_tzWidget->width() );
    setLayout( mainLayout );

    connect( config, &Config::currentLocationChanged, m_tzWidget, &TimeZoneWidget::setCurrentLocation );
    connect( config, &Config::currentLocationChanged, this, &LocalePage::locationChanged );
    connect( m_tzWidget,
             &TimeZoneWidget::locationChanged,
             config,
             QOverload< const CalamaresUtils::Locale::TZZone* >::of( &Config::setCurrentLocation ) );

    connect( m_regionCombo, QOverload< int >::of( &QComboBox::currentIndexChanged ), this, &LocalePage::regionChanged );
    connect( m_zoneCombo, QOverload< int >::of( &QComboBox::currentIndexChanged ), this, &LocalePage::zoneChanged );

    connect( m_localeChangeButton, &QPushButton::clicked, this, &LocalePage::changeLocale );
    connect( m_formatsChangeButton, &QPushButton::clicked, this, &LocalePage::changeFormats );

    CALAMARES_RETRANSLATE_SLOT( &LocalePage::updateLocaleLabels )

    m_regionCombo->setModel( m_config->regionModel() );
    m_regionCombo->currentIndexChanged( m_regionCombo->currentIndex() );
    updateGlobalStorage();
}


LocalePage::~LocalePage() {}


void
LocalePage::updateLocaleLabels()
{
    m_regionLabel->setText( tr( "Region:" ) );
    m_zoneLabel->setText( tr( "Zone:" ) );
    m_localeChangeButton->setText( tr( "&Change..." ) );
    m_formatsChangeButton->setText( tr( "&Change..." ) );

    LocaleConfiguration lc = m_config->localeConfiguration();
    auto labels = prettyLocaleStatus( lc );
    m_localeLabel->setText( labels.first );
    m_formatsLabel->setText( labels.second );
}

std::pair< QString, QString >
LocalePage::prettyLocaleStatus( const LocaleConfiguration& lc ) const
{
    using CalamaresUtils::Locale::Label;

    Label lang( lc.language(), Label::LabelFormat::AlwaysWithCountry );
    Label num( lc.lc_numeric, Label::LabelFormat::AlwaysWithCountry );

    return std::make_pair< QString, QString >(
        tr( "The system language will be set to %1." ).arg( lang.label() ),
        tr( "The numbers and dates locale will be set to %1." ).arg( num.label() ) );
}

QString
LocalePage::prettyStatus() const
{
    QString status;
    status += tr( "Set timezone to %1/%2.<br/>" ).arg( m_regionCombo->currentText() ).arg( m_zoneCombo->currentText() );

    LocaleConfiguration lc = m_config->localeConfiguration();
    auto labels = prettyLocaleStatus( lc );
    status += labels.first + "<br/>";
    status += labels.second + "<br/>";

    return status;
}


QMap< QString, QString >
LocalePage::localesMap()
{
    return m_config->localeConfiguration().toMap();
}


void
LocalePage::onActivate()
{
    m_regionCombo->setFocus();
    updateGlobalLocale();
    updateLocaleLabels();
}


void
LocalePage::updateGlobalLocale()
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();
    const QString bcp47 = m_config->localeConfiguration().toBcp47();
    gs->insert( "locale", bcp47 );
}


void
LocalePage::updateGlobalStorage()
{
    auto* gs = Calamares::JobQueue::instance()->globalStorage();

    const auto* location = m_config->currentLocation();
    bool locationChanged = ( location->region() != gs->value( "locationRegion" ) )
        || ( location->zone() != gs->value( "locationZone" ) );

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

    updateLocaleLabels();
}

void
LocalePage::regionChanged( int currentIndex )
{
    using namespace CalamaresUtils::Locale;

    Q_UNUSED( currentIndex )
    QString selectedRegion = m_regionCombo->currentData().toString();

    TZRegion* region = m_config->timezoneData().find< TZRegion >( selectedRegion );
    if ( !region )
    {
        return;
    }

    {
        cSignalBlocker b( m_zoneCombo );
        m_zoneCombo->setModel( new CStringListModel( region->zones() ) );
    }

    m_zoneCombo->currentIndexChanged( m_zoneCombo->currentIndex() );
}

void
LocalePage::zoneChanged( int currentIndex )
{
    Q_UNUSED( currentIndex )
    if ( !m_blockTzWidgetSet )
    {
        m_config->setCurrentLocation( m_regionCombo->currentData().toString(), m_zoneCombo->currentData().toString() );
    }
    updateGlobalStorage();
}

void
LocalePage::locationChanged( const CalamaresUtils::Locale::TZZone* location )
{
    cBoolSetter< true > b( m_blockTzWidgetSet );

    // Set region index
    int index = m_regionCombo->findData( location->region() );
    if ( index < 0 )
    {
        return;
    }

    m_regionCombo->setCurrentIndex( index );

    // Set zone index
    index = m_zoneCombo->findData( location->zone() );
    if ( index < 0 )
    {
        return;
    }

    m_zoneCombo->setCurrentIndex( index );

    updateGlobalStorage();
}

void
LocalePage::changeLocale()
{
    LCLocaleDialog* dlg
        = new LCLocaleDialog( m_config->localeConfiguration().language(), m_config->supportedLocales(), this );
    dlg->exec();
    if ( dlg->result() == QDialog::Accepted && !dlg->selectedLCLocale().isEmpty() )
    {
        m_config->setLanguageExplicitly( dlg->selectedLCLocale() );
        updateGlobalLocale();
        updateLocaleLabels();
    }

    dlg->deleteLater();
}


void
LocalePage::changeFormats()
{
    LCLocaleDialog* dlg
        = new LCLocaleDialog( m_config->localeConfiguration().lc_numeric, m_config->supportedLocales(), this );
    dlg->exec();
    if ( dlg->result() == QDialog::Accepted && !dlg->selectedLCLocale().isEmpty() )
    {
        m_config->setLCLocaleExplicitly( dlg->selectedLCLocale() );
        updateLocaleLabels();
    }

    dlg->deleteLater();
}
