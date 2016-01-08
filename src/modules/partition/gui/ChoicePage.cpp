/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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
#include "core/PartitionActions.h"
#include "core/PartitionCoreModule.h"
#include "core/DeviceModel.h"
#include "core/PartitionModel.h"
#include "core/OsproberEntry.h"

#include "ReplaceWidget.h"
#include "PrettyRadioButton.h"
#include "ExpandableRadioButton.h"
#include "PartitionBarsView.h"
#include "PartitionLabelsView.h"
#include "DeviceInfoWidget.h"
#include "ScanningDialog.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "Branding.h"
#include "core/KPMHelpers.h"

#include <kpmcore/core/device.h>

#include <QBoxLayout>
#include <QButtonGroup>
#include <QComboBox>
#include <QDir>
#include <QLabel>
#include <QListView>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>



/**
 * @brief ChoicePage::ChoicePage is the default constructor. Called on startup as part of
 *      the module loading code path.
 * @param compactMode if true, the drive selector will be a combo box on top, otherwise it
 *      will show up as a list view.
 * @param parent the QWidget parent.
 */
ChoicePage::ChoicePage( QWidget* parent )
    : QWidget( parent )
    , m_choice( NoChoice )
    , m_nextEnabled( false )
    , m_core( nullptr )
    , m_alongsideButton( nullptr )
    , m_eraseButton( nullptr )
    , m_replaceButton( nullptr )
    , m_somethingElseButton( nullptr )
    , m_deviceInfoWidget( nullptr )
    , m_lastSelectedDeviceIndex( -1 )
    , m_isEfi( false )
    , m_beforePartitionBarsView( nullptr )
    , m_beforePartitionLabelsView( nullptr )
{
    setupUi( this );

    // Set up drives combo
    m_mainLayout->setDirection( QBoxLayout::TopToBottom );
    m_drivesLayout->setDirection( QBoxLayout::LeftToRight );
    m_drivesCombo = new QComboBox( this );
    m_mainLayout->setStretchFactor( m_drivesLayout, 0 );
    m_mainLayout->setStretchFactor( m_rightLayout, 1 );
    m_drivesLabel->setBuddy( m_drivesCombo );

    m_drivesLayout->addWidget( m_drivesCombo );

    m_drivesLayout->addStretch();
    m_deviceInfoWidget = new DeviceInfoWidget;
    m_drivesLayout->addWidget( m_deviceInfoWidget );

    m_messageLabel->setWordWrap( true );
    m_messageLabel->hide();

    CalamaresUtils::unmarginLayout( m_itemsLayout );

    // Drive selector + preview
    CALAMARES_RETRANSLATE(
        retranslateUi( this );
        m_drivesLabel->setText( tr( "Pick a storage de&vice:" ) );
        m_previewBeforeLabel->setText( tr( "Device:" ) );
        m_previewAfterLabel->setText(  tr( "After:" ) );
    )

    m_previewBeforeFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    m_previewAfterFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    m_previewAfterLabel->hide();
    m_previewAfterFrame->hide();
    // end
}


ChoicePage::~ChoicePage()
{}


/**
 * @brief ChoicePage::init runs when the PartitionViewStep and the PartitionCoreModule are
 *      ready. Sets up the rest of the UI based on os-prober output.
 * @param core the PartitionCoreModule pointer.
 * @param osproberEntries the output of os-prober, cleaned up and structured.
 */
void
ChoicePage::init( PartitionCoreModule* core )
{
    m_core = core;
    m_isEfi = QDir( "/sys/firmware/efi/efivars" ).exists();

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

    ChoicePage::applyDeviceChoice();
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

    QSize iconSize( CalamaresUtils::defaultIconSize().width() * 2.5,
                    CalamaresUtils::defaultIconSize().height() * 2.5 );
    m_grp = new QButtonGroup( this );

    m_alongsideButton = new PrettyRadioButton;
    m_alongsideButton->setIconSize( iconSize );
    m_alongsideButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionAlongside,
                                                               CalamaresUtils::Original,
                                                               iconSize ) );
    m_grp->addButton( m_alongsideButton->buttonWidget(), Alongside );

    m_eraseButton = createEraseButton();

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

    m_itemsLayout->addWidget( m_alongsideButton );
    m_itemsLayout->addWidget( m_replaceButton );
    m_itemsLayout->addWidget( m_eraseButton );
    m_itemsLayout->setSpacing( CalamaresUtils::defaultFontHeight() / 2 );

    m_somethingElseButton = new PrettyRadioButton;
    CALAMARES_RETRANSLATE(
        m_somethingElseButton->setText( tr( "<strong>Manual partitioning</strong><br/>"
                                            "You can create or resize partitions yourself." ) );
    )
    m_somethingElseButton->setIconSize( iconSize );
    m_somethingElseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionManual,
                                                                   CalamaresUtils::Original,
                                                                   iconSize ) );
    m_itemsLayout->addWidget( m_somethingElseButton );
    m_grp->addButton( m_somethingElseButton->buttonWidget(), Manual );

    m_itemsLayout->addStretch();

    connect( m_grp, static_cast< void( QButtonGroup::* )( int, bool ) >( &QButtonGroup::buttonToggled ),
             this, [ this ]( int id, bool checked )
    {
        if ( checked )  // An action was picked.
        {
            m_choice = static_cast< Choice >( id );
            if ( m_choice == Replace )
            {
                setNextEnabled( false );
            }
            else
            {
                setNextEnabled( true );
            }
            emit actionChosen();
        }
        else    // An action was unpicked, either on its own or because of another selection.
        {
            if ( m_grp->checkedButton() == nullptr )  // If no other action is chosen, we must
            {                                       // set m_choice to NoChoice and reset previews.
                m_choice == NoChoice;
                setNextEnabled( false );
                emit actionChosen();
            }
        }
    } );

    m_rightLayout->setStretchFactor( m_itemsLayout, 1 );
    m_rightLayout->setStretchFactor( m_previewBeforeFrame, 0 );
    m_rightLayout->setStretchFactor( m_previewAfterFrame, 0 );

    connect( this, &ChoicePage::actionChosen,
             this, [=]
    {
        Device* currd = selectedDevice();
        if ( currd )
        {
            applyActionChoice( currentChoice() );
        }
    } );
}


QComboBox*
ChoicePage::createBootloaderComboBox( ExpandableRadioButton* parentButton )
{
    QComboBox* bcb = new QComboBox;
    bcb->setModel( m_core->bootLoaderModel() );

    // When the chosen bootloader device changes, we update the choice in the PCM
    connect( bcb, static_cast< void (QComboBox::*)(int) >( &QComboBox::currentIndexChanged ),
             [=]( int newIndex )
    {
        QVariant var = bcb->itemData( newIndex, BootLoaderModel::BootLoaderPathRole );
        if ( !var.isValid() )
            return;
        m_core->setBootLoaderInstallPath( var.toString() );
    } );

    // If the user picks a new device, we update the bootloader choice to that
    // same device automatically.
    auto updateBootloaderDevice = [bcb, this]()
    {
        Device* currd = selectedDevice();
        if ( !currd )
            return;
        QString devPath = currd->deviceNode();
        for ( int i = 0; i < bcb->count(); ++i )
        {
            QVariant var = bcb->itemData( i , BootLoaderModel::BootLoaderPathRole );
            if ( !var.isValid() )
                continue;
            if ( var.toString() == devPath )
            {
                bcb->setCurrentIndex( i );
                return;
            }
        }
    };
    connect( this, &ChoicePage::deviceChosen,
             this, updateBootloaderDevice );
    connect( parentButton, &ExpandableRadioButton::expanded,
             this, [=]( bool expanded )
    {
        if ( expanded )
            updateBootloaderDevice();
    }, Qt::QueuedConnection );
    connect( m_core, &PartitionCoreModule::deviceReverted,
             this, [ this, bcb ]( Device* dev )
    {
        if ( bcb->model() != m_core->bootLoaderModel() )
            bcb->setModel( m_core->bootLoaderModel() );
        bcb->setCurrentIndex( m_lastSelectedDeviceIndex );
    }, Qt::QueuedConnection );
    // ^ Must be Queued so it's sure to run when the widget is already visible.

    return bcb;
}


ExpandableRadioButton*
ChoicePage::createEraseButton()
{
    ExpandableRadioButton* eraseButton = new ExpandableRadioButton;
    if ( !m_isEfi )
    {
        QWidget* eraseWidget = new QWidget;

        QHBoxLayout* eraseLayout = new QHBoxLayout;
        eraseWidget->setLayout( eraseLayout );
        eraseLayout->setContentsMargins( 0, 0, 0, 0 );
        QLabel* eraseBootloaderLabel = new QLabel( eraseWidget );
        eraseLayout->addWidget( eraseBootloaderLabel );
        eraseBootloaderLabel->setText( tr( "Boot loader location:" ) );

        QComboBox* eraseBootloaderCombo = createBootloaderComboBox( eraseButton );
        eraseLayout->addWidget( eraseBootloaderCombo );
        eraseBootloaderLabel->setBuddy( eraseBootloaderCombo );
        eraseLayout->addStretch();

        eraseButton->setExpandableWidget( eraseWidget );
    }
    return eraseButton;
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
        return;

    if ( m_core->isDirty() )
    {
        m_core->revertDevice( selectedDevice() );
    }

    Device* currd = selectedDevice();


    // The device should only be nullptr immediately after a PCM reset.
    // applyDeviceChoice() will be called again momentarily as soon as we handle the
    // PartitionCoreModule::reverted signal.
    if ( !currd )
        return;

    updateDeviceStatePreview();
    // Preview setup done. Now we show/hide choices as needed.

    setupActions();

    m_lastSelectedDeviceIndex = m_drivesCombo->currentIndex();

    emit actionChosen();
    emit deviceChosen();
}


void
ChoicePage::applyActionChoice( ChoicePage::Choice choice )
{
    m_beforePartitionBarsView->selectionModel()->
            disconnect( SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ) );
    m_beforePartitionBarsView->selectionModel()->clearSelection();
    m_beforePartitionBarsView->selectionModel()->clearCurrentIndex();

    switch ( choice )
    {
    case Erase:
        if ( m_core->isDirty() )
        {
            ScanningDialog::run( QtConcurrent::run( [ = ]
            {
                QMutexLocker locker( &m_coreMutex );
                m_core->revertDevice( selectedDevice() );
            } ),
            [ = ]
            {
                PartitionActions::doAutopartition( m_core, selectedDevice() );
                emit deviceChosen();
            },
            this );
        }
        else
        {
            PartitionActions::doAutopartition( m_core, selectedDevice() );
            emit deviceChosen();
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
        setNextEnabled( !m_beforePartitionBarsView->selectionModel()->selectedRows().isEmpty() );

        connect( m_beforePartitionBarsView->selectionModel(), SIGNAL( currentRowChanged( QModelIndex, QModelIndex ) ),
                 this, SLOT( doReplaceSelectedPartition( QModelIndex, QModelIndex ) ),
                 Qt::UniqueConnection );
        break;
    case NoChoice:
    case Manual:
        break;
    }
    updateActionChoicePreview( currentChoice() );
}


void
ChoicePage::doReplaceSelectedPartition( const QModelIndex& current,
                                        const QModelIndex& previous )
{
    if ( !current.isValid() )
        return;

    ScanningDialog::run( QtConcurrent::run( [ = ]
    {
        QMutexLocker locker( &m_coreMutex );

        if ( m_core->isDirty() )
        {
            m_core->revertDevice( selectedDevice() );
        }
        // We can't use the PartitionPtrRole because we need to make changes to the
        // main DeviceModel, not the immutable copy.
        QString partPath = current.data( PartitionModel::PartitionPathRole ).toString();
        Partition* partition = KPMHelpers::findPartitionByPath( { selectedDevice() },
                                                                partPath );
        if ( partition )
            PartitionActions::doReplacePartition( m_core,
                                                  selectedDevice(),
                                                  partition );
    } ),
    [=]
    {
        setNextEnabled( !m_beforePartitionBarsView->selectionModel()->selectedRows().isEmpty() );
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
    m_previewBeforeFrame->layout()->deleteLater();

    QVBoxLayout* layout = new QVBoxLayout;
    m_previewBeforeFrame->setLayout( layout );
    CalamaresUtils::unmarginLayout( layout );
    layout->setSpacing( 6 );

    m_beforePartitionBarsView = new PartitionBarsView( m_previewBeforeFrame );
    m_beforePartitionLabelsView = new PartitionLabelsView( m_previewBeforeFrame );

    Device* deviceBefore = m_core->createImmutableDeviceCopy( currentDevice );

    PartitionModel* model = new PartitionModel( m_beforePartitionBarsView );
    model->init( deviceBefore, m_core->osproberEntries() );

    // The QObject parents tree is meaningful for memory management here,
    // see qDeleteAll above.
    deviceBefore->setParent( model );
    model->setParent( m_beforePartitionBarsView );

    m_beforePartitionBarsView->setModel( model );
    m_beforePartitionLabelsView->setModel( model );

    // Make the bars and labels view use the same selectionModel.
    auto sm = m_beforePartitionLabelsView->selectionModel();
    m_beforePartitionLabelsView->setSelectionModel( m_beforePartitionBarsView->selectionModel() );
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
ChoicePage::updateActionChoicePreview( ChoicePage::Choice choice )
{
    Device* currentDevice = selectedDevice();
    Q_ASSERT( currentDevice );

    QMutexLocker locker( &m_previewsMutex );

    cDebug() << "Updating partitioning preview widgets.";
    qDeleteAll( m_previewAfterFrame->children() );
    m_previewAfterFrame->layout()->deleteLater();

    QVBoxLayout* layout = new QVBoxLayout;
    m_previewAfterFrame->setLayout( layout );
    CalamaresUtils::unmarginLayout( layout );
    layout->setSpacing( 6 );

    switch ( choice )
    {
    case Alongside:
        m_previewBeforeLabel->setText( tr( "Device:" ) );
        m_previewAfterLabel->hide();
        // split widget goes here
        //label->setText( tr( "Drag to split:" ) );
        m_selectLabel->hide();

        break;
    case Erase:
    case Replace:
        {
            m_previewBeforeLabel->setText( tr( "Before:" ) );
            m_afterPartitionBarsView = new PartitionBarsView( m_previewAfterFrame );
            m_afterPartitionLabelsView = new PartitionLabelsView( m_previewAfterFrame );
            m_afterPartitionLabelsView->setCustomNewRootLabel( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::BootloaderEntryName ) );

            PartitionModel* model = m_core->partitionModelForDevice( selectedDevice() );

            // The QObject parents tree is meaningful for memory management here,
            // see qDeleteAll above.
            m_afterPartitionBarsView->setModel( model );
            m_afterPartitionLabelsView->setModel( model );
            m_afterPartitionBarsView->setSelectionMode( QAbstractItemView::NoSelection );
            m_afterPartitionLabelsView->setSelectionMode( QAbstractItemView::NoSelection );

            layout->addWidget( m_afterPartitionBarsView );
            layout->addWidget( m_afterPartitionLabelsView );

            m_previewAfterFrame->show();
            m_previewAfterLabel->show();

            if ( m_choice == Erase )
                m_selectLabel->hide();
            else
            {
                m_selectLabel->show();
                m_selectLabel->setText( tr( "<strong>Select which partition to replace</strong>" ) );
            }

            break;
        }
    case NoChoice:
    case Manual:
        m_selectLabel->hide();
        m_previewAfterFrame->hide();
        m_previewBeforeLabel->setText( tr( "Device:" ) );
        m_previewAfterLabel->hide();
        break;
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

    if ( currentDevice->partitionTable() )
        m_deviceInfoWidget->setPartitionTableType( currentDevice->partitionTable()->type() );
    else
        m_deviceInfoWidget->setPartitionTableType( PartitionTable::unknownTableType );

    if ( osproberEntriesForCurrentDevice.count() == 0 )
    {
        CALAMARES_RETRANSLATE(
            m_messageLabel->setText( tr( "This storage device does not seem to have an operating system on it. "
                                         "What would you like to do?<br/>"
                                         "You will be able to review and confirm your choices "
                                         "before any change is made to the storage device." ) );

            m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                        "This will <font color=\"red\">delete</font> all data "
                                        "currently present on the selected storage device." ) );
        )

        m_replaceButton->hide();
        m_alongsideButton->hide();
        m_replaceButton->buttonWidget()->setChecked( false );
        m_alongsideButton->buttonWidget()->setChecked( false );
    }
    else if ( osproberEntriesForCurrentDevice.count() == 1 )
    {
        QString osName = osproberEntriesForCurrentDevice.first().prettyName;

        if ( !osName.isEmpty() )
        {
            CALAMARES_RETRANSLATE(
                m_messageLabel->setText( tr( "This storage device has %1 on it. "
                                             "What would you like to do?<br/>"
                                             "You will be able to review and confirm your choices "
                                             "before any change is made to the storage device." )
                                            .arg( osName ) );

                m_alongsideButton->setText( tr( "<strong>Install alongside</strong><br/>"
                                                "The installer will shrink a partition to make room for %1." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all data "
                                            "currently present on the selected storage device." ) );


                m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                              "Replaces a partition with %1." )
                                          .arg( Calamares::Branding::instance()->
                                                string( Calamares::Branding::ShortVersionedName ) ) );
            )
        }
        else
        {
            CALAMARES_RETRANSLATE(
                m_messageLabel->setText( tr( "This storage device already has an operating system on it. "
                                             "What would you like to do?<br/>"
                                             "You will be able to review and confirm your choices "
                                             "before any change is made to the storage device." ) );

                m_alongsideButton->setText( tr( "<strong>Install alongside</strong><br/>"
                                                "The installer will shrink a partition to make room for %1." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all data "
                                            "currently present on the selected storage device." ) );

                m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                              "Replaces a partition with %1." )
                                          .arg( Calamares::Branding::instance()->
                                                string( Calamares::Branding::ShortVersionedName ) ) );
            )
        }

        m_replaceButton->show();

        if ( osproberEntriesForCurrentDevice.first().canBeResized )
            m_alongsideButton->show();
        else
        {
            m_alongsideButton->hide();
            m_alongsideButton->buttonWidget()->setChecked( false );
        }
    }
    else
    {
        // osproberEntriesForCurrentDevice has at least 2 items.

        bool atLeastOneCanBeResized = false;

        foreach ( const OsproberEntry& entry, osproberEntriesForCurrentDevice )
        {
            if ( entry.canBeResized )
            {
                atLeastOneCanBeResized = true;
                break;
            }
        }

        CALAMARES_RETRANSLATE(
            m_messageLabel->setText( tr( "This storage device has multiple operating systems on it. "
                                         "What would you like to do?<br/>"
                                         "You will be able to review and confirm your choices "
                                         "before any change is made to the storage device." ) );

            m_alongsideButton->setText( tr( "<strong>Install alongside</strong><br/>"
                                            "The installer will shrink a partition to make room for %1." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );

            m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                        "This will <font color=\"red\">delete</font> all data "
                                        "currently present on the selected storage device." ) );

            m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                          "Replaces a partition with %1." )
                                      .arg( Calamares::Branding::instance()->
                                            string( Calamares::Branding::ShortVersionedName ) ) );
        )

        m_replaceButton->show();

        if ( atLeastOneCanBeResized )
            m_alongsideButton->show();
        else
        {
            m_alongsideButton->hide();
            m_alongsideButton->buttonWidget()->setChecked( false );
        }
    }

    bool isEfi = QDir( "/sys/firmware/efi/efivars" ).exists();
    bool efiSystemPartitionFound = !m_core->efiSystemPartitions().isEmpty();

    if ( isEfi && !efiSystemPartitionFound )
    {
        cDebug() << "WARNING: system is EFI but there's no EFI system partition, "
                    "DISABLING alongside and replace features.";
        m_alongsideButton->hide();
        m_replaceButton->hide();
    }
}


OsproberEntryList
ChoicePage::getOsproberEntriesForDevice( Device* device ) const
{
    OsproberEntryList eList;
    foreach ( const OsproberEntry& entry, m_core->osproberEntries() )
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


ChoicePage::Choice
ChoicePage::currentChoice() const
{
    return m_choice;
}


void
ChoicePage::setNextEnabled( bool enabled )
{
    if ( enabled == m_nextEnabled )
        return;

    m_nextEnabled = enabled;
    emit nextStatusChanged( enabled );
}

