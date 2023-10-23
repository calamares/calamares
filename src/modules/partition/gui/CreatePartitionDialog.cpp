/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2018 Andrius Štikonas <andrius@stikonas.eu>
 *   SPDX-FileCopyrightText: 2018 Caio Carvalho <caiojcarvalho@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "CreatePartitionDialog.h"
#include "ui_CreatePartitionDialog.h"

#include "core/ColorUtils.h"
#include "core/KPMHelpers.h"
#include "core/PartUtils.h"
#include "core/PartitionInfo.h"
#include "gui/PartitionDialogHelpers.h"
#include "gui/PartitionSizeController.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "partition/FileSystem.h"
#include "partition/PartitionQuery.h"
#include "utils/Logger.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>
#include <kpmcore/fs/filesystemfactory.h>
#include <kpmcore/fs/luks.h>
#include <kpmcore/fs/luks2.h>

#include <QComboBox>
#include <QDir>
#include <QListWidgetItem>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSet>

using Calamares::Partition::untranslatedFS;
using Calamares::Partition::userVisibleFS;

static QSet< FileSystem::Type > s_unmountableFS( { FileSystem::Unformatted,
                                                   FileSystem::LinuxSwap,
                                                   FileSystem::Extended,
                                                   FileSystem::Unknown,
                                                   FileSystem::Lvm2_PV } );

CreatePartitionDialog::CreatePartitionDialog( Device* device,
                                              PartitionNode* parentPartition,
                                              const QStringList& usedMountPoints,
                                              QWidget* parentWidget )
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

    if ( m_device->type() != Device::Type::LVM_Device )
    {
        m_ui->lvNameLabel->hide();
        m_ui->lvNameLineEdit->hide();
    }
    if ( m_device->type() == Device::Type::LVM_Device )
    {
        /* LVM logical volume name can consist of: letters numbers _ . - +
         * It cannot start with underscore _ and must not be equal to . or .. or any entry in /dev/
         * QLineEdit accepts QValidator::Intermediate, so we just disable . at the beginning */
        QRegularExpression re( QStringLiteral( R"(^(?!_|\.)[\w\-.+]+)" ) );
        QRegularExpressionValidator* validator = new QRegularExpressionValidator( re, this );
        m_ui->lvNameLineEdit->setValidator( validator );
    }

    if ( device->partitionTable()->type() == PartitionTable::msdos
         || device->partitionTable()->type() == PartitionTable::msdos_sectorbased )
    {
        initMbrPartitionTypeUi();
    }
    else
    {
        initGptPartitionTypeUi();
    }

    // File system; the config value is translated (best-effort) to a type
    FileSystem::Type defaultFSType;
    QString untranslatedFSName = PartUtils::canonicalFilesystemName(
        Calamares::JobQueue::instance()->globalStorage()->value( "defaultFileSystemType" ).toString(), &defaultFSType );
    if ( defaultFSType == FileSystem::Type::Unknown )
    {
        defaultFSType = FileSystem::Type::Ext4;
    }

    int defaultFsIndex = -1;
    int fsCounter = 0;
    QStringList fsNames;
    for ( auto fs : FileSystemFactory::map() )
    {
        // We need to ensure zfs is added to the list if the zfs module is enabled
        if ( ( fs->type() == FileSystem::Type::Zfs && Calamares::Settings::instance()->isModuleEnabled( "zfs" ) )
             || ( fs->supportCreate() != FileSystem::cmdSupportNone && fs->type() != FileSystem::Extended ) )
        {
            fsNames << userVisibleFS( fs );  // This is put into the combobox
            if ( fs->type() == defaultFSType )
            {
                defaultFsIndex = fsCounter;
            }
            fsCounter++;
        }
    }
    m_ui->fsComboBox->addItems( fsNames );

    // Connections
    connect( m_ui->fsComboBox, SIGNAL( activated( int ) ), SLOT( updateMountPointUi() ) );
    connect( m_ui->extendedRadioButton, SIGNAL( toggled( bool ) ), SLOT( updateMountPointUi() ) );

    connect( m_ui->mountPointComboBox,
             &QComboBox::currentTextChanged,
             this,
             &CreatePartitionDialog::checkMountPointSelection );

    // Select a default
    m_ui->fsComboBox->setCurrentIndex( defaultFsIndex );
    updateMountPointUi();
    checkMountPointSelection();
}

CreatePartitionDialog::CreatePartitionDialog( Device* device,
                                              const FreeSpace& freeSpacePartition,
                                              const QStringList& usedMountPoints,
                                              QWidget* parentWidget )
    : CreatePartitionDialog( device, freeSpacePartition.p->parent(), usedMountPoints, parentWidget )
{
    standardMountPoints( *( m_ui->mountPointComboBox ), QString() );
    setFlagList( *( m_ui->m_listFlags ),
                 static_cast< PartitionTable::Flags >( ~PartitionTable::Flags::Int( 0 ) ),
                 PartitionTable::Flags() );
    initPartResizerWidget( freeSpacePartition.p );
}

CreatePartitionDialog::CreatePartitionDialog( Device* device,
                                              const FreshPartition& existingNewPartition,
                                              const QStringList& usedMountPoints,
                                              QWidget* parentWidget )
    : CreatePartitionDialog( device, existingNewPartition.p->parent(), usedMountPoints, parentWidget )
{
    standardMountPoints( *( m_ui->mountPointComboBox ), PartitionInfo::mountPoint( existingNewPartition.p ) );
    setFlagList( *( m_ui->m_listFlags ),
                 static_cast< PartitionTable::Flags >( ~PartitionTable::Flags::Int( 0 ) ),
                 PartitionInfo::flags( existingNewPartition.p ) );

    const bool isExtended = existingNewPartition.p->roles().has( PartitionRole::Extended );
    if ( isExtended )
    {
        cDebug() << "Editing extended partitions is not supported.";
        return;
    }

    initPartResizerWidget( existingNewPartition.p );

    FileSystem::Type fsType = existingNewPartition.p->fileSystem().type();
    m_ui->fsComboBox->setCurrentText( FileSystem::nameForType( fsType ) );

    setSelectedMountPoint( m_ui->mountPointComboBox, PartitionInfo::mountPoint( existingNewPartition.p ) );
    updateMountPointUi();
}

CreatePartitionDialog::~CreatePartitionDialog() {}


PartitionTable::Flags
CreatePartitionDialog::newFlags() const
{
    return flagsFromList( *( m_ui->m_listFlags ) );
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
    {
        m_ui->fixedPartitionLabel->hide();
    }
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
CreatePartitionDialog::getNewlyCreatedPartition()
{
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

    if ( m_role.roles() == PartitionRole::None )
    {
        m_role = PartitionRole( m_ui->extendedRadioButton->isChecked() ? PartitionRole::Extended
                                                                       : PartitionRole::Primary );
    }

    qint64 first = m_partitionSizeController->firstSector();
    qint64 last = m_partitionSizeController->lastSector();

    FileSystem::Type fsType = m_role.has( PartitionRole::Extended )
        ? FileSystem::Extended
        : FileSystem::typeForName( m_ui->fsComboBox->currentText() );
    const QString fsLabel = m_ui->filesystemLabelEdit->text();

    // The newly-created partitions have no flags set (no **active** flags),
    // because they're new. The desired flags can be retrieved from
    // newFlags() and the consumer (see PartitionPage::onCreateClicked)
    // does so, to set up the partition for create-and-then-set-flags.
    Partition* partition = nullptr;
    QString luksFsType = gs->value( "luksFileSystemType" ).toString();
    QString luksPassphrase = m_ui->encryptWidget->passphrase();
    if ( m_ui->encryptWidget->state() == EncryptWidget::Encryption::Confirmed && !luksPassphrase.isEmpty()
         && fsType != FileSystem::Zfs )
    {
        partition = KPMHelpers::createNewEncryptedPartition(
            m_parent,
            *m_device,
            m_role,
            fsType,
            fsLabel,
            first,
            last,
            Config::luksGenerationNames().find( luksFsType, Config::LuksGeneration::Luks1 ),
            luksPassphrase,
            PartitionTable::Flags() );
    }
    else
    {
        partition = KPMHelpers::createNewPartition(
            m_parent, *m_device, m_role, fsType, fsLabel, first, last, PartitionTable::Flags() );
    }

    // For zfs, we let the zfs module handle the encryption but we need to make the passphrase available to later modules
    if ( fsType == FileSystem::Zfs )
    {
        Calamares::GlobalStorage* storage = Calamares::JobQueue::instance()->globalStorage();
        QList< QVariant > zfsInfoList;
        QVariantMap zfsInfo;

        // If this is not the first encrypted zfs partition, get the old list first
        if ( storage->contains( "zfsInfo" ) )
        {
            zfsInfoList = storage->value( "zfsInfo" ).toList();
            storage->remove( "zfsInfo" );
        }

        // Save the information subsequent modules will need
        zfsInfo[ "encrypted" ]
            = m_ui->encryptWidget->state() == EncryptWidget::Encryption::Confirmed && !luksPassphrase.isEmpty();
        zfsInfo[ "passphrase" ] = luksPassphrase;
        zfsInfo[ "mountpoint" ] = selectedMountPoint( m_ui->mountPointComboBox );

        // Add it to the list and insert it into global storage
        zfsInfoList.append( zfsInfo );
        storage->insert( "zfsInfo", zfsInfoList );
    }

    if ( m_device->type() == Device::Type::LVM_Device )
    {
        partition->setPartitionPath( m_device->deviceNode() + QStringLiteral( "/" )
                                     + m_ui->lvNameLineEdit->text().trimmed() );
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
        // This maps translated (user-visible) FS names to a type
        FileSystem::Type type = FileSystem::typeForName( m_ui->fsComboBox->currentText() );
        enabled = !s_unmountableFS.contains( type );

        if ( FileSystemFactory::map()[ FileSystem::Type::Luks ]->supportCreate() && FS::luks::canEncryptType( type )
             && !m_role.has( PartitionRole::Extended ) )
        {
            m_ui->encryptWidget->show();
            m_ui->encryptWidget->reset();
        }
        else if ( FileSystemFactory::map()[ FileSystem::Type::Luks2 ]->supportCreate()
                  && FS::luks2::canEncryptType( type ) && !m_role.has( PartitionRole::Extended ) )
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
    {
        m_ui->mountPointComboBox->setCurrentText( QString() );
    }
}

void
CreatePartitionDialog::checkMountPointSelection()
{
    validateMountPoint( selectedMountPoint( m_ui->mountPointComboBox ),
                        m_usedMountPoints,
                        m_ui->mountPointExplanation,
                        m_ui->buttonBox->button( QDialogButtonBox::Ok ) );
}

void
CreatePartitionDialog::initPartResizerWidget( Partition* partition )
{
    QColor color = Calamares::Partition::isPartitionFreeSpace( partition )
        ? ColorUtils::colorForPartitionInFreeSpace( partition )
        : ColorUtils::colorForPartition( partition );
    m_partitionSizeController->init( m_device, partition, color );
    m_partitionSizeController->setPartResizerWidget( m_ui->partResizerWidget );
    m_partitionSizeController->setSpinBox( m_ui->sizeSpinBox );
}
