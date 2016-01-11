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

#include "AlongsidePage.h"

#include "core/ColorUtils.h"
#include "core/PartitionCoreModule.h"
#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/PartitionInfo.h"
#include "core/PartitionIterator.h"
#include "gui/PartitionSplitterWidget.h"
#include "gui/PartitionBarsView.h"
#include "gui/PartitionLabelsView.h"

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"
#include "Branding.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>

#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QDir>


AlongsidePage::AlongsidePage( QWidget* parent )
    : QWidget( parent )
    , m_nextEnabled( false )
    , m_core( nullptr )
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    QHBoxLayout* partitionsComboLayout = new QHBoxLayout;
    mainLayout->addLayout( partitionsComboLayout );

    QLabel* partitionsLabel = new QLabel;
    partitionsComboLayout->addWidget( partitionsLabel );

    m_partitionsComboBox = new QComboBox;
    partitionsComboLayout->addWidget( m_partitionsComboBox );
    partitionsLabel->setBuddy( m_partitionsComboBox );

    partitionsComboLayout->addStretch();

    m_previewWidget = new PartitionBarsView;
    m_previewLabels = new PartitionLabelsView;
    mainLayout->addWidget( m_previewWidget );
    mainLayout->addWidget( m_previewLabels );

    QLabel* allocateSpaceLabel = new QLabel();
    mainLayout->addWidget( allocateSpaceLabel );

    CALAMARES_RETRANSLATE(
        partitionsLabel->setText( tr( "Choose partition to shrink:" ) );
        allocateSpaceLabel->setText( tr( "Allocate drive space by dragging the divider below:" ) );
    )

    m_splitterWidget = new PartitionSplitterWidget;
    mainLayout->addWidget( m_splitterWidget );

    m_sizeLabel = new QLabel;
    m_sizeLabel->setWordWrap( true );
    mainLayout->addWidget( m_sizeLabel );

    QBoxLayout* efiLayout = new QHBoxLayout;
    m_efiLabel = new QLabel;
    m_efiComboBox = new QComboBox;
    efiLayout->addWidget( m_efiLabel );
    efiLayout->addWidget( m_efiComboBox );
    m_efiLabel->setBuddy( m_efiComboBox );
    efiLayout->addStretch();
    mainLayout->addLayout( efiLayout );

    m_efiLabel->hide();
    m_efiComboBox->hide();

    m_isEfi = QDir( "/sys/firmware/efi/efivars" ).exists();

    mainLayout->addStretch();
}


void
AlongsidePage::init( PartitionCoreModule* core )
{
    if ( m_core != core )
        m_core = core;

    m_partitionsComboBox->clear();

    connect( m_partitionsComboBox,
             static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
             this, &AlongsidePage::onPartitionSelected );

    connect( m_splitterWidget, &PartitionSplitterWidget::partitionResized,
             this, [ this ]( const QString& path, qint64 size, qint64 sizeNext )
    {
        m_sizeLabel->setText( tr( "With this operation, the partition <strong>%1</strong> which contains "
                                  "%4 will be shrunk "
                                  "to %2MB and a new %3MB partition will be created for %5." )
                              .arg( path )
                              .arg( size / ( 1024 * 1024 ) )
                              .arg( sizeNext / ( 1024 * 1024 ) )
                              .arg( m_partitionsComboBox->currentText() )
                              .arg( Calamares::Branding::instance()->
                                        string( Calamares::Branding::ProductName ) ) );
    } );

    foreach ( const OsproberEntry& e, m_core->osproberEntries() )
    {
        if ( e.canBeResized )
            m_partitionsComboBox->addItem( e.prettyName + " (" + e.path + ")", e.path );
    }
    setNextEnabled( true );
}


void
AlongsidePage::onPartitionSelected( int comboBoxIndex )
{
    QString path = m_partitionsComboBox->itemData( comboBoxIndex ).toString();
    cDebug() << "Current index changed:" << path;

    DeviceModel* dm = m_core->deviceModel();
    for ( int i = 0; i < dm->rowCount(); ++i )
    {
        Device* dev = dm->deviceForIndex( dm->index( i ) );
        Partition* candidate = KPMHelpers::findPartitionByPath( { dev }, path );
        if ( candidate )
        {
            // store candidate->partitionPath() here!

            bool ok = false;
            double requiredStorageGB = Calamares::JobQueue::instance()
                                            ->globalStorage()
                                            ->value( "requiredStorageGB" )
                                            .toDouble( &ok );

            qint64 usedStorageB = candidate->sectorsUsed() * dev->logicalSectorSize();
            qint64 requiredStorageB = ( requiredStorageGB + 0.1 + 2.0 ) * 1024 * 1024 * 1024;

            // set up splitter widget here, then set up the split position

            Device* deviceBefore = m_core->createImmutableDeviceCopy( dev );

            PartitionModel* partitionModelBefore = new PartitionModel;
            partitionModelBefore->init( deviceBefore, m_core->osproberEntries() );
            deviceBefore->setParent( partitionModelBefore );
            partitionModelBefore->setParent( m_previewWidget );

            m_previewWidget->setModel( partitionModelBefore );
            m_previewLabels->setModel( partitionModelBefore );
            m_splitterWidget->init( dev );

            m_splitterWidget->setSplitPartition( candidate->partitionPath(),
                                                 candidate->used() * 1.1,
                                                 candidate->capacity() - requiredStorageB,
                                                 candidate->capacity() / 2,
                                                 Calamares::Branding::instance()->
                                                     string( Calamares::Branding::ProductName ) );

            m_splitterWidget->setFixedHeight( qMax< int >( CalamaresUtils::defaultFontHeight() * 1.5, 30 ) );

            m_efiComboBox->hide();
            m_efiLabel->hide();

            if ( m_isEfi )
            {
                QList< Partition* > efiSystemPartitions = m_core->efiSystemPartitions();
                m_efiLabel->show();

                if ( efiSystemPartitions.count() == 0 )
                {
                    m_efiLabel->setText(
                                tr( "An EFI system partition cannot be found anywhere "
                                    "on this system. Please go back and use manual "
                                    "partitioning to set up %1." )
                                .arg( Calamares::Branding::instance()->
                                      string( Calamares::Branding::ShortProductName ) ) );
                    setNextEnabled( false );
                }
                else if ( efiSystemPartitions.count() == 1 )
                {
                    m_efiLabel->setText(
                                tr( "The EFI system partition at %1 will be used for "
                                    "starting %2." )
                                .arg( efiSystemPartitions.first()->partitionPath() )
                                .arg( Calamares::Branding::instance()->
                                      string( Calamares::Branding::ShortProductName ) ) );
                    setNextEnabled( true );
                }
                else
                {
                    m_efiComboBox->show();
                    m_efiLabel->setText( tr( "EFI system partition:" ) );
                    for ( int i = 0; i < efiSystemPartitions.count(); ++i )
                    {
                        Partition* efiPartition = efiSystemPartitions.at( i );
                        m_efiComboBox->addItem( efiPartition->partitionPath(), i );
                        if ( efiPartition->devicePath() == candidate->devicePath() &&
                             efiPartition->number() == 1 )
                            m_efiComboBox->setCurrentIndex( i );
                    }
                    setNextEnabled( true );
                }
            }
            else
            {
                setNextEnabled( true );
            }
            return;
        }
    }
}


bool
AlongsidePage::isNextEnabled() const
{
    return m_nextEnabled;
}


void
AlongsidePage::applyChanges()
{
    m_core->revert();

    Q_ASSERT( m_splitterWidget->splitPartitionSize() >= 0 );
    Q_ASSERT( m_splitterWidget->newPartitionSize()   >= 0 );


    QString path = m_partitionsComboBox->currentData().toString();

    DeviceModel* dm = m_core->deviceModel();
    for ( int i = 0; i < dm->rowCount(); ++i )
    {
        Device* dev = dm->deviceForIndex( dm->index( i ) );
        Partition* candidate = KPMHelpers::findPartitionByPath( { dev }, path );
        if ( candidate )
        {
            qint64 firstSector = candidate->firstSector();
            qint64 oldLastSector = candidate->lastSector();
            qint64 newLastSector = m_splitterWidget->splitPartitionSize() /
                                   dev->logicalSectorSize();

            m_core->resizePartition( dev, candidate, firstSector, newLastSector );
            Partition* newPartition = KPMHelpers::createNewPartition(
                                          candidate->parent(),
                                          *dev,
                                          candidate->roles(),
                                          FileSystem::Ext4,
                                          newLastSector + 1,
                                          oldLastSector );
            PartitionInfo::setMountPoint( newPartition, "/" );
            PartitionInfo::setFormat( newPartition, true );

            m_core->createPartition( dev, newPartition );
            m_core->setBootLoaderInstallPath( dev->deviceNode() );

            if ( m_isEfi )
            {
                QList< Partition* > efiSystemPartitions = m_core->efiSystemPartitions();
                if ( efiSystemPartitions.count() == 1 )
                {
                    PartitionInfo::setMountPoint(
                            efiSystemPartitions.first(),
                            Calamares::JobQueue::instance()->
                                globalStorage()->
                                    value( "efiSystemPartition" ).toString() );
                }
                else if ( efiSystemPartitions.count() > 1 )
                {
                    PartitionInfo::setMountPoint(
                            efiSystemPartitions.at( m_efiComboBox->currentIndex() ),
                            Calamares::JobQueue::instance()->
                                globalStorage()->
                                    value( "efiSystemPartition" ).toString() );
                }
            }

            m_core->dumpQueue();

            break;
        }
    }
}


void
AlongsidePage::setNextEnabled( bool enabled )
{
    if ( enabled == m_nextEnabled )
        return;

    m_nextEnabled = enabled;
    emit nextStatusChanged( enabled );
}

