/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "PreparePage.h"

#include "PrepareCheckWidget.h"

#include "utils/CalamaresUtilsGui.h"
#include "Branding.h"

#include <QBoxLayout>
#include <QLabel>


PreparePage::PreparePage( QWidget* parent )
    : QWidget()
{
    QBoxLayout *mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QLabel* text = new QLabel( tr( "For best results, please ensure that this "
                                   "computer:" ), this );

    mainLayout->addSpacing( CalamaresUtils::defaultFontHeight() );
    mainLayout->addWidget( text );
    QHBoxLayout* spacerLayout = new QHBoxLayout;
    mainLayout->addLayout( spacerLayout );
    spacerLayout->addSpacing( CalamaresUtils::defaultFontHeight() * 2 );
    m_entriesLayout = new QVBoxLayout;
    spacerLayout->addLayout( m_entriesLayout );
    CalamaresUtils::unmarginLayout( spacerLayout );
    mainLayout->addStretch();
}


void
PreparePage::init( const QList< PrepareEntry >& checkEntries )
{
    bool allChecked = true;
    bool requirementsSatisfied = true;

    for ( const PrepareEntry& entry : checkEntries )
    {
        PrepareCheckWidget* pcw = new PrepareCheckWidget( entry.text, entry.checked );
        m_entriesLayout->addWidget( pcw );
        pcw->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

        if ( !entry.checked )
        {
            allChecked = false;
            if ( entry.required )
            {
                requirementsSatisfied = false;
            }
        }
    }

    if ( !allChecked )
    {
        QBoxLayout* mainLayout = dynamic_cast< QBoxLayout* >( layout() );
        QBoxLayout* infoLayout = new QHBoxLayout;
        QLabel* iconLabel = new QLabel;
        QLabel* textLabel = new QLabel;
        int iconSize = qBound( 32, CalamaresUtils::defaultFontHeight() * 6, 128 );
        iconLabel->setFixedSize( iconSize, iconSize );
        textLabel->setWordWrap( true );
        infoLayout->addWidget( iconLabel );
        infoLayout->addWidget( textLabel );
        textLabel->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

        if ( !requirementsSatisfied )
        {
            iconLabel->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Fail,
                                                                 CalamaresUtils::Original,
                                                                 iconLabel->size() ) );
            textLabel->setText( tr( "This computer does not satisfy the minimum "
                                    "requirements for installing %1.\n"
                                    "Installation cannot continue." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
        }
        else
        {
            iconLabel->setPixmap( CalamaresUtils::defaultPixmap( CalamaresUtils::Information,
                                                                 CalamaresUtils::Original,
                                                                 iconLabel->size() ) );
            textLabel->setText( tr( "This computer does not satisfy some of the "
                                    "recommended requirements for installing %1.\n"
                                    "Installation can continue, but some features "
                                    "might be disabled." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );

        }

        mainLayout->insertLayout( mainLayout->count(), infoLayout );
    }
}
