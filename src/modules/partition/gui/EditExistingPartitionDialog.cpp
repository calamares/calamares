/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2008-2009 Volker Lanz <vl@fidra.de>
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2016 Andrius Štikonas <andrius@stikonas.eu>
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Flags handling originally from KDE Partition Manager.
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "EditExistingPartitionDialog.h"
#include "ui_EditExistingPartitionDialog.h"

#include "core/ColorUtils.h"
#include "core/KPMHelpers.h"
#include "core/PartUtils.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionInfo.h"
#include "gui/PartitionDialogHelpers.h"
#include "gui/PartitionSizeController.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Settings.h"
#include "partition/FileSystem.h"
#include "utils/Logger.h"
#include "widgets/TranslationFix.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystemfactory.h>
#include <kpmcore/fs/luks.h>

#include <QComboBox>
#include <QDir>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>

using CalamaresUtils::Partition::untranslatedFS;
using CalamaresUtils::Partition::userVisibleFS;

EditExistingPartitionDialog::EditExistingPartitionDialog( Device* device,
                                                          Partition* partition,
                                                          const QStringList& usedMountPoints,
                                                          QWidget* parentWidget )
    : QDialog( parentWidget )
    , m_ui( new Ui_EditExistingPartitionDialog )
    , m_device( device )
    , m_partition( partition )
    , m_partitionSizeController( new PartitionSizeController( this ) )
    , m_usedMountPoints( usedMountPoints )
{
    m_ui->setupUi( this );
    m_ui->encryptWidget->hide();
    standardMountPoints( *( m_ui->mountPointComboBox ), PartitionInfo::mountPoint( partition ) );

    QColor color = ColorUtils::colorForPartition( m_partition );
    m_partitionSizeController->init( m_device, m_partition, color );
    m_partitionSizeController->setSpinBox( m_ui->sizeSpinBox );

    connect( m_ui->mountPointComboBox,
             &QComboBox::currentTextChanged,
             this,
             &EditExistingPartitionDialog::checkMountPointSelection );

    // The filesystem label dialog is always enabled, because we may want to change
    // the label on the current filesystem without formatting.
    m_ui->fileSystemLabelEdit->setText( m_partition->fileSystem().label() );

    replacePartResizerWidget();

    connect( m_ui->formatRadioButton,
             &QAbstractButton::toggled,
             [ this ]( bool doFormat )
             {
                 replacePartResizerWidget();

                 m_ui->fileSystemLabel->setEnabled( doFormat );
                 m_ui->fileSystemComboBox->setEnabled( doFormat );

                 if ( !doFormat )
                 {
                     m_ui->fileSystemComboBox->setCurrentText( userVisibleFS( m_partition->fileSystem() ) );
                 }

                 updateMountPointPicker();
             } );

    connect(
        m_ui->fileSystemComboBox, &QComboBox::currentTextChanged, [ this ]( QString ) { updateMountPointPicker(); } );

    // File system
    QStringList fsNames;
    for ( auto fs : FileSystemFactory::map() )
    {
        // We need to ensure zfs is added to the list if the zfs module is enabled
        if ( ( fs->type() == FileSystem::Type::Zfs && Calamares::Settings::instance()->isModuleEnabled( "zfs" ) )
             || ( fs->supportCreate() != FileSystem::cmdSupportNone && fs->type() != FileSystem::Extended ) )
        {
            fsNames << userVisibleFS( fs );  // For the combo box
        }
    }
    m_ui->fileSystemComboBox->addItems( fsNames );

    FileSystem::Type defaultFSType;
    QString untranslatedFSName = PartUtils::canonicalFilesystemName(
        Calamares::JobQueue::instance()->globalStorage()->value( "defaultFileSystemType" ).toString(), &defaultFSType );
    if ( defaultFSType == FileSystem::Type::Unknown )
    {
        defaultFSType = FileSystem::Type::Ext4;
    }

    QString thisFSNameForUser = userVisibleFS( m_partition->fileSystem() );
    if ( fsNames.contains( thisFSNameForUser ) )
    {
        m_ui->fileSystemComboBox->setCurrentText( thisFSNameForUser );
    }
    else
    {
        m_ui->fileSystemComboBox->setCurrentText( FileSystem::nameForType( defaultFSType ) );
    }

    m_ui->fileSystemLabel->setEnabled( m_ui->formatRadioButton->isChecked() );
    m_ui->fileSystemComboBox->setEnabled( m_ui->formatRadioButton->isChecked() );

    // Force a format if the existing device is a zfs device since reusing a zpool isn't currently supported
    m_ui->formatRadioButton->setChecked( m_partition->fileSystem().type() == FileSystem::Type::Zfs );
    m_ui->formatRadioButton->setEnabled( !( m_partition->fileSystem().type() == FileSystem::Type::Zfs ) );
    m_ui->keepRadioButton->setChecked( !( m_partition->fileSystem().type() == FileSystem::Type::Zfs ) );
    m_ui->keepRadioButton->setEnabled( !( m_partition->fileSystem().type() == FileSystem::Type::Zfs ) );

    setFlagList( *( m_ui->m_listFlags ), m_partition->availableFlags(), PartitionInfo::flags( m_partition ) );
}

EditExistingPartitionDialog::~EditExistingPartitionDialog() {}

PartitionTable::Flags
EditExistingPartitionDialog::newFlags() const
{
    return flagsFromList( *( m_ui->m_listFlags ) );
}

void
EditExistingPartitionDialog::applyChanges( PartitionCoreModule* core )
{
    PartitionInfo::setMountPoint( m_partition, selectedMountPoint( m_ui->mountPointComboBox ) );

    qint64 newFirstSector = m_partitionSizeController->firstSector();
    qint64 newLastSector = m_partitionSizeController->lastSector();
    bool partResizedMoved = newFirstSector != m_partition->firstSector() || newLastSector != m_partition->lastSector();

    cDebug() << "old boundaries:" << m_partition->firstSector() << m_partition->lastSector() << m_partition->length();
    cDebug() << Logger::SubEntry << "new boundaries:" << newFirstSector << newLastSector;
    cDebug() << Logger::SubEntry << "dirty status:" << m_partitionSizeController->isDirty();

    FileSystem::Type fsType = FileSystem::Unknown;
    if ( m_ui->formatRadioButton->isChecked() )
    {
        fsType = m_partition->roles().has( PartitionRole::Extended )
            ? FileSystem::Extended
            : FileSystem::typeForName( m_ui->fileSystemComboBox->currentText() );
    }
    const QString fsLabel = m_ui->fileSystemLabelEdit->text();

    const auto resultFlags = newFlags();
    const auto currentFlags = PartitionInfo::flags( m_partition );

    if ( partResizedMoved )
    {
        if ( m_ui->formatRadioButton->isChecked() )
        {
            Partition* newPartition = KPMHelpers::createNewPartition( m_partition->parent(),
                                                                      *m_device,
                                                                      m_partition->roles(),
                                                                      fsType,
                                                                      fsLabel,
                                                                      newFirstSector,
                                                                      newLastSector,
                                                                      resultFlags );
            PartitionInfo::setMountPoint( newPartition, PartitionInfo::mountPoint( m_partition ) );
            PartitionInfo::setFormat( newPartition, true );

            core->deletePartition( m_device, m_partition );
            core->createPartition( m_device, newPartition );
            core->setPartitionFlags( m_device, newPartition, resultFlags );
        }
        else
        {
            core->resizePartition( m_device, m_partition, newFirstSector, newLastSector );
            if ( currentFlags != resultFlags )
            {
                core->setPartitionFlags( m_device, m_partition, resultFlags );
            }
        }
    }
    else
    {
        // No size changes
        if ( m_ui->formatRadioButton->isChecked() )
        {
            // if the FS type is unchanged, we just format
            if ( m_partition->fileSystem().type() == fsType )
            {
                core->formatPartition( m_device, m_partition );
                if ( currentFlags != resultFlags )
                {
                    core->setPartitionFlags( m_device, m_partition, resultFlags );
                }
                core->setFilesystemLabel( m_device, m_partition, fsLabel );
            }
            else  // otherwise, we delete and recreate the partition with new fs type
            {
                Partition* newPartition = KPMHelpers::createNewPartition( m_partition->parent(),
                                                                          *m_device,
                                                                          m_partition->roles(),
                                                                          fsType,
                                                                          fsLabel,
                                                                          m_partition->firstSector(),
                                                                          m_partition->lastSector(),
                                                                          resultFlags );
                PartitionInfo::setMountPoint( newPartition, PartitionInfo::mountPoint( m_partition ) );
                PartitionInfo::setFormat( newPartition, true );

                core->deletePartition( m_device, m_partition );
                core->createPartition( m_device, newPartition );
                core->setPartitionFlags( m_device, newPartition, resultFlags );
            }
        }
        else
        {
            if ( currentFlags != resultFlags )
            {
                core->setPartitionFlags( m_device, m_partition, resultFlags );
            }
            // In this case, we are not formatting the partition, but we are setting the
            // label on the current filesystem, if any. We only create the job if the
            // label actually changed.
            if ( m_partition->fileSystem().type() != FileSystem::Type::Unformatted
                 && fsLabel != m_partition->fileSystem().label() )
            {
                core->setFilesystemLabel( m_device, m_partition, fsLabel );
            }

            core->refreshPartition( m_device, m_partition );
        }

        // Update the existing luks partition
        const QString passphrase = m_ui->encryptWidget->passphrase();
        if ( !passphrase.isEmpty() )
        {
            if ( KPMHelpers::savePassphrase( m_partition, passphrase ) != KPMHelpers::SavePassphraseValue::NoError )
            {
                QString message = tr( "Passphrase for existing partition" );
                QString description = tr( "Partition %1 could not be decrypted "
                                          "with the given passphrase."
                                          "<br/><br/>"
                                          "Edit the partition again and give the correct passphrase "
                                          "or delete and create a new encrypted partition." )
                                          .arg( m_partition->partitionPath() );

                QMessageBox mb( QMessageBox::Information, message, description, QMessageBox::Ok, this->parentWidget() );
                Calamares::fixButtonLabels( &mb );
                mb.exec();
            }
        }
    }
}


void
EditExistingPartitionDialog::replacePartResizerWidget()
{
    /*
     * There is no way to reliably update the partition used by
     * PartResizerWidget, which is necessary when we switch between "format" and
     * "keep". This is a hack which replaces the existing PartResizerWidget
     * with a new one.
     */
    PartResizerWidget* widget = new PartResizerWidget( this );

    layout()->replaceWidget( m_ui->partResizerWidget, widget );
    delete m_ui->partResizerWidget;
    m_ui->partResizerWidget = widget;

    m_partitionSizeController->setPartResizerWidget( widget, m_ui->formatRadioButton->isChecked() );
}

void
EditExistingPartitionDialog::updateMountPointPicker()
{
    bool doFormat = m_ui->formatRadioButton->isChecked();
    FileSystem::Type fsType = FileSystem::Unknown;
    if ( doFormat )
    {
        fsType = FileSystem::typeForName( m_ui->fileSystemComboBox->currentText() );
    }
    else
    {
        fsType = m_partition->fileSystem().type();
    }
    bool canMount = true;
    if ( fsType == FileSystem::Extended || fsType == FileSystem::LinuxSwap || fsType == FileSystem::Unformatted
         || fsType == FileSystem::Unknown || fsType == FileSystem::Lvm2_PV )
    {
        canMount = false;
    }

    m_ui->mountPointLabel->setEnabled( canMount );
    m_ui->mountPointComboBox->setEnabled( canMount );
    if ( !canMount )
    {
        setSelectedMountPoint( m_ui->mountPointComboBox, QString() );
    }

    toggleEncryptWidget();
}

void
EditExistingPartitionDialog::checkMountPointSelection()
{
    if ( validateMountPoint( selectedMountPoint( m_ui->mountPointComboBox ),
                             m_usedMountPoints,
                             m_ui->mountPointExplanation,
                             m_ui->buttonBox->button( QDialogButtonBox::Ok ) ) )
    {
        toggleEncryptWidget();
    }
}

void
EditExistingPartitionDialog::toggleEncryptWidget()
{
    // Show/hide encryptWidget:
    // check if partition is a previously luks formatted partition
    // and not currently formatted
    // and its mount point not a standard mount point except when it's /home
    QString mp = selectedMountPoint( m_ui->mountPointComboBox );
    if ( !mp.isEmpty() && m_partition->fileSystem().type() == FileSystem::Luks && !m_ui->formatRadioButton->isChecked()
         && ( !standardMountPoints().contains( mp ) || mp == "/home" ) )
    {
        m_ui->encryptWidget->show();
        m_ui->encryptWidget->reset( false );
    }
    // TODO: When formatting a partition user must be able to encrypt that partition
    //       Probably need to delete this partition and create a new one
    // else if ( m_ui->formatRadioButton->isChecked()
    //           && !mp.isEmpty())
    // {
    //     m_ui->encryptWidget->show();
    //     m_ui->encryptWidget->reset();
    // }
    else
    {
        m_ui->encryptWidget->reset();
        m_ui->encryptWidget->hide();
    }
}
