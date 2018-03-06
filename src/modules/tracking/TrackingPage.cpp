/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include <QButtonGroup>
#include <QDesktopServices>
#include <QLabel>

TrackingPage::TrackingPage(QWidget *parent)
    : QWidget( parent )
    , ui( new Ui::TrackingPage )
{
    using StringEntry = Calamares::Branding::StringEntry;

    ui->setupUi( this );
    CALAMARES_RETRANSLATE(
        ui->retranslateUi( this );
        ui->generalExplanation->setText( tr( "Install tracking helps %1 to see how many users they have, what hardware they install %1 to and (with the last two options below), get continuous information about preferred applications. To see what will be sent, please click the help icon next to each area." ).arg( *StringEntry::ShortProductName ) );
        ui->installExplanation->setText( tr( "By selecting this you will send information about your installation and hardware. This information will <b>only be sent once</b> after the installation finishes." ) );
        ui->machineExplanation->setText( tr( "By selecting this you will <b>periodically</b> send information about your installation, hardware and applications, to %1." ).arg( *StringEntry::ShortProductName ) );
        ui->userExplanation->setText( tr( "By selecting this you will <b>regularly</b> send information about your installation, hardware, applications and usage patterns, to %1." ).arg( *StringEntry::ShortProductName ) );
    )

    QButtonGroup *group = new QButtonGroup( this );
    group->setExclusive( true );
    group->addButton( ui->noneRadio );
    group->addButton( ui->installRadio );
    group->addButton( ui->machineRadio );
    group->addButton( ui->userRadio );
    ui->noneRadio->setChecked( true );
}

void TrackingPage::enableTrackingOption(TrackingType t, bool enabled)
{
    QWidget* group = nullptr;

    switch ( t )
    {
        case TrackingType::InstallTracking:
            group = ui->installGroup;
            break;
        case TrackingType::MachineTracking:
            group = ui->machineGroup;
            break;
        case TrackingType::UserTracking:
            group = ui->userGroup;
            break;
    }

    if ( group != nullptr )
    {
        if ( enabled )
            group->show();
        else
            group->hide();
    }
    else
        cWarning() << "unknown tracking option" << int(t);
}

bool TrackingPage::getTrackingOption(TrackingType t)
{
    bool enabled = false;

    // A tracking type is enabled if it is checked, or
    // any higher level is checked.
#define ch(x) ui->x->isChecked()
    switch ( t )
    {
        case TrackingType::InstallTracking:
            enabled = ch(installRadio) || ch(machineRadio) || ch(userRadio);
            break;
        case TrackingType::MachineTracking:
            enabled = ch(machineRadio) || ch(userRadio);
            break;
        case TrackingType::UserTracking:
            enabled = ch(userRadio);
            break;
    }
#undef ch
    return enabled;
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
        cWarning() << "unknown tracking option" << int(t);
}

void TrackingPage::setGeneralPolicy( QString url )
{
    if ( url.isEmpty() )
        ui->generalPolicyLabel->hide();
    else
    {
        ui->generalPolicyLabel->show();
        ui->generalPolicyLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
        ui->generalPolicyLabel->show();
        connect( ui->generalPolicyLabel, &QLabel::linkActivated, [url]{ QDesktopServices::openUrl( url ); } );
    }
}

void TrackingPage::setTrackingLevel(const QString& l)
{
    QString level = l.toLower();
    QRadioButton* button = nullptr;

    if (level.isEmpty() || level == "none")
        button = ui->noneRadio;
    else if (level == "install")
        button = ui->installRadio;
    else if (level == "machine")
        button = ui->machineRadio;
    else if (level == "user")
        button = ui->userRadio;

    if ( button != nullptr )
        button->setChecked( true );
    else
        cWarning() << "unknown default tracking level" << l;
}
