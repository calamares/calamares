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

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "Branding.h"

#include <kpmcore/core/device.h>

#include <QBoxLayout>
#include <QButtonGroup>
#include <QComboBox>
#include <QDir>
#include <QLabel>
#include <QListView>



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
        m_previewBeforeLabel->setText( tr( "Before:" ) );
        m_previewAfterLabel->setText(  tr( "After:" ) );
    )

    m_previewBeforeFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    m_previewAfterFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
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
    QButtonGroup* grp = new QButtonGroup( this );

    m_alongsideButton = new PrettyRadioButton;
    m_alongsideButton->setIconSize( iconSize );
    m_alongsideButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionAlongside,
                                                               CalamaresUtils::Original,
                                                               iconSize ) );
    grp->addButton( m_alongsideButton->buttonWidget() );

    m_eraseButton = createEraseButton();

    m_eraseButton->setIconSize( iconSize );
    m_eraseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionEraseAuto,
                                                           CalamaresUtils::Original,
                                                           iconSize ) );
    grp->addButton( m_eraseButton->buttonWidget() );

    m_replaceButton = createReplaceButton();

    m_replaceButton->setIconSize( iconSize );
    m_replaceButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionReplaceOs,
                                                             CalamaresUtils::Original,
                                                             iconSize ) );
    grp->addButton( m_replaceButton->buttonWidget() );

    m_itemsLayout->addWidget( m_alongsideButton );
    m_itemsLayout->addWidget( m_replaceButton );
    m_itemsLayout->addWidget( m_eraseButton );
    m_itemsLayout->setSpacing( CalamaresUtils::defaultFontHeight() / 2 );

    QFrame* hLine = new QFrame;
    hLine->setFrameStyle( QFrame::HLine );
    m_itemsLayout->addWidget( hLine );

    m_somethingElseButton = new PrettyRadioButton;
    CALAMARES_RETRANSLATE(
        m_somethingElseButton->setText( tr( "<strong>Manual partitioning</strong><br/>"
                                            "You can create or resize partitions yourself, or choose "
                                            "multiple partitions for %1." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
    )
    m_somethingElseButton->setIconSize( iconSize );
    m_somethingElseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionManual,
                                                                   CalamaresUtils::Original,
                                                                   iconSize ) );
    m_itemsLayout->addWidget( m_somethingElseButton );
    grp->addButton( m_somethingElseButton->buttonWidget() );

    m_itemsLayout->addStretch();

    connect( m_alongsideButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
        {
            m_choice = Alongside;
            setNextEnabled( true );
            emit actionChosen();
        }
    } );

    connect( m_eraseButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
        {
            m_choice = Erase;
            setNextEnabled( true );
            emit actionChosen();
        }
    } );

    connect( m_replaceButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
        {
            m_choice = Replace;
            setNextEnabled( true );
            emit actionChosen();
        }
    } );

    connect( m_somethingElseButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
        {
            m_choice = Manual;
            setNextEnabled( true );
            emit actionChosen();
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
            applyActionChoice( currd, currentChoice() );
            updateActionChoicePreview( currd, currentChoice() );
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
    auto updateBootloaderDevice = [bcb]( Device* currd )
    {
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
            updateBootloaderDevice( selectedDevice() );
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


ExpandableRadioButton*
ChoicePage::createReplaceButton()
{
    ExpandableRadioButton* replaceButton = new ExpandableRadioButton;
    QWidget* replaceContainer = new QWidget;
    QVBoxLayout* mainReplaceLayout = new QVBoxLayout;
    replaceContainer->setLayout( mainReplaceLayout );
    CalamaresUtils::unmarginLayout( mainReplaceLayout );
    ReplaceWidget* replaceWidget = new ReplaceWidget( m_core, m_drivesCombo );
    mainReplaceLayout->addWidget( replaceWidget );

    if ( !m_isEfi )
    {
        QHBoxLayout* bootloaderLayout = new QHBoxLayout;
        bootloaderLayout->setContentsMargins( 0, 0, 0, 0 );
        QLabel* eraseBootloaderLabel = new QLabel( replaceButton );
        bootloaderLayout->addWidget( eraseBootloaderLabel );
        eraseBootloaderLabel->setText( tr( "Boot loader location:" ) );

        QComboBox* eraseBootloaderCombo = createBootloaderComboBox( replaceButton );
        bootloaderLayout->addWidget( eraseBootloaderCombo );
        eraseBootloaderLabel->setBuddy( eraseBootloaderCombo );
        bootloaderLayout->addStretch();

        mainReplaceLayout->addLayout( bootloaderLayout );
    }

    replaceButton->setExpandableWidget( replaceContainer );

    return replaceButton;
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
    Device* currd = selectedDevice();

    if ( m_core->isDirty() )
        m_core->clearJobs();

    // The device should only be nullptr immediately after a PCM reset.
    // applyDeviceChoice() will be called again momentarily as soon as we handle the
    // PartitionCoreModule::reverted signal.
    if ( !currd )
        return;

    updateDeviceStatePreview( currd );
    // Preview setup done. Now we show/hide choices as needed.

    setupActions( currd );

    m_lastSelectedDeviceIndex = m_drivesCombo->currentIndex();

    emit actionChosen();
    emit deviceChosen( currd );
}


void
ChoicePage::applyActionChoice( Device* currentDevice, ChoicePage::Choice choice )
{
    switch ( choice )
    {
    case Erase:
        if ( m_core->isDirty() )
            m_core->clearJobs();

        PartitionActions::doAutopartition( m_core, selectedDevice() );
        break;
    case Replace:
    case NoChoice:
    case Manual:
        break;
    }
}


/**
 * @brief ChoicePage::updateDeviceStatePreview clears and rebuilds the contents of the
 *      preview widget for the current on-disk state. This also triggers a rescan in the
 *      PCM to get a Device* copy that's unaffected by subsequent PCM changes.
 * @param currentDevice a pointer to the selected Device.
 */
void
ChoicePage::updateDeviceStatePreview( Device* currentDevice )
{
    //FIXME: this needs to be made async because the rescan can block the UI thread for
    //       a while. --Teo 10/2015
    Q_ASSERT( currentDevice );
    QMutexLocker locker( &m_previewsMutex );

    cDebug() << "Updating partitioning state widgets.";
    qDeleteAll( m_previewBeforeFrame->children() );
    m_previewBeforeFrame->layout()->deleteLater();

    QVBoxLayout* layout = new QVBoxLayout;
    m_previewBeforeFrame->setLayout( layout );
    CalamaresUtils::unmarginLayout( layout );
    layout->setSpacing( 6 );

    PartitionBarsView* preview = new PartitionBarsView( m_previewBeforeFrame );
    PartitionLabelsView* previewLabels = new PartitionLabelsView( m_previewBeforeFrame );

    Device* deviceBefore = m_core->createImmutableDeviceCopy( currentDevice );

    PartitionModel* model = new PartitionModel( preview );
    model->init( deviceBefore, m_core->osproberEntries() );

    // The QObject parents tree is meaningful for memory management here,
    // see qDeleteAll above.
    deviceBefore->setParent( model );
    model->setParent( preview );

    preview->setModel( model );
    previewLabels->setModel( model );
    layout->addWidget( preview );
    layout->addWidget( previewLabels );
}


/**
 * @brief ChoicePage::updateActionChoicePreview clears and rebuilds the contents of the
 *      preview widget for the current PCM-proposed state. No rescans here, this should
 *      be immediate.
 * @param currentDevice a pointer to the selected Device.
 * @param choice the chosen partitioning action.
 */
void
ChoicePage::updateActionChoicePreview( Device* currentDevice, ChoicePage::Choice choice )
{
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
        // split widget goes here
        //label->setText( tr( "Drag to split:" ) );

        break;
    case Erase:
    case Replace:
        {
            PartitionBarsView* preview = new PartitionBarsView( m_previewAfterFrame );
            PartitionLabelsView* previewLabels = new PartitionLabelsView( m_previewAfterFrame );
            previewLabels->setCustomNewRootLabel( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortProductName ) );

            PartitionModel* model = new PartitionModel( preview );
            model->init( currentDevice, m_core->osproberEntries() );

            // The QObject parents tree is meaningful for memory management here,
            // see qDeleteAll above.
            model->setParent( preview );
            preview->setModel( model );
            previewLabels->setModel( model );
            layout->addWidget( preview );
            layout->addWidget( previewLabels );

            m_previewAfterFrame->show();
            break;
        }
    case NoChoice:
    case Manual:
        m_previewAfterFrame->hide();
        break;
    }
}


/**
 * @brief ChoicePage::setupActions happens every time a new Device* is selected in the
 *      device picker. Sets up the text and visibility of the partitioning actions based
 *      on the currently selected Device*, bootloader and os-prober output.
 * @param currentDevice
 */
void
ChoicePage::setupActions( Device *currentDevice )
{
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
                                        "This will <font color=\"red\">delete</font> all the data "
                                        "currently present on %1 (if any), including programs, "
                                        "documents, photos, music, and other files." )
                                    .arg( currentDevice->deviceNode() ) );
        )

        m_replaceButton->hide();
        m_alongsideButton->hide();
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
                                                "The installer will shrink a volume to make room for %1." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all the data "
                                            "currently present on %1 (if any), including programs, "
                                            "documents, photos, music, and other files." )
                                        .arg( currentDevice->deviceNode() ) );


                m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                              "You will be offered a choice of which partition to erase." ) );
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
                                                "The installer will shrink a volume to make room for %1." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all the data "
                                            "currently present on %1 (if any), including programs, "
                                            "documents, photos, music, and other files." )
                                        .arg( currentDevice->deviceNode() ) );

                m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                              "You will be offered a choice of which partition to erase." ) );
            )
        }
        if ( !osproberEntriesForCurrentDevice.first().canBeResized )
            m_alongsideButton->hide();
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
                                            "The installer will shrink a volume to make room for %1." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );

            m_eraseButton->setText( tr( "<strong>Erase disk</strong><br/>"
                                        "This will <font color=\"red\">delete</font> all the data "
                                        "currently present on %1 (if any), including programs, "
                                        "documents, photos, music, and other files." )
                                    .arg( currentDevice->deviceNode() ) );

            m_replaceButton->setText( tr( "<strong>Replace a partition</strong><br/>"
                                          "You will be offered a choice of which partition to erase." ) );
        )

        if ( !atLeastOneCanBeResized )
            m_alongsideButton->hide();
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

