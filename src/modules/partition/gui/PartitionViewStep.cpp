/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2018-2019, 2020, Adriaan de Groot <groot@kde.org>
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
 *   Copyright 2020, Anke Boersma <demm@kaosx.us
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

#include "gui/PartitionViewStep.h"

#include "core/DeviceModel.h"
#include "core/KPMHelpers.h"
#include "core/OsproberEntry.h"
#include "core/PartUtils.h"
#include "core/PartitionActions.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionModel.h"
#include "gui/ChoicePage.h"
#include "gui/PartitionBarsView.h"
#include "gui/PartitionLabelsView.h"
#include "gui/PartitionPage.h"

#include "Branding.h"
#include "CalamaresVersion.h"
#include "GlobalStorage.h"
#include "Job.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/NamedEnum.h"
#include "utils/Retranslator.h"
#include "utils/Variant.h"
#include "widgets/WaitingWidget.h"


#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>

#include <QApplication>
#include <QDir>
#include <QFormLayout>
#include <QFutureWatcher>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QStackedWidget>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>

PartitionViewStep::PartitionViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_core( nullptr )
    , m_widget( new QStackedWidget() )
    , m_choicePage( nullptr )
    , m_manualPartitionPage( nullptr )
    , m_requiredStorageGiB( 0.0 )
{
    m_widget->setContentsMargins( 0, 0, 0, 0 );

    m_waitingWidget = new WaitingWidget( QString() );
    m_widget->addWidget( m_waitingWidget );
    CALAMARES_RETRANSLATE( m_waitingWidget->setText( tr( "Gathering system information..." ) ); )

    m_core = new PartitionCoreModule( this );  // Unusable before init is complete!
    // We're not done loading, but we need the configuration map first.
}


void
PartitionViewStep::initPartitionCoreModule()
{
    Q_ASSERT( m_core );
    m_core->init();
}


void
PartitionViewStep::continueLoading()
{
    Q_ASSERT( !m_choicePage );
    m_choicePage = new ChoicePage( m_swapChoices );
    m_choicePage->init( m_core );
    m_widget->addWidget( m_choicePage );

    // Instantiate the manual partitioning page as needed.
    //
    Q_ASSERT( !m_manualPartitionPage );
    // m_manualPartitionPage = new PartitionPage( m_core );
    // m_widget->addWidget( m_manualPartitionPage );

    m_widget->removeWidget( m_waitingWidget );
    m_waitingWidget->deleteLater();
    m_waitingWidget = nullptr;

    connect( m_core, &PartitionCoreModule::hasRootMountPointChanged, this, &PartitionViewStep::nextStatusChanged );
    connect( m_choicePage, &ChoicePage::nextStatusChanged, this, &PartitionViewStep::nextStatusChanged );
}


PartitionViewStep::~PartitionViewStep()
{
    if ( m_choicePage && m_choicePage->parent() == nullptr )
    {
        m_choicePage->deleteLater();
    }
    if ( m_manualPartitionPage && m_manualPartitionPage->parent() == nullptr )
    {
        m_manualPartitionPage->deleteLater();
    }
}


QString
PartitionViewStep::prettyName() const
{
    return tr( "Partitions" );
}


QWidget*
PartitionViewStep::widget()
{
    return m_widget;
}


QWidget*
PartitionViewStep::createSummaryWidget() const
{
    QWidget* widget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    widget->setLayout( mainLayout );
    mainLayout->setMargin( 0 );

    ChoicePage::InstallChoice choice = m_choicePage->currentChoice();

    QFormLayout* formLayout = new QFormLayout( widget );
    const int MARGIN = CalamaresUtils::defaultFontHeight() / 2;
    formLayout->setContentsMargins( MARGIN, 0, MARGIN, MARGIN );
    mainLayout->addLayout( formLayout );

    QList< PartitionCoreModule::SummaryInfo > list = m_core->createSummaryInfo();
    if ( list.length() > 1 )  // There are changes on more than one disk
    {
        //NOTE: all of this should only happen when Manual partitioning is active.
        //      Any other choice should result in a list.length() == 1.
        QLabel* modeLabel = new QLabel;
        formLayout->addRow( modeLabel );
        QString modeText;
        switch ( choice )
        {
        case ChoicePage::Alongside:
            modeText = tr( "Install %1 <strong>alongside</strong> another operating system." )
                           .arg( *Calamares::Branding::ShortVersionedName );
            break;
        case ChoicePage::Erase:
            modeText
                = tr( "<strong>Erase</strong> disk and install %1." ).arg( *Calamares::Branding::ShortVersionedName );
            break;
        case ChoicePage::Replace:
            modeText
                = tr( "<strong>Replace</strong> a partition with %1." ).arg( *Calamares::Branding::ShortVersionedName );
            break;
        case ChoicePage::NoChoice:
        case ChoicePage::Manual:
            modeText = tr( "<strong>Manual</strong> partitioning." );
        }
        modeLabel->setText( modeText );
    }
    for ( const auto& info : list )
    {
        QLabel* diskInfoLabel = new QLabel;
        if ( list.length() == 1 )  // this is the only disk preview
        {
            QString modeText;
            switch ( choice )
            {
            case ChoicePage::Alongside:
                modeText = tr( "Install %1 <strong>alongside</strong> another operating system on disk "
                               "<strong>%2</strong> (%3)." )
                               .arg( *Calamares::Branding::ShortVersionedName )
                               .arg( info.deviceNode )
                               .arg( info.deviceName );
                break;
            case ChoicePage::Erase:
                modeText = tr( "<strong>Erase</strong> disk <strong>%2</strong> (%3) and install %1." )
                               .arg( *Calamares::Branding::ShortVersionedName )
                               .arg( info.deviceNode )
                               .arg( info.deviceName );
                break;
            case ChoicePage::Replace:
                modeText = tr( "<strong>Replace</strong> a partition on disk <strong>%2</strong> (%3) with %1." )
                               .arg( *Calamares::Branding::ShortVersionedName )
                               .arg( info.deviceNode )
                               .arg( info.deviceName );
                break;
            case ChoicePage::NoChoice:
            case ChoicePage::Manual:
                modeText = tr( "<strong>Manual</strong> partitioning on disk <strong>%1</strong> (%2)." )
                               .arg( info.deviceNode )
                               .arg( info.deviceName );
            }
            diskInfoLabel->setText( modeText );
        }
        else  // multiple disk previews!
        {
            diskInfoLabel->setText(
                tr( "Disk <strong>%1</strong> (%2)" ).arg( info.deviceNode ).arg( info.deviceName ) );
        }
        formLayout->addRow( diskInfoLabel );

        PartitionBarsView* preview;
        PartitionLabelsView* previewLabels;
        QVBoxLayout* field;

        PartitionBarsView::NestedPartitionsMode mode
            = Calamares::JobQueue::instance()->globalStorage()->value( "drawNestedPartitions" ).toBool()
            ? PartitionBarsView::DrawNestedPartitions
            : PartitionBarsView::NoNestedPartitions;
        preview = new PartitionBarsView;
        preview->setNestedPartitionsMode( mode );
        previewLabels = new PartitionLabelsView;
        previewLabels->setExtendedPartitionHidden( mode == PartitionBarsView::NoNestedPartitions );
        preview->setModel( info.partitionModelBefore );
        previewLabels->setModel( info.partitionModelBefore );
        preview->setSelectionMode( QAbstractItemView::NoSelection );
        previewLabels->setSelectionMode( QAbstractItemView::NoSelection );
        info.partitionModelBefore->setParent( widget );
        field = new QVBoxLayout;
        CalamaresUtils::unmarginLayout( field );
        field->setSpacing( 6 );
        field->addWidget( preview );
        field->addWidget( previewLabels );
        formLayout->addRow( tr( "Current:" ), field );

        preview = new PartitionBarsView;
        preview->setNestedPartitionsMode( mode );
        previewLabels = new PartitionLabelsView;
        previewLabels->setExtendedPartitionHidden( mode == PartitionBarsView::NoNestedPartitions );
        preview->setModel( info.partitionModelAfter );
        previewLabels->setModel( info.partitionModelAfter );
        preview->setSelectionMode( QAbstractItemView::NoSelection );
        previewLabels->setSelectionMode( QAbstractItemView::NoSelection );
        previewLabels->setCustomNewRootLabel( *Calamares::Branding::BootloaderEntryName );
        info.partitionModelAfter->setParent( widget );
        field = new QVBoxLayout;
        CalamaresUtils::unmarginLayout( field );
        field->setSpacing( 6 );
        field->addWidget( preview );
        field->addWidget( previewLabels );
        formLayout->addRow( tr( "After:" ), field );
    }
    QStringList jobsLines;
    foreach ( const Calamares::job_ptr& job, jobs() )
    {
        if ( !job->prettyDescription().isEmpty() )
        {
            jobsLines.append( job->prettyDescription() );
        }
    }
    if ( !jobsLines.isEmpty() )
    {
        QLabel* jobsLabel = new QLabel( widget );
        mainLayout->addWidget( jobsLabel );
        jobsLabel->setText( jobsLines.join( "<br/>" ) );
        jobsLabel->setMargin( CalamaresUtils::defaultFontHeight() / 2 );
        QPalette pal;
        pal.setColor( QPalette::Background, pal.window().color().lighter( 108 ) );
        jobsLabel->setAutoFillBackground( true );
        jobsLabel->setPalette( pal );
    }
    return widget;
}


void
PartitionViewStep::next()
{
    if ( m_choicePage == m_widget->currentWidget() )
    {
        if ( m_choicePage->currentChoice() == ChoicePage::Manual )
        {
            if ( !m_manualPartitionPage )
            {
                m_manualPartitionPage = new PartitionPage( m_core );
                m_widget->addWidget( m_manualPartitionPage );
            }

            m_widget->setCurrentWidget( m_manualPartitionPage );
            m_manualPartitionPage->selectDeviceByIndex( m_choicePage->lastSelectedDeviceIndex() );
            if ( m_core->isDirty() )
            {
                m_manualPartitionPage->onRevertClicked();
            }
        }
        cDebug() << "Choice applied: " << m_choicePage->currentChoice();
    }
}


void
PartitionViewStep::back()
{
    if ( m_widget->currentWidget() != m_choicePage )
    {
        m_widget->setCurrentWidget( m_choicePage );
        m_choicePage->setLastSelectedDeviceIndex( m_manualPartitionPage->selectedDeviceIndex() );

        if ( m_manualPartitionPage )
        {
            m_manualPartitionPage->deleteLater();
            m_manualPartitionPage = nullptr;
        }
    }
}


bool
PartitionViewStep::isNextEnabled() const
{
    if ( m_choicePage && m_widget->currentWidget() == m_choicePage )
    {
        return m_choicePage->isNextEnabled();
    }

    if ( m_manualPartitionPage && m_widget->currentWidget() == m_manualPartitionPage )
    {
        return m_core->hasRootMountPoint();
    }

    return false;
}


bool
PartitionViewStep::isBackEnabled() const
{
    return true;
}


bool
PartitionViewStep::isAtBeginning() const
{
    if ( m_widget->currentWidget() != m_choicePage )
    {
        return false;
    }
    return true;
}


bool
PartitionViewStep::isAtEnd() const
{
    if ( m_widget->currentWidget() == m_choicePage )
    {
        if ( m_choicePage->currentChoice() == ChoicePage::Erase || m_choicePage->currentChoice() == ChoicePage::Replace
             || m_choicePage->currentChoice() == ChoicePage::Alongside )
        {
            return true;
        }
        return false;
    }
    return true;
}


void
PartitionViewStep::onActivate()
{
    // If there's no setting (e.g. from the welcome page) for required storage
    // then use ours, if it was set.
    auto* gs = Calamares::JobQueue::instance() ? Calamares::JobQueue::instance()->globalStorage() : nullptr;
    if ( m_requiredStorageGiB >= 0.0 && gs && !gs->contains( "requiredStorageGiB" ) )
    {
        gs->insert( "requiredStorageGiB", m_requiredStorageGiB );
    }

    // if we're coming back to PVS from the next VS
    if ( m_widget->currentWidget() == m_choicePage && m_choicePage->currentChoice() == ChoicePage::Alongside )
    {
        m_choicePage->applyActionChoice( ChoicePage::Alongside );
        //        m_choicePage->reset();
        //FIXME: ReplaceWidget should be reset maybe?
    }
}


void
PartitionViewStep::onLeave()
{
    if ( m_widget->currentWidget() == m_choicePage )
    {
        m_choicePage->onLeave();
        return;
    }

    if ( m_widget->currentWidget() == m_manualPartitionPage )
    {
        if ( PartUtils::isEfiSystem() )
        {
            QString espMountPoint
                = Calamares::JobQueue::instance()->globalStorage()->value( "efiSystemPartition" ).toString();
            Partition* esp = m_core->findPartitionByMountPoint( espMountPoint );

            QString message;
            QString description;
            if ( !esp )
            {
                message = tr( "No EFI system partition configured" );
                description = tr( "An EFI system partition is necessary to start %1."
                                  "<br/><br/>"
                                  "To configure an EFI system partition, go back and "
                                  "select or create a FAT32 filesystem with the "
                                  "<strong>esp</strong> flag enabled and mount point "
                                  "<strong>%2</strong>.<br/><br/>"
                                  "You can continue without setting up an EFI system "
                                  "partition but your system may fail to start." )
                                  .arg( *Calamares::Branding::ShortProductName )
                                  .arg( espMountPoint );
            }
            else if ( esp && !PartUtils::isEfiBootable( esp ) )
            {
                message = tr( "EFI system partition flag not set" );
                description = tr( "An EFI system partition is necessary to start %1."
                                  "<br/><br/>"
                                  "A partition was configured with mount point "
                                  "<strong>%2</strong> but its <strong>esp</strong> "
                                  "flag is not set.<br/>"
                                  "To set the flag, go back and edit the partition."
                                  "<br/><br/>"
                                  "You can continue without setting the flag but your "
                                  "system may fail to start." )
                                  .arg( *Calamares::Branding::ShortProductName )
                                  .arg( espMountPoint );
            }

            if ( !message.isEmpty() )
            {
                cWarning() << message;
                QMessageBox::warning( m_manualPartitionPage, message, description );
            }
        }
        else
        {

            cDebug() << "device: BIOS";
            // TODO: this *always* warns, which might be annoying, so it'd be
            //       best to find a way to detect that bios_grub partition.

            QString message = tr( "Option to use GPT on BIOS" );
            QString description = tr( "A GPT partition table is the best option for all "
                              "systems. This installer supports such a setup for "
                              "BIOS systems too."
                              "<br/><br/>"
                              "To configure a GPT partition table on BIOS, "
                              "(if not done so already) go back "
                              "and set the partition table to GPT, next create a 8 MB "
                              "unformatted partition with the "
                              "<strong>bios_grub</strong> flag enabled.<br/><br/>"
                              "An unformatted 8 MB partition is necessary "
                              "to start %1 on a BIOS system with GPT." )
                              .arg( *Calamares::Branding::ShortProductName );

            QMessageBox::information( m_manualPartitionPage, message, description );
        }

        Partition* root_p = m_core->findPartitionByMountPoint( "/" );
        Partition* boot_p = m_core->findPartitionByMountPoint( "/boot" );

        if ( root_p and boot_p )
        {
            QString message;
            QString description;

            // If the root partition is encrypted, and there's a separate boot
            // partition which is not encrypted
            if ( root_p->fileSystem().type() == FileSystem::Luks && boot_p->fileSystem().type() != FileSystem::Luks )
            {
                message = tr( "Boot partition not encrypted" );
                description = tr( "A separate boot partition was set up together with "
                                  "an encrypted root partition, but the boot partition "
                                  "is not encrypted."
                                  "<br/><br/>"
                                  "There are security concerns with this kind of "
                                  "setup, because important system files are kept "
                                  "on an unencrypted partition.<br/>"
                                  "You may continue if you wish, but filesystem "
                                  "unlocking will happen later during system startup."
                                  "<br/>To encrypt the boot partition, go back and "
                                  "recreate it, selecting <strong>Encrypt</strong> "
                                  "in the partition creation window." );

                QMessageBox::warning( m_manualPartitionPage, message, description );
            }
        }
    }
}


void
PartitionViewStep::setConfigurationMap( const QVariantMap& configurationMap )
{
    // Copy the efiSystemPartition setting to the global storage. It is needed not only in
    // the EraseDiskPage, but also in the bootloader configuration modules (grub, bootloader).
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QString efiSP = CalamaresUtils::getString( configurationMap, "efiSystemPartition" );
    if ( efiSP.isEmpty() )
    {
        efiSP = QStringLiteral( "/boot/efi" );
    }
    gs->insert( "efiSystemPartition", efiSP );

    // Set up firmwareType global storage entry. This is used, e.g. by the bootloader module.
    QString firmwareType( PartUtils::isEfiSystem() ? QStringLiteral( "efi" ) : QStringLiteral( "bios" ) );
    cDebug() << "Setting firmwareType to" << firmwareType;
    gs->insert( "firmwareType", firmwareType );

    // Read and parse key efiSystemPartitionSize
    if ( configurationMap.contains( "efiSystemPartitionSize" ) )
    {
        gs->insert( "efiSystemPartitionSize", CalamaresUtils::getString( configurationMap, "efiSystemPartitionSize" ) );
    }

    // SWAP SETTINGS
    //
    // This is a bit convoluted because there's legacy settings to handle as well
    // as the new-style list of choices, with mapping back-and-forth.
    if ( configurationMap.contains( "userSwapChoices" )
         && ( configurationMap.contains( "ensureSuspendToDisk" ) || configurationMap.contains( "neverCreateSwap" ) ) )
    {
        cError() << "Partition-module configuration mixes old- and new-style swap settings.";
    }

    if ( configurationMap.contains( "ensureSuspendToDisk" ) )
    {
        cWarning() << "Partition-module setting *ensureSuspendToDisk* is deprecated.";
    }
    bool ensureSuspendToDisk = CalamaresUtils::getBool( configurationMap, "ensureSuspendToDisk", true );

    if ( configurationMap.contains( "neverCreateSwap" ) )
    {
        cWarning() << "Partition-module setting *neverCreateSwap* is deprecated.";
    }
    bool neverCreateSwap = CalamaresUtils::getBool( configurationMap, "neverCreateSwap", false );

    QSet< PartitionActions::Choices::SwapChoice > choices;  // Available swap choices
    if ( configurationMap.contains( "userSwapChoices" ) )
    {
        // We've already warned about overlapping settings with the
        // legacy *ensureSuspendToDisk* and *neverCreateSwap*.
        QStringList l = configurationMap[ "userSwapChoices" ].toStringList();

        for ( const auto& item : l )
        {
            bool ok = false;
            auto v = PartitionActions::Choices::nameToChoice( item, ok );
            if ( ok )
            {
                choices.insert( v );
            }
        }

        if ( choices.isEmpty() )
        {
            cWarning() << "Partition-module configuration for *userSwapChoices* is empty:" << l;
            choices.insert( PartitionActions::Choices::SwapChoice::FullSwap );
        }

        // suspend if it's one of the possible choices; suppress swap only if it's
        // the **only** choice available.
        ensureSuspendToDisk = choices.contains( PartitionActions::Choices::SwapChoice::FullSwap );
        neverCreateSwap = ( choices.count() == 1 ) && choices.contains( PartitionActions::Choices::SwapChoice::NoSwap );
    }
    else
    {
        // Convert the legacy settings into a single setting for now.
        if ( neverCreateSwap )
        {
            choices.insert( PartitionActions::Choices::SwapChoice::NoSwap );
        }
        else if ( ensureSuspendToDisk )
        {
            choices.insert( PartitionActions::Choices::SwapChoice::FullSwap );
        }
        else
        {
            choices.insert( PartitionActions::Choices::SwapChoice::SmallSwap );
        }
    }

    // Not all are supported right now // FIXME
    static const char unsupportedSetting[] = "Partition-module does not support *userSwapChoices* setting";

#define COMPLAIN_UNSUPPORTED( x ) \
    if ( choices.contains( x ) ) \
    { \
        cWarning() << unsupportedSetting << PartitionActions::Choices::choiceToName( x ); \
        choices.remove( x ); \
    }

    COMPLAIN_UNSUPPORTED( PartitionActions::Choices::SwapChoice::SwapFile )
    COMPLAIN_UNSUPPORTED( PartitionActions::Choices::SwapChoice::ReuseSwap )
#undef COMPLAIN_UNSUPPORTED

    m_swapChoices = choices;

    // Settings that overlap with the Welcome module
    m_requiredStorageGiB = CalamaresUtils::getDouble( configurationMap, "requiredStorage", -1.0 );

    // These gs settings seem to be unused (in upstream Calamares) outside of
    // the partition module itself.
    gs->insert( "ensureSuspendToDisk", ensureSuspendToDisk );
    gs->insert( "neverCreateSwap", neverCreateSwap );

    // OTHER SETTINGS
    //
    gs->insert( "drawNestedPartitions", CalamaresUtils::getBool( configurationMap, "drawNestedPartitions", false ) );
    gs->insert( "alwaysShowPartitionLabels",
                CalamaresUtils::getBool( configurationMap, "alwaysShowPartitionLabels", true ) );
    gs->insert( "enableLuksAutomatedPartitioning",
                CalamaresUtils::getBool( configurationMap, "enableLuksAutomatedPartitioning", true ) );
    gs->insert( "allowManualPartitioning",
                CalamaresUtils::getBool( configurationMap, "allowManualPartitioning", true ) );

    // The defaultFileSystemType setting needs a bit more processing,
    // as we want to cover various cases (such as different cases)
    QString fsName = CalamaresUtils::getString( configurationMap, "defaultFileSystemType" );
    FileSystem::Type fsType;
    if ( fsName.isEmpty() )
    {
        cWarning() << "Partition-module setting *defaultFileSystemType* is missing, will use ext4";
    }
    QString fsRealName = PartUtils::findFS( fsName, &fsType );
    if ( fsRealName == fsName )
    {
        cDebug() << "Partition-module setting *defaultFileSystemType*" << fsRealName;
    }
    else if ( fsType != FileSystem::Unknown )
    {
        cWarning() << "Partition-module setting *defaultFileSystemType* changed" << fsRealName;
    }
    else
    {
        cWarning() << "Partition-module setting *defaultFileSystemType* is bad (" << fsName << ") using" << fsRealName
                   << "instead.";
    }
    gs->insert( "defaultFileSystemType", fsRealName );


    // Now that we have the config, we load the PartitionCoreModule in the background
    // because it could take a while. Then when it's done, we can set up the widgets
    // and remove the spinner.
    m_future = new QFutureWatcher< void >();
    connect( m_future, &QFutureWatcher< void >::finished, this, [this] {
        continueLoading();
        this->m_future->deleteLater();
        this->m_future = nullptr;
    } );

    QFuture< void > future = QtConcurrent::run( this, &PartitionViewStep::initPartitionCoreModule );
    m_future->setFuture( future );

    if ( configurationMap.contains( "partitionLayout" ) )
    {
        m_core->initLayout( configurationMap.values( "partitionLayout" ).at( 0 ).toList() );
    }
    else
    {
        m_core->initLayout();
    }
}


Calamares::JobList
PartitionViewStep::jobs() const
{
    return m_core->jobs();
}

Calamares::RequirementsList
PartitionViewStep::checkRequirements()
{
    if ( m_future )
    {
        m_future->waitForFinished();
    }

    Calamares::RequirementsList l;
    l.append( {
        QLatin1String( "partitions" ),
        [] { return tr( "has at least one disk device available." ); },
        [] { return tr( "There are no partitions to install on." ); },
        m_core->deviceModel()->rowCount() > 0,  // satisfied
#ifdef DEBUG_PARTITION_UNSAFE
        false  // optional
#else
        true  // required
#endif
    } );

    return l;
}


CALAMARES_PLUGIN_FACTORY_DEFINITION( PartitionViewStepFactory, registerPlugin< PartitionViewStep >(); )
