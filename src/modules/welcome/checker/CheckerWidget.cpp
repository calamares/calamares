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

#include "CheckerWidget.h"

#include "CheckItemWidget.h"

#include "Branding.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "widgets/FixedAspectRatioLabel.h"

#include <QAbstractButton>
#include <QBoxLayout>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>


CheckerWidget::CheckerWidget( QWidget* parent )
    : QWidget( parent )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    m_mainLayout = new QVBoxLayout;
    setLayout( m_mainLayout );

    QHBoxLayout* spacerLayout = new QHBoxLayout;
    m_mainLayout->addLayout( spacerLayout );
    m_paddingSize = qBound( 32, CalamaresUtils::defaultFontHeight() * 4, 128 );
    spacerLayout->addSpacing( m_paddingSize );
    m_entriesLayout = new QVBoxLayout;
    spacerLayout->addLayout( m_entriesLayout );
    spacerLayout->addSpacing( m_paddingSize );
    CalamaresUtils::unmarginLayout( spacerLayout );
}


void
CheckerWidget::init( const QList< PrepareEntry >& checkEntries )
{
    bool allChecked = true;
    bool requirementsSatisfied = true;

    for ( const PrepareEntry& entry : checkEntries )
    {
        if ( !entry.checked )
        {
            CheckItemWidget* ciw = new CheckItemWidget( entry.checked );
            CALAMARES_RETRANSLATE( ciw->setText( entry.negatedText() ); )
            m_entriesLayout->addWidget( ciw );
            ciw->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

            allChecked = false;
            if ( entry.required )
            {
                requirementsSatisfied = false;
            }
            ciw->setAutoFillBackground( true );
            QPalette pal( ciw->palette() );
            pal.setColor( QPalette::Background, Qt::white );
            ciw->setPalette( pal );

        }
    }

    QLabel* textLabel = new QLabel;

    textLabel->setWordWrap( true );
    m_entriesLayout->insertWidget( 0, textLabel );
    textLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

    if ( !allChecked )
    {
        m_entriesLayout->insertSpacing( 1, CalamaresUtils::defaultFontHeight() / 2 );

        if ( !requirementsSatisfied )
        {
            CALAMARES_RETRANSLATE(
                textLabel->setText( tr( "This computer does not satisfy the minimum "
                                        "requirements for installing %1.<br/>"
                                        "Installation cannot continue. "
                                        "<a href=\"#details\">Details...</a>" )
                                        .arg( *Calamares::Branding::ShortVersionedName ) );
            )
            textLabel->setOpenExternalLinks( false );
            connect( textLabel, &QLabel::linkActivated,
                     this, [ this, checkEntries ]( const QString& link )
            {
                if ( link == "#details" )
                    showDetailsDialog( checkEntries );
            } );
        }
        else
        {
            CALAMARES_RETRANSLATE(
                textLabel->setText( tr( "This computer does not satisfy some of the "
                                        "recommended requirements for installing %1.<br/>"
                                        "Installation can continue, but some features "
                                        "might be disabled." )
                                        .arg( *Calamares::Branding::ShortVersionedName ) );
            )
        }
    }

    if ( allChecked && requirementsSatisfied )
    {
        if ( !Calamares::Branding::instance()->
             imagePath( Calamares::Branding::ProductWelcome ).isEmpty() )
        {
            QPixmap theImage = QPixmap( Calamares::Branding::instance()->
                               imagePath( Calamares::Branding::ProductWelcome ) );
            if ( !theImage.isNull() )
            {
                QLabel* imageLabel;
                if ( Calamares::Branding::instance()->welcomeExpandingLogo() )
                {
                    FixedAspectRatioLabel *p = new FixedAspectRatioLabel;
                    p->setPixmap( theImage );
                    imageLabel = p;
                }
                else
                {
                    imageLabel = new QLabel;
                    imageLabel->setPixmap( theImage );
                }

                imageLabel->setContentsMargins( 4, CalamaresUtils::defaultFontHeight() * 3 / 4, 4, 4 );
                m_mainLayout->addWidget( imageLabel );
                imageLabel->setAlignment( Qt::AlignCenter );
                imageLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
            }
        }
        CALAMARES_RETRANSLATE(
            textLabel->setText( tr( "This program will ask you some questions and "
                                    "set up %2 on your computer." )
                                .arg( *Calamares::Branding::ProductName ) );
            textLabel->setAlignment( Qt::AlignCenter );
        )
    }
    else
    {
        m_mainLayout->addStretch();
    }
}


void
CheckerWidget::showDetailsDialog( const QList< PrepareEntry >& checkEntries )
{
    QDialog* detailsDialog = new QDialog( this );
    QBoxLayout* mainLayout = new QVBoxLayout;
    detailsDialog->setLayout( mainLayout );

    QLabel* textLabel = new QLabel;
    mainLayout->addWidget( textLabel );
    CALAMARES_RETRANSLATE(
        textLabel->setText( tr( "For best results, please ensure that this computer:" ) );
    )
    QBoxLayout* entriesLayout = new QVBoxLayout;
    CalamaresUtils::unmarginLayout( entriesLayout );
    mainLayout->addLayout( entriesLayout );

    for ( const PrepareEntry& entry : checkEntries )
    {
        if ( entry.enumerationText().isEmpty() )
            continue;

        CheckItemWidget* ciw = new CheckItemWidget( entry.checked );
        CALAMARES_RETRANSLATE( ciw->setText( entry.enumerationText() ); )
        entriesLayout->addWidget( ciw );
        ciw->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

        ciw->setAutoFillBackground( true );
        QPalette pal( ciw->palette() );
        pal.setColor( QPalette::Background, Qt::white );
        ciw->setPalette( pal );
    }

    QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Close,
                                                        Qt::Horizontal,
                                                        this );
    mainLayout->addWidget( buttonBox );

    detailsDialog->setModal( true );
    detailsDialog->setWindowTitle( tr( "System requirements" ) );

    connect( buttonBox, &QDialogButtonBox::clicked,
             detailsDialog, &QDialog::close );
    detailsDialog->exec();
    detailsDialog->deleteLater();
}
