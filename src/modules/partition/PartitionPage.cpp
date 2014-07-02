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
#include <CreatePartitionDialog.h>
#include <DeviceModel.h>
#include <PartitionCoreModule.h>
#include <PartitionModel.h>
#include <PMUtils.h>
#include <ui_PartitionPage.h>

// Qt
#include <QDebug>
#include <QItemSelectionModel>
#include <QPointer>

PartitionPage::PartitionPage( QWidget* parent )
    : Calamares::AbstractPage( parent )
    , m_ui( new Ui_PartitionPage )
    , m_core( new PartitionCoreModule( this ) )
{
    m_ui->setupUi( this );
    m_ui->deviceListView->setModel( m_core->deviceModel() );
    updateButtons();

    connect( m_ui->deviceListView->selectionModel(), &QItemSelectionModel::currentChanged,
             [ this ]( const QModelIndex& index, const QModelIndex& oldIndex )
    {
        Device* device = m_core->deviceModel()->deviceForIndex( index );
        PartitionModel* model = m_core->partitionModelForDevice( device );
        m_ui->partitionListView->setModel( model );
        updateButtons();
        // Establish connection here because selection model is destroyed when
        // model changes
        connect( m_ui->partitionListView->selectionModel(), &QItemSelectionModel::currentChanged,
                 [ this ]( const QModelIndex& index, const QModelIndex& oldIndex )
        {
            updateButtons();
        } );
        connect( model, &QAbstractItemModel::modelReset, this, &PartitionPage::updateButtons );
    } );

    connect( m_ui->createButton, &QAbstractButton::clicked, this, &PartitionPage::onCreateClicked );
    connect( m_ui->deleteButton, &QAbstractButton::clicked, this, &PartitionPage::onDeleteClicked );
}

PartitionPage::~PartitionPage()
{
}

void
PartitionPage::updateButtons()
{
    bool create = false, edit = false, del = false;

    QModelIndex index = m_ui->partitionListView->currentIndex();
    if ( index.isValid() )
    {
        const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
        Q_ASSERT( model );
        Partition* partition = model->partitionForIndex( index );
        Q_ASSERT( partition );
        bool isFree = PMUtils::isPartitionFreeSpace( partition );
        create = isFree;
        edit = del = !isFree;
    }
    m_ui->createButton->setEnabled( create );
    m_ui->editButton->setEnabled( edit );
    m_ui->deleteButton->setEnabled( del );
}

void
PartitionPage::onCreateClicked()
{
    QModelIndex index = m_ui->partitionListView->currentIndex();
    Q_ASSERT( index.isValid() );

    const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
    Partition* partition = model->partitionForIndex( index );
    Q_ASSERT( partition );

    QPointer<CreatePartitionDialog> dlg = new CreatePartitionDialog( model->device(), partition, this );
    if ( dlg->exec() == QDialog::Accepted )
    {
        m_core->createPartition( dlg->createJob() );
    }
    delete dlg;
}

void
PartitionPage::onDeleteClicked()
{
    QModelIndex index = m_ui->partitionListView->currentIndex();
    Q_ASSERT( index.isValid() );

    const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
    Partition* partition = model->partitionForIndex( index );
    Q_ASSERT( partition );

    m_core->deletePartition( model->device(), partition );
}
