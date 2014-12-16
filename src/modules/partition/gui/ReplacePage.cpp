/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#include "ReplacePage.h"
#include "ui_ReplacePage.h"

#include <core/PartitionCoreModule.h>
#include <core/DeviceModel.h>
#include <core/partition.h>
#include <fs/filesystem.h>
#include <core/PMUtils.h>
#include <core/PartitionInfo.h>

#include <JobQueue.h>
#include <GlobalStorage.h>
#include <utils/Retranslator.h>
#include <utils/CalamaresUtilsGui.h>
#include <utils/Logger.h>
#include <Branding.h>


ReplacePage::ReplacePage( PartitionCoreModule* core, QWidget* parent )
    : QWidget( parent )
    , m_ui( new Ui_ReplacePage )
    , m_core( core )
{
    m_ui->setupUi( this );
    m_ui->deviceComboBox->setModel( m_core->deviceModel() );

//    updateButtons();

    updateFromCurrentDevice();

    connect( m_ui->deviceComboBox, &QComboBox::currentTextChanged,
             [ this ]( const QString& /* text */ )
    {
        updateFromCurrentDevice();
    } );

    connect( m_ui->partitionTreeView, &QAbstractItemView::activated,
             this, &ReplacePage::onPartitionViewActivated );

    CALAMARES_RETRANSLATE(
        m_ui->retranslateUi( this );
        onPartitionSelected();
    )
}


ReplacePage::~ReplacePage()
{}


bool
ReplacePage::isNextEnabled() const
{
    return m_nextEnabled;
}


void
ReplacePage::applyChanges()
{
    PartitionModel* model = qobject_cast< PartitionModel* >( m_ui->partitionTreeView->model() );
    if ( model )
    {
        Partition* partition = model->partitionForIndex( m_ui->partitionTreeView->currentIndex() );
        if ( partition )
        {
            Device* dev = model->device();
            Partition* newPartition = PMUtils::createNewPartition(
                                          partition->parent(),
                                          *dev,
                                          partition->roles(),
                                          FileSystem::Ext4,
                                          partition->firstSector(),
                                          partition->lastSector() );
            PartitionInfo::setMountPoint( newPartition, "/" );
            PartitionInfo::setFormat( newPartition, true );

            m_core->deletePartition( dev, partition );
            m_core->createPartition( dev, newPartition );

            m_core->dumpQueue();
        }
    }
}


void
ReplacePage::onPartitionSelected()
{
    if ( m_ui->partitionTreeView->currentIndex() == QModelIndex() )
    {
        updateStatus( CalamaresUtils::Partitions,
                      tr( "Select where to install %1.<br/>"
                          "<font color=\"red\">Warning: </font>This will delete all files "
                          "on the selected partition." )
                          .arg( Calamares::Branding::instance()->
                                string( Calamares::Branding::VersionedName ) ) );
        setNextEnabled( false );
        return;
    }

    bool ok = false;
    double requiredSpaceB = Calamares::JobQueue::instance()
                            ->globalStorage()
                            ->value( "requiredStorageGB" )
                            .toDouble( &ok ) * 1024 * 1024 * 1024;

    PartitionModel* model = qobject_cast< PartitionModel* >( m_ui->partitionTreeView->model() );
    if ( model && ok )
    {
        Partition* partition = model->partitionForIndex( m_ui->partitionTreeView->currentIndex() );
        if ( !partition ||
             partition->state() != Partition::StateNone )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "The selected item does not appear to be a valid partition." ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->roles().has( PartitionRole::Unallocated ) )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "%1 cannot be installed on empty space. Please select an "
                              "existing partition." )
                          .arg( Calamares::Branding::instance()->
                                string( Calamares::Branding::VersionedName ) ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->roles().has( PartitionRole::Extended ) )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "%1 cannot be installed on an extended partition. Please select an "
                              "existing primary or logical partition." )
                          .arg( Calamares::Branding::instance()->
                                string( Calamares::Branding::VersionedName ) ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->partitionPath().isEmpty() )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "%1 cannot be installed on this partition." )
                          .arg( Calamares::Branding::instance()->
                                string( Calamares::Branding::VersionedName ) ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->capacity() < requiredSpaceB )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "The partition %1 is too small for %2. Please select a partition "
                              "with capacity at least %3 GB." )
                          .arg( partition->partitionPath() )
                          .arg( Calamares::Branding::instance()->
                                string( Calamares::Branding::VersionedName ) )
                          .arg( requiredSpaceB / ( 1024. * 1024. * 1024. ),
                                0, 'f', 1 ) );
            setNextEnabled( false );
            return;
        }

        updateStatus( CalamaresUtils::Partitions,
                      tr( "%1 will be installed on %2." )
                        .arg( Calamares::Branding::instance()->
                            string( Calamares::Branding::VersionedName ) )
                        .arg( partition->partitionPath() ) );
        setNextEnabled( true );
    }
}


void
ReplacePage::setNextEnabled( bool enabled )
{
    if ( enabled == m_nextEnabled )
        return;

    m_nextEnabled = enabled;
    emit nextStatusChanged( enabled );
}


void
ReplacePage::updateStatus( CalamaresUtils::ImageType imageType, const QString& text )
{
    int iconSize = CalamaresUtils::defaultFontHeight() * 8;
    m_ui->selectedIconLabel->setPixmap( CalamaresUtils::defaultPixmap( imageType,
                                                                       CalamaresUtils::Original,
                                                                       QSize( iconSize, iconSize ) ) );
    m_ui->selectedIconLabel->setFixedHeight( iconSize );
    m_ui->selectedStatusLabel->setText( text );
}


void
ReplacePage::updateFromCurrentDevice()
{
    QModelIndex index = m_core->deviceModel()->index( m_ui->deviceComboBox->currentIndex(), 0 );
    if ( !index.isValid() )
        return;

    Device* device = m_core->deviceModel()->deviceForIndex( index );

    QAbstractItemModel* oldModel = m_ui->partitionTreeView->model();
    if ( oldModel )
        disconnect( oldModel, 0, this, 0 );

    PartitionModel* model = m_core->partitionModelForDevice( device );
    m_ui->partitionPreview->setModel( model );
    m_ui->partitionTreeView->setModel( model );
    m_ui->partitionTreeView->expandAll();

    // Must be done here because we need to have a model set to define
    // individual column resize mode
    QHeaderView* header = m_ui->partitionTreeView->header();
    header->setSectionResizeMode( QHeaderView::ResizeToContents );
    header->setSectionResizeMode( 0, QHeaderView::Stretch );

    //updateButtons();
    // Establish connection here because selection model is destroyed when
    // model changes
    connect( m_ui->partitionTreeView->selectionModel(), &QItemSelectionModel::currentChanged,
             [ this ]( const QModelIndex& index, const QModelIndex& oldIndex )
    {
    //    updateButtons();
    } );
    connect( model, &QAbstractItemModel::modelReset, this, &ReplacePage::onPartitionModelReset );
}


void
ReplacePage::onPartitionViewActivated()
{
    QModelIndex index = m_ui->partitionTreeView->currentIndex();
    if ( !index.isValid() )
        return;

    const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
    Q_ASSERT( model );
    Partition* partition = model->partitionForIndex( index );
    Q_ASSERT( partition );

    onPartitionSelected();
}


void
ReplacePage::onPartitionModelReset()
{
    m_ui->partitionTreeView->expandAll();
    onPartitionSelected();
}
