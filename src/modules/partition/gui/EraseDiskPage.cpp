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

#include "EraseDiskPage.h"

#include "core/DeviceModel.h"
#include "core/PartitionCoreModule.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"

#include <QBoxLayout>
#include <QListView>
#include <QLabel>

EraseDiskPage::EraseDiskPage( QWidget* parent )
    : QWidget( parent )
    , m_nextEnabled( false )
    , m_core( nullptr )
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QLabel* driveLabel = new QLabel( tr( "Select drive:" ) );
    mainLayout->addWidget( driveLabel );

    m_drivesView = new QListView;
    mainLayout->addWidget( m_drivesView );
    m_drivesView->setViewMode( QListView::IconMode );
    m_drivesView->setWrapping( false );
    m_drivesView->setFlow( QListView::LeftToRight );
    m_drivesView->setSelectionRectVisible( false );
    m_drivesView->setWordWrap( true );
    m_drivesView->setUniformItemSizes( true );
    m_drivesView->setSelectionMode( QAbstractItemView::SingleSelection );

    m_drivesView->setIconSize( CalamaresUtils::defaultIconSize() * 3 );
    m_drivesView->setGridSize( QSize( CalamaresUtils::defaultFontHeight() * 8,
                                      m_drivesView->iconSize().height() +
                                      CalamaresUtils::defaultFontHeight() * 4 ) );
    m_drivesView->setMinimumHeight( m_drivesView->gridSize().height() +
                                    CalamaresUtils::defaultFontHeight() / 2 );
    m_drivesView->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

    mainLayout->addStretch();
    setNextEnabled( false );
}


void
EraseDiskPage::init( PartitionCoreModule* core )
{
    if ( m_core ) //this should probably never happen
    {
        m_core->revert();
        return;
    }

    m_core = core;
    m_drivesView->setModel( core->deviceModel() );

    connect( m_drivesView->selectionModel(), &QItemSelectionModel::selectionChanged,
             this, [ this ]()
    {
        setNextEnabled( m_drivesView->selectionModel()->hasSelection() );

        //TODO: show a before/after view before this model, update it on selection changed
    } );
}


bool
EraseDiskPage::isNextEnabled()
{
    return m_nextEnabled;
}


void
EraseDiskPage::setNextEnabled( bool enabled )
{
    if ( enabled == m_nextEnabled )
        return;

    m_nextEnabled = enabled;
    emit nextStatusChanged( enabled );
}
