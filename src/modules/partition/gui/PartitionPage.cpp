/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2015-2016, Teo Mrnjavac <teo@kde.org>
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
#include "core/BootLoaderModel.h"
#include "core/DeviceModel.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionModel.h"
#include "core/KPMHelpers.h"
#include "gui/CreatePartitionDialog.h"
#include "gui/EditExistingPartitionDialog.h"
#include "gui/ScanningDialog.h"

#include "ui_PartitionPage.h"
#include "ui_CreatePartitionTableDialog.h"

#include "utils/Retranslator.h"
#include "Branding.h"
#include "JobQueue.h"
#include "GlobalStorage.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

// Qt
#include <QDebug>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QMessageBox>
#include <QPointer>
#include <QDir>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

PartitionPage::PartitionPage( PartitionCoreModule* core, QWidget* parent )
    : QWidget( parent )
    , m_ui( new Ui_PartitionPage )
    , m_core( core )
{
    m_ui->setupUi( this );
    m_ui->deviceComboBox->setModel( m_core->deviceModel() );
    m_ui->bootLoaderComboBox->setModel( m_core->bootLoaderModel() );
    PartitionBarsView::NestedPartitionsMode mode = Calamares::JobQueue::instance()->globalStorage()->
                                                   value( "drawNestedPartitions" ).toBool() ?
                                                       PartitionBarsView::DrawNestedPartitions :
                                                       PartitionBarsView::NoNestedPartitions;
    m_ui->partitionBarsView->setNestedPartitionsMode( mode );
    updateButtons();
    updateBootLoaderInstallPath();

    updateFromCurrentDevice();

    connect( m_ui->deviceComboBox, &QComboBox::currentTextChanged,
             [ this ]( const QString& /* text */ )
    {
        updateFromCurrentDevice();
    } );

    connect( m_ui->bootLoaderComboBox, &QComboBox::currentTextChanged,
             [ this ]( const QString& /* text */ )
    {
        updateBootLoaderInstallPath();
    } );

    connect( m_core, &PartitionCoreModule::isDirtyChanged, m_ui->revertButton, &QWidget::setEnabled );

    connect( m_ui->partitionTreeView, &QAbstractItemView::activated, this, &PartitionPage::onPartitionViewActivated );
    connect( m_ui->revertButton, &QAbstractButton::clicked, this, &PartitionPage::onRevertClicked );
    connect( m_ui->newPartitionTableButton, &QAbstractButton::clicked, this, &PartitionPage::onNewPartitionTableClicked );
    connect( m_ui->createButton, &QAbstractButton::clicked, this, &PartitionPage::onCreateClicked );
    connect( m_ui->editButton, &QAbstractButton::clicked, this, &PartitionPage::onEditClicked );
    connect( m_ui->deleteButton, &QAbstractButton::clicked, this, &PartitionPage::onDeleteClicked );

    if ( QDir( "/sys/firmware/efi/efivars" ).exists() ) {
        m_ui->bootLoaderComboBox->hide();
        m_ui->label_3->hide();
    }
    
    CALAMARES_RETRANSLATE( m_ui->retranslateUi( this ); )
}

PartitionPage::~PartitionPage()
{
}

void
PartitionPage::updateButtons()
{
    bool create = false, edit = false, del = false;

    QModelIndex index = m_ui->partitionTreeView->currentIndex();
    if ( index.isValid() )
    {
        const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
        Q_ASSERT( model );
        Partition* partition = model->partitionForIndex( index );
        Q_ASSERT( partition );
        bool isFree = KPMHelpers::isPartitionFreeSpace( partition );
        bool isExtended = partition->roles().has( PartitionRole::Extended );

        create = isFree;
        // Keep it simple for now: do not support editing extended partitions as
        // it does not work with our current edit implementation which is
        // actually remove + add. This would not work with extended partitions
        // because they need to be created *before* creating logical partitions
        // inside them, so an edit must be applied without altering the job
        // order.
        edit = !isFree && !isExtended;
        del = !isFree;
    }
    m_ui->createButton->setEnabled( create );
    m_ui->editButton->setEnabled( edit );
    m_ui->deleteButton->setEnabled( del );

    m_ui->newPartitionTableButton->setEnabled( m_ui->deviceComboBox->currentIndex() >= 0 );
}

void
PartitionPage::onNewPartitionTableClicked()
{
    QModelIndex index = m_core->deviceModel()->index( m_ui->deviceComboBox->currentIndex(), 0 );
    Q_ASSERT( index.isValid() );
    Device* device = m_core->deviceModel()->deviceForIndex( index );

    QPointer<QDialog> dlg = new QDialog( this );
    Ui_CreatePartitionTableDialog ui;
    ui.setupUi( dlg.data() );
    QString areYouSure = tr( "Are you sure you want to create a new partition table on %1?" ).arg( device->name() );
    ui.areYouSureLabel->setText( areYouSure );
    if ( dlg->exec() == QDialog::Accepted )
    {
        PartitionTable::TableType type = ui.mbrRadioButton->isChecked() ? PartitionTable::msdos : PartitionTable::gpt;
        m_core->createPartitionTable( device, type );
    }
    delete dlg;
}

void
PartitionPage::onCreateClicked()
{
    QModelIndex index = m_ui->partitionTreeView->currentIndex();
    Q_ASSERT( index.isValid() );

    const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
    Partition* partition = model->partitionForIndex( index );
    Q_ASSERT( partition );

    QPointer<CreatePartitionDialog> dlg = new CreatePartitionDialog( model->device(), partition->parent(), this );
    dlg->initFromFreeSpace( partition );
    if ( dlg->exec() == QDialog::Accepted )
    {
        Partition* newPart = dlg->createPartition();
        m_core->createPartition( model->device(), newPart, dlg->newFlags() );
    }
    delete dlg;
}

void
PartitionPage::onEditClicked()
{
    QModelIndex index = m_ui->partitionTreeView->currentIndex();
    Q_ASSERT( index.isValid() );

    const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
    Partition* partition = model->partitionForIndex( index );
    Q_ASSERT( partition );

    if ( KPMHelpers::isPartitionNew( partition ) )
        updatePartitionToCreate( model->device(), partition );
    else
        editExistingPartition( model->device(), partition );
}

void
PartitionPage::onDeleteClicked()
{
    QModelIndex index = m_ui->partitionTreeView->currentIndex();
    Q_ASSERT( index.isValid() );

    const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
    Partition* partition = model->partitionForIndex( index );
    Q_ASSERT( partition );

    m_core->deletePartition( model->device(), partition );
}


void
PartitionPage::onRevertClicked()
{
    ScanningDialog::run(
        QtConcurrent::run( [ this ]
        {
            QMutexLocker locker( &m_revertMutex );

            int oldIndex = m_ui->deviceComboBox->currentIndex();
            m_core->revertAllDevices();
            m_ui->deviceComboBox->setCurrentIndex( oldIndex );
            updateFromCurrentDevice();
        } ),
        []{},
        this );
}

void
PartitionPage::onPartitionViewActivated()
{
    QModelIndex index = m_ui->partitionTreeView->currentIndex();
    if ( !index.isValid() )
        return;

    const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
    Q_ASSERT( model );
    Partition* partition = model->partitionForIndex( index );
    Q_ASSERT( partition );

    // Use the buttons to trigger the actions so that they do nothing if they
    // are disabled. Alternatively, the code could use QAction to centralize,
    // but I don't expect there will be other occurences of triggering the same
    // action from multiple UI elements in this page, so it does not feel worth
    // the price.
    if ( KPMHelpers::isPartitionFreeSpace( partition ) )
        m_ui->createButton->click();
    else
        m_ui->editButton->click();
}

void
PartitionPage::updatePartitionToCreate( Device* device, Partition* partition )
{
    QPointer<CreatePartitionDialog> dlg = new CreatePartitionDialog( device, partition->parent(), this );
    dlg->initFromPartitionToCreate( partition );
    if ( dlg->exec() == QDialog::Accepted )
    {
        Partition* newPartition = dlg->createPartition();
        m_core->deletePartition( device, partition );
        m_core->createPartition( device, newPartition, dlg->newFlags() );
    }
    delete dlg;
}

void
PartitionPage::editExistingPartition( Device* device, Partition* partition )
{
    QPointer<EditExistingPartitionDialog> dlg = new EditExistingPartitionDialog( device, partition, this );
    if ( dlg->exec() == QDialog::Accepted )
        dlg->applyChanges( m_core );
    delete dlg;
}

void
PartitionPage::updateBootLoaderInstallPath()
{
    QVariant var = m_ui->bootLoaderComboBox->currentData( BootLoaderModel::BootLoaderPathRole );
    if ( !var.isValid() )
        return;
    m_core->setBootLoaderInstallPath( var.toString() );
}

void
PartitionPage::updateFromCurrentDevice()
{
    QModelIndex index = m_core->deviceModel()->index( m_ui->deviceComboBox->currentIndex(), 0 );
    if ( !index.isValid() )
        return;

    Device* device = m_core->deviceModel()->deviceForIndex( index );

    QAbstractItemModel* oldModel = m_ui->partitionTreeView->model();
    if ( oldModel )
        disconnect( oldModel, 0, this, 0 );

    PartitionModel* model = m_core->partitionModelForDevice( device );
    m_ui->partitionBarsView->setModel( model );
    m_ui->partitionTreeView->setModel( model );
    m_ui->partitionTreeView->expandAll();

    // Make both views use the same selection model.
    if ( m_ui->partitionBarsView->selectionModel() !=
         m_ui->partitionTreeView->selectionModel() )
    {
        QItemSelectionModel* selectionModel = m_ui->partitionTreeView->selectionModel();
        m_ui->partitionTreeView->setSelectionModel( m_ui->partitionBarsView->selectionModel() );
        selectionModel->deleteLater();
    }

    // This is necessary because even with the same selection model it might happen that
    // a !=0 column is selected in the tree view, which for some reason doesn't trigger a
    // timely repaint in the bars view.
    connect( m_ui->partitionBarsView->selectionModel(), &QItemSelectionModel::currentChanged,
             this, [=]
    {
        QModelIndex selectedIndex = m_ui->partitionBarsView->selectionModel()->currentIndex();
        selectedIndex = selectedIndex.sibling( selectedIndex.row(), 0 );
        m_ui->partitionBarsView->setCurrentIndex( selectedIndex );
    }, Qt::UniqueConnection );

    // Must be done here because we need to have a model set to define
    // individual column resize mode
    QHeaderView* header = m_ui->partitionTreeView->header();
    header->setSectionResizeMode( QHeaderView::ResizeToContents );
    header->setSectionResizeMode( 0, QHeaderView::Stretch );

    updateButtons();
    // Establish connection here because selection model is destroyed when
    // model changes
    connect( m_ui->partitionTreeView->selectionModel(), &QItemSelectionModel::currentChanged,
             [ this ]( const QModelIndex& index, const QModelIndex& oldIndex )
    {
        updateButtons();
    } );
    connect( model, &QAbstractItemModel::modelReset, this, &PartitionPage::onPartitionModelReset );
}

void
PartitionPage::onPartitionModelReset()
{
    m_ui->partitionTreeView->expandAll();
    updateButtons();
}
