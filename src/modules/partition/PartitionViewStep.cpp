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
#include "utils/Gui.h"
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
        if ( m_waitingWidget ) { m_waitingWidget->setText( tr( "Gathering system information…", "@status" ) ); } );

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
    return tr( "Partitions", "@label" );
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
 * Returns a translated string describing what @p choice will do.
 * Includes branding information.
 */
static QString
modeDescription( Config::InstallChoice choice )
{
    const auto* branding = Calamares::Branding::instance();

    switch ( choice )
    {
    case Config::InstallChoice::Alongside:
        return QCoreApplication::translate(
                   "PartitionViewStep", "Install %1 <strong>alongside</strong> another operating system", "@label" )
            .arg( branding->shortVersionedName() );
    case Config::InstallChoice::Erase:
        return QCoreApplication::translate(
                   "PartitionViewStep", "<strong>Erase</strong> disk and install %1", "@label" )
            .arg( branding->shortVersionedName() );
    case Config::InstallChoice::Replace:
        return QCoreApplication::translate(
                   "PartitionViewStep", "<strong>Replace</strong> a partition with %1", "@label" )
            .arg( branding->shortVersionedName() );
    case Config::InstallChoice::NoChoice:
    case Config::InstallChoice::Manual:
        return QCoreApplication::translate( "PartitionViewStep", "<strong>Manual</strong> partitioning", "@label" );
    }
    return QString();
}

/** @brief A top-level description of what @p choice does to disk @p info
 *
 * Returns a translated string, with branding and device information, describing what
 * will be done to device @p info when @p choice is made. The @p listLength
 * is used to provide context; when more than one disk is in use, the description
 * works differently.
 */
static QString
diskDescription( int listLength, const PartitionCoreModule::SummaryInfo& info, Config::InstallChoice choice )
{
    const auto* branding = Calamares::Branding::instance();

    if ( listLength == 1 )  // this is the only disk preview
    {
        switch ( choice )
        {
        case Config::Alongside:
            return QCoreApplication::translate(
                       "PartitionViewStep",
                       "Install %1 <strong>alongside</strong> another operating system on disk "
                       "<strong>%2</strong> (%3)",
                       "@info" )
                .arg( branding->shortVersionedName() )
                .arg( info.deviceNode )
                .arg( info.deviceName );
        case Config::Erase:
            return QCoreApplication::translate( "PartitionViewStep",
                                                "<strong>Erase</strong> disk <strong>%2</strong> (%3) and install %1",
                                                "@info" )
                .arg( branding->shortVersionedName() )
                .arg( info.deviceNode )
                .arg( info.deviceName );
        case Config::Replace:
            return QCoreApplication::translate(
                       "PartitionViewStep",
                       "<strong>Replace</strong> a partition on disk <strong>%2</strong> (%3) with %1",
                       "@info" )
                .arg( branding->shortVersionedName() )
                .arg( info.deviceNode )
                .arg( info.deviceName );
        case Config::NoChoice:
        case Config::Manual:
            return QCoreApplication::translate( "PartitionViewStep",
                                                "<strong>Manual</strong> partitioning on disk <strong>%1</strong> (%2)",
                                                "@info" )
                .arg( info.deviceNode )
                .arg( info.deviceName );
        }
        return QString();
    }
    else  // multiple disk previews!
    {
        return QCoreApplication::translate( "PartitionViewStep", "Disk <strong>%1</strong> (%2)", "@info" )
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
    auto joinDiskInfo = [ choice ]( QString& s, const PartitionCoreModule::SummaryInfo& i )
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
    Calamares::unmarginLayout( mainLayout );

    Config::InstallChoice choice = m_config->installChoice();

    QFormLayout* formLayout = new QFormLayout( widget );
    const int MARGIN = Calamares::defaultFontHeight() / 2;
    formLayout->setContentsMargins( MARGIN, 0, MARGIN, MARGIN );
    mainLayout->addLayout( formLayout );

#if defined( DEBUG_PARTITION_UNSAFE ) || defined( DEBUG_PARTITION_BAIL_OUT ) || defined( DEBUG_PARTITION_SKIP )
    auto specialRow = [ = ]( Calamares::ImageType t, const QString& s )
    {
        QLabel* icon = new QLabel;
        icon->setPixmap( Calamares::defaultPixmap( t ) );
        formLayout->addRow( icon, new QLabel( s ) );
    };
#endif
#if defined( DEBUG_PARTITION_UNSAFE )
    specialRow( Calamares::ImageType::StatusWarning, tr( "Unsafe partition actions are enabled." ) );
#endif
#if defined( DEBUG_PARTITION_BAIL_OUT )
    specialRow( Calamares::ImageType::Information, tr( "Partitioning is configured to <b>always</b> fail." ) );
#endif
#if defined( DEBUG_PARTITION_SKIP )
    specialRow( Calamares::ImageType::Information, tr( "No partitions will be changed." ) );
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
        Calamares::unmarginLayout( field );
        field->setSpacing( 6 );
        field->addWidget( preview );
        field->addWidget( previewLabels );
        formLayout->addRow( tr( "Current:", "@label" ), field );

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
        Calamares::unmarginLayout( field );
        field->setSpacing( 6 );
        field->addWidget( preview );
        field->addWidget( previewLabels );
        formLayout->addRow( tr( "After:", "@label" ), field );
    }
    const QStringList jobsLines = jobDescriptions( jobs() );
    if ( !jobsLines.isEmpty() )
    {
        QLabel* jobsLabel = new QLabel( widget );
        mainLayout->addWidget( jobsLabel );
        jobsLabel->setText( jobsLines.join( "<br/>" ) );
        jobsLabel->setMargin( Calamares::defaultFontHeight() / 2 );
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
                using Calamares::Units::operator""_MiB;
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

static bool
shouldWarnForNotEncryptedBoot( const Config* config, const PartitionCoreModule* core )
{
    if ( config->showNotEncryptedBootMessage() )
    {
        Partition* root_p = core->findPartitionByMountPoint( "/" );
        Partition* boot_p = core->findPartitionByMountPoint( "/boot" );

        if ( root_p && boot_p )
        {
            const auto encryptionMismatch
                = [ root_t = root_p->fileSystem().type(), boot_t = boot_p->fileSystem().type() ]( FileSystem::Type t )
            { return root_t == t && boot_t != t; };
            if ( encryptionMismatch( FileSystem::Luks ) || encryptionMismatch( FileSystem::Luks2 ) )
            {
                return true;
            }
        }
    }
    return false;
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
            const bool okRecommendedSize = esp && PartUtils::isEfiFilesystemRecommendedSize( esp );
            const bool okMinimumSize = esp && PartUtils::isEfiFilesystemMinimumSize( esp );
            const bool okFlag = esp && PartUtils::isEfiBootable( esp );

            const bool espExistsButIsWrong = esp && !( okType && okMinimumSize && okFlag );

            const QString genericWrongnessMessage = tr( "An EFI system partition is necessary to start %1."
                                                        "<br/><br/>"
                                                        "To configure an EFI system partition, go back and "
                                                        "select or create a suitable filesystem." )
                                                        .arg( branding->shortProductName() );
            const QString genericRecommendationMessage
                = tr( "An EFI system partition is necessary to start %1."
                      "<br/><br/>"
                      "The EFI system partition does not meet recommendations. It is "
                      "recommended to go back and "
                      "select or create a suitable filesystem." )
                      .arg( branding->shortProductName() );

            const QString wrongMountPointMessage
                = tr( "The filesystem must be mounted on <strong>%1</strong>." ).arg( espMountPoint );
            const QString wrongTypeMessage = tr( "The filesystem must have type FAT32." );
            const QString wrongFlagMessage = tr( "The filesystem must have flag <strong>%1</strong> set." )
                                                 .arg( PartitionTable::flagName( PartitionTable::Flag::Boot ) );

            const auto recommendedMiB = Calamares::BytesToMiB( PartUtils::efiFilesystemRecommendedSize() );
            const auto minimumMiB = Calamares::BytesToMiB( PartUtils::efiFilesystemMinimumSize() );

            // Three flavors of size-is-wrong
            const QString requireConfiguredSize
                = tr( "The filesystem must be at least %1 MiB in size." ).arg( recommendedMiB );
            const QString requiredMinimumSize
                = tr( "The filesystem must be at least %1 MiB in size." ).arg( minimumMiB );
            const QString suggestConfiguredSize
                = tr( "The minimum recommended size for the filesystem is %1 MiB." ).arg( recommendedMiB );

            const QString mayFail = tr( "You can continue without setting up an EFI system "
                                        "partition but your system may fail to start." );
            const QString possibleFail = tr( "You can continue with this EFI system "
                                             "partition configuration but your system may fail to start." );

            const QString startList = QStringLiteral( "<br/><br/><ul>" );
            const QString endList = QStringLiteral( "</ul><br/><br/>" );

            auto listItem = []( QString s ) -> QString
            { return s.prepend( QStringLiteral( "<li>" ) ).append( QStringLiteral( "</li>" ) ); };

            if ( !esp )
            {
                cDebug() << o << "No ESP mounted";
                message = tr( "No EFI system partition configured" );

                description = genericWrongnessMessage + startList + listItem( wrongMountPointMessage )
                    + listItem( requireConfiguredSize ) + listItem( wrongTypeMessage ) + listItem( wrongFlagMessage )
                    + endList + mayFail;
            }
            else if ( espExistsButIsWrong )
            {
                message = tr( "EFI system partition configured incorrectly" );

                description = genericWrongnessMessage + startList;
                if ( !okMinimumSize )
                {
                    description.append( listItem( requiredMinimumSize ) );
                }
                if ( !okType )
                {
                    description.append( listItem( wrongTypeMessage ) );
                }
                if ( !okFlag )
                {
                    description.append( listItem( wrongFlagMessage ) );
                }
                description.append( endList );
                description.append( mayFail );
            }
            else if ( !okRecommendedSize )
            {
                message = tr( "EFI system partition recommendation" );
                description = genericRecommendationMessage + suggestConfiguredSize + possibleFail;
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

        if ( shouldWarnForNotEncryptedBoot( m_config, m_core ) )
        {
            QString message = tr( "Boot partition not encrypted" );
            QString description = tr( "A separate boot partition was set up together with "
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
        gs->insert( "swapPartitionName", Calamares::getString( configurationMap, "swapPartitionName" ) );
    }

    // OTHER SETTINGS
    //
    gs->insert( "drawNestedPartitions", Calamares::getBool( configurationMap, "drawNestedPartitions", false ) );
    gs->insert( "alwaysShowPartitionLabels",
                Calamares::getBool( configurationMap, "alwaysShowPartitionLabels", true ) );
    gs->insert( "enableLuksAutomatedPartitioning",
                Calamares::getBool( configurationMap, "enableLuksAutomatedPartitioning", true ) );

    QString partitionTableName = Calamares::getString( configurationMap, "defaultPartitionTableType" );
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

#if QT_VERSION < QT_VERSION_CHECK( 6, 0, 0 )
    QFuture< void > future = QtConcurrent::run( this, &PartitionViewStep::initPartitionCoreModule );
#else
    QFuture< void > future = QtConcurrent::run( &PartitionViewStep::initPartitionCoreModule, this );
#endif
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
