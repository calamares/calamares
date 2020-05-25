/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#include <QButtonGroup>
#include <QDesktopServices>
#include <QLabel>

TrackingPage::TrackingPage( Config* config, QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::TrackingPage )
{
    ui->setupUi( this );
    CALAMARES_RETRANSLATE_SLOT( &TrackingPage::retranslate );

    QButtonGroup* group = new QButtonGroup( this );
    group->setExclusive( true );
    group->addButton( ui->noneRadio );
    group->addButton( ui->installRadio );
    group->addButton( ui->machineRadio );
    group->addButton( ui->userRadio );
    ui->noneRadio->setChecked( true );

    // TODO: move to .ui file
    ui->generalPolicyLabel->setTextInteractionFlags( Qt::TextBrowserInteraction );

    connect( config, &Config::generalPolicyChanged, [ this ]( const QString& url ) {
        this->ui->generalPolicyLabel->setVisible( !url.isEmpty() );
    } );
    connect( ui->generalPolicyLabel, &QLabel::linkActivated, [ config ] {
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
            "will <b>only be sent once</b> after the installation finishes." ) );
    ui->machineExplanation->setText(
        tr( "By selecting this you will <b>periodically</b> send information about your machine installation, "
            "hardware and applications, to %1." )
            .arg( product ) );
    ui->userExplanation->setText(
        tr( "By selecting this you will <b>regularly</b> send information about your "
            "user installation, hardware, applications and application usage patterns, to %1." )
            .arg( product ) );
}


void
TrackingPage::setTrackingLevel( TrackingType t )
{
    QRadioButton* button = nullptr;

    switch ( t )
    {
    case TrackingType::NoTracking:
        button = ui->noneRadio;
        break;
    case TrackingType::InstallTracking:
        button = ui->installRadio;
        break;
    case TrackingType::MachineTracking:
        button = ui->machineRadio;
        break;
    case TrackingType::UserTracking:
        button = ui->userRadio;
        break;
    }

    if ( button != nullptr )
    {
        button->setChecked( true );
    }
}
