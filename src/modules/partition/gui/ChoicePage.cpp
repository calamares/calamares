/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2019, Adriaan de Groot <groot@kde.org>
 *   Copyright 2019, Collabora Ltd
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

#include "ChoicePage.h"

#include "core/BootLoaderModel.h"
#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/OsproberEntry.h"
#include "core/PartUtils.h"
#include "core/PartitionActions.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionInfo.h"
#include "core/PartitionModel.h"

#include "BootInfoWidget.h"
#include "DeviceInfoWidget.h"
#include "PartitionBarsView.h"
#include "PartitionLabelsView.h"
#include "PartitionSplitterWidget.h"
#include "PrettyRadioButton.h"
#include "ReplaceWidget.h"
#include "ScanningDialog.h"

#include "GlobalStorage.h"
#include "JobQueue.h"
#include "partition/PartitionIterator.h"
#include "partition/PartitionQuery.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Units.h"

#include "Branding.h"
#include "utils/CalamaresUtilsGui.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#ifdef WITH_KPMCORE4API
#include <kpmcore/core/softwareraid.h>
#endif

#include <QBoxLayout>
#include <QButtonGroup>
#include <QComboBox>
#include <QDir>
#include <QLabel>
#include <QListView>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

using PartitionActions::Choices::SwapChoice;
using CalamaresUtils::Partition::PartitionIterator;
using CalamaresUtils::Partition::isPartitionFreeSpace;
using CalamaresUtils::Partition::findPartitionByPath;

/** @brief Given a set of swap choices, return a sensible value from it.
 *
 * "Sensible" here means: if there is one value, use it; otherwise, use
 * NoSwap if there are no choices, or if NoSwap is one of the choices, in the set.
 * If that's not possible, any value from the set.
 */
SwapChoice pickOne( const SwapChoiceSet& s )
{
    if ( s.count() == 0 )
        return SwapChoice::NoSwap;
    if ( s.count() == 1 )
        return *( s.begin() );
    if ( s.contains( SwapChoice::NoSwap ) )
        return SwapChoice::NoSwap;
    // Here, count > 1 but NoSwap is not a member.
    return *( s.begin() );
}

/**
 * @brief ChoicePage::ChoicePage is the default constructor. Called on startup as part of
 *      the module loading code path.
 * @param parent the QWidget parent.
 */
ChoicePage::ChoicePage( const SwapChoiceSet& swapChoices, QWidget* parent )
    : QWidget( parent )
    , m_nextEnabled( false )
    , m_core( nullptr )
    , m_choice( NoChoice )
    , m_isEfi( false )
    , m_grp( nullptr )
    , m_alongsideButton( nullptr )
    , m_eraseButton( nullptr )
    , m_replaceButton( nullptr )
    , m_somethingElseButton( nullptr )
    , m_eraseSwapChoiceComboBox( nullptr )
    , m_deviceInfoWidget( nullptr )
    , m_beforePartitionBarsView( nullptr )
    , m_beforePartitionLabelsView( nullptr )
    , m_bootloaderComboBox( nullptr )
    , m_lastSelectedDeviceIndex( -1 )
    , m_enableEncryptionWidget( true )
    , m_availableSwapChoices( swapChoices )
    , m_eraseSwapChoice( pickOne( swapChoices ) )
    , m_allowManualPartitioning( true )
{
    setupUi( this );

    auto gs = Calamares::JobQueue::instance()->globalStorage();

    m_defaultFsType = gs->value( "defaultFileSystemType" ).toString();
    m_enableEncryptionWidget = gs->value( "enableLuksAutomatedPartitioning" ).toBool();
    m_allowManualPartitioning = gs->value( "allowManualPartitioning" ).toBool();

    if ( FileSystem::typeForName( m_defaultFsType ) == FileSystem::Unknown )
        m_defaultFsType = "ext4";

    // Set up drives combo
    m_mainLayout->setDirection( QBoxLayout::TopToBottom );
    m_drivesLayout->setDirection( QBoxLayout::LeftToRight );

    BootInfoWidget* bootInfoWidget = new BootInfoWidget( this );
    m_drivesLayout->insertWidget( 0, bootInfoWidget );
    m_drivesLayout->insertSpacing( 1, CalamaresUtils::defaultFontHeight() / 2 );

    m_drivesCombo = new QComboBox( this );
    m_mainLayout->setStretchFactor( m_drivesLayout, 0 );
    m_mainLayout->setStretchFactor( m_rightLayout, 1 );
    m_drivesLabel->setBuddy( m_drivesCombo );

    m_drivesLayout->addWidget( m_drivesCombo );

    m_deviceInfoWidget = new DeviceInfoWidget;
    m_drivesLayout->addWidget( m_deviceInfoWidget );
    m_drivesLayout->addStretch();

    m_messageLabel->setWordWrap( true );
    m_messageLabel->hide();

    CalamaresUtils::unmarginLayout( m_itemsLayout );

    // Drive selector + preview
    CALAMARES_RETRANSLATE(
        retranslateUi( this );
        m_drivesLabel->setText( tr( "Select storage de&vice:" ) );
        m_previewBeforeLabel->setText( tr( "Current:" ) );
        m_previewAfterLabel->setText(  tr( "After:" ) );
    )

    m_previewBeforeFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    m_previewAfterFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    m_previewAfterLabel->hide();
    m_previewAfterFrame->hide();
    m_encryptWidget->hide();
    m_reuseHomeCheckBox->hide();
    gs->insert( "reuseHome", false );
}


ChoicePage::~ChoicePage()
{}


void
ChoicePage::init( PartitionCoreModule* core )
{
    m_core = core;
    m_isEfi = PartUtils::isEfiSystem();

    setupChoices();


    // We need to do this because a PCM revert invalidates the deviceModel.
    connect( core, &PartitionCoreModule::reverted,
             this, [=]
    {
        m_drivesCombo->setModel( core->deviceModel() );
        m_drivesCombo->setCurrentIndex( m_lastSelectedDeviceIndex );
    } );
    m_drivesCombo->setModel( core->deviceModel() );

    connect( m_drivesCombo,
             static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
             this, &ChoicePage::applyDeviceChoice );

    connect( m_encryptWidget, &EncryptWidget::stateChanged,
             this, &ChoicePage::onEncryptWidgetStateChanged );
    connect( m_reuseHomeCheckBox, &QCheckBox::stateChanged,
             this, &ChoicePage::onHomeCheckBoxStateChanged );

    ChoicePage::applyDeviceChoice();
}


/** @brief Creates a combobox with the given choices in it.
 *
 * Pre-selects the choice given by @p dflt.
 * No texts are set -- that happens later by the translator functions.
 */
static inline QComboBox*
createCombo( const QSet< SwapChoice >& s, SwapChoice dflt )
{
    QComboBox* box = new QComboBox;
    for ( SwapChoice c : { SwapChoice::NoSwap, SwapChoice::SmallSwap, SwapChoice::FullSwap, SwapChoice::ReuseSwap, SwapChoice::SwapFile } )
        if ( s.contains( c ) )
            box->addItem( QString(), c );

    int dfltIndex = box->findData( dflt );
    if ( dfltIndex >= 0 )
        box->setCurrentIndex( dfltIndex );

    return box;
}

/**
 * @brief ChoicePage::setupChoices creates PrettyRadioButton objects for the action
 *      choices.
 * @warning This must only run ONCE because it creates signal-slot connections for the
 *      actions. When an action is triggered, it runs action-specific code that may
 *      change the internal state of the PCM, and it updates the bottom preview (or
 *      split) widget.
 *      Synchronous loading ends here.
 */
void
ChoicePage::setupChoices()
{
    // sample os-prober output:
    // /dev/sda2:Windows 7 (loader):Windows:chain
    // /dev/sda6::Arch:linux
    //
    // There are three possibilities we have to consider:
    //  - There are no operating systems present
    //  - There is one operating system present
    //  - There are multiple operating systems present
    //
    // There are three outcomes we have to provide:
    //  1) Wipe+autopartition
    //  2) Resize+autopartition
    //  3) Manual
    //  TBD: upgrade option?

    QSize iconSize( CalamaresUtils::defaultIconSize().width() * 2,
                    CalamaresUtils::defaultIconSize().height() * 2 );
    m_grp = new QButtonGroup( this );

    m_alongsideButton = new PrettyRadioButton;
    m_alongsideButton->setIconSize( iconSize );
    m_alongsideButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionAlongside,
                                                               CalamaresUtils::Original,
                                                               iconSize ) );
    m_grp->addButton( m_alongsideButton->buttonWidget(), Alongside );

    m_eraseButton = new PrettyRadioButton;
    m_eraseButton->setIconSize( iconSize );
    m_eraseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionEraseAuto,
                                                           CalamaresUtils::Original,
                                                           iconSize ) );
    m_grp->addButton( m_eraseButton->buttonWidget(), Erase );

    m_replaceButton = new PrettyRadioButton;

    m_replaceButton->setIconSize( iconSize );
    m_replaceButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionReplaceOs,
                                                             CalamaresUtils::Original,
                                                             iconSize ) );
    m_grp->addButton( m_replaceButton->buttonWidget(), Replace );

    // Fill up swap options
    // .. TODO: only if enabled in the config
    if ( m_availableSwapChoices.count() > 1 )
    {
        m_eraseSwapChoiceComboBox = createCombo( m_availableSwapChoices, m_eraseSwapChoice );
        m_eraseButton->addOptionsComboBox( m_eraseSwapChoiceComboBox );
    }

    m_itemsLayout->addWidget( m_alongsideButton );
    m_itemsLayout->addWidget( m_replaceButton );
    m_itemsLayout->addWidget( m_eraseButton );

    m_somethingElseButton = new PrettyRadioButton;
    m_somethingElseButton->setIconSize( iconSize );
    m_somethingElseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionManual,
                                                                   CalamaresUtils::Original,
                                                                   iconSize ) );
    m_itemsLayout->addWidget( m_somethingElseButton );
    m_grp->addButton( m_somethingElseButton->buttonWidget(), Manual );

    m_itemsLayout->addStretch();

    connect( m_grp, QOverload<int, bool>::of( &QButtonGroup::buttonToggled ),
             this, [ this ]( int id, bool checked )
    {
        if ( checked )  // An action was picked.
        {
            m_choice = static_cast< InstallChoice >( id );
            updateNextEnabled();

            emit actionChosen();
        }
        else    // An action was unpicked, either on its own or because of another selection.
        {
            if ( m_grp->checkedButton() == nullptr )  // If no other action is chosen, we must
            {                                         // set m_choice to NoChoice and reset previews.
                m_choice = NoChoice;
                updateNextEnabled();

                emit actionChosen();
            }
        }
    } );

    m_rightLayout->setStretchFactor( m_itemsLayout, 1 );
    m_rightLayout->setStretchFactor( m_previewBeforeFrame, 0 );
    m_rightLayout->setStretchFactor( m_previewAfterFrame, 0 );

    connect( this, &ChoicePage::actionChosen,
             this, &ChoicePage::onActionChanged );
    if ( m_eraseSwapChoiceComboBox )
        connect( m_eraseSwapChoiceComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                 this, &ChoicePage::onEraseSwapChoiceChanged );

    CALAMARES_RETRANSLATE(
        m_somethingElseButton->setText( tr( "<strong>Manual partitioning</strong><br/>"
                                            "You can create or resize partitions yourself."
                                            " Having a GPT partition table and <strong>fat32 512Mb /boot partition "
                                            "is a must for UEFI installs</strong>, either use an existing without formatting or create one." ) );
        updateSwapChoicesTr( m_eraseSwapChoiceComboBox );
    )
}


/**
 * @brief ChoicePage::selectedDevice queries the device picker (which may be a combo or
 *      a list view) to get a pointer to the currently selected Device.
 * @return a Device pointer, valid in the current state of the PCM, or nullptr if
 *      something goes wrong.
 */
Device*
ChoicePage::selectedDevice()
{
    Device* currentDevice = nullptr;
    currentDevice = m_core->deviceModel()->deviceForIndex(
              m_core->deviceModel()->index(
                  m_drivesCombo->currentIndex() ) );

    return currentDevice;
}


void
ChoicePage::hideButtons()
{
    m_eraseButton->hide();
    m_replaceButton->hide();
    m_alongsideButton->hide();
    m_somethingElseButton->hide();
}


/**
 * @brief ChoicePage::applyDeviceChoice handler for the selected event of the device
 *      picker. Calls ChoicePage::selectedDevice() to get the current Device*, then
 *      updates the preview widget for the on-disk state (calls ChoicePage::
 *      updateDeviceStatePreview()) and finally sets up the available actions and their
 *      text by calling ChoicePage::setupActions().
 */
void
ChoicePage::applyDeviceChoice()
{
    if ( !selectedDevice() )
    {
        hideButtons();
        return;
    }

    if ( m_core->isDirty() )
    {
        ScanningDialog::run( QtConcurrent::run( [ = ]
        {
            QMutexLocker locker( &m_coreMutex );
            m_core->revertAllDevices();
        } ),
        [ this ]
        {
            continueApplyDeviceChoice();
        },
        this );
    }
    else
    {
        continueApplyDeviceChoice();
    }
}


void
ChoicePage::continueApplyDeviceChoice()
{
    Device* currd = selectedDevice();

    // The device should only be nullptr immediately after a PCM reset.
    // applyDeviceChoice() will be called again momentarily as soon as we handle the
    // PartitionCoreModule::reverted signal.
    if ( !currd )
    {
        hideButtons();
        return;
    }

    updateDeviceStatePreview();

    // Preview setup done. Now we show/hide choices as needed.
    setupActions();

    m_lastSelectedDeviceIndex = m_drivesCombo->currentIndex();

    emit actionChosen();
    emit deviceChosen();
}


void
ChoicePage::onActionChanged()
{
    Device* currd = selectedDevice();
    if ( currd )
    {
        applyActionChoice( currentChoice() );
    }
}

void
ChoicePage::onEraseSwapChoiceChanged()
{
    if ( m_eraseSwapChoiceComboBox )
    {
        m_eraseSwapChoice = static_cast<PartitionActions::Choices::SwapChoice>( m_eraseSwapChoiceComboBox->currentData().toInt() );
        onActionChanged();
    }
}

void
ChoicePage::applyActionChoice( ChoicePage::InstallChoice choice )
{
    m_beforePartitionBarsView->selectionModel()->
            disconnect( SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ) );
    m_beforePartitionBarsView->selectionModel()->clearSelection();
    m_beforePartitionBarsView->selectionModel()->clearCurrentIndex();

    switch ( choice )
    {
    case Erase:
        {
            auto gs = Calamares::JobQueue::instance()->globalStorage();

            PartitionActions::Choices::AutoPartitionOptions options {
                gs->value( "defaultFileSystemType" ).toString(),
                m_encryptWidget->passphrase(),
                gs->value( "efiSystemPartition" ).toString(),
                CalamaresUtils::GiBtoBytes( gs->value( "requiredStorageGiB" ).toDouble() ),
                m_eraseSwapChoice
            };

            if ( m_core->isDirty() )
            {
                ScanningDialog::run( QtConcurrent::run( [ = ]
                {
                    QMutexLocker locker( &m_coreMutex );
                    m_core->revertDevice( selectedDevice() );
                } ),
                [ = ]
                {
                    PartitionActions::doAutopartition( m_core, selectedDevice(), options );
                    emit deviceChosen();
                },
                this );
            }
            else
            {
                PartitionActions::doAutopartition( m_core, selectedDevice(), options );
                emit deviceChosen();
            }
        }
        break;
    case Replace:
        if ( m_core->isDirty() )
        {
            ScanningDialog::run( QtConcurrent::run( [ = ]
            {
                QMutexLocker locker( &m_coreMutex );
                m_core->revertDevice( selectedDevice() );
            } ),
            []{},
            this );
        }
        updateNextEnabled();

        connect( m_beforePartitionBarsView->selectionModel(), SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ),
                 this, SLOT( onPartitionToReplaceSelected( QModelIndex, QModelIndex ) ),
                 Qt::UniqueConnection );
        break;

    case Alongside:
        if ( m_core->isDirty() )
        {
            ScanningDialog::run( QtConcurrent::run( [ = ]
            {
                QMutexLocker locker( &m_coreMutex );
                m_core->revertDevice( selectedDevice() );
            } ),
            [this]
            {
                // We need to reupdate after reverting because the splitter widget is
                // not a true view.
                updateActionChoicePreview( currentChoice() );
                updateNextEnabled();
            },
            this );
        }
        updateNextEnabled();

        connect( m_beforePartitionBarsView->selectionModel(), SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ),
                 this, SLOT( doAlongsideSetupSplitter( QModelIndex, QModelIndex ) ),
                 Qt::UniqueConnection );
        break;
    case NoChoice:
    case Manual:
        break;
    }
    updateActionChoicePreview( choice );
}


void
ChoicePage::doAlongsideSetupSplitter( const QModelIndex& current,
                                      const QModelIndex& previous )
{
    Q_UNUSED( previous )
    if ( !current.isValid() )
        return;

    if ( !m_afterPartitionSplitterWidget )
        return;

    const PartitionModel* modl = qobject_cast< const PartitionModel* >( current.model() );
    if ( !modl )
        return;

    Partition* part = modl->partitionForIndex( current );
    if ( !part )
    {
        cDebug() << Q_FUNC_INFO << "Partition not found for index" << current;
        return;
    }

    double requiredStorageGB = Calamares::JobQueue::instance()
                                    ->globalStorage()
                                    ->value( "requiredStorageGiB" )
                                    .toDouble();

    qint64 requiredStorageB = CalamaresUtils::GiBtoBytes( requiredStorageGB + 0.1 + 2.0 );

    m_afterPartitionSplitterWidget->setSplitPartition(
                part->partitionPath(),
                qRound64( part->used() * 1.1 ),
                part->capacity() - requiredStorageB,
                part->capacity() / 2 );

    if ( m_isEfi )
        setupEfiSystemPartitionSelector();

    cDebug() << "Partition selected for Alongside.";

    updateNextEnabled();
}


void
ChoicePage::onEncryptWidgetStateChanged()
{
    EncryptWidget::Encryption state = m_encryptWidget->state();
    if ( m_choice == Erase )
    {
        if ( state == EncryptWidget::Encryption::Confirmed ||
             state == EncryptWidget::Encryption::Disabled )
            applyActionChoice( m_choice );
    }
    else if ( m_choice == Replace )
    {
        if ( m_beforePartitionBarsView &&
             m_beforePartitionBarsView->selectionModel()->currentIndex().isValid() &&
             ( state == EncryptWidget::Encryption::Confirmed ||
               state == EncryptWidget::Encryption::Disabled ) )
        {
            doReplaceSelectedPartition( m_beforePartitionBarsView->
                                            selectionModel()->
                                                currentIndex() );
        }
    }
    updateNextEnabled();
}


void
ChoicePage::onHomeCheckBoxStateChanged()
{
    if ( currentChoice() == Replace &&
         m_beforePartitionBarsView->selectionModel()->currentIndex().isValid() )
    {
        doReplaceSelectedPartition( m_beforePartitionBarsView->
                                        selectionModel()->
                                            currentIndex() );
    }
}


void
ChoicePage::onLeave()
{
    if ( m_choice == Alongside )
        doAlongsideApply();

    if ( m_isEfi && ( m_choice == Alongside || m_choice == Replace ) )
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
        else if ( efiSystemPartitions.count() > 1 && m_efiComboBox )
        {
            PartitionInfo::setMountPoint(
                    efiSystemPartitions.at( m_efiComboBox->currentIndex() ),
                    Calamares::JobQueue::instance()->
                        globalStorage()->
                            value( "efiSystemPartition" ).toString() );
        }
        else
        {
            cError() << "cannot set up EFI system partition.\nESP count:"
                     << efiSystemPartitions.count() << "\nm_efiComboBox:"
                     << m_efiComboBox;
        }
    }
    else    // installPath is then passed to the bootloader module for MBR setup
    {
        if ( !m_isEfi )
        {
            if ( m_bootloaderComboBox.isNull() )
            {
                auto d_p = selectedDevice();
                if ( d_p )
                    m_core->setBootLoaderInstallPath( d_p->deviceNode() );
                else
                    cWarning() << "No device selected for bootloader.";
            }
            else
            {
                QVariant var = m_bootloaderComboBox->currentData( BootLoaderModel::BootLoaderPathRole );
                if ( !var.isValid() )
                    return;
                m_core->setBootLoaderInstallPath( var.toString() );
            }
        }
    }
}


void
ChoicePage::doAlongsideApply()
{
    Q_ASSERT( m_afterPartitionSplitterWidget->splitPartitionSize() >= 0 );
    Q_ASSERT( m_afterPartitionSplitterWidget->newPartitionSize()   >= 0 );

    QMutexLocker locker( &m_coreMutex );

    QString path = m_beforePartitionBarsView->
                   selectionModel()->
                   currentIndex().data( PartitionModel::PartitionPathRole ).toString();

    DeviceModel* dm = m_core->deviceModel();
    for ( int i = 0; i < dm->rowCount(); ++i )
    {
        Device* dev = dm->deviceForIndex( dm->index( i ) );
        Partition* candidate = findPartitionByPath( { dev }, path );
        if ( candidate )
        {
            qint64 firstSector = candidate->firstSector();
            qint64 oldLastSector = candidate->lastSector();
            qint64 newLastSector = firstSector +
                                   m_afterPartitionSplitterWidget->splitPartitionSize() /
                                   dev->logicalSize();

            m_core->resizePartition( dev, candidate, firstSector, newLastSector );
            m_core->layoutApply( dev, newLastSector + 2, oldLastSector,
                                 m_encryptWidget->passphrase(), candidate->parent(),
                                 candidate->roles()
                               );
            m_core->dumpQueue();

            break;
        }
    }
}


void
ChoicePage::onPartitionToReplaceSelected( const QModelIndex& current,
                                          const QModelIndex& previous )
{
    Q_UNUSED( previous )
    if ( !current.isValid() )
        return;

    // Reset state on selection regardless of whether this will be used.
    m_reuseHomeCheckBox->setChecked( false );

    doReplaceSelectedPartition( current );
}


void
ChoicePage::doReplaceSelectedPartition( const QModelIndex& current )
{
    if ( !current.isValid() )
        return;

    QString* homePartitionPath = new QString();
    bool doReuseHomePartition = m_reuseHomeCheckBox->isChecked();

    // NOTE: using by-ref captures because we need to write homePartitionPath and
    //       doReuseHomePartition *after* the device revert, for later use.
    ScanningDialog::run( QtConcurrent::run(
    [ this, current ]( QString* homePartitionPath, bool doReuseHomePartition )
    {
        QMutexLocker locker( &m_coreMutex );

        if ( m_core->isDirty() )
        {
            m_core->revertDevice( selectedDevice() );
        }

        // if the partition is unallocated(free space), we don't replace it but create new one
        // with the same first and last sector
        Partition* selectedPartition =
            static_cast< Partition* >( current.data( PartitionModel::PartitionPtrRole )
                                       .value< void* >() );
        if ( isPartitionFreeSpace( selectedPartition ) )
        {
            //NOTE: if the selected partition is free space, we don't deal with
            //      a separate /home partition at all because there's no existing
            //      rootfs to read it from.
            PartitionRole newRoles = PartitionRole( PartitionRole::Primary );
            PartitionNode* newParent = selectedDevice()->partitionTable();

            if ( selectedPartition->parent() )
            {
                Partition* parent = dynamic_cast< Partition* >( selectedPartition->parent() );
                if ( parent && parent->roles().has( PartitionRole::Extended ) )
                {
                    newRoles = PartitionRole( PartitionRole::Logical );
                    newParent = findPartitionByPath( { selectedDevice() }, parent->partitionPath() );
                }
            }

            m_core->layoutApply( selectedDevice(), selectedPartition->firstSector(),
                                 selectedPartition->lastSector(),
                                 m_encryptWidget->passphrase(), newParent, newRoles
                               );
        }
        else
        {
            // We can't use the PartitionPtrRole because we need to make changes to the
            // main DeviceModel, not the immutable copy.
            QString partPath = current.data( PartitionModel::PartitionPathRole ).toString();
            selectedPartition = findPartitionByPath( { selectedDevice() },
                                                                 partPath );
            if ( selectedPartition )
            {
                // Find out is the selected partition has a rootfs. If yes, then make the
                // m_reuseHomeCheckBox visible and set its text to something meaningful.
                homePartitionPath->clear();
                for ( const OsproberEntry& osproberEntry : m_core->osproberEntries() )
                    if ( osproberEntry.path == partPath )
                        *homePartitionPath = osproberEntry.homePath;
                if ( homePartitionPath->isEmpty() )
                    doReuseHomePartition = false;

                Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

                PartitionActions::doReplacePartition(
                    m_core,
                    selectedDevice(),
                    selectedPartition,
                    {
                        gs->value( "defaultFileSystemType" ).toString(),
                        m_encryptWidget->passphrase()
                    } );
                Partition* homePartition = findPartitionByPath( { selectedDevice() },
                                                                            *homePartitionPath );

                if ( homePartition && doReuseHomePartition )
                {
                    PartitionInfo::setMountPoint( homePartition, "/home" );
                    gs->insert( "reuseHome", true );
                }
                else
                {
                    gs->insert( "reuseHome", false );
                }
            }
        }
    }, homePartitionPath, doReuseHomePartition ),
    [ = ]
    {
        m_reuseHomeCheckBox->setVisible( !homePartitionPath->isEmpty() );
        if ( !homePartitionPath->isEmpty() )
            m_reuseHomeCheckBox->setText( tr( "Reuse %1 as home partition for %2." )
                                          .arg( *homePartitionPath )
                                          .arg( *Calamares::Branding::ShortProductName ) );
        delete homePartitionPath;

        if ( m_isEfi )
            setupEfiSystemPartitionSelector();

        updateNextEnabled();
        if ( !m_bootloaderComboBox.isNull() &&
             m_bootloaderComboBox->currentIndex() < 0 )
            m_bootloaderComboBox->setCurrentIndex( m_lastSelectedDeviceIndex );
    }, this );
}


/**
 * @brief ChoicePage::updateDeviceStatePreview clears and rebuilds the contents of the
 *      preview widget for the current on-disk state. This also triggers a rescan in the
 *      PCM to get a Device* copy that's unaffected by subsequent PCM changes.
 * @param currentDevice a pointer to the selected Device.
 */
void
ChoicePage::updateDeviceStatePreview()
{
    //FIXME: this needs to be made async because the rescan can block the UI thread for
    //       a while. --Teo 10/2015
    Device* currentDevice = selectedDevice();
    Q_ASSERT( currentDevice );
    QMutexLocker locker( &m_previewsMutex );

    cDebug() << "Updating partitioning state widgets.";
    qDeleteAll( m_previewBeforeFrame->children() );

    auto layout = m_previewBeforeFrame->layout();
    if ( layout )
        layout->deleteLater();  // Doesn't like nullptr

    layout = new QVBoxLayout;
    m_previewBeforeFrame->setLayout( layout );
    CalamaresUtils::unmarginLayout( layout );
    layout->setSpacing( 6 );

    PartitionBarsView::NestedPartitionsMode mode = Calamares::JobQueue::instance()->globalStorage()->
                                                   value( "drawNestedPartitions" ).toBool() ?
                                                       PartitionBarsView::DrawNestedPartitions :
                                                       PartitionBarsView::NoNestedPartitions;
    m_beforePartitionBarsView = new PartitionBarsView( m_previewBeforeFrame );
    m_beforePartitionBarsView->setNestedPartitionsMode( mode );
    m_beforePartitionLabelsView = new PartitionLabelsView( m_previewBeforeFrame );
    m_beforePartitionLabelsView->setExtendedPartitionHidden( mode == PartitionBarsView::NoNestedPartitions );

    Device* deviceBefore = m_core->immutableDeviceCopy( currentDevice );

    PartitionModel* model = new PartitionModel( m_beforePartitionBarsView );
    model->init( deviceBefore, m_core->osproberEntries() );

    m_beforePartitionBarsView->setModel( model );
    m_beforePartitionLabelsView->setModel( model );

    // Make the bars and labels view use the same selectionModel.
    auto sm = m_beforePartitionLabelsView->selectionModel();
    m_beforePartitionLabelsView->setSelectionModel( m_beforePartitionBarsView->selectionModel() );
    if ( sm )
        sm->deleteLater();

    switch ( m_choice )
    {
    case Replace:
    case Alongside:
        m_beforePartitionBarsView->setSelectionMode( QAbstractItemView::SingleSelection );
        m_beforePartitionLabelsView->setSelectionMode( QAbstractItemView::SingleSelection );
        break;
    default:
        m_beforePartitionBarsView->setSelectionMode( QAbstractItemView::NoSelection );
        m_beforePartitionLabelsView->setSelectionMode( QAbstractItemView::NoSelection );
    }

    layout->addWidget( m_beforePartitionBarsView );
    layout->addWidget( m_beforePartitionLabelsView );
}


/**
 * @brief ChoicePage::updateActionChoicePreview clears and rebuilds the contents of the
 *      preview widget for the current PCM-proposed state. No rescans here, this should
 *      be immediate.
 * @param currentDevice a pointer to the selected Device.
 * @param choice the chosen partitioning action.
 */
void
ChoicePage::updateActionChoicePreview( ChoicePage::InstallChoice choice )
{
    Device* currentDevice = selectedDevice();
    Q_ASSERT( currentDevice );

    QMutexLocker locker( &m_previewsMutex );

    cDebug() << "Updating partitioning preview widgets.";
    qDeleteAll( m_previewAfterFrame->children() );

    auto oldlayout = m_previewAfterFrame->layout();
    if ( oldlayout )
        oldlayout->deleteLater();

    QVBoxLayout* layout = new QVBoxLayout;
    m_previewAfterFrame->setLayout( layout );
    CalamaresUtils::unmarginLayout( layout );
    layout->setSpacing( 6 );

    PartitionBarsView::NestedPartitionsMode mode = Calamares::JobQueue::instance()->globalStorage()->
                                                   value( "drawNestedPartitions" ).toBool() ?
                                                       PartitionBarsView::DrawNestedPartitions :
                                                       PartitionBarsView::NoNestedPartitions;

    m_reuseHomeCheckBox->hide();
    Calamares::JobQueue::instance()->globalStorage()->insert( "reuseHome", false );

    switch ( choice )
    {
    case Alongside:
        {
            if ( m_enableEncryptionWidget )
                m_encryptWidget->show();
            m_previewBeforeLabel->setText( tr( "Current:" ) );
            m_selectLabel->setText( tr( "<strong>Select a partition to shrink, "
                                        "then drag the bottom bar to resize</strong>" ) );
            m_selectLabel->show();

            m_afterPartitionSplitterWidget = new PartitionSplitterWidget( m_previewAfterFrame );
            m_afterPartitionSplitterWidget->init( selectedDevice(), mode == PartitionBarsView::DrawNestedPartitions );
            layout->addWidget( m_afterPartitionSplitterWidget );

            QLabel* sizeLabel = new QLabel( m_previewAfterFrame );
            layout->addWidget( sizeLabel );
            sizeLabel->setWordWrap( true );
            connect( m_afterPartitionSplitterWidget, &PartitionSplitterWidget::partitionResized, this,
                [ this, sizeLabel ]( const QString& path, qint64 size, qint64 sizeNext )
                {
                    Q_UNUSED( path )
                    sizeLabel->setText( tr( "%1 will be shrunk to %2MiB and a new "
                                            "%3MiB partition will be created for %4." )
                                        .arg( m_beforePartitionBarsView->selectionModel()->currentIndex().data().toString() )
                                        .arg( CalamaresUtils::BytesToMiB( size ) )
                                        .arg( CalamaresUtils::BytesToMiB( sizeNext ) )
                                        .arg( *Calamares::Branding::ShortProductName ) );
                }
            );

            m_previewAfterFrame->show();
            m_previewAfterLabel->show();

            SelectionFilter filter = [ this ]( const QModelIndex& index )
            {
                return PartUtils::canBeResized(
                    static_cast< Partition* >(
                        index.data( PartitionModel::PartitionPtrRole )
                            .value< void* >() ) );
            };
            m_beforePartitionBarsView->setSelectionFilter( filter );
            m_beforePartitionLabelsView->setSelectionFilter( filter );

            break;
        }
    case Erase:
    case Replace:
        {
            if ( m_enableEncryptionWidget )
                m_encryptWidget->show();
            m_previewBeforeLabel->setText( tr( "Current:" ) );
            m_afterPartitionBarsView = new PartitionBarsView( m_previewAfterFrame );
            m_afterPartitionBarsView->setNestedPartitionsMode( mode );
            m_afterPartitionLabelsView = new PartitionLabelsView( m_previewAfterFrame );
            m_afterPartitionLabelsView->setExtendedPartitionHidden( mode == PartitionBarsView::NoNestedPartitions );
            m_afterPartitionLabelsView->setCustomNewRootLabel( *Calamares::Branding::BootloaderEntryName );

            PartitionModel* model = m_core->partitionModelForDevice( selectedDevice() );

            // The QObject parents tree is meaningful for memory management here,
            // see qDeleteAll above.
            m_afterPartitionBarsView->setModel( model );
            m_afterPartitionLabelsView->setModel( model );
            m_afterPartitionBarsView->setSelectionMode( QAbstractItemView::NoSelection );
            m_afterPartitionLabelsView->setSelectionMode( QAbstractItemView::NoSelection );

            layout->addWidget( m_afterPartitionBarsView );
            layout->addWidget( m_afterPartitionLabelsView );

            if ( !m_isEfi )
            {
                QWidget* eraseWidget = new QWidget;

                QHBoxLayout* eraseLayout = new QHBoxLayout;
                eraseWidget->setLayout( eraseLayout );
                eraseLayout->setContentsMargins( 0, 0, 0, 0 );
                QLabel* eraseBootloaderLabel = new QLabel( eraseWidget );
                eraseLayout->addWidget( eraseBootloaderLabel );
                eraseBootloaderLabel->setText( tr( "Boot loader location:" ) );

                m_bootloaderComboBox = createBootloaderComboBox( eraseWidget );
                connect( m_core->bootLoaderModel(), &QAbstractItemModel::modelReset,
                    [ this ]()
                    {
                        if ( !m_bootloaderComboBox.isNull() )
                            Calamares::restoreSelectedBootLoader( *m_bootloaderComboBox, m_core->bootLoaderInstallPath() );
                    }
                );
                connect( m_core, &PartitionCoreModule::deviceReverted, this,
                    [ this ]( Device* dev )
                    {
                        Q_UNUSED( dev )
                        if ( !m_bootloaderComboBox.isNull() )
                        {
                            if ( m_bootloaderComboBox->model() != m_core->bootLoaderModel() )
                                m_bootloaderComboBox->setModel( m_core->bootLoaderModel() );

                            m_bootloaderComboBox->setCurrentIndex( m_lastSelectedDeviceIndex );
                        }
                    }, Qt::QueuedConnection );
                // ^ Must be Queued so it's sure to run when the widget is already visible.

                eraseLayout->addWidget( m_bootloaderComboBox );
                eraseBootloaderLabel->setBuddy( m_bootloaderComboBox );
                eraseLayout->addStretch();

                layout->addWidget( eraseWidget );
            }

            m_previewAfterFrame->show();
            m_previewAfterLabel->show();

            if ( m_choice == Erase )
                m_selectLabel->hide();
            else
            {
                SelectionFilter filter = [ this ]( const QModelIndex& index )
                {
                    return PartUtils::canBeReplaced(
                        static_cast< Partition* >(
                            index.data( PartitionModel::PartitionPtrRole )
                                .value< void* >() ) );
                };
                m_beforePartitionBarsView->setSelectionFilter( filter );
                m_beforePartitionLabelsView->setSelectionFilter( filter );

                m_selectLabel->show();
                m_selectLabel->setText( tr( "<strong>Select a partition to install on</strong>" ) );
            }

            break;
        }
    case NoChoice:
    case Manual:
        m_selectLabel->hide();
        m_previewAfterFrame->hide();
        m_previewBeforeLabel->setText( tr( "Current:" ) );
        m_previewAfterLabel->hide();
        m_encryptWidget->hide();
        break;
    }

    if ( m_isEfi && ( m_choice == Alongside || m_choice == Replace ) )
    {
        QHBoxLayout* efiLayout = new QHBoxLayout;
        layout->addLayout( efiLayout );
        m_efiLabel = new QLabel( m_previewAfterFrame );
        efiLayout->addWidget( m_efiLabel );
        m_efiComboBox = new QComboBox( m_previewAfterFrame );
        efiLayout->addWidget( m_efiComboBox );
        m_efiLabel->setBuddy( m_efiComboBox );
        m_efiComboBox->hide();
        efiLayout->addStretch();
    }

    // Also handle selection behavior on beforeFrame.
    QAbstractItemView::SelectionMode previewSelectionMode;
    switch ( m_choice )
    {
    case Replace:
    case Alongside:
        previewSelectionMode = QAbstractItemView::SingleSelection;
        break;
    default:
        previewSelectionMode = QAbstractItemView::NoSelection;
    }

    m_beforePartitionBarsView->setSelectionMode( previewSelectionMode );
    m_beforePartitionLabelsView->setSelectionMode( previewSelectionMode );
}


void
ChoicePage::setupEfiSystemPartitionSelector()
{
    Q_ASSERT( m_isEfi );

    // Only the already existing ones:
    QList< Partition* > efiSystemPartitions = m_core->efiSystemPartitions();

    if ( efiSystemPartitions.count() == 0 ) //should never happen
    {
        m_efiLabel->setText(
                    tr( "An EFI system partition cannot be found anywhere "
                        "on this system. Please go back and use manual "
                        "partitioning to set up %1." )
                    .arg( *Calamares::Branding::ShortProductName ) );
        updateNextEnabled();
    }
    else if ( efiSystemPartitions.count() == 1 ) //probably most usual situation
    {
        m_efiLabel->setText(
                    tr( "The EFI system partition at %1 will be used for "
                        "starting %2." )
                    .arg( efiSystemPartitions.first()->partitionPath() )
                    .arg( *Calamares::Branding::ShortProductName ) );
    }
    else
    {
        m_efiComboBox->show();
        m_efiLabel->setText( tr( "EFI system partition:" ) );
        for ( int i = 0; i < efiSystemPartitions.count(); ++i )
        {
            Partition* efiPartition = efiSystemPartitions.at( i );
            m_efiComboBox->addItem( efiPartition->partitionPath(), i );

            // We pick an ESP on the currently selected device, if possible
            if ( efiPartition->devicePath() == selectedDevice()->deviceNode() &&
                 efiPartition->number() == 1 )
                m_efiComboBox->setCurrentIndex( i );
        }
    }
}


QComboBox*
ChoicePage::createBootloaderComboBox( QWidget* parent )
{
    QComboBox* bcb = new QComboBox( parent );
    bcb->setModel( m_core->bootLoaderModel() );

    // When the chosen bootloader device changes, we update the choice in the PCM
    connect( bcb, QOverload<int>::of( &QComboBox::currentIndexChanged ),
             this, [this]( int newIndex )
    {
        QComboBox* bcb = qobject_cast< QComboBox* >( sender() );
        if ( bcb )
        {
            QVariant var = bcb->itemData( newIndex, BootLoaderModel::BootLoaderPathRole );
            if ( !var.isValid() )
                return;
            m_core->setBootLoaderInstallPath( var.toString() );
        }
    } );

    return bcb;
}


static inline void
force_uncheck(QButtonGroup* grp, PrettyRadioButton* button)
{
    button->hide();
    grp->setExclusive( false );
    button->buttonWidget()->setChecked( false );
    grp->setExclusive( true );
}

static inline QDebug&
operator <<( QDebug& s, PartitionIterator& it )
{
    s << ( ( *it ) ? ( *it )->deviceNode() : QString( "<null device>" ) );
    return s;
}

/**
 * @brief ChoicePage::setupActions happens every time a new Device* is selected in the
 *      device picker. Sets up the text and visibility of the partitioning actions based
 *      on the currently selected Device*, bootloader and os-prober output.
 * @param currentDevice
 */
void
ChoicePage::setupActions()
{
    Device* currentDevice = selectedDevice();
    OsproberEntryList osproberEntriesForCurrentDevice =
            getOsproberEntriesForDevice( currentDevice );

    cDebug() << "Setting up actions for" << currentDevice->deviceNode()
        << "with" << osproberEntriesForCurrentDevice.count() << "entries.";

    if ( currentDevice->partitionTable() )
        m_deviceInfoWidget->setPartitionTableType( currentDevice->partitionTable()->type() );
    else
        m_deviceInfoWidget->setPartitionTableType( PartitionTable::unknownTableType );

    if ( m_allowManualPartitioning )
        m_somethingElseButton->show();
    else
        force_uncheck( m_grp, m_somethingElseButton );

    bool atLeastOneCanBeResized = false;
    bool atLeastOneCanBeReplaced = false;
    bool atLeastOneIsMounted = false;  // Suppress 'erase' if so
    bool isInactiveRAID = false;

#ifdef WITH_KPMCORE4API
    if ( currentDevice->type() == Device::Type::SoftwareRAID_Device &&
         static_cast< SoftwareRAID* >(currentDevice)->status() == SoftwareRAID::Status::Inactive )
    {
        cDebug() << Logger::SubEntry << "part of an inactive RAID device";
        isInactiveRAID = true;
    }
#endif

    for ( auto it = PartitionIterator::begin( currentDevice );
          it != PartitionIterator::end( currentDevice ); ++it )
    {
        if ( PartUtils::canBeResized( *it ) )
        {
            cDebug() << Logger::SubEntry << "contains resizable" << it;
            atLeastOneCanBeResized = true;
        }
        if ( PartUtils::canBeReplaced( *it ) )
        {
            cDebug() << Logger::SubEntry << "contains replaceable" << it;
            atLeastOneCanBeReplaced = true;
        }
        if ( (*it)->isMounted() )
        {
            atLeastOneIsMounted = true;
        }
    }

    if ( osproberEntriesForCurrentDevice.count() == 0 )
    {
        CALAMARES_RETRANSLATE(
            cDebug() << "Setting texts for 0 osprober entries";
            m_messageLabel->setText( tr( "This storage device does not seem to have an operating system on it. "
                                         "What would you like to do?<br/>"
                                         "You will be able to review and confirm your choices "
                                         "before any change is made to the storage device." ) );

            m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                        "This will <font color=\"red\">delete</font> all data "
                                        "currently present on the selected storage device." ) );

            m_alongsideButton->setText( tr( "<strong>Install alongside</strong><br/>"
                                            "The installer will shrink a partition to make room for %1." )
                                        .arg( *Calamares::Branding::ShortVersionedName ) );

            m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                          "Replaces a partition with %1." )
                                      .arg( *Calamares::Branding::ShortVersionedName ) );
        )

        m_replaceButton->hide();
        m_alongsideButton->hide();
        m_grp->setExclusive( false );
        m_replaceButton->buttonWidget()->setChecked( false );
        m_alongsideButton->buttonWidget()->setChecked( false );
        m_grp->setExclusive( true );
    }
    else if ( osproberEntriesForCurrentDevice.count() == 1 )
    {
        QString osName = osproberEntriesForCurrentDevice.first().prettyName;

        if ( !osName.isEmpty() )
        {
            CALAMARES_RETRANSLATE(
                cDebug() << "Setting texts for 1 non-empty osprober entry";
                m_messageLabel->setText( tr( "This storage device has %1 on it. "
                                             "What would you like to do?<br/>"
                                             "You will be able to review and confirm your choices "
                                             "before any change is made to the storage device." )
                                            .arg( osName ) );

                m_alongsideButton->setText( tr( "<strong>Install alongside</strong><br/>"
                                                "The installer will shrink a partition to make room for %1." )
                                            .arg( *Calamares::Branding::ShortVersionedName ) );

                m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all data "
                                            "currently present on the selected storage device." ) );


                m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                              "Replaces a partition with %1." )
                                          .arg( *Calamares::Branding::ShortVersionedName ) );
            )
        }
        else
        {
            CALAMARES_RETRANSLATE(
                cDebug() << "Setting texts for 1 empty osprober entry";
                m_messageLabel->setText( tr( "This storage device already has an operating system on it. "
                                             "What would you like to do?<br/>"
                                             "You will be able to review and confirm your choices "
                                             "before any change is made to the storage device." ) );

                m_alongsideButton->setText( tr( "<strong>Install alongside</strong><br/>"
                                                "The installer will shrink a partition to make room for %1." )
                                            .arg( *Calamares::Branding::ShortVersionedName ) );

                m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all data "
                                            "currently present on the selected storage device." ) );

                m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                              "Replaces a partition with %1." )
                                          .arg( *Calamares::Branding::ShortVersionedName ) );
            )
        }
    }
    else
    {
        // osproberEntriesForCurrentDevice has at least 2 items.

        CALAMARES_RETRANSLATE(
            cDebug() << "Setting texts for >= 2 osprober entries";

            m_messageLabel->setText( tr( "This storage device has multiple operating systems on it. "
                                         "What would you like to do?<br/>"
                                         "You will be able to review and confirm your choices "
                                         "before any change is made to the storage device." ) );

            m_alongsideButton->setText( tr( "<strong>Install alongside</strong><br/>"
                                            "The installer will shrink a partition to make room for %1." )
                                        .arg( *Calamares::Branding::ShortVersionedName ) );

            m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                        "This will <font color=\"red\">delete</font> all data "
                                        "currently present on the selected storage device." ) );

            m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                          "Replaces a partition with %1." )
                                      .arg( *Calamares::Branding::ShortVersionedName ) );
        )
    }

#ifdef DEBUG_PARTITION_UNSAFE
#ifdef DEBUG_PARTITION_LAME
    // If things can't be broken, allow all the buttons
    atLeastOneCanBeReplaced = true;
    atLeastOneCanBeResized = true;
    atLeastOneIsMounted = false;
    isInactiveRAID = false;
#endif
#endif

    if ( atLeastOneCanBeReplaced )
        m_replaceButton->show();
    else
    {
        cDebug() << "Replace button suppressed because none can be replaced.";
        force_uncheck( m_grp, m_replaceButton );
    }

    if ( atLeastOneCanBeResized )
        m_alongsideButton->show();
    else
    {
        cDebug() << "Alongside button suppressed because none can be resized.";
        force_uncheck( m_grp, m_alongsideButton );
    }

    if ( !atLeastOneIsMounted && !isInactiveRAID )
        m_eraseButton->show();  // None mounted
    else
    {
        cDebug() << "Erase button suppressed"
            << "mount?" << atLeastOneIsMounted
            << "raid?" << isInactiveRAID;
        force_uncheck( m_grp, m_eraseButton );
    }

    bool isEfi = PartUtils::isEfiSystem();
    bool efiSystemPartitionFound = !m_core->efiSystemPartitions().isEmpty();

    if ( isEfi && !efiSystemPartitionFound )
    {
        cWarning() << "System is EFI but there's no EFI system partition, "
                    "DISABLING alongside and replace features.";
        m_alongsideButton->hide();
        m_replaceButton->hide();
    }
}


OsproberEntryList
ChoicePage::getOsproberEntriesForDevice( Device* device ) const
{
    OsproberEntryList eList;
    for ( const OsproberEntry& entry : m_core->osproberEntries() )
    {
        if ( entry.path.startsWith( device->deviceNode() ) )
            eList.append( entry );
    }
    return eList;
}


bool
ChoicePage::isNextEnabled() const
{
    return m_nextEnabled;
}


ChoicePage::InstallChoice
ChoicePage::currentChoice() const
{
    return m_choice;
}


void
ChoicePage::updateNextEnabled()
{
    bool enabled = false;

    auto sm_p = m_beforePartitionBarsView ? m_beforePartitionBarsView->selectionModel() : nullptr;

    switch ( m_choice )
    {
    case NoChoice:
        enabled = false;
        break;
    case Replace:
    case Alongside:
        enabled = sm_p && sm_p->currentIndex().isValid();
        break;
    case Erase:
    case Manual:
        enabled = true;
    }

    if ( m_isEfi &&
         ( m_choice == Alongside ||
           m_choice == Replace ) )
    {
        if ( m_core->efiSystemPartitions().count() == 0 )
            enabled = false;
    }

    if ( m_choice != Manual &&
         m_encryptWidget->isVisible() &&
         m_encryptWidget->state() == EncryptWidget::Encryption::Unconfirmed )
        enabled = false;

    if ( enabled == m_nextEnabled )
        return;

    m_nextEnabled = enabled;
    emit nextStatusChanged( enabled );
}

void
ChoicePage::updateSwapChoicesTr(QComboBox* box)
{
    if ( !box )
        return;

    static_assert(SwapChoice::NoSwap == 0, "Enum values out-of-sync");
    for ( int index = 0; index < box->count(); ++index )
    {
        bool ok = false;
        int value = 0;

        switch ( value = box->itemData( index ).toInt( &ok ) )
        {
            // case 0:
            case SwapChoice::NoSwap:
                // toInt() returns 0 on failure, so check for ok
                if ( ok )  // It was explicitly set to 0
                    box->setItemText( index, tr( "No Swap" ) );
                else
                    cWarning() << "Box item" << index << box->itemText( index ) << "has non-integer role.";
                break;
            case SwapChoice::ReuseSwap:
                box->setItemText( index, tr( "Reuse Swap" ) );
                break;
            case SwapChoice::SmallSwap:
                box->setItemText( index, tr( "Swap (no Hibernate)" ) );
                break;
            case SwapChoice::FullSwap:
                box->setItemText( index, tr( "Swap (with Hibernate)" ) );
                break;
            case SwapChoice::SwapFile:
                box->setItemText( index, tr( "Swap to file" ) );
                break;
            default:
                cWarning() << "Box item" << index << box->itemText( index ) << "has role" << value;
        }
    }
}

int
ChoicePage::lastSelectedDeviceIndex()
{
    return m_lastSelectedDeviceIndex;
}

void
ChoicePage::setLastSelectedDeviceIndex( int index )
{
    m_lastSelectedDeviceIndex = index;
    m_drivesCombo->setCurrentIndex( m_lastSelectedDeviceIndex );
}
