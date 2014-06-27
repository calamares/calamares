/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include "PartitionPage.h"

// Local
#include <DeviceModel.h>
#include <PartitionModel.h>
#include <ui_PartitionPage.h>

// CalaPM
#include <CalaPM.h>
#include <backend/corebackend.h>
#include <backend/corebackendmanager.h>

// Qt
#include <QDebug>
#include <QItemSelectionModel>

PartitionPage::PartitionPage( QWidget* parent )
    : Calamares::AbstractPage( parent )
    , m_ui( new Ui_PartitionPage )
    , m_deviceModel( new DeviceModel( this ) )
{
    // FIXME: Should be done at startup
    if ( !CalaPM::init() )
    {
        qFatal( "Failed to init CalaPM" );
    }
    m_backend = CoreBackendManager::self()->backend();
    m_ui->setupUi( this );
    m_ui->deviceListView->setModel( m_deviceModel );

    m_deviceModel->init( m_backend->scanDevices() );

    connect( m_ui->deviceListView->selectionModel(), &QItemSelectionModel::currentChanged,
             [ this ]( const QModelIndex& index, const QModelIndex& oldIndex )
    {
        PartitionModel* model = m_deviceModel->partitionModelForIndex( index );
        m_ui->partitionListView->setModel( model );
    } );
}

PartitionPage::~PartitionPage()
{
}
