/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
 *   SPDX-FileCopyrightText: 2014-2017 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2019 2020, Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-FileCopyrightText: 2020 Anke Boersma <demm@kaosx.us
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "gui/PartitionViewStep.h"

#include "core/Config.h"
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
#include "utils/QtCompat.h"
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
    , m_config( new Config( this ) )
    , m_core( nullptr )
    , m_widget( new QStackedWidget() )
    , m_choicePage( nullptr )
    , m_manualPartitionPage( nullptr )
{
    m_widget->setContentsMargins( 0, 0, 0, 0 );

    m_waitingWidget = new WaitingWidget( QString() );
    m_widget->addWidget( m_waitingWidget );
    CALAMARES_RETRANSLATE( m_waitingWidget->setText( tr( "Gathering system information..." ) ); );

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
    m_choicePage = new ChoicePage( m_config );
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

    connect( m_core, &PartitionCoreModule::hasRootMountPointChanged, this, &PartitionViewStep::nextPossiblyChanged );
    connect( m_choicePage, &ChoicePage::nextStatusChanged, this, &PartitionViewStep::nextPossiblyChanged );
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
    delete m_core;
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

    Config::InstallChoice choice = m_config->installChoice();

    QFormLayout* formLayout = new QFormLayout( widget );
    const int MARGIN = CalamaresUtils::defaultFontHeight() / 2;
    formLayout->setContentsMargins( MARGIN, 0, MARGIN, MARGIN );
    mainLayout->addLayout( formLayout );

    const auto* branding = Calamares::Branding::instance();
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
        case Config::InstallChoice::Alongside:
            modeText = tr( "Install %1 <strong>alongside</strong> another operating system." )
                           .arg( branding->shortVersionedName() );
            break;
        case Config::InstallChoice::Erase:
            modeText = tr( "<strong>Erase</strong> disk and install %1." ).arg( branding->shortVersionedName() );
            break;
        case Config::InstallChoice::Replace:
            modeText = tr( "<strong>Replace</strong> a partition with %1." ).arg( branding->shortVersionedName() );
            break;
        case Config::InstallChoice::NoChoice:
        case Config::InstallChoice::Manual:
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
            case Config::InstallChoice::Alongside:
                modeText = tr( "Install %1 <strong>alongside</strong> another operating system on disk "
                               "<strong>%2</strong> (%3)." )
                               .arg( branding->shortVersionedName() )
                               .arg( info.deviceNode )
                               .arg( info.deviceName );
                break;
            case Config::InstallChoice::Erase:
                modeText = tr( "<strong>Erase</strong> disk <strong>%2</strong> (%3) and install %1." )
                               .arg( branding->shortVersionedName() )
                               .arg( info.deviceNode )
                               .arg( info.deviceName );
                break;
            case Config::InstallChoice::Replace:
                modeText = tr( "<strong>Replace</strong> a partition on disk <strong>%2</strong> (%3) with %1." )
                               .arg( branding->shortVersionedName() )
                               .arg( info.deviceNode )
                               .arg( info.deviceName );
                break;
            case Config::InstallChoice::NoChoice:
            case Config::InstallChoice::Manual:
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
        previewLabels->setCustomNewRootLabel(
            Calamares::Branding::instance()->string( Calamares::Branding::BootloaderEntryName ) );
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
        pal.setColor( WindowBackground, pal.window().color().lighter( 108 ) );
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
        if ( m_config->installChoice() == Config::InstallChoice::Manual )
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
        cDebug() << "Choice applied: " << m_config->installChoice();
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

void
PartitionViewStep::nextPossiblyChanged( bool )
{
    emit nextStatusChanged( isNextEnabled() );
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
        auto choice = m_config->installChoice();
        if ( Config::InstallChoice::Erase == choice || Config::InstallChoice::Replace == choice
             || Config::InstallChoice::Alongside == choice )
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
    m_config->updateGlobalStorage();

    // if we're coming back to PVS from the next VS
    if ( m_widget->currentWidget() == m_choicePage && m_config->installChoice() == Config::InstallChoice::Alongside )
    {
        m_choicePage->applyActionChoice( Config::InstallChoice::Alongside );
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

    const auto* branding = Calamares::Branding::instance();
    if ( m_widget->currentWidget() == m_manualPartitionPage )
    {
        if ( PartUtils::isEfiSystem() )
        {
            QString espMountPoint
                = Calamares::JobQueue::instance()->globalStorage()->value( "efiSystemPartition" ).toString();
#ifdef WITH_KPMCORE4API
            auto espFlag = PartitionTable::Flag::Boot;
#else
            auto espFlag = PartitionTable::FlagEsp;
#endif
            QString espFlagName = PartitionTable::flagName( espFlag );
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
                                  "<strong>%3</strong> flag enabled and mount point "
                                  "<strong>%2</strong>.<br/><br/>"
                                  "You can continue without setting up an EFI system "
                                  "partition but your system may fail to start." )
                                  .arg( branding->shortProductName() )
                                  .arg( espMountPoint, espFlagName );
            }
            else if ( esp && !PartUtils::isEfiBootable( esp ) )
            {
                message = tr( "EFI system partition flag not set" );
                description = tr( "An EFI system partition is necessary to start %1."
                                  "<br/><br/>"
                                  "A partition was configured with mount point "
                                  "<strong>%2</strong> but its <strong>%3</strong> "
                                  "flag is not set.<br/>"
                                  "To set the flag, go back and edit the partition."
                                  "<br/><br/>"
                                  "You can continue without setting the flag but your "
                                  "system may fail to start." )
                                  .arg( branding->shortProductName() )
                                  .arg( espMountPoint, espFlagName );
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
                                      .arg( branding->shortProductName() );

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
    m_config->setConfigurationMap( configurationMap );

    // Copy the efiSystemPartition setting to the global storage. It is needed not only in
    // the EraseDiskPage, but also in the bootloader configuration modules (grub, bootloader).
    Calamares::GlobalStorage* gs = Calamares::JobQueue::instance()->globalStorage();
    QString efiSP = CalamaresUtils::getString( configurationMap, "efiSystemPartition", QStringLiteral( "/boot/efi" ) );
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

    // Read and parse key efiSystemPartitionName
    if ( configurationMap.contains( "efiSystemPartitionName" ) )
    {
        gs->insert( "efiSystemPartitionName", CalamaresUtils::getString( configurationMap, "efiSystemPartitionName" ) );
    }

    // Read and parse key swapPartitionName
    if ( configurationMap.contains( "swapPartitionName" ) )
    {
        gs->insert( "swapPartitionName", CalamaresUtils::getString( configurationMap, "swapPartitionName" ) );
    }

    // OTHER SETTINGS
    //
    gs->insert( "drawNestedPartitions", CalamaresUtils::getBool( configurationMap, "drawNestedPartitions", false ) );
    gs->insert( "alwaysShowPartitionLabels",
                CalamaresUtils::getBool( configurationMap, "alwaysShowPartitionLabels", true ) );
    gs->insert( "enableLuksAutomatedPartitioning",
                CalamaresUtils::getBool( configurationMap, "enableLuksAutomatedPartitioning", true ) );

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

    QString partitionTableName = CalamaresUtils::getString( configurationMap, "defaultPartitionTableType" );
    if ( partitionTableName.isEmpty() )
    {
        cWarning() << "Partition-module setting *defaultPartitionTableType* is unset, "
                      "will use gpt for efi or msdos for bios";
    }
    gs->insert( "defaultPartitionTableType", partitionTableName );

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

    m_core->initLayout( fsType == FileSystem::Unknown ? FileSystem::Ext4 : fsType,
                        configurationMap.value( "partitionLayout" ).toList() );
}


Calamares::JobList
PartitionViewStep::jobs() const
{
    return m_core->jobs( m_config );
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
