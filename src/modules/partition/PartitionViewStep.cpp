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

#include "PartitionViewStep.h"

#include "Config.h"
#include "core/BootLoaderModel.h"
#include "core/DeviceModel.h"
#include "core/PartitionCoreModule.h"
#include "gui/ChoicePage.h"
#include "gui/PartitionBarsView.h"
#include "gui/PartitionLabelsView.h"
#include "gui/PartitionPage.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/QtCompat.h"
#include "utils/Retranslator.h"
#include "utils/Variant.h"
#include "widgets/TranslationFix.h"
#include "widgets/WaitingWidget.h"

#include <kpmcore/core/partition.h>

#include <QFormLayout>
#include <QMessageBox>
#include <QStackedWidget>
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
    CALAMARES_RETRANSLATE(
        if ( m_waitingWidget ) { m_waitingWidget->setText( tr( "Gathering system information..." ) ); } );

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

/** @brief Gather the pretty descriptions of all the partitioning jobs
 *
 * Returns a QStringList of each job's pretty description, including
 * empty strings and duplicates. The list is in-order of how the
 * jobs will be run.
 */
static QStringList
jobDescriptions( const Calamares::JobList& jobs )
{
    QStringList jobsLines;
    for ( const Calamares::job_ptr& job : qAsConst( jobs ) )
    {
        if ( !job->prettyDescription().isEmpty() )
        {
            jobsLines.append( job->prettyDescription() );
        }
    }
    return jobsLines;
}

/** @brief A top-level description of what @p choice does
 *
 * Returns a (branded) string describing what @p choice will do.
 */
static QString
modeDescription( Config::InstallChoice choice )
{
    const auto* branding = Calamares::Branding::instance();
    static const char context[] = "PartitionViewStep";

    switch ( choice )
    {
    case Config::InstallChoice::Alongside:
        return QCoreApplication::translate( context, "Install %1 <strong>alongside</strong> another operating system." )
            .arg( branding->shortVersionedName() );
    case Config::InstallChoice::Erase:
        return QCoreApplication::translate( context, "<strong>Erase</strong> disk and install %1." )
            .arg( branding->shortVersionedName() );
    case Config::InstallChoice::Replace:
        return QCoreApplication::translate( context, "<strong>Replace</strong> a partition with %1." )
            .arg( branding->shortVersionedName() );
    case Config::InstallChoice::NoChoice:
    case Config::InstallChoice::Manual:
        return QCoreApplication::translate( context, "<strong>Manual</strong> partitioning." );
    }
    return QString();
}

/** @brief A top-level description of what @p choice does to disk @p info
 *
 * Returns a (branded, and device-specific) string describing what
 * will be done to device @p info when @p choice is made. The @p listLength
 * is used to provide context; when more than one disk is in use, the description
 * works differently.
 */
static QString
diskDescription( int listLength, const PartitionCoreModule::SummaryInfo& info, Config::InstallChoice choice )
{
    const auto* branding = Calamares::Branding::instance();
    static const char context[] = "PartitionViewStep";

    if ( listLength == 1 )  // this is the only disk preview
    {
        switch ( choice )
        {
        case Config::Alongside:
            return QCoreApplication::translate(
                       context,
                       "Install %1 <strong>alongside</strong> another operating system on disk "
                       "<strong>%2</strong> (%3)." )
                .arg( branding->shortVersionedName() )
                .arg( info.deviceNode )
                .arg( info.deviceName );
        case Config::Erase:
            return QCoreApplication::translate( context,
                                                "<strong>Erase</strong> disk <strong>%2</strong> (%3) and install %1." )
                .arg( branding->shortVersionedName() )
                .arg( info.deviceNode )
                .arg( info.deviceName );
        case Config::Replace:
            return QCoreApplication::translate(
                       context, "<strong>Replace</strong> a partition on disk <strong>%2</strong> (%3) with %1." )
                .arg( branding->shortVersionedName() )
                .arg( info.deviceNode )
                .arg( info.deviceName );
        case Config::NoChoice:
        case Config::Manual:
            return QCoreApplication::translate(
                       context, "<strong>Manual</strong> partitioning on disk <strong>%1</strong> (%2)." )
                .arg( info.deviceNode )
                .arg( info.deviceName );
        }
        return QString();
    }
    else  // multiple disk previews!
    {
        return QCoreApplication::translate( context, "Disk <strong>%1</strong> (%2)" )
            .arg( info.deviceNode )
            .arg( info.deviceName );
    }
}

QString
PartitionViewStep::prettyStatus() const
{
    const Config::InstallChoice choice = m_config->installChoice();
    const QList< PartitionCoreModule::SummaryInfo > list = m_core->createSummaryInfo();

    cDebug() << "Summary for Partition" << list.length() << choice;
    auto joinDiskInfo = [ choice = choice ]( QString& s, const PartitionCoreModule::SummaryInfo& i )
    { return s + diskDescription( 1, i, choice ); };
    const QString diskInfoLabel = std::accumulate( list.begin(), list.end(), QString(), joinDiskInfo );
    const QString jobsLabel = jobDescriptions( jobs() ).join( QStringLiteral( "<br/>" ) );
    return diskInfoLabel + "<br/>" + jobsLabel;
}

QWidget*
PartitionViewStep::createSummaryWidget() const
{
    QWidget* widget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    widget->setLayout( mainLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    Config::InstallChoice choice = m_config->installChoice();

    QFormLayout* formLayout = new QFormLayout( widget );
    const int MARGIN = CalamaresUtils::defaultFontHeight() / 2;
    formLayout->setContentsMargins( MARGIN, 0, MARGIN, MARGIN );
    mainLayout->addLayout( formLayout );

#if defined( DEBUG_PARTITION_UNSAFE ) || defined( DEBUG_PARTITION_BAIL_OUT ) || defined( DEBUG_PARTITION_SKIP )
    auto specialRow = [ = ]( CalamaresUtils::ImageType t, const QString& s )
    {
        QLabel* icon = new QLabel;
        icon->setPixmap( CalamaresUtils::defaultPixmap( t ) );
        formLayout->addRow( icon, new QLabel( s ) );
    };
#endif
#if defined( DEBUG_PARTITION_UNSAFE )
    specialRow( CalamaresUtils::ImageType::StatusWarning, tr( "Unsafe partition actions are enabled." ) );
#endif
#if defined( DEBUG_PARTITION_BAIL_OUT )
    specialRow( CalamaresUtils::ImageType::Information, tr( "Partitioning is configured to <b>always</b> fail." ) );
#endif
#if defined( DEBUG_PARTITION_SKIP )
    specialRow( CalamaresUtils::ImageType::Information, tr( "No partitions will be changed." ) );
#endif

    const QList< PartitionCoreModule::SummaryInfo > list = m_core->createSummaryInfo();
    if ( list.length() > 1 )  // There are changes on more than one disk
    {
        //NOTE: all of this should only happen when Manual partitioning is active.
        //      Any other choice should result in a list.length() == 1.
        QLabel* modeLabel = new QLabel;
        formLayout->addRow( modeLabel );
        modeLabel->setText( modeDescription( choice ) );
    }
    for ( const auto& info : list )
    {
        QLabel* diskInfoLabel = new QLabel;
        diskInfoLabel->setText( diskDescription( list.length(), info, choice ) );
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
    const QStringList jobsLines = jobDescriptions( jobs() );
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

QWidget*
PartitionViewStep::widget()
{
    return m_widget;
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
    Q_EMIT nextStatusChanged( isNextEnabled() );
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
    m_config->fillGSSecondaryConfiguration();

    // if we're coming back to PVS from the next VS
    if ( m_widget->currentWidget() == m_choicePage && m_config->installChoice() == Config::InstallChoice::Alongside )
    {
        m_choicePage->applyActionChoice( Config::InstallChoice::Alongside );
        //        m_choicePage->reset();
        //FIXME: ReplaceWidget should be reset maybe?
    }
}

static bool
shouldWarnForGPTOnBIOS( const PartitionCoreModule* core )
{
    if ( PartUtils::isEfiSystem() )
    {
        return false;
    }

    const QString biosFlagName = PartitionTable::flagName( KPM_PARTITION_FLAG( BiosGrub ) );

    auto [ r, device ] = core->bootLoaderModel()->findBootLoader( core->bootLoaderInstallPath() );
    Q_UNUSED( r );
    if ( device )
    {
        auto* table = device->partitionTable();
        cDebug() << "Found device for bootloader" << device->deviceNode();
        if ( table && table->type() == PartitionTable::TableType::gpt )
        {
            // So this is a BIOS system, and the bootloader will be installed on a GPT system
            for ( const auto& partition : qAsConst( table->children() ) )
            {
                using CalamaresUtils::Units::operator""_MiB;
                if ( ( partition->activeFlags() & KPM_PARTITION_FLAG( BiosGrub ) )
                     && ( partition->fileSystem().type() == FileSystem::Unformatted )
                     && ( partition->capacity() >= 8_MiB ) )
                {
                    cDebug() << Logger::SubEntry << "Partition" << partition->devicePath() << partition->partitionPath()
                             << "is a suitable" << biosFlagName << "partition";
                    return false;
                }
            }
        }
        cDebug() << Logger::SubEntry << "No suitable partition for" << biosFlagName << "found";
    }
    else
    {
        cDebug() << "Found no device for" << core->bootLoaderInstallPath();
    }
    return true;
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
            const QString espMountPoint
                = Calamares::JobQueue::instance()->globalStorage()->value( "efiSystemPartition" ).toString();
            Partition* esp = m_core->findPartitionByMountPoint( espMountPoint );

            QString message;
            QString description;

            Logger::Once o;

            const bool okType = esp && PartUtils::isEfiFilesystemSuitableType( esp );
            const bool okSize = esp && PartUtils::isEfiFilesystemSuitableSize( esp );
            const bool okFlag = esp && PartUtils::isEfiBootable( esp );

            if ( !esp )
            {
                message = tr( "No EFI system partition configured" );
            }
            else if ( !( okType && okSize && okFlag ) )
            {
                message = tr( "EFI system partition configured incorrectly" );
            }

            if ( !esp || !( okType && okSize && okFlag ) )
            {
                description = tr( "An EFI system partition is necessary to start %1."
                                  "<br/><br/>"
                                  "To configure an EFI system partition, go back and "
                                  "select or create a suitable filesystem." )
                                  .arg( branding->shortProductName() );
            }
            if ( !esp )
            {
                cDebug() << o << "No ESP mounted";
                description.append( ' ' );
                description.append(
                    tr( "The filesystem must be mounted on <strong>%1</strong>." ).arg( espMountPoint ) );
            }
            if ( !okType )
            {
                cDebug() << o << "ESP wrong type";
                description.append( ' ' );
                description.append( tr( "The filesystem must have type FAT32." ) );
            }
            if ( !okSize )
            {
                cDebug() << o << "ESP too small";
                const qint64 atLeastBytes = static_cast< qint64 >( PartUtils::efiFilesystemMinimumSize() );
                const auto atLeastMiB = CalamaresUtils::BytesToMiB( atLeastBytes );
                description.append( ' ' );
                description.append( tr( "The filesystem must be at least %1 MiB in size." ).arg( atLeastMiB ) );
            }
            if ( !okFlag )
            {
                cDebug() << o << "ESP missing flag";
                description.append( ' ' );
                description.append( tr( "The filesystem must have flag <strong>%1</strong> set." )
                                        .arg( PartitionTable::flagName( PartitionTable::Flag::Boot ) ) );
            }
            if ( !description.isEmpty() )
            {
                description.append( "<br/><br/>" );
                description.append( tr( "You can continue without setting up an EFI system "
                                        "partition but your system may fail to start." ) );
            }
            if ( !message.isEmpty() )
            {
                QMessageBox mb( QMessageBox::Warning, message, description, QMessageBox::Ok, m_manualPartitionPage );
                Calamares::fixButtonLabels( &mb );
                mb.exec();
            }
        }
        else
        {

            cDebug() << "device: BIOS";

            if ( shouldWarnForGPTOnBIOS( m_core ) )
            {
                const QString biosFlagName = PartitionTable::flagName( KPM_PARTITION_FLAG( BiosGrub ) );
                QString message = tr( "Option to use GPT on BIOS" );
                QString description = tr( "A GPT partition table is the best option for all "
                                          "systems. This installer supports such a setup for "
                                          "BIOS systems too."
                                          "<br/><br/>"
                                          "To configure a GPT partition table on BIOS, "
                                          "(if not done so already) go back "
                                          "and set the partition table to GPT, next create a 8 MB "
                                          "unformatted partition with the "
                                          "<strong>%2</strong> flag enabled.<br/><br/>"
                                          "An unformatted 8 MB partition is necessary "
                                          "to start %1 on a BIOS system with GPT." )
                                          .arg( branding->shortProductName(), biosFlagName );

                QMessageBox mb(
                    QMessageBox::Information, message, description, QMessageBox::Ok, m_manualPartitionPage );
                Calamares::fixButtonLabels( &mb );
                mb.exec();
            }
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

                QMessageBox mb( QMessageBox::Warning, message, description, QMessageBox::Ok, m_manualPartitionPage );
                Calamares::fixButtonLabels( &mb );
                mb.exec();
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
    connect( m_future,
             &QFutureWatcher< void >::finished,
             this,
             [ this ]
             {
                 continueLoading();
                 this->m_future->deleteLater();
                 this->m_future = nullptr;
             } );

    QFuture< void > future = QtConcurrent::run( this, &PartitionViewStep::initPartitionCoreModule );
    m_future->setFuture( future );

    m_core->partitionLayout().init( m_config->defaultFsType(), configurationMap.value( "partitionLayout" ).toList() );
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
