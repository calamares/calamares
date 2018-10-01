/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2018, Andrius Štikonas <andrius@stikonas.eu>
 *   Copyright 2018, Caio Carvalho <caiojcarvalho@gmail.com>
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

#include "gui/CreatePartitionDialog.h"

#include "core/ColorUtils.h"
#include "core/PartitionInfo.h"
#include "core/PartUtils.h"
#include "core/KPMHelpers.h"
#include "gui/PartitionDialogHelpers.h"
#include "gui/PartitionSizeController.h"

#include "ui_CreatePartitionDialog.h"

#include "utils/Logger.h"
#include "GlobalStorage.h"
#include "JobQueue.h"

// KPMcore
#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/fs/filesystemfactory.h>
#include <kpmcore/fs/luks.h>

// Qt
#include <QComboBox>
#include <QDir>
#include <QListWidgetItem>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSet>

static QSet< FileSystem::Type > s_unmountableFS(
{
    FileSystem::Unformatted,
    FileSystem::LinuxSwap,
    FileSystem::Extended,
    FileSystem::Unknown,
    FileSystem::Lvm2_PV
} );

CreatePartitionDialog::CreatePartitionDialog( Device* device, PartitionNode* parentPartition, Partition* partition, const QStringList& usedMountPoints, QWidget* parentWidget )
    : QDialog( parentWidget )
    , m_ui( new Ui_CreatePartitionDialog )
    , m_partitionSizeController( new PartitionSizeController( this ) )
    , m_device( device )
    , m_parent( parentPartition )
    , m_usedMountPoints( usedMountPoints )
{
    m_ui->setupUi( this );
    m_ui->encryptWidget->setText( tr( "En&crypt" ) );
    m_ui->encryptWidget->hide();

    if (m_device->type() != Device::Type::LVM_Device) {
        m_ui->lvNameLabel->hide();
        m_ui->lvNameLineEdit->hide();
    }
    if (m_device->type() == Device::Type::LVM_Device) {
        /* LVM logical volume name can consist of: letters numbers _ . - +
         * It cannot start with underscore _ and must not be equal to . or .. or any entry in /dev/
         * QLineEdit accepts QValidator::Intermediate, so we just disable . at the beginning */
        QRegularExpression re(QStringLiteral(R"(^(?!_|\.)[\w\-.+]+)"));
        QRegularExpressionValidator *validator = new QRegularExpressionValidator(re, this);
        m_ui->lvNameLineEdit->setValidator(validator);
    }

    standardMountPoints( *(m_ui->mountPointComboBox), partition ? PartitionInfo::mountPoint( partition ) : QString() );

    if ( device->partitionTable()->type() == PartitionTable::msdos ||
         device->partitionTable()->type() == PartitionTable::msdos_sectorbased )
        initMbrPartitionTypeUi();
    else
        initGptPartitionTypeUi();

    // File system
    FileSystem::Type defaultFsType = FileSystem::typeForName(
                                         Calamares::JobQueue::instance()->
                                         globalStorage()->
                                         value( "defaultFileSystemType" ).toString() );
    int defaultFsIndex = -1;
    int fsCounter = 0;
    QStringList fsNames;
    for ( auto fs : FileSystemFactory::map() )
    {
        if ( fs->supportCreate() != FileSystem::cmdSupportNone &&
             fs->type() != FileSystem::Extended )
        {
            fsNames << fs->name();
            if ( fs->type() == defaultFsType )
                defaultFsIndex = fsCounter;
            fsCounter++;
        }
    }
    m_ui->fsComboBox->addItems( fsNames );

    // Connections
    connect( m_ui->fsComboBox, SIGNAL( activated( int ) ), SLOT( updateMountPointUi() ) );
    connect( m_ui->extendedRadioButton, SIGNAL( toggled( bool ) ), SLOT( updateMountPointUi() ) );

    connect( m_ui->mountPointComboBox, &QComboBox::currentTextChanged, this, &CreatePartitionDialog::checkMountPointSelection );

    // Select a default
    m_ui->fsComboBox->setCurrentIndex( defaultFsIndex );
    updateMountPointUi();

    setFlagList( *(m_ui->m_listFlags), static_cast< PartitionTable::Flags >( ~PartitionTable::Flags::Int(0) ), partition ? PartitionInfo::flags( partition ) : PartitionTable::Flags() );

    // Checks the initial selection.
    checkMountPointSelection();
}

CreatePartitionDialog::~CreatePartitionDialog()
{}


PartitionTable::Flags
CreatePartitionDialog::newFlags() const
{
    return flagsFromList( *(m_ui->m_listFlags) );
}

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

    qint64 first = m_partitionSizeController->firstSector();
    qint64 last = m_partitionSizeController->lastSector();

    FileSystem::Type fsType = m_role.has( PartitionRole::Extended )
                              ? FileSystem::Extended
                              : FileSystem::typeForName( m_ui->fsComboBox->currentText() );

    Partition* partition = nullptr;
    QString luksPassphrase = m_ui->encryptWidget->passphrase();
    if ( m_ui->encryptWidget->state() == EncryptWidget::EncryptionConfirmed &&
         !luksPassphrase.isEmpty() )
    {
        partition = KPMHelpers::createNewEncryptedPartition(
            m_parent,
            *m_device,
            m_role,
            fsType, first, last, luksPassphrase, newFlags()
        );
    }
    else
    {
        partition = KPMHelpers::createNewPartition(
            m_parent,
            *m_device,
            m_role,
            fsType, first, last, newFlags()
        );
    }

    if (m_device->type() == Device::Type::LVM_Device) {
        partition->setPartitionPath(m_device->deviceNode() + QStringLiteral("/") + m_ui->lvNameLineEdit->text().trimmed());
    }

    PartitionInfo::setMountPoint( partition, selectedMountPoint( m_ui->mountPointComboBox ) );
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

        if ( FileSystemFactory::map()[FileSystem::Type::Luks]->supportCreate() &&
             FS::luks::canEncryptType( type ) &&
             !m_role.has( PartitionRole::Extended ) )
        {
            m_ui->encryptWidget->show();
            m_ui->encryptWidget->reset();
        }
        else
        {
            m_ui->encryptWidget->reset();
            m_ui->encryptWidget->hide();
        }
    }
    m_ui->mountPointLabel->setEnabled( enabled );
    m_ui->mountPointComboBox->setEnabled( enabled );
    if ( !enabled )
        m_ui->mountPointComboBox->setCurrentText( QString() );
}

void
CreatePartitionDialog::checkMountPointSelection()
{
    if ( m_usedMountPoints.contains( selectedMountPoint( m_ui->mountPointComboBox ) ) )
    {
        m_ui->labelMountPoint->setText( tr( "Mountpoint already in use. Please select another one." ) );
        m_ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( false );
    }
    else
    {
        m_ui->labelMountPoint->setText( QString() );
        m_ui->buttonBox->button( QDialogButtonBox::Ok )->setEnabled( true );
    }
}

void
CreatePartitionDialog::initPartResizerWidget( Partition* partition )
{
    QColor color = KPMHelpers::isPartitionFreeSpace( partition )
                   ? ColorUtils::colorForPartitionInFreeSpace( partition )
                   : ColorUtils::colorForPartition( partition );
    m_partitionSizeController->init( m_device, partition, color );
    m_partitionSizeController->setPartResizerWidget( m_ui->partResizerWidget );
    m_partitionSizeController->setSpinBox( m_ui->sizeSpinBox );
}

void
CreatePartitionDialog::initFromFreeSpace( Partition* freeSpacePartition )
{
    initPartResizerWidget( freeSpacePartition );
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

    initPartResizerWidget( partition );

    // File System
    FileSystem::Type fsType = partition->fileSystem().type();
    m_ui->fsComboBox->setCurrentText( FileSystem::nameForType( fsType ) );

    // Mount point
    setSelectedMountPoint( m_ui->mountPointComboBox, PartitionInfo::mountPoint( partition ) );

    updateMountPointUi();
}
