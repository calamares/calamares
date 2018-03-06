/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Alexandre Arnt <qtgzmanager@gmail.com>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
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
    , m_isNextEnabled( false )
{
    ui->setupUi( this );

    ui->verticalLayout->insertSpacing( 1, CalamaresUtils::defaultFontHeight() );

    ui->mainText->setAlignment( Qt::AlignCenter );
    ui->mainText->setWordWrap( true );
    ui->mainText->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );

    ui->additionalText->setWordWrap( true );

    ui->verticalLayout->insertSpacing( 4, CalamaresUtils::defaultFontHeight() / 2 );

    ui->verticalLayout->setContentsMargins( CalamaresUtils::defaultFontHeight(),
                                            CalamaresUtils::defaultFontHeight() * 3,
                                            CalamaresUtils::defaultFontHeight(),
                                            CalamaresUtils::defaultFontHeight() );
    
    ui->acceptFrame->setFrameStyle( QFrame::NoFrame | QFrame::Plain );
    ui->acceptFrame->setStyleSheet( "#acceptFrame { border: 1px solid red;"
                                    "background-color: #fff6f6;"
                                    "border-radius: 4px;"
                                    "padding: 2px; }" );
    ui->acceptFrame->layout()->setMargin( CalamaresUtils::defaultFontHeight() / 2 );

    connect( ui->acceptCheckBox, &QCheckBox::toggled,
             this, [ this ]( bool checked )
    {
        Calamares::JobQueue::instance()->globalStorage()->insert( "licenseAgree", checked );
        m_isNextEnabled = checked;
        if ( !checked )
        {
            ui->acceptFrame->setStyleSheet( "#acceptFrame { border: 1px solid red;"
                                            "background-color: #fff8f8;"
                                            "border-radius: 4px;"
                                            "padding: 2px; }" );
        }
        else
        {
            ui->acceptFrame->setStyleSheet( "#acceptFrame { padding: 3px }" );
        }
        emit nextStatusChanged( checked );
    } );

    CALAMARES_RETRANSLATE(
        ui->acceptCheckBox->setText( tr( "I accept the terms and conditions above." ) );
    );

}


void
LicensePage::setEntries( const QList< LicenseEntry >& entriesList )
{
    CalamaresUtils::clearLayout( ui->licenseEntriesLayout );

    bool required = false;
    for ( const LicenseEntry& entry : entriesList )
    {
        if ( entry.required )
        {
            required = true;
            break;
        }
    }

    m_isNextEnabled = !required;
    nextStatusChanged( m_isNextEnabled );

    CALAMARES_RETRANSLATE(
        if ( required )
        {
            ui->mainText->setText( tr( "<h1>License Agreement</h1>"
                "This setup procedure will install proprietary "
                "software that is subject to licensing terms." ) );
            ui->additionalText->setText( tr( "Please review the End User License "
                "Agreements (EULAs) above.<br/>"
                "If you do not agree with the terms, the setup procedure cannot continue." ) );
        }
        else
        {
            ui->mainText->setText( tr( "<h1>License Agreement</h1>"
                "This setup procedure can install proprietary "
                "software that is subject to licensing terms "
                "in order to provide additional features and enhance the user "
                "experience." ) );
            ui->additionalText->setText( tr( "Please review the End User License "
                "Agreements (EULAs) above.<br/>"
                "If you do not agree with the terms, proprietary software will not "
                "be installed, and open source alternatives will be used instead." ) );
        }
        ui->retranslateUi( this );
    )

    for ( const LicenseEntry& entry : entriesList )
    {
        QWidget* widget = new QWidget( this );
        QPalette pal( palette() );
        pal.setColor( QPalette::Background, palette().background().color().lighter( 108 ) );
        widget->setAutoFillBackground( true );
        widget->setPalette( pal );
        widget->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
        widget->setContentsMargins( 4, 4, 4, 4 );

        QHBoxLayout* wiLayout = new QHBoxLayout;
        widget->setLayout( wiLayout );
        QLabel* label = new QLabel( widget );
        label->setWordWrap( true );
        wiLayout->addWidget( label );
        label->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Minimum );

        QString productDescription;
        switch ( entry.type )
        {
        case LicenseEntry::Driver:
            //: %1 is an untranslatable product name, example: Creative Audigy driver
            productDescription = tr( "<strong>%1 driver</strong><br/>"
                                     "by %2" )
                                 .arg( entry.prettyName )
                                 .arg( entry.prettyVendor );
            break;
        case LicenseEntry::GpuDriver:
            //: %1 is usually a vendor name, example: Nvidia graphics driver
            productDescription = tr( "<strong>%1 graphics driver</strong><br/>"
                                     "<font color=\"Grey\">by %2</font>" )
                                 .arg( entry.prettyName )
                                 .arg( entry.prettyVendor );
            break;
        case LicenseEntry::BrowserPlugin:
            productDescription = tr( "<strong>%1 browser plugin</strong><br/>"
                                     "<font color=\"Grey\">by %2</font>" )
                                 .arg( entry.prettyName )
                                 .arg( entry.prettyVendor );
            break;
        case LicenseEntry::Codec:
            productDescription = tr( "<strong>%1 codec</strong><br/>"
                                     "<font color=\"Grey\">by %2</font>" )
                                 .arg( entry.prettyName )
                                 .arg( entry.prettyVendor );
            break;
        case LicenseEntry::Package:
            productDescription = tr( "<strong>%1 package</strong><br/>"
                                     "<font color=\"Grey\">by %2</font>" )
                                 .arg( entry.prettyName )
                                 .arg( entry.prettyVendor );
            break;
        case LicenseEntry::Software:
            productDescription = tr( "<strong>%1</strong><br/>"
                                     "<font color=\"Grey\">by %2</font>" )
                                 .arg( entry.prettyName )
                                 .arg( entry.prettyVendor );
        }
        label->setText( productDescription );

        QLabel* viewLicenseLabel = new QLabel( widget );
        wiLayout->addWidget( viewLicenseLabel );
        viewLicenseLabel->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
        viewLicenseLabel->setOpenExternalLinks( true );
        viewLicenseLabel->setAlignment( Qt::AlignVCenter | Qt::AlignRight );
        viewLicenseLabel->setText( tr( "<a href=\"%1\">view license agreement</a>" )
                                   .arg( entry.url.toString() ) );

        ui->licenseEntriesLayout->addWidget( widget );
    }
    ui->licenseEntriesLayout->addStretch();
}


bool
LicensePage::isNextEnabled() const
{
    return m_isNextEnabled;
}
