/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
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

#include "CalamaresVersion.h"
#include "ViewManager.h"
#include "ui_FinishedPage.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"

#include <QApplication>
#include <QBoxLayout>
#include <QFocusEvent>
#include <QLabel>
#include <QProcess>

#include "Branding.h"
#include "Settings.h"

FinishedPage::FinishedPage( QWidget* parent )
    : QWidget( parent )
    , ui( new Ui::FinishedPage )
    , m_mode( FinishedViewStep::RestartMode::UserUnchecked )
{
    ui->setupUi( this );

    ui->mainText->setAlignment( Qt::AlignCenter );
    ui->mainText->setWordWrap( true );
    ui->mainText->setOpenExternalLinks( true );

    CALAMARES_RETRANSLATE(
        const auto* branding = Calamares::Branding::instance(); ui->retranslateUi( this );
        if ( Calamares::Settings::instance()->isSetupMode() ) {
            ui->mainText->setText( tr( "<h1>All done.</h1><br/>"
                                       "%1 has been set up on your computer.<br/>"
                                       "You may now start using your new system." )
                                       .arg( branding->versionedName() ) );
            ui->restartCheckBox->setToolTip( tr( "<html><head/><body>"
                                                 "<p>When this box is checked, your system will "
                                                 "restart immediately when you click on "
                                                 "<span style=\"font-style:italic;\">Done</span> "
                                                 "or close the setup program.</p></body></html>" ) );
        } else {
            ui->mainText->setText( tr( "<h1>All done.</h1><br/>"
                                       "%1 has been installed on your computer.<br/>"
                                       "You may now restart into your new system, or continue "
                                       "using the %2 Live environment." )
                                       .arg( branding->versionedName(), branding->productName() ) );
            ui->restartCheckBox->setToolTip( tr( "<html><head/><body>"
                                                 "<p>When this box is checked, your system will "
                                                 "restart immediately when you click on "
                                                 "<span style=\"font-style:italic;\">Done</span> "
                                                 "or close the installer.</p></body></html>" ) );
        } )
}


void
FinishedPage::setRestart( FinishedViewStep::RestartMode mode )
{
    using Mode = FinishedViewStep::RestartMode;

    m_mode = mode;

    ui->restartCheckBox->setVisible( mode != Mode::Never );
    ui->restartCheckBox->setEnabled( mode != Mode::Always );
    ui->restartCheckBox->setChecked( ( mode == Mode::Always ) || ( mode == Mode::UserChecked ) );
}


void
FinishedPage::setRestartNowCommand( const QString& command )
{
    m_restartNowCommand = command;
}


void
FinishedPage::setUpRestart()
{
    cDebug() << "FinishedPage::setUpRestart(), Quit button"
             << "setup=" << FinishedViewStep::modeName( m_mode ) << "command=" << m_restartNowCommand;

    connect( qApp, &QApplication::aboutToQuit, [ this ]() {
        if ( ui->restartCheckBox->isVisible() && ui->restartCheckBox->isChecked() )
        {
            cDebug() << "Running restart command" << m_restartNowCommand;
            QProcess::execute( "/bin/sh", { "-c", m_restartNowCommand } );
        }
    } );
}


void
FinishedPage::focusInEvent( QFocusEvent* e )
{
    e->accept();
}

void
FinishedPage::onInstallationFailed( const QString& message, const QString& details )
{
    const auto* branding = Calamares::Branding::instance();
    Q_UNUSED( details )
    if ( Calamares::Settings::instance()->isSetupMode() )
        ui->mainText->setText( tr( "<h1>Setup Failed</h1><br/>"
                                   "%1 has not been set up on your computer.<br/>"
                                   "The error message was: %2." )
                                   .arg( branding->versionedName() )
                                   .arg( message ) );
    else
        ui->mainText->setText( tr( "<h1>Installation Failed</h1><br/>"
                                   "%1 has not been installed on your computer.<br/>"
                                   "The error message was: %2." )
                                   .arg( branding->versionedName() )
                                   .arg( message ) );
    setRestart( FinishedViewStep::RestartMode::Never );
}
