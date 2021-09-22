/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "LocalePage.h"

#include "Config.h"
#include "LCLocaleDialog.h"
#include "timezonewidget/timezonewidget.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/RAII.h"
#include "utils/Retranslator.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QPointer>
#include <QPushButton>

LocalePage::LocalePage( Config* config, QWidget* parent )
    : QWidget( parent )
    , m_config( config )
    , m_blockTzWidgetSet( false )
{
    QBoxLayout* mainLayout = new QVBoxLayout;

    QBoxLayout* tzwLayout = new QHBoxLayout;
    m_tzWidget = new TimeZoneWidget( m_config->zonesModel(), this );
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

    // Set up the location before connecting signals, to avoid a signal
    // storm as various parts interact.
    {
        auto* regions = m_config->regionModel();
        auto* zones = m_config->regionalZonesModel();
        auto* location = m_config->currentLocation();
        zones->setRegion( location->region() );
        m_regionCombo->setModel( regions );
        m_zoneCombo->setModel( zones );
        m_tzWidget->setCurrentLocation( location );
        locationChanged( location );  // doesn't inform TZ widget
    }

    connect( config, &Config::currentLCStatusChanged, m_formatsLabel, &QLabel::setText );
    connect( config, &Config::currentLanguageStatusChanged, m_localeLabel, &QLabel::setText );
    connect( config, &Config::currentLocationChanged, m_tzWidget, &TimeZoneWidget::setCurrentLocation );
    connect( config, &Config::currentLocationChanged, this, &LocalePage::locationChanged );
    connect( m_tzWidget,
             &TimeZoneWidget::locationChanged,
             config,
             QOverload< const CalamaresUtils::Locale::TimeZoneData* >::of( &Config::setCurrentLocation ) );

    connect( m_regionCombo, QOverload< int >::of( &QComboBox::currentIndexChanged ), this, &LocalePage::regionChanged );
    connect( m_zoneCombo, QOverload< int >::of( &QComboBox::currentIndexChanged ), this, &LocalePage::zoneChanged );

    connect( m_localeChangeButton, &QPushButton::clicked, this, &LocalePage::changeLocale );
    connect( m_formatsChangeButton, &QPushButton::clicked, this, &LocalePage::changeFormats );

    CALAMARES_RETRANSLATE_SLOT( &LocalePage::updateLocaleLabels );
}


LocalePage::~LocalePage() {}


void
LocalePage::updateLocaleLabels()
{
    m_regionLabel->setText( tr( "Region:" ) );
    m_zoneLabel->setText( tr( "Zone:" ) );
    m_localeChangeButton->setText( tr( "&Change..." ) );
    m_formatsChangeButton->setText( tr( "&Change..." ) );
    m_localeLabel->setText( m_config->currentLanguageStatus() );
    m_formatsLabel->setText( m_config->currentLCStatus() );
}


void
LocalePage::onActivate()
{
    m_regionCombo->setFocus();
    updateLocaleLabels();
}


void
LocalePage::regionChanged( int currentIndex )
{
    using namespace CalamaresUtils::Locale;

    QString selectedRegion = m_regionCombo->itemData( currentIndex ).toString();
    {
        cSignalBlocker z( m_zoneCombo );
        m_config->regionalZonesModel()->setRegion( selectedRegion );
    }
    m_zoneCombo->currentIndexChanged( 0 );
}

void
LocalePage::zoneChanged( int currentIndex )
{
    if ( !m_blockTzWidgetSet )
    {
        m_config->setCurrentLocation( m_regionCombo->currentData().toString(),
                                      m_zoneCombo->itemData( currentIndex ).toString() );
    }
}

void
LocalePage::locationChanged( const CalamaresUtils::Locale::TimeZoneData* location )
{
    if ( !location )
    {
        return;
    }
    cScopedAssignment b( &m_blockTzWidgetSet, true, false );

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
}

void
LocalePage::changeLocale()
{
    QPointer< LCLocaleDialog > dlg(
        new LCLocaleDialog( m_config->localeConfiguration().language(), m_config->supportedLocales(), this ) );
    dlg->exec();
    if ( dlg && dlg->result() == QDialog::Accepted && !dlg->selectedLCLocale().isEmpty() )
    {
        m_config->setLanguageExplicitly( dlg->selectedLCLocale() );
        updateLocaleLabels();
    }

    delete dlg;
}


void
LocalePage::changeFormats()
{
    QPointer< LCLocaleDialog > dlg(
        new LCLocaleDialog( m_config->localeConfiguration().lc_numeric, m_config->supportedLocales(), this ) );
    dlg->exec();
    if ( dlg && dlg->result() == QDialog::Accepted && !dlg->selectedLCLocale().isEmpty() )
    {
        m_config->setLCLocaleExplicitly( dlg->selectedLCLocale() );
        updateLocaleLabels();
    }

    delete dlg;
}
