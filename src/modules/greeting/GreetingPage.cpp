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

#include "GreetingPage.h"

#include <QBoxLayout>
#include <QLabel>

#include "Branding.h"


GreetingPage::GreetingPage( QWidget* parent )
    : QWidget()
{
    QBoxLayout *mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    QLabel* text = new QLabel( tr( "<h1>Welcome to the %1 installer.</h1><br/>"
                                   "This program will ask you some questions and "
                                   "set up %2 on your computer." )
                               .arg( Calamares::Branding::instance()->
                                     string( Calamares::Branding::VersionedName ) )
                               .arg( Calamares::Branding::instance()->
                                     string( Calamares::Branding::ProductName ) ), this );
    text->setAlignment( Qt::AlignCenter );
    text->setWordWrap( true );

    mainLayout->addStretch();
    mainLayout->addWidget( text );
    mainLayout->addStretch();
}
