/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd
 *   SPDX-FileCopyrightText: 2022 Aditya Mehra <aix.m@outlook.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "ChoicePageQml.h"
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

#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "partition/PartitionIterator.h"
#include "partition/PartitionQuery.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "utils/Units.h"

#include <kpmcore/core/device.h>
#ifdef WITH_KPMCORE4API
#include <kpmcore/core/softwareraid.h>
#endif

#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

using CalamaresUtils::Partition::findPartitionByPath;
using CalamaresUtils::Partition::isPartitionFreeSpace;
using CalamaresUtils::Partition::PartitionIterator;
using InstallChoice = Config::InstallChoice;
using SwapChoice = Config::SwapChoice;

/**
 * @brief ChoicePage::ChoicePage is the default constructor. Called on startup as part of
 *      the module loading code path.
 * @param parent the QObject parent.
 */
ChoicePageQml::ChoicePageQml( Config* config, QObject* parent )
    : QObject( parent )
    , m_config( config )
    , m_nextEnabled( false )
    , m_core( nullptr )
    , m_isEfi( false )
    , m_enableEncryptionWidget( true )
    , m_partitionModel( new PartitionModel( this ) )
{
    auto gs = Calamares::JobQueue::instance()->globalStorage();
    m_enableEncryptionWidget = gs->value( "enableLuksAutomatedPartitioning" ).toBool();
    gs->insert( "reuseHome", false );
}

void
ChoicePageQml::init( PartitionCoreModule* core )
{
    m_core = core;
    m_isEfi = PartUtils::isEfiSystem();

    ChoicePageQml::applyDeviceChoice();
}

void 
ChoicePageQml::setDeviceIndex( int index )
{
    m_deviceIndex = index;
    ChoicePageQml::applyDeviceChoice();
}

/**
 * @brief ChoicePage::selectedDevice queries the device picker (which may be a combo or
 *      a list view) to get a pointer to the currently selected Device.
 * @return a Device pointer, valid in the current state of the PCM, or nullptr if
 *      something goes wrong.
 */
Device*
ChoicePageQml::selectedDevice()
{
    Device* currentDevice = nullptr;
    currentDevice
        = m_core->deviceModel()->deviceForIndex( m_core->deviceModel()->index( m_deviceIndex ) );

    return currentDevice;
}

void 
ChoicePageQml::setInstallChoice(int choice){
    if(choice == InstallChoiceType::EraseChoice){
        m_config->setInstallChoice( InstallChoice::Erase );
    } else if(choice == InstallChoiceType::ReplaceChoice){
        m_config->setInstallChoice( InstallChoice::Replace );
    } else if(choice == InstallChoiceType::AlongSideChoice){
        m_config->setInstallChoice( InstallChoice::Alongside );
    } else if(choice == InstallChoiceType::ManualChoice){
        m_config->setInstallChoice( InstallChoice::Manual );
    }

    Device* currd = selectedDevice();
    if ( currd )
    {
        applyActionChoice( m_config->installChoice() );
    }
}

void 
ChoicePageQml::setPartitionModelForDevice()
{
    Device* currd = selectedDevice();
    if ( !currd )
    {
        return;
    }
    OsproberEntryList osproberEntriesForCurrentDevice = getOsproberEntriesForDevice( currd );
    m_partitionModel->init(currd, osproberEntriesForCurrentDevice);
}

PartitionModel* 
ChoicePageQml::partitionModel() const
{
    return m_partitionModel;
}

QVariantList 
ChoicePageQml::getEraseSwapChoices() const
{
    auto choices = m_config->swapChoices();
    QVariantList qvChoices;
    QVariantMap qvChoice;

    // Check which choices are supported by the current device
    for ( auto c : choices )
    {
        if ( c == SwapChoice::NoSwap )
        {
            qvChoice["label"] = tr( "No swap" );
            qvChoice["value"] = c;
            qvChoices.append( qvChoice );
        }
        if ( c == SwapChoice::ReuseSwap )
        {
            qvChoice["label"] = tr( "Reuse swap" );
            qvChoice["value"] = c;
            qvChoices.append( qvChoice );
        }
        if ( c == SwapChoice::SmallSwap )
        {
            qvChoice["label"] = tr( "Swap (no Hibernate)" );
            qvChoice["value"] = c;
            qvChoices.append( qvChoice );
        }
        if ( c == SwapChoice::FullSwap )
        {
            qvChoice["label"] = tr( "Swap (with Hibernate)" );
            qvChoice["value"] = c;
            qvChoices.append( qvChoice );
        }
        if ( c == SwapChoice::SwapFile )
        {
            qvChoice["label"] = tr( "Swap to file" );
            qvChoice["value"] = c;
            qvChoices.append( qvChoice );
        }
    }
    
    // If no choices are supported, only offer the NoSwap and full swap choices
    // As done in the partition config 
    if ( qvChoices.isEmpty() )
    {
        qvChoice["label"] = tr( "No swap" );
        qvChoice["value"] = SwapChoice::NoSwap;
        qvChoices.append( qvChoice );
        qvChoice["label"] = tr( "Swap (with Hibernate)" );
        qvChoice["value"] = SwapChoice::FullSwap;
        qvChoices.append( qvChoice );
    }

    return qvChoices;   
}

int 
ChoicePageQml::getInitialSwapChoice() const
{
    return m_config->initialSwapChoice();
}

void 
ChoicePageQml::setSwapChoice(int selectedSwapChoice)
{
     if ( selectedSwapChoice == SwapChoice::NoSwap ) {
        m_config->setSwapChoice( SwapChoice::NoSwap );
     } else if ( selectedSwapChoice == SwapChoice::ReuseSwap ) {
        m_config->setSwapChoice( SwapChoice::ReuseSwap );
     } else if ( selectedSwapChoice == SwapChoice::SmallSwap ) {
        m_config->setSwapChoice( SwapChoice::SmallSwap );
     } else if ( selectedSwapChoice == SwapChoice::FullSwap ) {
        m_config->setSwapChoice( SwapChoice::FullSwap );
     } else if ( selectedSwapChoice == SwapChoice::SwapFile ) {
        m_config->setSwapChoice( SwapChoice::SwapFile );
     }
     onActionChanged();
}

bool 
ChoicePageQml::encryptWidgetEnabled() const
{
    return m_enableEncryptionWidget;
}

void 
ChoicePageQml::setEncryptionSelected(bool enabled)
{
    m_encryptionSelected = enabled;
    
    if ( m_config->installChoice() == InstallChoice::Erase )
    {
        if (m_encryptionSelected)
        {
            applyActionChoice( m_config->installChoice() );
        }
    }
    updateNextEnabled();
}

void 
ChoicePageQml::setEncryptionPhrase(const QString& phrase)
{
    m_encryptPassphrase = phrase;
}

/**
 * @brief ChoicePage::applyDeviceChoice handler for the selected event of the device
 *      picker. Calls ChoicePage::selectedDevice() to get the current Device*, then
 *      updates the preview widget for the on-disk state (calls ChoicePage::
 *      updateDeviceStatePreview()) and finally sets up the available actions and their
 *      text by calling ChoicePage::setupActions().
 */
void
ChoicePageQml::applyDeviceChoice()
{
    if ( !selectedDevice() )
    {
        return;
    }

    if ( m_core->isDirty() )
    {
        emit scanningDialogShow();
        QFuture<void> future = 
            QtConcurrent::run(
                [ = ]
                {
                    QMutexLocker locker( &m_coreMutex );
                    m_core->revertAllDevices();
                } );
        // wait for the future to finish
        future.waitForFinished();
        emit scanningDialogHide();
        continueApplyDeviceChoice();
    }
    else
    {
        continueApplyDeviceChoice();
    }
}


void
ChoicePageQml::continueApplyDeviceChoice()
{
    Device* currd = selectedDevice();

    // The device should only be nullptr immediately after a PCM reset.
    // applyDeviceChoice() will be called again momentarily as soon as we handle the
    // PartitionCoreModule::reverted signal.
    if ( !currd )
    {
        return;
    }

    // Preview setup done. Now we show/hide choices as needed.
    setupActions();

    cDebug() << "Previous device" << m_lastSelectedDeviceIndex << "new device" << m_deviceIndex;
    if ( m_lastSelectedDeviceIndex != m_deviceIndex )
    {
        m_lastSelectedDeviceIndex = m_deviceIndex;
        m_lastSelectedActionIndex = -1;
        m_config->setInstallChoice( m_config->initialInstallChoice() );
    }

    Q_EMIT actionChosen();
    Q_EMIT deviceChosen();
}


void
ChoicePageQml::onActionChanged()
{
    Device* currd = selectedDevice();
    if ( currd )
    {
        applyActionChoice( m_config->installChoice() );
    }
}

void
ChoicePageQml::applyActionChoice( InstallChoice choice )
{
    cDebug() << "Prev" << m_lastSelectedActionIndex << "InstallChoice" << choice
             << Config::installChoiceNames().find( choice );

    switch ( choice )
    {
    case InstallChoice::Erase:
    {
        auto gs = Calamares::JobQueue::instance()->globalStorage();
        PartitionActions::Choices::AutoPartitionOptions options { gs->value( "defaultPartitionTableType" ).toString(),
                                                                  m_config->eraseFsType(),
                                                                  m_encryptPassphrase,
                                                                  gs->value( "efiSystemPartition" ).toString(),
                                                                  CalamaresUtils::GiBtoBytes(
                                                                      gs->value( "requiredStorageGiB" ).toDouble() ),
                                                                  m_config->swapChoice() };

        if ( m_core->isDirty() )
        {
            emit scanningDialogShow();
            QFuture<void> future = QtConcurrent::run(
                    [ = ]
                    {
                        QMutexLocker locker( &m_coreMutex );
                        m_core->revertDevice( selectedDevice() );
                    } );
            // wait for the future to finish
            future.waitForFinished();
            updateNextEnabled();
            PartitionActions::doAutopartition( m_core, selectedDevice(), options );
            Q_EMIT deviceChosen();
            emit scanningDialogHide();
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
            emit scanningDialogShow();
            QFuture<void> future =
            QtConcurrent::run(
                [ = ]
                {
                    QMutexLocker locker( &m_coreMutex );
                    m_core->revertDevice( selectedDevice() );
                } );
            // wait for the future to finish
            future.waitForFinished();
            emit scanningDialogHide();
        }
        break;

    case InstallChoice::Alongside:
        if ( m_core->isDirty() )
        {
            emit scanningDialogShow();
            QFuture<void> future = QtConcurrent::run(
                    [ = ]
                    {
                        QMutexLocker locker( &m_coreMutex );
                        m_core->revertDevice( selectedDevice() );
                    } );
            // wait for the future to finish
            future.waitForFinished();
            updateNextEnabled();
            emit scanningDialogHide();
        }
        break;
    case InstallChoice::NoChoice:
    case InstallChoice::Manual:
        break;
    }
    updateNextEnabled();
}

void
ChoicePageQml::onLeave()
{
}

bool 
ChoicePageQml::eraseButtonEnabled()
{
    return m_eraseButtonEnabled;
}

void 
ChoicePageQml::setEraseButtonEnabled( bool enabled )
{
    m_eraseButtonEnabled = enabled;
    emit eraseButtonEnabledChanged();
}

bool 
ChoicePageQml::alongSideButtonEnabled()
{
    return m_alongSideButtonEnabled;
}

void 
ChoicePageQml::setAlongSideButtonEnabled( bool enabled )
{
    m_alongSideButtonEnabled = enabled;
    emit alongSideButtonEnabledChanged();
}

bool 
ChoicePageQml::replaceButtonEnabled()
{
    return m_replaceButtonEnabled;
}

void 
ChoicePageQml::setReplaceButtonEnabled( bool enabled )
{
    m_replaceButtonEnabled = enabled;
    emit replaceButtonEnabledChanged();
}

bool 
ChoicePageQml::manualButtonEnabled()
{
    return m_somethingElseButtonEnabled;
}

void 
ChoicePageQml::setManualButtonEnabled( bool enabled )
{
    m_somethingElseButtonEnabled = enabled;
    emit manualButtonEnabledChanged();
}

QString 
ChoicePageQml::messageLabel() const
{
    return m_messageLabel;
}

void 
ChoicePageQml::setMessageLabel( QString messageLabel )
{
    m_messageLabel = messageLabel;
    emit messageLabelChanged();
}

QString 
ChoicePageQml::eraseButtonLabel() const
{
    return m_eraseButtonLabel;
}

void 
ChoicePageQml::setEraseButtonLabel( QString eraseButtonLabel )
{
    m_eraseButtonLabel = eraseButtonLabel;
    emit eraseButtonLabelChanged();
}

QString 
ChoicePageQml::alongSideButtonLabel() const
{
    return m_alongSideButtonLabel;
}

void 
ChoicePageQml::setAlongSideButtonLabel( QString alongSideButtonLabel )
{
    m_alongSideButtonLabel = alongSideButtonLabel;
    emit alongSideButtonLabelChanged();
}

QString 
ChoicePageQml::replaceButtonLabel() const
{
    return m_replaceButtonLabel;
}

void 
ChoicePageQml::setReplaceButtonLabel( QString replaceButtonLabel )
{
    m_replaceButtonLabel = replaceButtonLabel;
    emit replaceButtonLabelChanged();
}

QString 
ChoicePageQml::somethingElseButtonLabel() const
{
    return m_somethingElseButtonLabel;
}

void 
ChoicePageQml::setSomethingElseButtonLabel( QString somethingElseButtonLabel )
{
    m_somethingElseButtonLabel = somethingElseButtonLabel;
    emit somethingElseButtonLabelChanged();
}

void
ChoicePageQml::setupEfiSystemPartitionSelector()
{
    Q_ASSERT( m_isEfi );

    // Only the already existing ones:
    QList< Partition* > efiSystemPartitions = m_core->efiSystemPartitions();

    if ( efiSystemPartitions.count() == 0 )  //should never happen
    {
        emit setEFIMessageLabel( tr( "An EFI system partition cannot be found anywhere "
                                 "on this system. Please go back and use manual "
                                 "partitioning to set up %1." )
                                 .arg( Calamares::Branding::instance()->shortProductName() ) );
        updateNextEnabled();
    }
    else if ( efiSystemPartitions.count() == 1 )  //probably most usual situation
    {
        emit setEFIMessageLabel( tr( "The EFI system partition at %1 will be used for "
                                 "starting %2." )
                                 .arg( efiSystemPartitions.first()->partitionPath() )
                                 .arg( Calamares::Branding::instance()->shortProductName() ) );
    }
    else
    {
        //m_efiComboBox->show();
        emit setEFIMessageLabel( tr( "EFI system partition:" ) );
        for ( int i = 0; i < efiSystemPartitions.count(); ++i )
        {
            Partition* efiPartition = efiSystemPartitions.at( i );
            //m_efiComboBox->addItem( efiPartition->partitionPath(), i );

            // We pick an ESP on the currently selected device, if possible
            if ( efiPartition->devicePath() == selectedDevice()->deviceNode() && efiPartition->number() == 1 )
            {   
                qDebug() << "ToDo: set it in qml";
                //m_efiComboBox->setCurrentIndex( i );
            }
        }
    }
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
            ChoicePageQml::staticMetaObject.className(), "any", "any partition-table type" );
    }
    if ( types.size() == 1 )
    {
        return types.first();
    }
    if ( types.size() == 2 )
    {
        return QCoreApplication::translate(
                   ChoicePageQml::staticMetaObject.className(), "%1 or %2", "partition-table types" )
            .arg( types.at( 0 ), types.at( 1 ) );
    }
    // More than two, rather unlikely
    return types.join( ", " );
}

QString
ChoicePageQml::getCurrentDevicePartitionType() const
{
    return m_currentDevicePartitionTypeName;
}

/**
 * @brief ChoicePage::setupActions happens every time a new Device* is selected in the
 *      device picker. Sets up the text and visibility of the partitioning actions based
 *      on the currently selected Device*, bootloader and os-prober output.
 */
void
ChoicePageQml::setupActions()
{
    Logger::Once o;

    Device* currentDevice = selectedDevice();
    OsproberEntryList osproberEntriesForCurrentDevice = getOsproberEntriesForDevice( currentDevice );

    cDebug() << o << "Setting up actions for" << currentDevice->deviceNode() << "with"
             << osproberEntriesForCurrentDevice.count() << "entries.";

    if ( currentDevice->partitionTable() )
    {
        m_currentDevicePartitionType = currentDevice->partitionTable()->type();
        m_currentDevicePartitionTypeName = currentDevice->partitionTable()->typeName();
    }
    else
    {
        m_currentDevicePartitionType = PartitionTable::unknownTableType;
        m_currentDevicePartitionTypeName = currentDevice->partitionTable()->typeName();
    }

    if ( m_config->allowManualPartitioning() )
    {
        setManualButtonEnabled(true);
    }
    else
    {
        setManualButtonEnabled(false);
    }

    bool atLeastOneCanBeResized = false;
    bool atLeastOneCanBeReplaced = false;
    bool atLeastOneIsMounted = false;  // Suppress 'erase' if so
    bool isInactiveRAID = false;
    bool matchTableType = false;

#ifdef WITH_KPMCORE4API
    if ( currentDevice->type() == Device::Type::SoftwareRAID_Device
         && static_cast< SoftwareRAID* >( currentDevice )->status() == SoftwareRAID::Status::Inactive )
    {
        cDebug() << Logger::SubEntry << "part of an inactive RAID device";
        isInactiveRAID = true;
    }
#endif

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
            setMessageLabel(tr( "This storage device does not seem to have an operating system on it. "
                                         "What would you like to do?<br/>"
                                         "You will be able to review and confirm your choices "
                                         "before any change is made to the storage device." ));

            setEraseButtonLabel(tr( "<strong>Erase disk</strong><br/>"
                                        "This will <font color=\"red\">delete</font> all data "
                                        "currently present on the selected storage device." ));

            setAlongSideButtonLabel(tr( "<strong>Install alongside</strong><br/>"
                                            "The installer will shrink a partition to make room for %1." )
                                            .arg( Calamares::Branding::instance()->shortVersionedName() ));

            setReplaceButtonLabel(tr( "<strong>Replace a partition</strong><br/>"
                                          "Replaces a partition with %1." )
                                          .arg( Calamares::Branding::instance()->shortVersionedName() ));
        );
        emit labelsUpdated();
        setReplaceButtonEnabled(false);
        setAlongSideButtonEnabled(false);
    }
    else if ( osproberEntriesForCurrentDevice.count() == 1 )
    {
        QString osName = osproberEntriesForCurrentDevice.first().prettyName;

        if ( !osName.isEmpty() )
        {
            CALAMARES_RETRANSLATE (
                cDebug() << "Setting texts for 1 non-empty osprober entry";
                setMessageLabel(tr( "This storage device has %1 on it. "
                                             "What would you like to do?<br/>"
                                             "You will be able to review and confirm your choices "
                                             "before any change is made to the storage device." )
                                             .arg( osName ));

                setAlongSideButtonLabel(tr( "<strong>Install alongside</strong><br/>"
                                                "The installer will shrink a partition to make room for %1." )
                                                .arg( Calamares::Branding::instance()->shortVersionedName() ));

                setEraseButtonLabel(tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all data "
                                            "currently present on the selected storage device." ));


                setReplaceButtonLabel(tr( "<strong>Replace a partition</strong><br/>"
                                              "Replaces a partition with %1." )
                                              .arg( Calamares::Branding::instance()->shortVersionedName() )); 
            );
            emit labelsUpdated();
        }
        else
        {
            CALAMARES_RETRANSLATE(
                cDebug() << "Setting texts for 1 empty osprober entry";
                setMessageLabel(tr( "This storage device already has an operating system on it. "
                                             "What would you like to do?<br/>"
                                             "You will be able to review and confirm your choices "
                                             "before any change is made to the storage device." ));

                setAlongSideButtonLabel(tr( "<strong>Install alongside</strong><br/>"
                                                "The installer will shrink a partition to make room for %1." )
                                                .arg( Calamares::Branding::instance()->shortVersionedName() ));

                setEraseButtonLabel(tr( "<strong>Erase disk</strong><br/>"
                                            "This will <font color=\"red\">delete</font> all data "
                                            "currently present on the selected storage device." ));

                setReplaceButtonLabel(tr( "<strong>Replace a partition</strong><br/>"
                                              "Replaces a partition with %1." )
                                              .arg( Calamares::Branding::instance()->shortVersionedName() ));
            );
            emit labelsUpdated();
        }
    }
    else
    {
        // osproberEntriesForCurrentDevice has at least 2 items.

        CALAMARES_RETRANSLATE(
            cDebug() << "Setting texts for >= 2 osprober entries";

            setMessageLabel(tr( "This storage device has multiple operating systems on it. "
                                         "What would you like to do?<br/>"
                                         "You will be able to review and confirm your choices "
                                         "before any change is made to the storage device." ));

            setAlongSideButtonLabel(tr( "<strong>Install alongside</strong><br/>"
                                            "The installer will shrink a partition to make room for %1." )
                                            .arg( Calamares::Branding::instance()->shortVersionedName() ));

            setEraseButtonLabel(tr( "<strong>Erase disk</strong><br/>"
                                        "This will <font color=\"red\">delete</font> all data "
                                        "currently present on the selected storage device." ));

            setReplaceButtonLabel(tr( "<strong>Replace a partition</strong><br/>"
                                          "Replaces a partition with %1." )
                                          .arg( Calamares::Branding::instance()->shortVersionedName() )); 
        );
        emit labelsUpdated();
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
        setReplaceButtonEnabled(true);
    }
    else
    {
        cDebug() << "No partitions available for replace-action.";
        setReplaceButtonEnabled(false);
    }

    if ( atLeastOneCanBeResized )
    {
        setAlongSideButtonEnabled(true);
    }
    else
    {
        cDebug() << "No partitions available for resize-action.";
        setAlongSideButtonEnabled(false);
    }

    if ( !atLeastOneIsMounted && !isInactiveRAID )
    {
        setEraseButtonEnabled(true);
    }
    else
    {
        cDebug() << "No partitions ("
                 << "any-mounted?" << atLeastOneIsMounted << "is-raid?" << isInactiveRAID << ") for erase-action.";
        setEraseButtonEnabled(false);
    }

    bool isEfi = PartUtils::isEfiSystem();
    bool efiSystemPartitionFound = !m_core->efiSystemPartitions().isEmpty();

    if ( isEfi && !efiSystemPartitionFound )
    {
        cWarning() << "System is EFI but there's no EFI system partition, "
                      "DISABLING alongside and replace features.";
        setAlongSideButtonEnabled(false);
        setReplaceButtonEnabled(false);
    }

    if ( tableType != PartitionTable::unknownTableType && !matchTableType )
    {
        setMessageLabel(tr( "This storage device already has an operating system on it, "
                                     "but the partition table <strong>%1</strong> is different from the "
                                     "needed <strong>%2</strong>.<br/>" )
                                     .arg( PartitionTable::tableTypeToName( tableType ) )
                                     .arg( describePartitionTypes( m_config->partitionTableTypes() ) ) );

        cWarning() << "Partition table" << PartitionTable::tableTypeToName( tableType )
                   << "does not match the requirement " << m_config->partitionTableTypes().join( ',' )
                   << ", ENABLING erase feature and DISABLING alongside, replace and manual features.";
        setEraseButtonEnabled(true);
        setAlongSideButtonEnabled(false);
        setReplaceButtonEnabled(false);
        setManualButtonEnabled(false);
        cDebug() << "Replace button suppressed because partition table type mismatch.";
    }

    if ( !m_somethingElseButtonEnabled && !m_alongSideButtonEnabled && !m_replaceButtonEnabled
         && !m_eraseButtonEnabled)
    {
        if ( atLeastOneIsMounted )
        {
            setMessageLabel( tr( "This storage device has one of its partitions <strong>mounted</strong>." ) );
        }
        else
        {
            setMessageLabel(
                tr( "This storage device is a part of an <strong>inactive RAID</strong> device." ) );
        }

        cWarning() << "No buttons available"
                   << "replaced?" << atLeastOneCanBeReplaced << "resized?" << atLeastOneCanBeResized
                   << "erased? (not-mounted and not-raid)" << !atLeastOneIsMounted << "and" << !isInactiveRAID;
    }

    if ( m_somethingElseButtonEnabled )
    {
        setSomethingElseButtonLabel(tr( "<strong>Manual partitioning</strong><br/>"
                                            "You can create or resize partitions yourself." ));
    }
    emit labelsUpdated();
    
    // Set Partition Model Here
    ChoicePageQml::setPartitionModelForDevice();
}


OsproberEntryList
ChoicePageQml::getOsproberEntriesForDevice( Device* device ) const
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
ChoicePageQml::isNextEnabled() const
{
    return m_nextEnabled;
}


bool
ChoicePageQml::calculateNextEnabled() const
{
    bool enabled = false;
    switch ( m_config->installChoice() )
    {
    case InstallChoice::NoChoice:
        cDebug() << "No partitioning choice";
        return false;
    case InstallChoice::Replace:
    case InstallChoice::Alongside:
        enabled = true;
        break;
    case InstallChoice::Erase:
    case InstallChoice::Manual:
        enabled = true;
    }

    if ( !enabled )
    {
        cDebug() << "No valid choice made";
        return false;
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

    if ( m_config->installChoice() == InstallChoice::Manual)
    {
        return true;
    }

    return true;
}


void
ChoicePageQml::updateNextEnabled()
{
    bool enabled = calculateNextEnabled();

    if ( enabled != m_nextEnabled )
    {
        m_nextEnabled = enabled;
        Q_EMIT nextStatusChanged( enabled );
    }
}

int
ChoicePageQml::lastSelectedDeviceIndex()
{
    return m_lastSelectedDeviceIndex;
}

void
ChoicePageQml::setLastSelectedDeviceIndex( int index )
{
    m_lastSelectedDeviceIndex = index;
}
