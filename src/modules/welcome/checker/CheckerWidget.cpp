/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "Branding.h"

#include <QBoxLayout>
#include <QLabel>


CheckerWidget::CheckerWidget( QWidget* parent )
    : QWidget( parent )
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum );

    QBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QHBoxLayout* spacerLayout = new QHBoxLayout;
    mainLayout->addLayout( spacerLayout );
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

    if ( !allChecked )
    {
        QLabel* iconLabel = new QLabel;
        QLabel* textLabel = new QLabel;
        int iconSize = qBound( 32, CalamaresUtils::defaultFontHeight() * 6, 128 );
        QHBoxLayout* iconLayout = new QHBoxLayout;
        iconLayout->addStretch();
        iconLayout->addWidget( iconLabel );
        iconLayout->addStretch();
        iconLabel->setFixedSize( iconSize, iconSize );
        CalamaresUtils::unmarginLayout( iconLayout );
        textLabel->setWordWrap( true );
        m_entriesLayout->insertLayout( 0, iconLayout );
        m_entriesLayout->insertWidget( 1, textLabel );
        m_entriesLayout->insertSpacing( 2, CalamaresUtils::defaultFontHeight() / 2 );
        textLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

        if ( !requirementsSatisfied )
        {
            iconLabel->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Fail,
                                                                 CalamaresUtils::Original,
                                                                 iconLabel->size() ) );
            CALAMARES_RETRANSLATE(
                textLabel->setText( tr( "This computer does not satisfy the minimum "
                                        "requirements for installing %1.\n"
                                        "Installation cannot continue." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            )
        }
        else
        {
            iconLabel->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Information,
                                                                 CalamaresUtils::Original,
                                                                 iconLabel->size() ) );
            CALAMARES_RETRANSLATE(
                textLabel->setText( tr( "This computer does not satisfy some of the "
                                        "recommended requirements for installing %1.\n"
                                        "Installation can continue, but some features "
                                        "might be disabled." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            )
        }
    }
}
