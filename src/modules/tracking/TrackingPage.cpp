/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "TrackingPage.h"

#include "Config.h"
#include "ui_page_trackingstep.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "ViewManager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QDesktopServices>
#include <QLabel>

TrackingPage::TrackingPage( Config* config, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::TrackingPage )
{
    ui->setupUi( this );
    CALAMARES_RETRANSLATE_SLOT( &TrackingPage::retranslate );

    ui->noneCheckBox->setChecked( true );
    ui->noneCheckBox->setEnabled( false );
    connect( ui->noneCheckBox, &QCheckBox::stateChanged, this, &TrackingPage::buttonNoneChecked );

    // Each "panel" of configuration has the same kind of setup,
    // where the xButton and xCheckBox is connected to the xTracking
    // configuration object; that takes macro-trickery, unfortunately.
#define trackingSetup( x ) \
    do \
    { \
        connect( ui->x##CheckBox, &QCheckBox::stateChanged, this, &TrackingPage::buttonChecked ); \
        connect( ui->x##CheckBox, \
                 &QCheckBox::stateChanged, \
                 config->x##Tracking(), \
                 QOverload< bool >::of( &TrackingStyleConfig::setTracking ) ); \
        connect( config->x##Tracking(), \
                 &TrackingStyleConfig::trackingChanged, \
                 this, \
                 [ this, config ]() \
                 { this->trackerChanged( config->x##Tracking(), this->ui->x##Group, this->ui->x##CheckBox ); } ); \
        connect( ui->x##PolicyButton, \
                 &QAbstractButton::clicked, \
                 config, \
                 [ config ] \
                 { \
                     QString url( config->x##Tracking()->policy() ); \
                     if ( !url.isEmpty() ) \
                     { \
                         QDesktopServices::openUrl( url ); \
                     } \
                 } ); \
    } while ( false )

    trackingSetup( install );
    trackingSetup( machine );
    trackingSetup( user );

#undef trackingSetup

    connect( config,
             &Config::generalPolicyChanged,
             [ this ]( const QString& url ) { this->ui->generalPolicyLabel->setVisible( !url.isEmpty() ); } );
    connect( ui->generalPolicyLabel,
             &QLabel::linkActivated,
             [ config ]
             {
                 QString url( config->generalPolicy() );
                 if ( !url.isEmpty() )
                 {
                     QDesktopServices::openUrl( url );
                 }
             } );

    retranslate();
}

void
TrackingPage::retranslate()
{
    QString product = Calamares::Branding::instance()->shortProductName();
    ui->retranslateUi( this );
    ui->generalExplanation->setText(
        tr( "Tracking helps %1 to see how often it is installed, what hardware it is installed on and "
            "which applications are used. To see what "
            "will be sent, please click the help icon next to each area." )
            .arg( product ) );
    ui->installExplanation->setText(
        tr( "By selecting this you will send information about your installation and hardware. This information "
            "will only be sent <b>once</b> after the installation finishes." ) );
    ui->machineExplanation->setText(
        tr( "By selecting this you will periodically send information about your <b>machine</b> installation, "
            "hardware and applications, to %1." )
            .arg( product ) );
    ui->userExplanation->setText(
        tr( "By selecting this you will regularly send information about your "
            "<b>user</b> installation, hardware, applications and application usage patterns, to %1." )
            .arg( product ) );
}

bool
TrackingPage::anyOtherChecked() const
{
    return ui->installCheckBox->isChecked() || ui->machineCheckBox->isChecked() || ui->userCheckBox->isChecked();
}


void
TrackingPage::buttonNoneChecked( int state )
{
    if ( state )
    {
        cDebug() << "Unchecking all other buttons because 'None' was checked";
        ui->installCheckBox->setChecked( false );
        ui->machineCheckBox->setChecked( false );
        ui->userCheckBox->setChecked( false );
        ui->noneCheckBox->setEnabled( false );
    }
}

void
TrackingPage::buttonChecked( int state )
{
    if ( state )
    {
        // Can't have none checked, if another one is
        ui->noneCheckBox->setEnabled( true );
        ui->noneCheckBox->setChecked( false );
    }
    else
    {
        if ( !anyOtherChecked() )
        {
            ui->noneCheckBox->setChecked( true );
            ui->noneCheckBox->setEnabled( false );
        }
    }
}

void
TrackingPage::trackerChanged( TrackingStyleConfig* config, QWidget* panel, QCheckBox* check )
{
    panel->setVisible( config->isConfigurable() );
    check->setChecked( config->isEnabled() );
}
