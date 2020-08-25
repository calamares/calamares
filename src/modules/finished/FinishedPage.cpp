/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
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

    connect( qApp, &QApplication::aboutToQuit, [this]() {
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
