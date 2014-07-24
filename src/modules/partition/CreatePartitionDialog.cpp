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
#include <QMessageBox>

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

    bool parentIsPartitionTable = parentPartition->isRoot();
    // Partition types
    QString fixedPartitionType;
    if ( !parentIsPartitionTable )
    {
        m_role = PartitionRole( PartitionRole::Logical );
        fixedPartitionType = tr( "Logical" );
    }
    else if ( m_device->partitionTable()->hasExtended() )
    {
        m_role = PartitionRole( PartitionRole::Primary );
        fixedPartitionType = tr( "Primary" );
    }

    if ( fixedPartitionType.isEmpty() )
        m_ui->fixedPartitionLabel->hide();
    else
    {
        m_ui->fixedPartitionLabel->setText( fixedPartitionType );
        m_ui->primaryRadioButton->hide();
        m_ui->extendedRadioButton->hide();
    }

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

    PartitionPage* parentPage = (PartitionPage*)parentWidget;
    // save the used mountpoints so that we can validate the dialog against them.
    m_used_mountpoints = parentPage->getUsedMountPoints();
    // If there are any used mountpoints, remove them from combo box so that the user
    // would not be able to re-select them.
    foreach (QString usedMountPoint, m_used_mountpoints)
    {
        m_ui->mountPointComboBox->removeItem(m_ui->mountPointComboBox->findText(usedMountPoint));
    }
}

CreatePartitionDialog::~CreatePartitionDialog()
{}

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

    qint64 lastSector;
    int mbSize = m_ui->sizeSpinBox->value();
    if ( mbSize == m_ui->sizeSpinBox->maximum() )
    {
        // If we are at the maximum value, select the last sector to avoid
        // potential rounding errors which could leave a few sectors at the end
        // unused
        lastSector = m_maxSector;
    }
    else
    {
        lastSector = m_minSector + qint64( mbSize ) * 1024 * 1024 / m_device->logicalSectorSize();
        Q_ASSERT( lastSector <= m_maxSector );
        if ( lastSector > m_maxSector )
        {
            cDebug() << "lastSector (" << lastSector << ") > m_maxSector (" << m_maxSector << "). This should not happen!";
            lastSector = m_maxSector;
        }
    }

    FileSystem::Type type = m_role.has( PartitionRole::Extended )
                            ? FileSystem::Extended
                            : FileSystem::typeForName( m_ui->fsComboBox->currentText() );
    FileSystem* fs = FileSystemFactory::create( type, m_minSector, lastSector );

    auto partition = new Partition(
        m_parent,
        *m_device,
        m_role,
        fs, m_minSector, lastSector,
        QString() /* path */,
        PartitionTable::FlagNone /* availableFlags */,
        QString() /* mountPoint */,
        false /* mounted */,
        PartitionTable::FlagNone /* activeFlags */,
        Partition::StateNew
    );

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
CreatePartitionDialog::initSectorRange( Partition* partition )
{
    PartitionTable* table = m_device->partitionTable();
    m_minSector = partition->firstSector() - table->freeSectorsBefore( *partition );
    m_maxSector = partition->lastSector() + table->freeSectorsAfter( *partition );

    m_ui->sizeSpinBox->setMaximum( mbSizeForSectorRange( m_minSector, m_maxSector ) );
    m_ui->sizeSpinBox->setValue( m_ui->sizeSpinBox->maximum() );
}

void
CreatePartitionDialog::initFromFreeSpace( Partition* freeSpacePartition )
{
    initSectorRange( freeSpacePartition );
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

    initSectorRange( partition );

    // Size
    m_ui->sizeSpinBox->setValue( mbSizeForSectorRange( partition->firstSector(), partition->lastSector() ) );

    // File System
    FileSystem::Type fsType = partition->fileSystem().type();
    m_ui->fsComboBox->setCurrentText( FileSystem::nameForType( fsType ) );

    // Mount point
    m_ui->mountPointComboBox->setCurrentText( PartitionInfo::mountPoint( partition ) );

    updateMountPointUi();
}

qint64
CreatePartitionDialog::mbSizeForSectorRange( qint64 first, qint64 last ) const
{
    return ( last - first + 1 ) * m_device->logicalSectorSize() / 1024 / 1024;
}

int
CreatePartitionDialog::exec()
{
    //override the exec method so that we're able to validate the dialog.
    while (true)
    {
        if (QDialog::exec() == QDialog::Rejected)
        {
            return QDialog::Rejected;
        }
        if (validate())
        {
            return QDialog::Accepted;
        }
    }
}

bool
CreatePartitionDialog::validate()
{
    // if the user specified an mountpoint which is already used,
    // reject the dialog and display an error message
    if (m_used_mountpoints.contains(m_ui->mountPointComboBox->currentText()))
    {
        QMessageBox::critical(this, "Error", "This mountpoint is already used");
        return false;
    }
    // if no errors were present, accept the dialog
    return true;
}
