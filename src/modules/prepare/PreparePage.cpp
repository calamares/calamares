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

#include <QBoxLayout>
#include <QLabel>


PreparePage::PreparePage( QWidget* parent )
    : QWidget()
{
    QBoxLayout *mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QLabel* text = new QLabel( tr( "For best results, please ensure that this "
                                   "computer:" ), this );

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
PreparePage::init( const QList< QPair< QString, bool > > &checkEntries )
{
    for ( const QPair< QString, bool >& entry : checkEntries )
    {
        PrepareCheckWidget* pcw = new PrepareCheckWidget( entry.first, entry.second );
        m_entriesLayout->addWidget( pcw );
        pcw->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    }
}
