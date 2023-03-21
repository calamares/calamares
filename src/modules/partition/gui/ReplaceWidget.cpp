/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2019-2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ReplaceWidget.h"
#include "ui_ReplaceWidget.h"

#include "core/DeviceModel.h"
#include "core/PartitionActions.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionInfo.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "partition/FileSystem.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>

#include <QComboBox>

using CalamaresUtils::Partition::untranslatedFS;
using CalamaresUtils::Partition::userVisibleFS;

ReplaceWidget::ReplaceWidget( PartitionCoreModule* core, QComboBox* devicesComboBox, QWidget* parent )
    : QWidget( parent )
    , m_ui( new Ui_ReplaceWidget )
    , m_core( core )
    , m_isEfi( false )
{
    m_ui->setupUi( this );

    m_ui->bootComboBox->hide();
    m_ui->bootComboBox->clear();
    m_ui->bootStatusLabel->hide();
    m_ui->bootStatusLabel->clear();

    updateFromCurrentDevice( devicesComboBox );
    connect( devicesComboBox, &QComboBox::currentTextChanged, this, [=]( const QString& /* text */ ) {
        updateFromCurrentDevice( devicesComboBox );
    } );

    CALAMARES_RETRANSLATE( onPartitionSelected(); );
}


ReplaceWidget::~ReplaceWidget() {}


bool
ReplaceWidget::isNextEnabled() const
{
    return m_nextEnabled;
}


void
ReplaceWidget::reset()
{
    //moo;
}


void
ReplaceWidget::applyChanges()
{
    auto gs = Calamares::JobQueue::instance()->globalStorage();

    PartitionModel* model = qobject_cast< PartitionModel* >( m_ui->partitionTreeView->model() );
    if ( model )
    {
        Partition* partition = model->partitionForIndex( m_ui->partitionTreeView->currentIndex() );
        if ( partition )
        {
            Device* dev = model->device();

            PartitionActions::doReplacePartition( m_core,
                                                  dev,
                                                  partition,
                                                  { gs->value( "defaultPartitionTableType" ).toString(),
                                                    gs->value( "defaultFileSystemType" ).toString(),
                                                    QString() } );

            if ( m_isEfi )
            {
                QList< Partition* > efiSystemPartitions = m_core->efiSystemPartitions();
                if ( efiSystemPartitions.count() == 1 )
                {
                    PartitionInfo::setMountPoint( efiSystemPartitions.first(),
                                                  gs->value( "efiSystemPartition" ).toString() );
                }
                else if ( efiSystemPartitions.count() > 1 )
                {
                    PartitionInfo::setMountPoint( efiSystemPartitions.at( m_ui->bootComboBox->currentIndex() ),
                                                  gs->value( "efiSystemPartition" ).toString() );
                }
            }

            m_core->dumpQueue();
        }
    }
}


void
ReplaceWidget::onPartitionSelected()
{
    if ( Calamares::JobQueue::instance()->globalStorage()->value( "firmwareType" ) == "efi" )
    {
        m_isEfi = true;
    }

    const auto* branding = Calamares::Branding::instance();
    if ( m_ui->partitionTreeView->currentIndex() == QModelIndex() )
    {
        updateStatus( CalamaresUtils::PartitionPartition,
                      tr( "Select where to install %1.<br/>"
                          "<font color=\"red\">Warning: </font>this will delete all files "
                          "on the selected partition." )
                          .arg( branding->versionedName() ) );
        setNextEnabled( false );
        return;
    }

    bool ok = false;
    double requiredSpaceB
        = Calamares::JobQueue::instance()->globalStorage()->value( "requiredStorageGiB" ).toDouble( &ok ) * 1024 * 1024
        * 1024;

    PartitionModel* model = qobject_cast< PartitionModel* >( m_ui->partitionTreeView->model() );
    if ( model && ok )
    {
        const QStringList osproberLines
            = Calamares::JobQueue::instance()->globalStorage()->value( "osproberLines" ).toStringList();

        Partition* partition = model->partitionForIndex( m_ui->partitionTreeView->currentIndex() );
        if ( !partition || partition->state() != KPM_PARTITION_STATE( None ) )
        {
            updateStatus( CalamaresUtils::Fail, tr( "The selected item does not appear to be a valid partition." ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->roles().has( PartitionRole::Unallocated ) )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "%1 cannot be installed on empty space. Please select an "
                              "existing partition." )
                              .arg( branding->versionedName() ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->roles().has( PartitionRole::Extended ) )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "%1 cannot be installed on an extended partition. Please select an "
                              "existing primary or logical partition." )
                              .arg( branding->versionedName() ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->partitionPath().isEmpty() )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "%1 cannot be installed on this partition." ).arg( branding->versionedName() ) );
            setNextEnabled( false );
            return;
        }

        QString fsNameForUser = userVisibleFS( partition->fileSystem() );
        QString prettyName = tr( "Data partition (%1)" ).arg( fsNameForUser );
        for ( const auto& line : osproberLines )
        {
            QStringList lineColumns = line.split( ':' );

            QString path = lineColumns.value( 0 ).simplified();
            if ( path == partition->partitionPath() )
            {
                QString osName;
                if ( !lineColumns.value( 1 ).simplified().isEmpty() )
                {
                    osName = lineColumns.value( 1 ).simplified();
                }
                else if ( !lineColumns.value( 2 ).simplified().isEmpty() )
                {
                    osName = lineColumns.value( 2 ).simplified();
                }

                if ( osName.isEmpty() )
                {
                    prettyName = tr( "Unknown system partition (%1)" ).arg( fsNameForUser );
                }
                else
                {
                    prettyName = tr( "%1 system partition (%2)" )
                                     .arg( osName.replace( 0, 1, osName.at( 0 ).toUpper() ) )
                                     .arg( fsNameForUser );
                }
                break;
            }
        }

        if ( partition->capacity() < requiredSpaceB )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "<strong>%4</strong><br/><br/>"
                              "The partition %1 is too small for %2. Please select a partition "
                              "with capacity at least %3 GiB." )
                              .arg( partition->partitionPath() )
                              .arg( branding->versionedName() )
                              .arg( requiredSpaceB / ( 1024. * 1024. * 1024. ), 0, 'f', 1 )
                              .arg( prettyName ) );
            setNextEnabled( false );
            return;
        }

        m_ui->bootComboBox->hide();
        m_ui->bootComboBox->clear();
        m_ui->bootStatusLabel->hide();
        m_ui->bootStatusLabel->clear();

        if ( m_isEfi )
        {
            QList< Partition* > efiSystemPartitions = m_core->efiSystemPartitions();
            if ( efiSystemPartitions.count() == 0 )
            {
                updateStatus( CalamaresUtils::Fail,
                              tr( "<strong>%2</strong><br/><br/>"
                                  "An EFI system partition cannot be found anywhere "
                                  "on this system. Please go back and use manual "
                                  "partitioning to set up %1." )
                                  .arg( branding->shortProductName() )
                                  .arg( prettyName ) );
                setNextEnabled( false );
            }
            else if ( efiSystemPartitions.count() == 1 )
            {
                updateStatus( CalamaresUtils::PartitionPartition,
                              tr( "<strong>%3</strong><br/><br/>"
                                  "%1 will be installed on %2.<br/>"
                                  "<font color=\"red\">Warning: </font>all data on partition "
                                  "%2 will be lost." )
                                  .arg( branding->versionedName() )
                                  .arg( partition->partitionPath() )
                                  .arg( prettyName ) );
                m_ui->bootStatusLabel->show();
                m_ui->bootStatusLabel->setText( tr( "The EFI system partition at %1 will be used for starting %2." )
                                                    .arg( efiSystemPartitions.first()->partitionPath() )
                                                    .arg( branding->shortProductName() ) );
                setNextEnabled( true );
            }
            else
            {
                updateStatus( CalamaresUtils::PartitionPartition,
                              tr( "<strong>%3</strong><br/><br/>"
                                  "%1 will be installed on %2.<br/>"
                                  "<font color=\"red\">Warning: </font>all data on partition "
                                  "%2 will be lost." )
                                  .arg( branding->versionedName() )
                                  .arg( partition->partitionPath() )
                                  .arg( prettyName ) );
                m_ui->bootStatusLabel->show();
                m_ui->bootStatusLabel->setText( tr( "EFI system partition:" ) );
                m_ui->bootComboBox->show();
                for ( int i = 0; i < efiSystemPartitions.count(); ++i )
                {
                    Partition* efiPartition = efiSystemPartitions.at( i );
                    m_ui->bootComboBox->addItem( efiPartition->partitionPath(), i );
                    if ( efiPartition->devicePath() == partition->devicePath() && efiPartition->number() == 1 )
                    {
                        m_ui->bootComboBox->setCurrentIndex( i );
                    }
                }
                setNextEnabled( true );
            }
        }
        else
        {
            updateStatus( CalamaresUtils::PartitionPartition,
                          tr( "<strong>%3</strong><br/><br/>"
                              "%1 will be installed on %2.<br/>"
                              "<font color=\"red\">Warning: </font>all data on partition "
                              "%2 will be lost." )
                              .arg( branding->versionedName() )
                              .arg( partition->partitionPath() )
                              .arg( prettyName ) );
            setNextEnabled( true );
        }
    }
}


void
ReplaceWidget::setNextEnabled( bool enabled )
{
    if ( enabled == m_nextEnabled )
    {
        return;
    }

    m_nextEnabled = enabled;
    Q_EMIT nextStatusChanged( enabled );
}


void
ReplaceWidget::updateStatus( CalamaresUtils::ImageType imageType, const QString& text )
{
    int iconSize = CalamaresUtils::defaultFontHeight() * 6;
    m_ui->selectedIconLabel->setPixmap(
        CalamaresUtils::defaultPixmap( imageType, CalamaresUtils::Original, QSize( iconSize, iconSize ) ) );
    m_ui->selectedIconLabel->setFixedHeight( iconSize );
    m_ui->selectedStatusLabel->setText( text );
}


void
ReplaceWidget::updateFromCurrentDevice( QComboBox* devicesComboBox )
{
    QModelIndex index = m_core->deviceModel()->index( devicesComboBox->currentIndex(), 0 );
    if ( !index.isValid() )
    {
        return;
    }

    Device* device = m_core->deviceModel()->deviceForIndex( index );

    QAbstractItemModel* oldModel = m_ui->partitionTreeView->model();
    if ( oldModel )
    {
        disconnect( oldModel, nullptr, this, nullptr );
    }

    PartitionModel* model = m_core->partitionModelForDevice( device );
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
    connect( m_ui->partitionTreeView->selectionModel(),
             &QItemSelectionModel::currentRowChanged,
             this,
             &ReplaceWidget::onPartitionViewActivated );

    connect( model, &QAbstractItemModel::modelReset, this, &ReplaceWidget::onPartitionModelReset );
}


void
ReplaceWidget::onPartitionViewActivated()
{
    QModelIndex index = m_ui->partitionTreeView->currentIndex();
    if ( !index.isValid() )
    {
        return;
    }

    const PartitionModel* model = static_cast< const PartitionModel* >( index.model() );
    Q_ASSERT( model );
    Partition* partition = model->partitionForIndex( index );
    Q_ASSERT( partition );

    onPartitionSelected();
}


void
ReplaceWidget::onPartitionModelReset()
{
    m_ui->partitionTreeView->expandAll();
    onPartitionSelected();
}
