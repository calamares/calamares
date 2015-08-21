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
                                "packages that have additional End User License Agreements (EULAs) <br/>"
                                "attached to them, do you accept these terms? <br/>"
                                "If declined a free version will be used (when available)." ) );
        ui->retranslateUi( this );
    )
    
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    if ( ui->disagreeButton->isChecked() )
        gs->insert( "licenseAgree", false ); 
    
}

void
LicensePage::showLicense1Url( bool enabled )
{
    ui->license1Button->setVisible( enabled );
    ui->license1Button->setText( "Nvidia License" );
    //ui->license1Button->setText( m_license1Button );
    
    ui->license1Button->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                   CalamaresUtils::Original,
                                                                   2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                          CalamaresUtils::defaultFontHeight() ) ) );
    
    connect( ui->license1Button, &QPushButton::clicked,
             this, [ this ]
    {
        QDesktopServices::openUrl(QUrl(m_license1Url));
        cDebug() << "Is: " << m_license1Url;
    } );
}

void
LicensePage::showLicense2Url( bool enabled )
{
    ui->license2Button->setVisible( enabled );
    ui->license2Button->setText( "Some License" );
    
    ui->license2Button->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                       CalamaresUtils::Original,
                                                                       2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                              CalamaresUtils::defaultFontHeight() ) ) );
    
    connect( ui->license2Button, &QPushButton::clicked,
             this, [ this ]
    {
        QDesktopServices::openUrl(QUrl(m_license2Url));
    } );
}

void
LicensePage::showLicense3Url( bool enabled )
{
    ui->license3Button->setVisible( enabled );
    ui->license3Button->setText( "Flash License" );
    
    ui->license3Button->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                        CalamaresUtils::Original,
                                                                        2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                               CalamaresUtils::defaultFontHeight() ) ) );
    
    connect( ui->license3Button, &QPushButton::clicked,
             this, [ this ]
    {
        QDesktopServices::openUrl(QUrl(m_license3Url));
    } );
}

void
LicensePage::showLicense4Url( bool enabled )
{
    ui->license4Button->setVisible( enabled );
    ui->license4Button->setText( "License" );
    
    ui->license4Button->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Release,
                                                                        CalamaresUtils::Original,
                                                                        2*QSize( CalamaresUtils::defaultFontHeight(),
                                                                               CalamaresUtils::defaultFontHeight() ) ) );
    
    connect( ui->license4Button, &QPushButton::clicked,
             this, [ this ]
    {
        QDesktopServices::openUrl(QUrl(m_license4Url));
    } );
}

void
LicensePage::setLicense1Url( const QString& url )
{
    m_license1Url = url;
}

void
LicensePage::setLicense2Url( const QString& url )
{
    m_license2Url = url;
}

void
LicensePage::setLicense3Url( const QString& url )
{
    m_license3Url = url;
}

void
LicensePage::setLicense4Url( const QString& url )
{
    m_license4Url = url;
}

void
LicensePage::setLicense1Button( const QString& text )
{
    m_license1Button = text;
}
/*QString
LicensePage::setLicense1Button() const
{
    return m_license1Button;
}*/