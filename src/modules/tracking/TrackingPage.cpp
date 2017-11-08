/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
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

#include "TrackingPage.h"

#include "ui_page_trackingstep.h"

#include "Branding.h"
#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "ViewManager.h"

#include <QApplication>
#include <QBoxLayout>
#include <QDesktopServices>
#include <QFocusEvent>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>

TrackingPage::TrackingPage(QWidget *parent)
    : QWidget( parent )
    , ui( new Ui::TrackingPage )
{
    using StringEntry = Calamares::Branding::StringEntry;

    ui->setupUi( this );
    CALAMARES_RETRANSLATE(
        ui->retranslateUi( this );
        ui->installExplanation->setText( tr( "Installation tracking helps %1 count how many people use it. If you enable install-tracking, at the end of the installation, information about your hardware will be sent <b>one time only</b> to our servers. To see what will be sent, click on the help-icon." ).arg( *StringEntry::ShortProductName ) );
        ui->machineExplanation->setText( tr( "Machine tracking helps %1 count how many people use it on an ongoing basis. If you enable machine-tracking, the system will send limited information about your hardware and installed software <b>periodically</b> to our servers. For information about the kind of information being sent, click on the help icon." ).arg( *StringEntry::ShortProductName ) );
        ui->userExplanation->setText( tr( "User tracking helps %1 understand how people use the system and the applications. If you enable user-tracking, the system will send information about your use of the installed software <b>regularly</b> to our servers. For information about the kind of information being sent and the policies that apply, click on the help icon." ).arg( *StringEntry::ShortProductName ) );
    )
}

void TrackingPage::setTrackingOption(TrackingType t, bool setting, bool user)
{
    QGroupBox* group = nullptr;
    QCheckBox* check = nullptr;

    switch ( t )
    {
        case TrackingType::InstallTracking:
            group = ui->installTrackingBox;
            check = ui->installCheckBox;
            break;
        case TrackingType::MachineTracking:
            group = ui->machineTrackingBox;
            check = ui->machineCheckBox;
            break;
        case TrackingType::UserTracking:
            group = ui->userTrackingBox;
            check = ui->userCheckBox;
            break;
    }

    if ( (group != nullptr) && (check != nullptr))
    {
        if ( setting )
            group->show();
        else
            group->hide();

        check->setChecked( user );
    }
    else
        cDebug() << "WARNING: unknown tracking option" << int(t);
}

bool TrackingPage::getTrackingOption(TrackingType t)
{
    QCheckBox* check = nullptr;

    switch ( t )
    {
        case TrackingType::InstallTracking:
            check = ui->installCheckBox;
            break;
        case TrackingType::MachineTracking:
            check = ui->machineCheckBox;
            break;
        case TrackingType::UserTracking:
            check = ui->userCheckBox;
            break;
    }

    return (check != nullptr) && check->isChecked();
}

void TrackingPage::setTrackingPolicy(TrackingType t, QString url)
{
    QToolButton *button = nullptr;
    switch( t )
    {
        case TrackingType::InstallTracking:
            button = ui->installPolicyButton;
            break;
        case TrackingType::MachineTracking:
            button = ui->machinePolicyButton;
            break;
        case TrackingType::UserTracking:
            button = ui->userPolicyButton;
            break;
    }

    if ( button != nullptr )
        if ( url.isEmpty() )
            button->hide();
        else
        {
            connect( button, &QToolButton::clicked, [url]{ QDesktopServices::openUrl( url ); } );
            cDebug() << "Tracking policy" << int(t) << "set to" << url;
        }
    else
        cDebug() << "WARNING: unknown tracking option" << int(t);
}
