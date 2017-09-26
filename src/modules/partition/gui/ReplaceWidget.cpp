/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#include "ReplaceWidget.h"
#include "ui_ReplaceWidget.h"

#include "core/DeviceModel.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionActions.h"
#include "core/PartitionInfo.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Retranslator.h"

#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>

#include <QComboBox>

ReplaceWidget::ReplaceWidget( PartitionCoreModule* core,
                              QComboBox* devicesComboBox,
                              QWidget* parent )
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
    connect( devicesComboBox, &QComboBox::currentTextChanged,
             this, [=]( const QString& /* text */ )
    {
        updateFromCurrentDevice( devicesComboBox );
    } );

    CALAMARES_RETRANSLATE(
        onPartitionSelected();
    )
}


ReplaceWidget::~ReplaceWidget()
{}


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
    PartitionModel* model = qobject_cast< PartitionModel* >( m_ui->partitionTreeView->model() );
    if ( model )
    {
        Partition* partition = model->partitionForIndex( m_ui->partitionTreeView->currentIndex() );
        if ( partition )
        {
            Device* dev = model->device();

            PartitionActions::doReplacePartition( m_core, dev, partition );

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
                            efiSystemPartitions.at( m_ui->bootComboBox->currentIndex() ),
                            Calamares::JobQueue::instance()->
                                globalStorage()->
                                    value( "efiSystemPartition" ).toString() );
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
        m_isEfi = true;

    if ( m_ui->partitionTreeView->currentIndex() == QModelIndex() )
    {
        updateStatus( CalamaresUtils::PartitionPartition,
                      tr( "Select where to install %1.<br/>"
                          "<font color=\"red\">Warning: </font>this will delete all files "
                          "on the selected partition." )
                          .arg( *Calamares::Branding::VersionedName ) );
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
        const QStringList osproberLines = Calamares::JobQueue::instance()
                                    ->globalStorage()
                                    ->value( "osproberLines" ).toStringList();

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
                          .arg( *Calamares::Branding::VersionedName ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->roles().has( PartitionRole::Extended ) )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "%1 cannot be installed on an extended partition. Please select an "
                              "existing primary or logical partition." )
                          .arg( *Calamares::Branding::VersionedName ) );
            setNextEnabled( false );
            return;
        }

        if ( partition->partitionPath().isEmpty() )
        {
            updateStatus( CalamaresUtils::Fail,
                          tr( "%1 cannot be installed on this partition." )
                          .arg( *Calamares::Branding::VersionedName ) );
            setNextEnabled( false );
            return;
        }

        QString prettyName = tr( "Data partition (%1)" )
                             .arg( partition->fileSystem().name() );
        for ( const QString& line : osproberLines )
        {
            QStringList lineColumns = line.split( ':' );

            QString path = lineColumns.value( 0 ).simplified();
            if ( path == partition->partitionPath() )
            {
                QString osName;
                if ( !lineColumns.value( 1 ).simplified().isEmpty() )
                    osName = lineColumns.value( 1 ).simplified();
                else if ( !lineColumns.value( 2 ).simplified().isEmpty() )
                    osName = lineColumns.value( 2 ).simplified();

                if ( osName.isEmpty() )
                {
                    prettyName = tr( "Unknown system partition (%1)" )
                                 .arg( partition->fileSystem().name() );
                }
                else
                {
                    prettyName = tr ( "%1 system partition (%2)" )
                                 .arg( osName.replace( 0, 1, osName.at( 0 ).toUpper() ) )
                                 .arg( partition->fileSystem().name() );
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
                          .arg( *Calamares::Branding::VersionedName )
                          .arg( requiredSpaceB / ( 1024. * 1024. * 1024. ),
                                0, 'f', 1 )
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
                              .arg( *Calamares::Branding::ShortProductName )
                              .arg( prettyName ) );
                setNextEnabled( false );
            }
            else if ( efiSystemPartitions.count() == 1 )
            {
                updateStatus( CalamaresUtils::PartitionPartition,
                              tr( "<strong>%3</strong><br/><br/>"
                                  "%1 will be installed on %2.<br/>"
                                  "<font color=\"red\">Warning: </font>all data on partition "
                                  "%2 will be lost.")
                                .arg( *Calamares::Branding::VersionedName )
                                .arg( partition->partitionPath() )
                                .arg( prettyName ) );
                m_ui->bootStatusLabel->show();
                m_ui->bootStatusLabel->setText(
                    tr( "The EFI system partition at %1 will be used for starting %2." )
                        .arg( efiSystemPartitions.first()->partitionPath() )
                        .arg( *Calamares::Branding::ShortProductName ) );
                setNextEnabled( true );
            }
            else
            {
                updateStatus( CalamaresUtils::PartitionPartition,
                              tr( "<strong>%3</strong><br/><br/>"
                                  "%1 will be installed on %2.<br/>"
                                  "<font color=\"red\">Warning: </font>all data on partition "
                                  "%2 will be lost.")
                                .arg( *Calamares::Branding::VersionedName )
                                .arg( partition->partitionPath() )
                                .arg( prettyName ) );
                m_ui->bootStatusLabel->show();
                m_ui->bootStatusLabel->setText( tr( "EFI system partition:" ) );
                m_ui->bootComboBox->show();
                for ( int i = 0; i < efiSystemPartitions.count(); ++i )
                {
                    Partition* efiPartition = efiSystemPartitions.at( i );
                    m_ui->bootComboBox->addItem( efiPartition->partitionPath(), i );
                    if ( efiPartition->devicePath() == partition->devicePath() &&
                         efiPartition->number() == 1 )
                        m_ui->bootComboBox->setCurrentIndex( i );
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
                              "%2 will be lost.")
                            .arg( *Calamares::Branding::VersionedName )
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
        return;

    m_nextEnabled = enabled;
    emit nextStatusChanged( enabled );
}


void
ReplaceWidget::updateStatus( CalamaresUtils::ImageType imageType, const QString& text )
{
    int iconSize = CalamaresUtils::defaultFontHeight() * 6;
    m_ui->selectedIconLabel->setPixmap( CalamaresUtils::defaultPixmap( imageType,
                                                                       CalamaresUtils::Original,
                                                                       QSize( iconSize, iconSize ) ) );
    m_ui->selectedIconLabel->setFixedHeight( iconSize );
    m_ui->selectedStatusLabel->setText( text );
}



void
ReplaceWidget::updateFromCurrentDevice( QComboBox* devicesComboBox )
{
    QModelIndex index = m_core->deviceModel()->index( devicesComboBox->currentIndex(), 0 );
    if ( !index.isValid() )
        return;

    Device* device = m_core->deviceModel()->deviceForIndex( index );

    QAbstractItemModel* oldModel = m_ui->partitionTreeView->model();
    if ( oldModel )
        disconnect( oldModel, nullptr, this, nullptr );

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
    connect( m_ui->partitionTreeView->selectionModel(), &QItemSelectionModel::currentRowChanged,
             this, &ReplaceWidget::onPartitionViewActivated );

    connect( model, &QAbstractItemModel::modelReset, this, &ReplaceWidget::onPartitionModelReset );
}


void
ReplaceWidget::onPartitionViewActivated()
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
ReplaceWidget::onPartitionModelReset()
{
    m_ui->partitionTreeView->expandAll();
    onPartitionSelected();
}
