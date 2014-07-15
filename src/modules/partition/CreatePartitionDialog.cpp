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

// CalaPM
#include <core/device.h>
#include <core/partition.h>
#include <fs/filesystem.h>
#include <fs/filesystemfactory.h>

// Qt
#include <QComboBox>
#include <QSet>

CreatePartitionDialog::CreatePartitionDialog( Device* device, Partition* freePartition, QWidget* parent )
    : QDialog( parent )
    , m_ui( new Ui_CreatePartitionDialog )
    , m_device( device )
    , m_freePartition( freePartition )
{
    m_ui->setupUi( this );

    FileSystemFactory::init();

    // Partition types
    QString fixedPartitionType;
    if ( freePartition->roles().has( PartitionRole::Logical ) )
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

    // Size
    qint64 maxSize = ( freePartition->lastSector() - freePartition->firstSector() + 1 ) * device->logicalSectorSize();

    m_ui->sizeSpinBox->setMaximum( maxSize / 1024 / 1024 );
    m_ui->sizeSpinBox->setValue( m_ui->sizeSpinBox->maximum() );

    // Connections
    connect( m_ui->fsComboBox, SIGNAL( activated( int ) ), SLOT( updateMountPointUi() ) );
    connect( m_ui->extendedRadioButton, SIGNAL( toggled( bool ) ), SLOT( updateMountPointUi() ) );
}

CreatePartitionDialog::~CreatePartitionDialog()
{}

PartitionInfo*
CreatePartitionDialog::createPartitionInfo()
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
    auto partition = new Partition(
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

    auto info = new PartitionInfo( partition );
    info->mountPoint = m_ui->mountPointComboBox->currentText();
    info->format = true;
    return info;
}

void
CreatePartitionDialog::updateMountPointUi()
{
    static QSet< FileSystem::Type > unmountableFS( { FileSystem::Unformatted, FileSystem::LinuxSwap } );

    bool enabled = m_ui->primaryRadioButton->isChecked();
    if ( enabled )
    {
        FileSystem::Type type = FileSystem::typeForName( m_ui->fsComboBox->currentText() );
        enabled = !unmountableFS.contains( type );
    }
    m_ui->mountPointLabel->setEnabled( enabled );
    m_ui->mountPointComboBox->setEnabled( enabled );
}
