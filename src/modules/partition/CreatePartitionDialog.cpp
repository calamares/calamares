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

#include <CreatePartitionJob.h>
#include <ui_CreatePartitionDialog.h>

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <fs/filesystem.h>
#include <fs/filesystemfactory.h>

CreatePartitionDialog::CreatePartitionDialog( Device* device, Partition* freePartition, QWidget* parent )
    : QDialog( parent )
    , m_ui( new Ui_CreatePartitionDialog )
    , m_device( device )
    , m_freePartition( freePartition )
{
    m_ui->setupUi( this );

    FileSystemFactory::init();

    bool hidePartitionType = false;
    if ( freePartition->roles().has( PartitionRole::Logical ) )
    {
        m_role = PartitionRole( PartitionRole::Logical );
        hidePartitionType = true;
    }
    else if ( m_device->partitionTable()->hasExtended() )
    {
        m_role = PartitionRole( PartitionRole::Primary );
        hidePartitionType = true;
    }

    if ( hidePartitionType )
    {
        m_ui->partitionTypeLabel->hide();
        m_ui->primaryRadioButton->hide();
        m_ui->extendedRadioButton->hide();
    }

    QStringList fsNames;
    for ( auto fs : FileSystemFactory::map() )
    {
        if ( fs->supportCreate() != FileSystem::cmdSupportNone && fs->type() != FileSystem::Extended )
        {
            fsNames << fs->name();
        }
    }
    m_ui->fsComboBox->addItems( fsNames );

    qint64 maxSize = ( freePartition->lastSector() - freePartition->firstSector() + 1 ) * device->logicalSectorSize();

    m_ui->sizeSpinBox->setMaximum( maxSize / 1024 / 1024 );
    m_ui->sizeSpinBox->setValue( m_ui->sizeSpinBox->maximum() );
}

CreatePartitionDialog::~CreatePartitionDialog()
{}

CreatePartitionJob*
CreatePartitionDialog::createJob()
{
    if ( m_role.roles() == PartitionRole::None )
    {
        m_role = PartitionRole(
                     m_ui->extendedRadioButton->isChecked()
                     ? PartitionRole::Extended
                     : PartitionRole::Primary
                 );
    }

    qint64 first = m_freePartition->firstSector();
    // FIXME: Check rounding errors here
    qint64 last = first + qint64( m_ui->sizeSpinBox->value() ) * 1024 * 1024 / m_device->logicalSectorSize();

    FileSystem::Type type = m_role.has( PartitionRole::Extended )
                            ? FileSystem::Extended
                            : FileSystem::typeForName( m_ui->fsComboBox->currentText() );
    FileSystem* fs = FileSystemFactory::create( type, first, last );

    PartitionNode* parent = m_freePartition->parent();
    Partition* partition = new Partition(
        parent,
        *m_device,
        m_role,
        fs, first, last,
        QString() /* path */,
        PartitionTable::FlagNone /* availableFlags */,
        QString() /* mountPoint */,
        false /* mounted */,
        PartitionTable::FlagNone /* activeFlags */,
        Partition::StateNew
    );
    return new CreatePartitionJob( m_device, partition );
}
