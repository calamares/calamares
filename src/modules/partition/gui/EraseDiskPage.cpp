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

#include "EraseDiskPage.h"

#include "core/DeviceModel.h"
#include "core/PartitionCoreModule.h"
#include "core/partition.h"
#include "core/PMUtils.h"
#include "core/PartitionInfo.h"
#include "core/device.h"
#include "fs/filesystem.h"
#include "gui/PartitionPreview.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QBoxLayout>
#include <QDir>
#include <QFormLayout>
#include <QListView>
#include <QLabel>
#include <QMutexLocker>

EraseDiskPage::EraseDiskPage( QWidget* parent )
    : QWidget( parent )
    , m_nextEnabled( false )
    , m_core( nullptr )
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QLabel* driveLabel = new QLabel( this );
    mainLayout->addWidget( driveLabel );
    CALAMARES_RETRANSLATE( driveLabel->setText( tr( "Select drive:" ) ); )

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

    m_previewFrame = new QWidget;
    m_previewFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    mainLayout->addWidget( m_previewFrame );

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

    connect( m_drivesView->selectionModel(), &QItemSelectionModel::currentChanged,
             this, [ this ]( const QModelIndex& index,
                             const QModelIndex& oldIndex )
    {
        setNextEnabled( m_drivesView->selectionModel()->hasSelection() );

        if ( m_core->isDirty() )
            m_core->clearJobs();

        Device* dev = m_core->deviceModel()->deviceForIndex( index );

        if ( dev )
            doAutopartition( dev );
    } );

    connect( m_core, &PartitionCoreModule::isDirtyChanged,
             this, &EraseDiskPage::updatePreviews );
}


bool
EraseDiskPage::isNextEnabled() const
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


void
EraseDiskPage::doAutopartition( Device* dev )
{
    bool isEfi = false;
    if ( QDir( "/sys/firmware/efi/efivars" ).exists() )
        isEfi = true;

#define MiB * 1024 * 1024

    // Partition sizes are expressed in MiB, should be multiples of
    // the logical sector size (usually 512B).
    int uefisys_part_size = 0;
    int empty_space_size = 0;
    if ( isEfi )
    {
        uefisys_part_size = 100;
        empty_space_size = 2;
    }
    else
    {
        // we start with a 1MiB offset before the first partition
        empty_space_size = 1;
    }

    qint64 first_free_sector = empty_space_size MiB / dev->logicalSectorSize() + 1;

    if ( isEfi )
    {
        qint64 lastSector = first_free_sector + ( uefisys_part_size MiB / dev->logicalSectorSize() );
        m_core->createPartitionTable( dev, PartitionTable::gpt );
        Partition* efiPartition = PMUtils::createNewPartition(
            dev->partitionTable(),
            *dev,
            PartitionRole( PartitionRole::Primary ),
            FileSystem::Fat32,
            first_free_sector,
            lastSector
        );
        PartitionInfo::setMountPoint( efiPartition, Calamares::JobQueue::instance()
                                                        ->globalStorage()
                                                        ->value( "efiSystemPartition" )
                                                        .toString() );
        PartitionInfo::setFormat( efiPartition, true );
        m_core->createPartition( dev, efiPartition );
        first_free_sector = lastSector + 1;
    }
    else
    {
        m_core->createPartitionTable( dev, PartitionTable::msdos );
    }

    Partition* rootPartition = PMUtils::createNewPartition(
        dev->partitionTable(),
        *dev,
        PartitionRole( PartitionRole::Primary ),
        FileSystem::Ext4,
        first_free_sector,
        dev->totalSectors() - 1 //last sector
    );
    PartitionInfo::setMountPoint( rootPartition, "/" );
    PartitionInfo::setFormat( rootPartition, true );
    m_core->createPartition( dev, rootPartition );

    updatePreviews();

    m_core->dumpQueue();
}


void
EraseDiskPage::updatePreviews()
{
    QMutexLocker locker( &m_previewsMutex );

    cDebug() << "Updating partitioning preview widgets.";
    qDeleteAll( m_previewFrame->children() );
    m_previewFrame->layout()->deleteLater();

    if ( m_drivesView->selectionModel()->currentIndex() == QModelIndex() )
    {
        cDebug() << "No disk selected, bailing out.";
        return;
    }

    QFormLayout* layout = new QFormLayout;
    m_previewFrame->setLayout( layout );
    layout->setMargin( 0 );

    QList< PartitionCoreModule::SummaryInfo > list = m_core->createSummaryInfo();
    for ( const auto& info : list )
    {
        PartitionPreview* preview;

        layout->addRow( new QLabel( info.deviceName ) );

        preview = new PartitionPreview;
        preview->setLabelsVisible( true );
        preview->setModel( info.partitionModelBefore );
        info.partitionModelBefore->setParent( m_previewFrame );
        layout->addRow( tr( "Before:" ), preview );

        preview = new PartitionPreview;
        preview->setLabelsVisible( true );
        preview->setModel( info.partitionModelAfter );
        info.partitionModelAfter->setParent( m_previewFrame );
        layout->addRow( tr( "After:" ), preview );
    }
}
