/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd
 *   SPDX-FileCopyrightText: 2021 Anubhav Choudhary <ac.10edu@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ChoicePage.h"

#include "Config.h"

#include "core/BootLoaderModel.h"
#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/OsproberEntry.h"
#include "core/PartUtils.h"
#include "core/PartitionActions.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionInfo.h"
#include "core/PartitionModel.h"
#include "gui/BootInfoWidget.h"
#include "gui/DeviceInfoWidget.h"
#include "gui/PartitionBarsView.h"
#include "gui/PartitionLabelsView.h"
#include "gui/PartitionSplitterWidget.h"
#include "gui/ReplaceWidget.h"
#include "gui/ScanningDialog.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "partition/PartitionIterator.h"
#include "partition/PartitionQuery.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Units.h"
#include "widgets/PrettyRadioButton.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/softwareraid.h>

#include <QBoxLayout>
#include <QButtonGroup>
#include <QComboBox>
#include <QDir>
#include <QFutureWatcher>
#include <QLabel>
#include <QListView>
#include <QtConcurrent/QtConcurrent>

using Calamares::Widgets::PrettyRadioButton;
using CalamaresUtils::Partition::findPartitionByPath;
using CalamaresUtils::Partition::isPartitionFreeSpace;
using CalamaresUtils::Partition::PartitionIterator;
using InstallChoice = Config::InstallChoice;
using SwapChoice = Config::SwapChoice;

/**
 * @brief ChoicePage::ChoicePage is the default constructor. Called on startup as part of
 *      the module loading code path.
 * @param parent the QWidget parent.
 */
ChoicePage::ChoicePage( Config* config, QWidget* parent )
    : QWidget( parent )
    , m_config( config )
    , m_nextEnabled( false )
    , m_core( nullptr )
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
    , m_enableEncryptionWidget( true )
{
    setupUi( this );

    auto gs = Calamares::JobQueue::instance()->globalStorage();

    m_enableEncryptionWidget = gs->value( "enableLuksAutomatedPartitioning" ).toBool();

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
    CALAMARES_RETRANSLATE_SLOT( &ChoicePage::retranslate );

    m_previewBeforeFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    m_previewAfterFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    m_previewAfterLabel->hide();
    m_previewAfterFrame->hide();
    m_encryptWidget->hide();
    m_reuseHomeCheckBox->hide();
    gs->insert( "reuseHome", false );

    updateNextEnabled();
}


ChoicePage::~ChoicePage() {}

void
ChoicePage::retranslate()
{
    retranslateUi( this );
    m_drivesLabel->setText( tr( "Select storage de&vice:" ) );
    m_previewBeforeLabel->setText( tr( "Current:" ) );
    m_previewAfterLabel->setText( tr( "After:" ) );

    updateSwapChoicesTr();
    updateChoiceButtonsTr();
}


/** @brief Sets the @p model for the given @p box and adjusts UI sizes to match.
 *
 * The model provides data for drawing the items in the model; the
 * drawing itself is done by the delegate, which may end up drawing a
 * different width in the popup than in the collapsed combo box.
 *
 * Make the box wide enough to accomodate the whole expanded delegate;
 * this avoids cases where the popup would truncate data being drawn
 * because the overall box is sized too narrow.
 */
void
setModelToComboBox( QComboBox* box, QAbstractItemModel* model )
{
    box->setModel( model );
    if ( model->rowCount() > 0 )
    {
        QStyleOptionViewItem options;
        options.initFrom( box );
        auto delegateSize = box->itemDelegate()->sizeHint( options, model->index( 0, 0 ) );
        box->setMinimumWidth( delegateSize.width() );
    }
}

void
ChoicePage::init( PartitionCoreModule* core )
{
    m_core = core;
    m_isEfi = PartUtils::isEfiSystem();

    setupChoices();


    // We need to do this because a PCM revert invalidates the deviceModel.
    connect( core,
             &PartitionCoreModule::reverted,
             this,
             [ = ]
             {
                 setModelToComboBox( m_drivesCombo, core->deviceModel() );
                 m_drivesCombo->setCurrentIndex( m_lastSelectedDeviceIndex );
             } );
    setModelToComboBox( m_drivesCombo, core->deviceModel() );

    connect( m_drivesCombo, qOverload< int >( &QComboBox::currentIndexChanged ), this, &ChoicePage::applyDeviceChoice );

    connect( m_encryptWidget, &EncryptWidget::stateChanged, this, &ChoicePage::onEncryptWidgetStateChanged );
    connect( m_reuseHomeCheckBox, &QCheckBox::stateChanged, this, &ChoicePage::onHomeCheckBoxStateChanged );

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
    for ( SwapChoice c : { SwapChoice::NoSwap,
                           SwapChoice::SmallSwap,
                           SwapChoice::FullSwap,
                           SwapChoice::ReuseSwap,
                           SwapChoice::SwapFile } )
        if ( s.contains( c ) )
        {
            box->addItem( QString(), c );
        }

    int dfltIndex = box->findData( dflt );
    if ( dfltIndex >= 0 )
    {
        box->setCurrentIndex( dfltIndex );
    }

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

    QSize iconSize( CalamaresUtils::defaultIconSize().width() * 2, CalamaresUtils::defaultIconSize().height() * 2 );
    m_grp = new QButtonGroup( this );

    m_alongsideButton = new PrettyRadioButton;
    m_alongsideButton->setIconSize( iconSize );
    m_alongsideButton->setIcon(
        CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionAlongside, CalamaresUtils::Original, iconSize ) );
    m_alongsideButton->addToGroup( m_grp, InstallChoice::Alongside );

    m_eraseButton = new PrettyRadioButton;
    m_eraseButton->setIconSize( iconSize );
    m_eraseButton->setIcon(
        CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionEraseAuto, CalamaresUtils::Original, iconSize ) );
    m_eraseButton->addToGroup( m_grp, InstallChoice::Erase );

    m_replaceButton = new PrettyRadioButton;

    m_replaceButton->setIconSize( iconSize );
    m_replaceButton->setIcon(
        CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionReplaceOs, CalamaresUtils::Original, iconSize ) );
    m_replaceButton->addToGroup( m_grp, InstallChoice::Replace );

    // Fill up swap options
    if ( m_config->swapChoices().count() > 1 )
    {
        m_eraseSwapChoiceComboBox = createCombo( m_config->swapChoices(), m_config->swapChoice() );
        m_eraseButton->addOptionsComboBox( m_eraseSwapChoiceComboBox );
    }

    if ( m_config->eraseFsTypes().count() > 1 )
    {
        m_eraseFsTypesChoiceComboBox = new QComboBox;
        m_eraseFsTypesChoiceComboBox->addItems( m_config->eraseFsTypes() );
        connect(
            m_eraseFsTypesChoiceComboBox, &QComboBox::currentTextChanged, m_config, &Config::setEraseFsTypeChoice );
        connect( m_config, &Config::eraseModeFilesystemChanged, this, &ChoicePage::onActionChanged );
        m_eraseButton->addOptionsComboBox( m_eraseFsTypesChoiceComboBox );
    }

    m_itemsLayout->addWidget( m_alongsideButton );
    m_itemsLayout->addWidget( m_replaceButton );
    m_itemsLayout->addWidget( m_eraseButton );

    m_somethingElseButton = new PrettyRadioButton;
    m_somethingElseButton->setIconSize( iconSize );
    m_somethingElseButton->setIcon(
        CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionManual, CalamaresUtils::Original, iconSize ) );
    m_itemsLayout->addWidget( m_somethingElseButton );
    m_somethingElseButton->addToGroup( m_grp, InstallChoice::Manual );

    m_itemsLayout->addStretch();

#if ( QT_VERSION < QT_VERSION_CHECK( 5, 15, 0 ) )
    auto buttonSignal = QOverload< int, bool >::of( &QButtonGroup::buttonToggled );
#else
    auto buttonSignal = &QButtonGroup::idToggled;
#endif
    connect( m_grp,
             buttonSignal,
             this,
             [ this ]( int id, bool checked )
             {
                 if ( checked )  // An action was picked.
                 {
                     m_config->setInstallChoice( id );
                     updateNextEnabled();

                     Q_EMIT actionChosen();
                 }
                 else  // An action was unpicked, either on its own or because of another selection.
                 {
                     if ( m_grp->checkedButton() == nullptr )  // If no other action is chosen, we must
                     {
                         // set m_choice to NoChoice and reset previews.
                         m_config->setInstallChoice( InstallChoice::NoChoice );
                         updateNextEnabled();

                         Q_EMIT actionChosen();
                     }
                 }
             } );

    m_rightLayout->setStretchFactor( m_itemsLayout, 1 );
    m_rightLayout->setStretchFactor( m_previewBeforeFrame, 0 );
    m_rightLayout->setStretchFactor( m_previewAfterFrame, 0 );

    connect( this, &ChoicePage::actionChosen, this, &ChoicePage::onActionChanged );
    if ( m_eraseSwapChoiceComboBox )
    {
        connect( m_eraseSwapChoiceComboBox,
                 QOverload< int >::of( &QComboBox::currentIndexChanged ),
                 this,
                 &ChoicePage::onEraseSwapChoiceChanged );
    }

    updateSwapChoicesTr();
    updateChoiceButtonsTr();
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
    currentDevice
        = m_core->deviceModel()->deviceForIndex( m_core->deviceModel()->index( m_drivesCombo->currentIndex() ) );

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

void
ChoicePage::checkInstallChoiceRadioButton( InstallChoice c )
{
    QSignalBlocker b( m_grp );
    m_grp->setExclusive( false );
    // If c == InstallChoice::NoChoice none will match and all are deselected
    m_eraseButton->setChecked( InstallChoice::Erase == c );
    m_replaceButton->setChecked( InstallChoice::Replace == c );
    m_alongsideButton->setChecked( InstallChoice::Alongside == c );
    m_somethingElseButton->setChecked( InstallChoice::Manual == c );
    m_grp->setExclusive( true );
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
        ScanningDialog::run(
            QtConcurrent::run(
                [ = ]
                {
                    QMutexLocker locker( &m_coreMutex );
                    m_core->revertAllDevices();
                } ),
            [ this ] { continueApplyDeviceChoice(); },
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

    cDebug() << "Previous device" << m_lastSelectedDeviceIndex << "new device" << m_drivesCombo->currentIndex();
    if ( m_lastSelectedDeviceIndex != m_drivesCombo->currentIndex() )
    {
        m_lastSelectedDeviceIndex = m_drivesCombo->currentIndex();
        m_lastSelectedActionIndex = -1;
        m_config->setInstallChoice( m_config->initialInstallChoice() );
        checkInstallChoiceRadioButton( m_config->installChoice() );
    }

    Q_EMIT actionChosen();
    Q_EMIT deviceChosen();
}

void
ChoicePage::onActionChanged()
{
    Device* currd = selectedDevice();
    if ( currd )
    {
        applyActionChoice( m_config->installChoice() );
    }

    // Whole disk encryption isn't implemented for zfs so disable the option for now
    if ( m_eraseFsTypesChoiceComboBox != nullptr && m_enableEncryptionWidget )
    {
        if ( m_eraseFsTypesChoiceComboBox->currentText() == "zfs" )
        {
            m_encryptWidget->hide();
        }
        else
        {
            m_encryptWidget->show();
        }
    }
    updateNextEnabled();
}

void
ChoicePage::onEraseSwapChoiceChanged()
{
    if ( m_eraseSwapChoiceComboBox )
    {
        m_config->setSwapChoice( m_eraseSwapChoiceComboBox->currentData().toInt() );
        onActionChanged();
    }
}

void
ChoicePage::applyActionChoice( InstallChoice choice )
{
    cDebug() << "Prev" << m_lastSelectedActionIndex << "InstallChoice" << choice
             << Config::installChoiceNames().find( choice );
    m_beforePartitionBarsView->selectionModel()->disconnect( SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ) );
    m_beforePartitionBarsView->selectionModel()->clearSelection();
    m_beforePartitionBarsView->selectionModel()->clearCurrentIndex();

    switch ( choice )
    {
    case InstallChoice::Erase:
    {
        auto gs = Calamares::JobQueue::instance()->globalStorage();
        PartitionActions::Choices::AutoPartitionOptions options { gs->value( "defaultPartitionTableType" ).toString(),
                                                                  m_config->eraseFsType(),
                                                                  m_encryptWidget->passphrase(),
                                                                  gs->value( "efiSystemPartition" ).toString(),
                                                                  CalamaresUtils::GiBtoBytes(
                                                                      gs->value( "requiredStorageGiB" ).toDouble() ),
                                                                  m_config->swapChoice() };

        if ( m_core->isDirty() )
        {
            ScanningDialog::run(
                QtConcurrent::run(
                    [ = ]
                    {
                        QMutexLocker locker( &m_coreMutex );
                        m_core->revertDevice( selectedDevice() );
                    } ),
                [ = ]
                {
                    PartitionActions::doAutopartition( m_core, selectedDevice(), options );
                    Q_EMIT deviceChosen();
                },
                this );
        }
        else
        {
            PartitionActions::doAutopartition( m_core, selectedDevice(), options );
            Q_EMIT deviceChosen();
        }
    }
    break;
    case InstallChoice::Replace:
        if ( m_core->isDirty() )
        {
            ScanningDialog::run(
                QtConcurrent::run(
                    [ = ]
                    {
                        QMutexLocker locker( &m_coreMutex );
                        m_core->revertDevice( selectedDevice() );
                    } ),
                [] {},
                this );
        }
        connect( m_beforePartitionBarsView->selectionModel(),
                 SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ),
                 this,
                 SLOT( onPartitionToReplaceSelected( QModelIndex, QModelIndex ) ),
                 Qt::UniqueConnection );
        break;

    case InstallChoice::Alongside:
        if ( m_core->isDirty() )
        {
            ScanningDialog::run(
                QtConcurrent::run(
                    [ = ]
                    {
                        QMutexLocker locker( &m_coreMutex );
                        m_core->revertDevice( selectedDevice() );
                    } ),
                [ this ]
                {
                    // We need to reupdate after reverting because the splitter widget is
                    // not a true view.
                    updateActionChoicePreview( m_config->installChoice() );
                    updateNextEnabled();
                },
                this );
        }

        connect( m_beforePartitionBarsView->selectionModel(),
                 SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ),
                 this,
                 SLOT( doAlongsideSetupSplitter( QModelIndex, QModelIndex ) ),
                 Qt::UniqueConnection );
        break;
    case InstallChoice::NoChoice:
    case InstallChoice::Manual:
        break;
    }
    updateNextEnabled();
    updateActionChoicePreview( choice );
}


void
ChoicePage::doAlongsideSetupSplitter( const QModelIndex& current, const QModelIndex& previous )
{
    Q_UNUSED( previous )
    if ( !current.isValid() )
    {
        return;
    }

    if ( !m_afterPartitionSplitterWidget )
    {
        return;
    }

    const PartitionModel* modl = qobject_cast< const PartitionModel* >( current.model() );
    if ( !modl )
    {
        return;
    }

    Partition* part = modl->partitionForIndex( current );
    if ( !part )
    {
        cDebug() << "Partition not found for index" << current;
        return;
    }

    double requiredStorageGB
        = Calamares::JobQueue::instance()->globalStorage()->value( "requiredStorageGiB" ).toDouble();

    qint64 requiredStorageB = CalamaresUtils::GiBtoBytes( requiredStorageGB + 0.1 + 2.0 );

    m_afterPartitionSplitterWidget->setSplitPartition( part->partitionPath(),
                                                       qRound64( part->used() * 1.1 ),
                                                       part->capacity() - requiredStorageB,
                                                       part->capacity() / 2 );

    if ( m_isEfi )
    {
        setupEfiSystemPartitionSelector();
    }

    cDebug() << "Partition selected for Alongside.";

    updateNextEnabled();
}


void
ChoicePage::onEncryptWidgetStateChanged()
{
    EncryptWidget::Encryption state = m_encryptWidget->state();
    if ( m_config->installChoice() == InstallChoice::Erase )
    {
        if ( state == EncryptWidget::Encryption::Confirmed || state == EncryptWidget::Encryption::Disabled )
        {
            applyActionChoice( m_config->installChoice() );
        }
    }
    else if ( m_config->installChoice() == InstallChoice::Replace )
    {
        if ( m_beforePartitionBarsView && m_beforePartitionBarsView->selectionModel()->currentIndex().isValid()
             && ( state == EncryptWidget::Encryption::Confirmed || state == EncryptWidget::Encryption::Disabled ) )
        {
            doReplaceSelectedPartition( m_beforePartitionBarsView->selectionModel()->currentIndex() );
        }
    }
    updateNextEnabled();
}


void
ChoicePage::onHomeCheckBoxStateChanged()
{
    if ( m_config->installChoice() == InstallChoice::Replace
         && m_beforePartitionBarsView->selectionModel()->currentIndex().isValid() )
    {
        doReplaceSelectedPartition( m_beforePartitionBarsView->selectionModel()->currentIndex() );
    }
}


void
ChoicePage::onLeave()
{
    if ( m_config->installChoice() == InstallChoice::Alongside )
    {
        doAlongsideApply();
    }

    if ( m_isEfi
         && ( m_config->installChoice() == InstallChoice::Alongside
              || m_config->installChoice() == InstallChoice::Replace ) )
    {
        QList< Partition* > efiSystemPartitions = m_core->efiSystemPartitions();
        if ( efiSystemPartitions.count() == 1 )
        {
            PartitionInfo::setMountPoint(
                efiSystemPartitions.first(),
                Calamares::JobQueue::instance()->globalStorage()->value( "efiSystemPartition" ).toString() );
        }
        else if ( efiSystemPartitions.count() > 1 && m_efiComboBox )
        {
            PartitionInfo::setMountPoint(
                efiSystemPartitions.at( m_efiComboBox->currentIndex() ),
                Calamares::JobQueue::instance()->globalStorage()->value( "efiSystemPartition" ).toString() );
        }
        else
        {
            cError() << "cannot set up EFI system partition.\nESP count:" << efiSystemPartitions.count()
                     << "\nm_efiComboBox:" << m_efiComboBox;
        }
    }
    else  // installPath is then passed to the bootloader module for MBR setup
    {
        if ( !m_isEfi )
        {
            if ( m_bootloaderComboBox.isNull() )
            {
                auto d_p = selectedDevice();
                if ( d_p )
                {
                    m_core->setBootLoaderInstallPath( d_p->deviceNode() );
                }
                else
                {
                    cWarning() << "No device selected for bootloader.";
                }
            }
            else
            {
                QVariant var = m_bootloaderComboBox->currentData( BootLoaderModel::BootLoaderPathRole );
                if ( !var.isValid() )
                {
                    return;
                }
                m_core->setBootLoaderInstallPath( var.toString() );
            }
        }
    }
}


void
ChoicePage::doAlongsideApply()
{
    Q_ASSERT( m_afterPartitionSplitterWidget->splitPartitionSize() >= 0 );
    Q_ASSERT( m_afterPartitionSplitterWidget->newPartitionSize() >= 0 );

    QMutexLocker locker( &m_coreMutex );

    QString path = m_beforePartitionBarsView->selectionModel()
                       ->currentIndex()
                       .data( PartitionModel::PartitionPathRole )
                       .toString();

    DeviceModel* dm = m_core->deviceModel();
    for ( int i = 0; i < dm->rowCount(); ++i )
    {
        Device* dev = dm->deviceForIndex( dm->index( i ) );
        Partition* candidate = findPartitionByPath( { dev }, path );
        if ( candidate )
        {
            qint64 firstSector = candidate->firstSector();
            qint64 oldLastSector = candidate->lastSector();
            qint64 newLastSector
                = firstSector + m_afterPartitionSplitterWidget->splitPartitionSize() / dev->logicalSize();

            m_core->resizePartition( dev, candidate, firstSector, newLastSector );
            m_core->layoutApply( dev,
                                 newLastSector + 2,
                                 oldLastSector,
                                 m_encryptWidget->passphrase(),
                                 candidate->parent(),
                                 candidate->roles() );
            m_core->dumpQueue();

            break;
        }
    }
}


void
ChoicePage::onPartitionToReplaceSelected( const QModelIndex& current, const QModelIndex& previous )
{
    Q_UNUSED( previous )
    if ( !current.isValid() )
    {
        return;
    }

    // Reset state on selection regardless of whether this will be used.
    m_reuseHomeCheckBox->setChecked( false );

    doReplaceSelectedPartition( current );
}


void
ChoicePage::doReplaceSelectedPartition( const QModelIndex& current )
{
    if ( !current.isValid() )
    {
        return;
    }

    // This will be deleted by the second lambda, below.
    QString* homePartitionPath = new QString();

    ScanningDialog::run(
        QtConcurrent::run(
            [ this, current, homePartitionPath ]( bool doReuseHomePartition )
            {
                QMutexLocker locker( &m_coreMutex );

                if ( m_core->isDirty() )
                {
                    m_core->revertDevice( selectedDevice() );
                }

                // if the partition is unallocated(free space), we don't replace it but create new one
                // with the same first and last sector
                Partition* selectedPartition
                    = static_cast< Partition* >( current.data( PartitionModel::PartitionPtrRole ).value< void* >() );
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

                    m_core->layoutApply( selectedDevice(),
                                         selectedPartition->firstSector(),
                                         selectedPartition->lastSector(),
                                         m_encryptWidget->passphrase(),
                                         newParent,
                                         newRoles );
                }
                else
                {
                    // We can't use the PartitionPtrRole because we need to make changes to the
                    // main DeviceModel, not the immutable copy.
                    QString partPath = current.data( PartitionModel::PartitionPathRole ).toString();
                    selectedPartition = findPartitionByPath( { selectedDevice() }, partPath );
                    if ( selectedPartition )
                    {
                        // Find out is the selected partition has a rootfs. If yes, then make the
                        // m_reuseHomeCheckBox visible and set its text to something meaningful.
                        homePartitionPath->clear();
                        for ( const OsproberEntry& osproberEntry : m_core->osproberEntries() )
                            if ( osproberEntry.path == partPath )
                            {
                                *homePartitionPath = osproberEntry.homePath;
                            }
                        if ( homePartitionPath->isEmpty() )
                        {
                            doReuseHomePartition = false;
                        }

                        Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();

                        PartitionActions::doReplacePartition( m_core,
                                                              selectedDevice(),
                                                              selectedPartition,
                                                              { gs->value( "defaultPartitionType" ).toString(),
                                                                gs->value( "defaultFileSystemType" ).toString(),
                                                                m_encryptWidget->passphrase() } );
                        Partition* homePartition = findPartitionByPath( { selectedDevice() }, *homePartitionPath );

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
            },
            m_reuseHomeCheckBox->isChecked() ),
        [ this, homePartitionPath ]
        {
            m_reuseHomeCheckBox->setVisible( !homePartitionPath->isEmpty() );
            if ( !homePartitionPath->isEmpty() )
                m_reuseHomeCheckBox->setText( tr( "Reuse %1 as home partition for %2." )
                                                  .arg( *homePartitionPath )
                                                  .arg( Calamares::Branding::instance()->shortProductName() ) );
            delete homePartitionPath;

            if ( m_isEfi )
                setupEfiSystemPartitionSelector();

            updateNextEnabled();
            if ( !m_bootloaderComboBox.isNull() && m_bootloaderComboBox->currentIndex() < 0 )
                m_bootloaderComboBox->setCurrentIndex( m_lastSelectedDeviceIndex );
        },
        this );
}


/**
 * @brief clear and then rebuild the contents of the preview widget
 *
 * The preview widget for the current disk is completely re-constructed
 * based on the on-disk state. This also triggers a rescan in the
 * PCM to get a Device* copy that's unaffected by subsequent PCM changes.
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
    {
        layout->deleteLater();  // Doesn't like nullptr
    }

    layout = new QVBoxLayout;
    m_previewBeforeFrame->setLayout( layout );
    CalamaresUtils::unmarginLayout( layout );
    layout->setSpacing( 6 );

    PartitionBarsView::NestedPartitionsMode mode
        = Calamares::JobQueue::instance()->globalStorage()->value( "drawNestedPartitions" ).toBool()
        ? PartitionBarsView::DrawNestedPartitions
        : PartitionBarsView::NoNestedPartitions;
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
    {
        sm->deleteLater();
    }

    switch ( m_config->installChoice() )
    {
    case InstallChoice::Replace:
    case InstallChoice::Alongside:
        m_beforePartitionBarsView->setSelectionMode( QAbstractItemView::SingleSelection );
        m_beforePartitionLabelsView->setSelectionMode( QAbstractItemView::SingleSelection );
        break;
    case InstallChoice::NoChoice:
    case InstallChoice::Erase:
    case InstallChoice::Manual:
        m_beforePartitionBarsView->setSelectionMode( QAbstractItemView::NoSelection );
        m_beforePartitionLabelsView->setSelectionMode( QAbstractItemView::NoSelection );
    }

    layout->addWidget( m_beforePartitionBarsView );
    layout->addWidget( m_beforePartitionLabelsView );
}


/**
 * @brief rebuild the contents of the preview for the PCM-proposed state.
 *
 * No rescans here, this should be immediate.
 *
 * @param choice the chosen partitioning action.
 */
void
ChoicePage::updateActionChoicePreview( InstallChoice choice )
{
    Device* currentDevice = selectedDevice();
    Q_ASSERT( currentDevice );

    QMutexLocker locker( &m_previewsMutex );

    cDebug() << "Updating partitioning preview widgets.";
    qDeleteAll( m_previewAfterFrame->children() );

    auto oldlayout = m_previewAfterFrame->layout();
    if ( oldlayout )
    {
        oldlayout->deleteLater();
    }

    QVBoxLayout* layout = new QVBoxLayout;
    m_previewAfterFrame->setLayout( layout );
    CalamaresUtils::unmarginLayout( layout );
    layout->setSpacing( 6 );

    PartitionBarsView::NestedPartitionsMode mode
        = Calamares::JobQueue::instance()->globalStorage()->value( "drawNestedPartitions" ).toBool()
        ? PartitionBarsView::DrawNestedPartitions
        : PartitionBarsView::NoNestedPartitions;

    m_reuseHomeCheckBox->hide();
    Calamares::JobQueue::instance()->globalStorage()->insert( "reuseHome", false );

    switch ( choice )
    {
    case InstallChoice::Alongside:
    {
        if ( m_enableEncryptionWidget )
        {
            m_encryptWidget->show();
        }
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

        if ( !m_isEfi )
        {
            layout->addWidget( createBootloaderPanel() );
        }

        connect( m_afterPartitionSplitterWidget,
                 &PartitionSplitterWidget::partitionResized,
                 this,
                 [ this, sizeLabel ]( const QString& path, qint64 size, qint64 sizeNext )
                 {
                     Q_UNUSED( path )
                     sizeLabel->setText(
                         tr( "%1 will be shrunk to %2MiB and a new "
                             "%3MiB partition will be created for %4." )
                             .arg( m_beforePartitionBarsView->selectionModel()->currentIndex().data().toString() )
                             .arg( CalamaresUtils::BytesToMiB( size ) )
                             .arg( CalamaresUtils::BytesToMiB( sizeNext ) )
                             .arg( Calamares::Branding::instance()->shortProductName() ) );
                 } );

        m_previewAfterFrame->show();
        m_previewAfterLabel->show();

        SelectionFilter filter = []( const QModelIndex& index )
        {
            return PartUtils::canBeResized(
                static_cast< Partition* >( index.data( PartitionModel::PartitionPtrRole ).value< void* >() ),
                Logger::Once() );
        };
        m_beforePartitionBarsView->setSelectionFilter( filter );
        m_beforePartitionLabelsView->setSelectionFilter( filter );

        break;
    }
    case InstallChoice::Erase:
    case InstallChoice::Replace:
    {
        if ( m_enableEncryptionWidget )
        {
            m_encryptWidget->show();
        }
        m_previewBeforeLabel->setText( tr( "Current:" ) );
        m_afterPartitionBarsView = new PartitionBarsView( m_previewAfterFrame );
        m_afterPartitionBarsView->setNestedPartitionsMode( mode );
        m_afterPartitionLabelsView = new PartitionLabelsView( m_previewAfterFrame );
        m_afterPartitionLabelsView->setExtendedPartitionHidden( mode == PartitionBarsView::NoNestedPartitions );
        m_afterPartitionLabelsView->setCustomNewRootLabel(
            Calamares::Branding::instance()->string( Calamares::Branding::BootloaderEntryName ) );

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
            layout->addWidget( createBootloaderPanel() );
        }

        m_previewAfterFrame->show();
        m_previewAfterLabel->show();

        if ( m_config->installChoice() == InstallChoice::Erase )
        {
            m_selectLabel->hide();
        }
        else
        {
            SelectionFilter filter = []( const QModelIndex& index )
            {
                return PartUtils::canBeReplaced(
                    static_cast< Partition* >( index.data( PartitionModel::PartitionPtrRole ).value< void* >() ),
                    Logger::Once() );
            };
            m_beforePartitionBarsView->setSelectionFilter( filter );
            m_beforePartitionLabelsView->setSelectionFilter( filter );

            m_selectLabel->show();
            m_selectLabel->setText( tr( "<strong>Select a partition to install on</strong>" ) );
        }

        break;
    }
    case InstallChoice::NoChoice:
    case InstallChoice::Manual:
        m_selectLabel->hide();
        m_previewAfterFrame->hide();
        m_previewBeforeLabel->setText( tr( "Current:" ) );
        m_previewAfterLabel->hide();
        m_encryptWidget->hide();
        break;
    }

    if ( m_isEfi
         && ( m_config->installChoice() == InstallChoice::Alongside
              || m_config->installChoice() == InstallChoice::Replace ) )
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
    QAbstractItemView::SelectionMode previewSelectionMode = QAbstractItemView::NoSelection;
    switch ( m_config->installChoice() )
    {
    case InstallChoice::Replace:
    case InstallChoice::Alongside:
        previewSelectionMode = QAbstractItemView::SingleSelection;
        break;
    case InstallChoice::NoChoice:
    case InstallChoice::Erase:
    case InstallChoice::Manual:
        previewSelectionMode = QAbstractItemView::NoSelection;
    }

    m_beforePartitionBarsView->setSelectionMode( previewSelectionMode );
    m_beforePartitionLabelsView->setSelectionMode( previewSelectionMode );

    updateNextEnabled();
}


void
ChoicePage::setupEfiSystemPartitionSelector()
{
    Q_ASSERT( m_isEfi );

    // Only the already existing ones:
    QList< Partition* > efiSystemPartitions = m_core->efiSystemPartitions();

    if ( efiSystemPartitions.count() == 0 )  //should never happen
    {
        m_efiLabel->setText( tr( "An EFI system partition cannot be found anywhere "
                                 "on this system. Please go back and use manual "
                                 "partitioning to set up %1." )
                                 .arg( Calamares::Branding::instance()->shortProductName() ) );
        updateNextEnabled();
    }
    else if ( efiSystemPartitions.count() == 1 )  //probably most usual situation
    {
        m_efiLabel->setText( tr( "The EFI system partition at %1 will be used for "
                                 "starting %2." )
                                 .arg( efiSystemPartitions.first()->partitionPath() )
                                 .arg( Calamares::Branding::instance()->shortProductName() ) );
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
            if ( efiPartition->devicePath() == selectedDevice()->deviceNode() && efiPartition->number() == 1 )
            {
                m_efiComboBox->setCurrentIndex( i );
            }
        }
    }
}

static inline void
force_uncheck( QButtonGroup* grp, PrettyRadioButton* button )
{
    button->hide();
    grp->setExclusive( false );
    button->setChecked( false );
    grp->setExclusive( true );
}

static inline QDebug&
operator<<( QDebug& s, PartitionIterator& it )
{
    s << ( ( *it ) ? ( *it )->deviceNode() : QString( "<null device>" ) );
    return s;
}

QString
describePartitionTypes( const QStringList& types )
{
    if ( types.empty() )
    {
        return QCoreApplication::translate(
            ChoicePage::staticMetaObject.className(), "any", "any partition-table type" );
    }
    if ( types.size() == 1 )
    {
        return types.first();
    }
    if ( types.size() == 2 )
    {
        return QCoreApplication::translate(
                   ChoicePage::staticMetaObject.className(), "%1 or %2", "partition-table types" )
            .arg( types.at( 0 ), types.at( 1 ) );
    }
    // More than two, rather unlikely
    return types.join( ", " );
}

/**
 * @brief ChoicePage::setupActions happens every time a new Device* is selected in the
 *      device picker. Sets up the text and visibility of the partitioning actions based
 *      on the currently selected Device*, bootloader and os-prober output.
 */
void
ChoicePage::setupActions()
{
    Logger::Once o;

    Device* currentDevice = selectedDevice();
    OsproberEntryList osproberEntriesForCurrentDevice = getOsproberEntriesForDevice( currentDevice );

    cDebug() << o << "Setting up actions for" << currentDevice->deviceNode() << "with"
             << osproberEntriesForCurrentDevice.count() << "entries.";

    if ( currentDevice->partitionTable() )
    {
        m_deviceInfoWidget->setPartitionTableType( currentDevice->partitionTable()->type() );
    }
    else
    {
        m_deviceInfoWidget->setPartitionTableType( PartitionTable::unknownTableType );
    }

    if ( m_config->allowManualPartitioning() )
    {
        m_somethingElseButton->show();
    }
    else
    {
        force_uncheck( m_grp, m_somethingElseButton );
    }

    bool atLeastOneCanBeResized = false;
    bool atLeastOneCanBeReplaced = false;
    bool atLeastOneIsMounted = false;  // Suppress 'erase' if so
    bool isInactiveRAID = false;
    bool matchTableType = false;

    if ( currentDevice->type() == Device::Type::SoftwareRAID_Device
         && static_cast< SoftwareRAID* >( currentDevice )->status() == SoftwareRAID::Status::Inactive )
    {
        cDebug() << Logger::SubEntry << "part of an inactive RAID device";
        isInactiveRAID = true;
    }

    PartitionTable::TableType tableType = PartitionTable::unknownTableType;
    if ( currentDevice->partitionTable() )
    {
        tableType = currentDevice->partitionTable()->type();
        matchTableType = m_config->acceptPartitionTableType( tableType );
    }

    for ( auto it = PartitionIterator::begin( currentDevice ); it != PartitionIterator::end( currentDevice ); ++it )
    {
        if ( PartUtils::canBeResized( *it, o ) )
        {
            cDebug() << Logger::SubEntry << "contains resizable" << it;
            atLeastOneCanBeResized = true;
        }
        if ( PartUtils::canBeReplaced( *it, o ) )
        {
            cDebug() << Logger::SubEntry << "contains replaceable" << it;
            atLeastOneCanBeReplaced = true;
        }
        if ( ( *it )->isMounted() )
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
                                            .arg( Calamares::Branding::instance()->shortVersionedName() ) );

            m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                          "Replaces a partition with %1." )
                                          .arg( Calamares::Branding::instance()->shortVersionedName() ) ); );

        m_replaceButton->hide();
        m_alongsideButton->hide();
        m_grp->setExclusive( false );
        m_replaceButton->setChecked( false );
        m_alongsideButton->setChecked( false );
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
                                                .arg( Calamares::Branding::instance()->shortVersionedName() ) );

                m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all data "
                                            "currently present on the selected storage device." ) );


                m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                              "Replaces a partition with %1." )
                                              .arg( Calamares::Branding::instance()->shortVersionedName() ) ); );
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
                                                .arg( Calamares::Branding::instance()->shortVersionedName() ) );

                m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all data "
                                            "currently present on the selected storage device." ) );

                m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                              "Replaces a partition with %1." )
                                              .arg( Calamares::Branding::instance()->shortVersionedName() ) ); );
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
                                            .arg( Calamares::Branding::instance()->shortVersionedName() ) );

            m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                        "This will <font color=\"red\">delete</font> all data "
                                        "currently present on the selected storage device." ) );

            m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                          "Replaces a partition with %1." )
                                          .arg( Calamares::Branding::instance()->shortVersionedName() ) ); );
    }

#ifdef DEBUG_PARTITION_UNSAFE
#ifdef DEBUG_PARTITION_BAIL_OUT
    // If things can't be broken, allow all the buttons
    atLeastOneCanBeReplaced = true;
    atLeastOneCanBeResized = true;
    atLeastOneIsMounted = false;
    isInactiveRAID = false;
#endif
#endif

    if ( atLeastOneCanBeReplaced )
    {
        m_replaceButton->show();
    }
    else
    {
        cDebug() << "No partitions available for replace-action.";
        force_uncheck( m_grp, m_replaceButton );
    }

    if ( atLeastOneCanBeResized )
    {
        m_alongsideButton->show();
    }
    else
    {
        cDebug() << "No partitions available for resize-action.";
        force_uncheck( m_grp, m_alongsideButton );
    }

    if ( !atLeastOneIsMounted && !isInactiveRAID )
    {
        m_eraseButton->show();  // None mounted
    }
    else
    {
        cDebug() << "No partitions ("
                 << "any-mounted?" << atLeastOneIsMounted << "is-raid?" << isInactiveRAID << ") for erase-action.";
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

    if ( tableType != PartitionTable::unknownTableType && !matchTableType )
    {
        m_messageLabel->setText( tr( "This storage device already has an operating system on it, "
                                     "but the partition table <strong>%1</strong> is different from the "
                                     "needed <strong>%2</strong>.<br/>" )
                                     .arg( PartitionTable::tableTypeToName( tableType ) )
                                     .arg( describePartitionTypes( m_config->partitionTableTypes() ) ) );
        m_messageLabel->show();

        cWarning() << "Partition table" << PartitionTable::tableTypeToName( tableType )
                   << "does not match the requirement " << m_config->partitionTableTypes().join( ',' )
                   << ", ENABLING erase feature and DISABLING alongside, replace and manual features.";
        m_eraseButton->show();
        m_alongsideButton->hide();
        m_replaceButton->hide();
        m_somethingElseButton->hide();
        cDebug() << "Replace button suppressed because partition table type mismatch.";
        force_uncheck( m_grp, m_replaceButton );
    }

    if ( m_somethingElseButton->isHidden() && m_alongsideButton->isHidden() && m_replaceButton->isHidden()
         && m_eraseButton->isHidden() )
    {
        if ( atLeastOneIsMounted )
        {
            m_messageLabel->setText( tr( "This storage device has one of its partitions <strong>mounted</strong>." ) );
        }
        else
        {
            m_messageLabel->setText(
                tr( "This storage device is a part of an <strong>inactive RAID</strong> device." ) );
        }

        m_messageLabel->show();
        cWarning() << "No buttons available"
                   << "replaced?" << atLeastOneCanBeReplaced << "resized?" << atLeastOneCanBeResized
                   << "erased? (not-mounted and not-raid)" << !atLeastOneIsMounted << "and" << !isInactiveRAID;
    }
}


OsproberEntryList
ChoicePage::getOsproberEntriesForDevice( Device* device ) const
{
    OsproberEntryList eList;
    for ( const OsproberEntry& entry : m_core->osproberEntries() )
    {
        if ( entry.path.startsWith( device->deviceNode() ) )
        {
            eList.append( entry );
        }
    }
    return eList;
}


bool
ChoicePage::isNextEnabled() const
{
    return m_nextEnabled;
}


bool
ChoicePage::calculateNextEnabled() const
{
    auto sm_p = m_beforePartitionBarsView ? m_beforePartitionBarsView->selectionModel() : nullptr;

    switch ( m_config->installChoice() )
    {
    case InstallChoice::NoChoice:
        cDebug() << "No partitioning choice has been made yet";
        return false;
    case InstallChoice::Replace:
    case InstallChoice::Alongside:
        if ( !( sm_p && sm_p->currentIndex().isValid() ) )
        {
            cDebug() << "No partition selected for alongside or replace";
            return false;
        }
        break;
    case InstallChoice::Erase:
    case InstallChoice::Manual:
        // Nothing to check for these
        break;
    }

    if ( m_isEfi
         && ( m_config->installChoice() == InstallChoice::Alongside
              || m_config->installChoice() == InstallChoice::Replace ) )
    {
        if ( m_core->efiSystemPartitions().count() == 0 )
        {
            cDebug() << "No EFI partition for alongside or replace";
            return false;
        }
    }

    if ( m_config->installChoice() != InstallChoice::Manual && m_encryptWidget->isVisible() )
    {
        switch ( m_encryptWidget->state() )
        {
        case EncryptWidget::Encryption::Unconfirmed:
            cDebug() << "No passphrase provided or passphrase mismatch.";
            return false;
        case EncryptWidget::Encryption::Disabled:
        case EncryptWidget::Encryption::Confirmed:
            // Checkbox not checked, **or** passphrases match
            break;
        }
    }

    return true;
}


void
ChoicePage::updateNextEnabled()
{
    bool enabled = calculateNextEnabled();

    if ( enabled != m_nextEnabled )
    {
        m_nextEnabled = enabled;
        Q_EMIT nextStatusChanged( enabled );
    }
}

void
ChoicePage::updateSwapChoicesTr()
{
    if ( !m_eraseSwapChoiceComboBox )
    {
        return;
    }

    static_assert( SwapChoice::NoSwap == 0, "Enum values out-of-sync" );
    for ( int index = 0; index < m_eraseSwapChoiceComboBox->count(); ++index )
    {
        bool ok = false;
        int value = 0;

        switch ( value = m_eraseSwapChoiceComboBox->itemData( index ).toInt( &ok ) )
        {
        // case 0:
        case SwapChoice::NoSwap:
            // toInt() returns 0 on failure, so check for ok
            if ( ok )  // It was explicitly set to 0
            {
                m_eraseSwapChoiceComboBox->setItemText( index, tr( "No Swap" ) );
            }
            else
            {
                cWarning() << "Box item" << index << m_eraseSwapChoiceComboBox->itemText( index )
                           << "has non-integer role.";
            }
            break;
        case SwapChoice::ReuseSwap:
            m_eraseSwapChoiceComboBox->setItemText( index, tr( "Reuse Swap" ) );
            break;
        case SwapChoice::SmallSwap:
            m_eraseSwapChoiceComboBox->setItemText( index, tr( "Swap (no Hibernate)" ) );
            break;
        case SwapChoice::FullSwap:
            m_eraseSwapChoiceComboBox->setItemText( index, tr( "Swap (with Hibernate)" ) );
            break;
        case SwapChoice::SwapFile:
            m_eraseSwapChoiceComboBox->setItemText( index, tr( "Swap to file" ) );
            break;
        default:
            cWarning() << "Box item" << index << m_eraseSwapChoiceComboBox->itemText( index ) << "has role" << value;
        }
    }
}

void
ChoicePage::updateChoiceButtonsTr()
{
    if ( m_somethingElseButton )
    {
        m_somethingElseButton->setText( tr( "<strong>Manual partitioning</strong><br/>"
                                            "You can create or resize partitions yourself." ) );
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

QWidget*
ChoicePage::createBootloaderPanel()
{
    QWidget* panelWidget = new QWidget;

    QHBoxLayout* mainLayout = new QHBoxLayout;
    panelWidget->setLayout( mainLayout );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
    QLabel* widgetLabel = new QLabel( panelWidget );
    mainLayout->addWidget( widgetLabel );
    widgetLabel->setText( tr( "Boot loader location:" ) );

    QComboBox* comboForBootloader = new QComboBox( panelWidget );
    comboForBootloader->setModel( m_core->bootLoaderModel() );

    // When the chosen bootloader device changes, we update the choice in the PCM
    connect( comboForBootloader,
             QOverload< int >::of( &QComboBox::currentIndexChanged ),
             this,
             [ this ]( int newIndex )
             {
                 QComboBox* bootloaderCombo = qobject_cast< QComboBox* >( sender() );
                 if ( bootloaderCombo )
                 {
                     QVariant var = bootloaderCombo->itemData( newIndex, BootLoaderModel::BootLoaderPathRole );
                     if ( !var.isValid() )
                     {
                         return;
                     }
                     m_core->setBootLoaderInstallPath( var.toString() );
                 }
             } );
    m_bootloaderComboBox = comboForBootloader;

    connect( m_core->bootLoaderModel(),
             &QAbstractItemModel::modelReset,
             [ this ]()
             {
                 if ( !m_bootloaderComboBox.isNull() )
                 {
                     Calamares::restoreSelectedBootLoader( *m_bootloaderComboBox, m_core->bootLoaderInstallPath() );
                 }
             } );
    connect(
        m_core,
        &PartitionCoreModule::deviceReverted,
        this,
        [ this ]( Device* )
        {
            if ( !m_bootloaderComboBox.isNull() )
            {
                if ( m_bootloaderComboBox->model() != m_core->bootLoaderModel() )
                {
                    m_bootloaderComboBox->setModel( m_core->bootLoaderModel() );
                }

                m_bootloaderComboBox->setCurrentIndex( m_lastSelectedDeviceIndex );
            }
        },
        Qt::QueuedConnection );
    // ^ Must be Queued so it's sure to run when the widget is already visible.

    mainLayout->addWidget( m_bootloaderComboBox );
    widgetLabel->setBuddy( m_bootloaderComboBox );
    mainLayout->addStretch();

    return panelWidget;
}
