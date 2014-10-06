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

#include "core/ColorUtils.h"
#include "core/PartitionCoreModule.h"
#include "core/DeviceModel.h"
#include "core/PMUtils.h"
#include "core/device.h"
#include "core/partition.h"
#include "core/PartitionInfo.h"
#include "core/PartitionIterator.h"
#include "gui/PartitionSplitterWidget.h"

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "utils/Logger.h"
#include "utils/CalamaresUtilsGui.h"

#include <QBoxLayout>
#include <QComboBox>
#include <QLabel>


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
    partitionsLabel->setText( tr( "Choose partition to shrink:" ) );
    partitionsComboLayout->addWidget( partitionsLabel );

    m_partitionsComboBox = new QComboBox;
    partitionsComboLayout->addWidget( m_partitionsComboBox );
    partitionsLabel->setBuddy( m_partitionsComboBox );

    partitionsComboLayout->addStretch();

    mainLayout->addWidget( new QLabel( tr( "Allocate drive space by dragging the divider below:" ) ) );

    m_splitterWidget = new PartitionSplitterWidget;
    mainLayout->addWidget( m_splitterWidget );

    m_sizeLabel = new QLabel;
    m_sizeLabel->setWordWrap( true );
    mainLayout->addWidget( m_sizeLabel );

    mainLayout->addStretch();
}


void
AlongsidePage::init( PartitionCoreModule* core , const OsproberEntryList& osproberEntries )
{
    if ( m_core != core )
        m_core = core;

    m_partitionsComboBox->clear();

    connect( m_partitionsComboBox,
             static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
             this, [ this ]( int index )
    {
        QString path = m_partitionsComboBox->itemData( index ).toString();
        cDebug() << "Current index changed:" << path;

        DeviceModel* dm = m_core->deviceModel();
        for ( int i = 0; i < dm->rowCount(); ++i )
        {
            Device* dev = dm->deviceForIndex( dm->index( i ) );
            Partition* candidate = PMUtils::findPartitionByPath( { dev }, path );
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
                QList< PartitionSplitterItem > allPartitionItems;
                {
                    PartitionSplitterItem* extendedPartitionItem = nullptr;
                    for ( auto it = PartitionIterator::begin( dev );
                          it != PartitionIterator::end( dev ); ++it )
                    {
                        PartitionSplitterItem newItem = {
                            ( *it )->partitionPath(),
                            ColorUtils::colorForPartition( *it ),
                            false,
                            ( *it )->capacity(),
                            {}
                        };

                        if ( ( *it )->roles().has( PartitionRole::Logical ) && extendedPartitionItem )
                            extendedPartitionItem->children.append( newItem );
                        else
                        {
                            allPartitionItems.append( newItem );
                            if ( ( *it )->roles().has( PartitionRole::Extended ) )
                                extendedPartitionItem = &allPartitionItems.last();
                        }
                    }
                }

                m_splitterWidget->init( allPartitionItems );

                m_splitterWidget->setSplitPartition( candidate->partitionPath(),
                                                     candidate->used() * 1.1,
                                                     candidate->capacity() - requiredStorageB,
                                                     candidate->capacity() / 2,
                                                     tr( "$RELEASE" ) );

                m_splitterWidget->setFixedHeight( qMax< int >( CalamaresUtils::defaultFontHeight() * 1.5, 30 ) );
                if ( ok )
                {



                }

                setNextEnabled( true );
                return;
            }
        }
    } );

    connect( m_splitterWidget, &PartitionSplitterWidget::partitionResized,
             this, [ this ]( const QString& path, qint64 size, qint64 sizeNext )
    {
        m_sizeLabel->setText( tr( "With this operation, the partition <b>%1</b> which contains "
                                  "%4 will be shrunk "
                                  "to %2MB and a new %3MB partition will be created for "
                                  "$RELEASE." )
                              .arg( path )
                              .arg( size / ( 1024 * 1024 ) )
                              .arg( sizeNext / ( 1024 * 1024 ) )
                              .arg( m_partitionsComboBox->currentText() ) );
    } );

    foreach ( const OsproberEntry& e, osproberEntries )
    {
        if ( e.canBeResized )
            m_partitionsComboBox->addItem( e.prettyName + " (" + e.path + ")", e.path );
    }
    setNextEnabled( true );
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
        Partition* candidate = PMUtils::findPartitionByPath( { dev }, path );
        if ( candidate )
        {
            qint64 firstSector = candidate->firstSector();
            qint64 oldLastSector = candidate->lastSector();
            qint64 newLastSector = m_splitterWidget->splitPartitionSize() /
                                   dev->logicalSectorSize();

            m_core->resizePartition( dev, candidate, firstSector, newLastSector );
            Partition* newPartition = PMUtils::createNewPartition(
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

