/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>


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

    QLabel* cityLabel = new QLabel( tr( "Region:" ), this );
    bottomLayout->addWidget( cityLabel );

    m_regionCombo = new QComboBox( this );
    bottomLayout->addWidget( m_regionCombo );
    m_regionCombo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    cityLabel->setBuddy( m_regionCombo );

    bottomLayout->addSpacing( 20 );

    QLabel* timezoneLabel = new QLabel( tr( "Zone:" ), this );
    bottomLayout->addWidget( timezoneLabel );

    m_timezoneCombo = new QComboBox( this );
    m_timezoneCombo->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    bottomLayout->addWidget( m_timezoneCombo );
    timezoneLabel->setBuddy( m_timezoneCombo );

    mainLayout->addStretch();

    setLayout( mainLayout );

    connect( m_regionCombo,
             static_cast< void ( QComboBox::* )( const QString& ) >( &QComboBox::currentIndexChanged ),
             [this]( const QString& current )
    {
        QHash< QString, QList< LocaleGlobal::Location > > regions = LocaleGlobal::getLocations();
        if ( !regions.contains( current ) )
            return;

        m_timezoneCombo->blockSignals( true );

        m_timezoneCombo->clear();

        QList< LocaleGlobal::Location > zones = regions.value( current );
        foreach ( const LocaleGlobal::Location& zone, zones )
        {
            m_timezoneCombo->addItem( zone.zone );
        }

        m_timezoneCombo->model()->sort( 0 );

        m_timezoneCombo->blockSignals( false );

        m_timezoneCombo->currentIndexChanged( m_timezoneCombo->currentText() );
    });

    connect( m_timezoneCombo,
             static_cast< void ( QComboBox::* )( const QString& ) >( &QComboBox::currentIndexChanged ),
             [this]( const QString& current )
    {
        if ( !m_blockTzWidgetSet )
            m_tzWidget->setCurrentLocation( m_regionCombo->currentText(), current );
    });

    connect( m_tzWidget, &TimeZoneWidget::locationChanged,
             [this]( LocaleGlobal::Location location )
    {
        m_blockTzWidgetSet = true;

        // Set region index
        int index = m_regionCombo->findText( location.region );
        if ( index < 0 )
            return;

        m_regionCombo->setCurrentIndex( index );

        // Set zone index
        index = m_timezoneCombo->findText( location.zone );
        if ( index < 0 )
            return;

        m_timezoneCombo->setCurrentIndex( index );

        m_blockTzWidgetSet = false;
    });
}


void
LocalePage::init()
{
    m_regionCombo->blockSignals( true );
    m_timezoneCombo->blockSignals( true );

    // Setup locations
    QHash< QString, QList< LocaleGlobal::Location > > regions = LocaleGlobal::getLocations();

    QStringList keys = regions.keys();
    keys.sort();

    foreach ( const QString& key, keys )
    {
        m_regionCombo->addItem( key );
    }

    m_regionCombo->blockSignals( false );
    m_timezoneCombo->blockSignals( false );

    m_regionCombo->currentIndexChanged( m_regionCombo->currentText() );

    // Default location
    // TODO: make configurable from module.conf
    m_tzWidget->setCurrentLocation( "Europe", "Berlin" );
    emit m_tzWidget->locationChanged( m_tzWidget->getCurrentLocation() );
}

