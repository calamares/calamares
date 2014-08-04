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

#include <CreatePartitionDialog.h>

#include <PartitionInfo.h>
#include <PMUtils.h>
#include <ui_CreatePartitionDialog.h>
#include <utils/Logger.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <fs/filesystem.h>
#include <fs/filesystemfactory.h>

// Qt
#include <QComboBox>
#include <QSet>

static QSet< FileSystem::Type > s_unmountableFS(
{
    FileSystem::Unformatted,
    FileSystem::LinuxSwap
} );

CreatePartitionDialog::CreatePartitionDialog( Device* device, PartitionNode* parentPartition, QWidget* parentWidget )
    : QDialog( parentWidget )
    , m_ui( new Ui_CreatePartitionDialog )
    , m_device( device )
    , m_parent( parentPartition )
{
    m_ui->setupUi( this );

    FileSystemFactory::init();

    if ( device->partitionTable()->type() == PartitionTable::msdos )
        initMbrPartitionTypeUi();
    else
        initGptPartitionTypeUi();

    // File system
    QStringList fsNames;
    for ( auto fs : FileSystemFactory::map() )
    {
        if ( fs->supportCreate() != FileSystem::cmdSupportNone && fs->type() != FileSystem::Extended )
            fsNames << fs->name();
    }
    m_ui->fsComboBox->addItems( fsNames );

    // Connections
    connect( m_ui->fsComboBox, SIGNAL( activated( int ) ), SLOT( updateMountPointUi() ) );
    connect( m_ui->extendedRadioButton, SIGNAL( toggled( bool ) ), SLOT( updateMountPointUi() ) );
}

CreatePartitionDialog::~CreatePartitionDialog()
{}

void
CreatePartitionDialog::initMbrPartitionTypeUi()
{
    QString fixedPartitionString;
    bool parentIsPartitionTable = m_parent->isRoot();
    if ( !parentIsPartitionTable )
    {
        m_role = PartitionRole( PartitionRole::Logical );
        fixedPartitionString = tr( "Logical" );
    }
    else if ( m_device->partitionTable()->hasExtended() )
    {
        m_role = PartitionRole( PartitionRole::Primary );
        fixedPartitionString = tr( "Primary" );
    }

    if ( fixedPartitionString.isEmpty() )
        m_ui->fixedPartitionLabel->hide();
    else
    {
        m_ui->fixedPartitionLabel->setText( fixedPartitionString );
        m_ui->primaryRadioButton->hide();
        m_ui->extendedRadioButton->hide();
    }
}

void
CreatePartitionDialog::initGptPartitionTypeUi()
{
    m_role = PartitionRole( PartitionRole::Primary );
    m_ui->fixedPartitionLabel->setText( tr( "GPT" ) );
    m_ui->primaryRadioButton->hide();
    m_ui->extendedRadioButton->hide();
}

Partition*
CreatePartitionDialog::createPartition()
{
    if ( m_role.roles() == PartitionRole::None )
    {
        m_role = PartitionRole(
                     m_ui->extendedRadioButton->isChecked()
                     ? PartitionRole::Extended
                     : PartitionRole::Primary
                 );
    }

    PartitionSizeWidget::SectorRange range = m_ui->sizeSpinBox->sectorRange();

    FileSystem::Type fsType = m_role.has( PartitionRole::Extended )
                              ? FileSystem::Extended
                              : FileSystem::typeForName( m_ui->fsComboBox->currentText() );
    Partition* partition = PMUtils::createNewPartition(
        m_parent,
        *m_device,
        m_role,
        fsType, range.first, range.second );

    PartitionInfo::setMountPoint( partition, m_ui->mountPointComboBox->currentText() );
    PartitionInfo::setFormat( partition, true );
    return partition;
}

void
CreatePartitionDialog::updateMountPointUi()
{
    bool enabled = m_ui->primaryRadioButton->isChecked();
    if ( enabled )
    {
        FileSystem::Type type = FileSystem::typeForName( m_ui->fsComboBox->currentText() );
        enabled = !s_unmountableFS.contains( type );
    }
    m_ui->mountPointLabel->setEnabled( enabled );
    m_ui->mountPointComboBox->setEnabled( enabled );
}

void
CreatePartitionDialog::initFromFreeSpace( Partition* freeSpacePartition )
{
    m_ui->sizeSpinBox->init( m_device, freeSpacePartition );
}

void
CreatePartitionDialog::initFromPartitionToCreate( Partition* partition )
{
    Q_ASSERT( partition );

    bool isExtended = partition->roles().has( PartitionRole::Extended );
    Q_ASSERT( !isExtended );
    if ( isExtended )
    {
        cDebug() << "Editing extended partitions is not supported for now";
        return;
    }

    m_ui->sizeSpinBox->init( m_device, partition );

    // File System
    FileSystem::Type fsType = partition->fileSystem().type();
    m_ui->fsComboBox->setCurrentText( FileSystem::nameForType( fsType ) );

    // Mount point
    m_ui->mountPointComboBox->setCurrentText( PartitionInfo::mountPoint( partition ) );

    updateMountPointUi();
}
