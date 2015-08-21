/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Alexandre Arnt <qtgzmanager@gmail.com>
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

#include "LicensePage.h"

#include "ui_LicensePage.h"
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

LicensePage::LicensePage(QWidget *parent)
    : QWidget( parent )
    , ui( new Ui::LicensePage )
{
    ui->setupUi( this );

    ui->verticalLayout->insertSpacing( 1, CalamaresUtils::defaultFontHeight() * 4 );

    ui->mainText->setAlignment( Qt::AlignCenter );
    ui->mainText->setWordWrap( true );
    ui->mainText->setOpenExternalLinks( true );

    CALAMARES_RETRANSLATE(
        ui->mainText->setText( tr( "<h1>License Approval</h1>" 
                                "In case non-free was selected, this installer will install proprietary <br/>"
                                "packages that have additional EULA's attached to them, do you accept these terms? <br/>"
                                "If declined a free version will be used (when available)." ) );
        ui->retranslateUi( this );
    )
    
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( ui->disagreeButton->isChecked() )
        gs->insert( "licenseAgree", false ); 
    
}

void
LicensePage::showNvidiaUrl( bool enabled )
{
    ui->nvidiaButton->setVisible( enabled );
    
    ui->nvidiaButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                   CalamaresUtils::Original,
                                                                   2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                          CalamaresUtils::defaultFontHeight() ) ) );
    
    connect( ui->nvidiaButton, &QPushButton::clicked,
             this, [ this ]
    {
        QDesktopServices::openUrl(QUrl(m_nvidiaUrl));
        cDebug() << "Is: " << m_nvidiaUrl;
    } );
}

void
LicensePage::showCatalystUrl( bool enabled )
{
    ui->catalystButton->setVisible( enabled );
    
    ui->catalystButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                       CalamaresUtils::Original,
                                                                       2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                              CalamaresUtils::defaultFontHeight() ) ) );
    
    connect( ui->catalystButton, &QPushButton::clicked,
             this, [ this ]
    {
        QDesktopServices::openUrl(QUrl(m_catalystUrl));
    } );
}

void
LicensePage::showFlashUrl( bool enabled )
{
    ui->flashButton->setVisible( enabled );
    
    ui->flashButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                        CalamaresUtils::Original,
                                                                        2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                               CalamaresUtils::defaultFontHeight() ) ) );
    
    connect( ui->flashButton, &QPushButton::clicked,
             this, [ this ]
    {
        QDesktopServices::openUrl(QUrl(m_flashUrl));
    } );
}

void
LicensePage::showLicenseUrl( bool enabled )
{
    ui->licenseButton->setVisible( enabled );
    
    ui->licenseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                        CalamaresUtils::Original,
                                                                        2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                               CalamaresUtils::defaultFontHeight() ) ) );
    
    connect( ui->licenseButton, &QPushButton::clicked,
             this, [ this ]
    {
        QDesktopServices::openUrl(QUrl(m_licenseUrl));
    } );
}

void
LicensePage::setNvidiaUrl( const QString& url )
{
    m_nvidiaUrl = url;
}

void
LicensePage::setCatalystUrl( const QString& url )
{
    m_catalystUrl = url;
}

void
LicensePage::setFlashUrl( const QString& url )
{
    m_flashUrl = url;
}

void
LicensePage::setLicenseUrl( const QString& url )
{
    m_licenseUrl = url;
}
