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

#include "AlongsidePage.h"

#include <QBoxLayout>
#include <QLabel>

AlongsidePage::AlongsidePage( QWidget* parent )
    : QWidget( parent )
    , m_nextEnabled( false )
    , m_core( nullptr )
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );
}


void
AlongsidePage::init( PartitionCoreModule* core , const QStringList& osproberLines )
{
    QLabel* placeholder = new QLabel( "Alongside partitioning goes here.\nOsprober:\n" +
                                      osproberLines.join( '\n' ) );
    layout()->addWidget( placeholder );
}


bool
AlongsidePage::isNextEnabled() const
{
    return m_nextEnabled;
}


void
AlongsidePage::setNextEnabled( bool enabled )
{
    if ( enabled == m_nextEnabled )
        return;

    m_nextEnabled = enabled;
    emit nextStatusChanged( enabled );
}
