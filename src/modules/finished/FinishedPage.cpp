/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "FinishedPage.h"

#include "ui_FinishedPage.h"
#include "CalamaresVersion.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "ViewManager.h"

#include <QApplication>
#include <QBoxLayout>
#include <QFocusEvent>
#include <QLabel>
#include <QProcess>

#include "Branding.h"


FinishedPage::FinishedPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::FinishedPage )
    , m_restartSetUp( false )
{
    cDebug() << "FinishedPage()";
    ui->setupUi( this );

    ui->mainText->setAlignment( Qt::AlignCenter );
    ui->mainText->setWordWrap( true );
    ui->mainText->setOpenExternalLinks( true );

    CALAMARES_RETRANSLATE(
        ui->retranslateUi( this );
        ui->mainText->setText( tr( "<h1>All done.</h1><br/>"
                                   "%1 has been installed on your computer.<br/>"
                                   "You may now restart into your new system, or continue "
                                   "using the %2 Live environment." )
                               .arg( *Calamares::Branding::VersionedName )
                               .arg( *Calamares::Branding::ProductName ) );
    )
}


void
FinishedPage::setRestartNowEnabled( bool enabled )
{
    ui->restartCheckBox->setVisible( enabled );
}


void
FinishedPage::setRestartNowChecked( bool checked )
{
    ui->restartCheckBox->setChecked( checked );
}


void
FinishedPage::setRestartNowCommand( const QString& command )
{
    m_restartNowCommand = command;
}


void
FinishedPage::setUpRestart()
{
    cDebug() << "FinishedPage::setUpRestart()";
    if ( !m_restartSetUp )
    {
        connect( qApp, &QApplication::aboutToQuit,
                 this, [this]
        {
            if ( ui->restartCheckBox->isVisible() &&
                    ui->restartCheckBox->isChecked() )
                QProcess::execute( "/bin/sh", { "-c", m_restartNowCommand } );
        } );
    }
}


void
FinishedPage::focusInEvent( QFocusEvent* e )
{
    e->accept();
}

void
FinishedPage::onInstallationFailed( const QString& message, const QString& details )
{
    Q_UNUSED( details );
    ui->mainText->setText( tr( "<h1>Installation Failed</h1><br/>"
                               "%1 has not been installed on your computer.<br/>"
                               "The error message was: %2." )
                           .arg( *Calamares::Branding::VersionedName )
                           .arg( message ) );
    setRestartNowEnabled( false );
}
