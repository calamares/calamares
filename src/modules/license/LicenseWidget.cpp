/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2015, Anke Boersma <demm@kaosx.us>
 *   Copyright 2015, Alexandre Arnt <qtgzmanager@gmail.com>
 *   Copyright 2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

#include "LicenseWidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>


LicenseWidget::LicenseWidget( LicenseEntry entry, QWidget* parent )
    : QWidget( parent )
    , m_entry( std::move( entry ) )
    , m_label( new QLabel( this ) )
    , m_viewLicenseLabel( new QLabel( this ) )
    , m_expandLicenseButton( nullptr )
{
    QPalette pal( palette() );
    pal.setColor( QPalette::Background, palette().background().color().lighter( 108 ) );

    setAutoFillBackground( true );
    setPalette( pal );
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );
    setContentsMargins( 4, 4, 4, 4 );

    QHBoxLayout* wiLayout = new QHBoxLayout;
    setLayout( wiLayout );

    m_label->setWordWrap( true );
    m_label->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Minimum );
    wiLayout->addWidget( m_label );

    m_viewLicenseLabel->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    m_viewLicenseLabel->setAlignment( Qt::AlignVCenter | Qt::AlignRight );
    wiLayout->addWidget( m_viewLicenseLabel );

    if ( m_entry.isLocal() )
    {
        m_expandLicenseButton = new QToolButton( this );
        m_expandLicenseButton->setArrowType( Qt::DownArrow );
        wiLayout->addWidget( m_expandLicenseButton );

        connect( m_expandLicenseButton, &QAbstractButton::clicked, this, &LicenseWidget::expandClicked );
    }
    else
        m_viewLicenseLabel->setOpenExternalLinks( true );


    retranslateUi();
}

LicenseWidget::~LicenseWidget()
{
}

void LicenseWidget::retranslateUi()
{
    QString productDescription;
    switch ( m_entry.m_type )
    {
    case LicenseEntry::Type::Driver:
        //: %1 is an untranslatable product name, example: Creative Audigy driver
        productDescription = tr( "<strong>%1 driver</strong><br/>"
                                    "by %2" )
                                .arg( m_entry.m_prettyName )
                                .arg( m_entry.m_prettyVendor );
        break;
    case LicenseEntry::Type::GpuDriver:
        //: %1 is usually a vendor name, example: Nvidia graphics driver
        productDescription = tr( "<strong>%1 graphics driver</strong><br/>"
                                    "<font color=\"Grey\">by %2</font>" )
                                .arg( m_entry.m_prettyName )
                                .arg( m_entry.m_prettyVendor );
        break;
    case LicenseEntry::Type::BrowserPlugin:
        productDescription = tr( "<strong>%1 browser plugin</strong><br/>"
                                    "<font color=\"Grey\">by %2</font>" )
                                .arg( m_entry.m_prettyName )
                                .arg( m_entry.m_prettyVendor );
        break;
    case LicenseEntry::Type::Codec:
        productDescription = tr( "<strong>%1 codec</strong><br/>"
                                    "<font color=\"Grey\">by %2</font>" )
                                .arg( m_entry.m_prettyName )
                                .arg( m_entry.m_prettyVendor );
        break;
    case LicenseEntry::Type::Package:
        productDescription = tr( "<strong>%1 package</strong><br/>"
                                    "<font color=\"Grey\">by %2</font>" )
                                .arg( m_entry.m_prettyName )
                                .arg( m_entry.m_prettyVendor );
        break;
    case LicenseEntry::Type::Software:
        productDescription = tr( "<strong>%1</strong><br/>"
                                    "<font color=\"Grey\">by %2</font>" )
                                .arg( m_entry.m_prettyName )
                                .arg( m_entry.m_prettyVendor );
    }
    m_label->setText( productDescription );

    if ( m_entry.isLocal() )
    {
        m_viewLicenseLabel->setText( tr( "Show license agreement" ) );
        updateExpandToolTip();
    }
    else
        m_viewLicenseLabel->setText( tr( "<a href=\"%1\">view license agreement</a>" )
                                .arg( m_entry.m_url.toString() ) );
}

void
LicenseWidget::expandClicked()
{
    if ( m_expandLicenseButton->arrowType() == Qt::DownArrow )
    {
        m_expandLicenseButton->setArrowType( Qt::UpArrow );
    }
    else
    {
        m_expandLicenseButton->setArrowType( Qt::DownArrow );
    }
    updateExpandToolTip();
}

void
LicenseWidget::updateExpandToolTip()
{
    if ( !m_expandLicenseButton )
        return;

    m_expandLicenseButton->setToolTip(
        ( m_expandLicenseButton->arrowType() == Qt::DownArrow )
        ? tr( "Show complete license text" )
        : tr( "Hide license text" )
        ) ;
}
