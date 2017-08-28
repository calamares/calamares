/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
 *   Copyright 2014-2017, Teo Mrnjavac <teo@kde.org>
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
#include "core/PartitionCoreModule.h"
#include "core/PartitionModel.h"
#include "core/KPMHelpers.h"
#include "core/OsproberEntry.h"
#include "core/PartUtils.h"
#include "gui/ChoicePage.h"
#include "gui/PartitionPage.h"
#include "gui/PartitionBarsView.h"
#include "gui/PartitionLabelsView.h"

#include "CalamaresVersion.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "widgets/WaitingWidget.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Job.h"
#include "Branding.h"

#include <kpmcore/core/device.h>
#include <kpmcore/core/partition.h>
#include <kpmcore/fs/filesystem.h>

// Qt
#include <QApplication>
#include <QDir>
#include <QFormLayout>
#include <QLabel>
#include <QMessageBox>
#include <QProcess>
#include <QStackedWidget>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include <QFutureWatcher>

PartitionViewStep::PartitionViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_core( nullptr )
    , m_widget( new QStackedWidget() )
    , m_choicePage( nullptr )
    , m_manualPartitionPage( nullptr )
{
    m_widget->setContentsMargins( 0, 0, 0, 0 );

    m_waitingWidget = new WaitingWidget( QString() );
    m_widget->addWidget( m_waitingWidget );
    CALAMARES_RETRANSLATE( qobject_cast< WaitingWidget* >( m_waitingWidget )->setText( tr( "Gathering system information..." ) ); )

    m_core = new PartitionCoreModule( this ); // Unusable before init is complete!
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
    Q_ASSERT( !m_manualPartitionPage );

    m_manualPartitionPage = new PartitionPage( m_core );
    m_choicePage = new ChoicePage();

    m_choicePage->init( m_core );

    m_widget->addWidget( m_choicePage );
    m_widget->addWidget( m_manualPartitionPage );
    m_widget->removeWidget( m_waitingWidget );
    m_waitingWidget->deleteLater();
    m_waitingWidget = nullptr;

    connect( m_core,            &PartitionCoreModule::hasRootMountPointChanged,
             this,              &PartitionViewStep::nextStatusChanged );
    connect( m_choicePage,      &ChoicePage::nextStatusChanged,
             this,              &PartitionViewStep::nextStatusChanged );
}


PartitionViewStep::~PartitionViewStep()
{
    if ( m_choicePage && m_choicePage->parent() == nullptr )
        m_choicePage->deleteLater();
    if ( m_manualPartitionPage && m_manualPartitionPage->parent() == nullptr )
        m_manualPartitionPage->deleteLater();
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

    ChoicePage::Choice choice = m_choicePage->currentChoice();

    QFormLayout* formLayout = new QFormLayout( widget );
    const int MARGIN = CalamaresUtils::defaultFontHeight() / 2;
    formLayout->setContentsMargins( MARGIN, 0, MARGIN, MARGIN );
    mainLayout->addLayout( formLayout );

    QList< PartitionCoreModule::SummaryInfo > list = m_core->createSummaryInfo();
    if ( list.length() > 1 ) // There are changes on more than one disk
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
            modeText = tr( "<strong>Erase</strong> disk and install %1." )
                       .arg( *Calamares::Branding::ShortVersionedName );
            break;
        case ChoicePage::Replace:
            modeText = tr( "<strong>Replace</strong> a partition with %1." )
                       .arg( *Calamares::Branding::ShortVersionedName );
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
        if ( list.length() == 1 ) // this is the only disk preview
        {
            QString modeText;
            switch ( choice )
            {
            case ChoicePage::Alongside:
                modeText = tr( "Install %1 <strong>alongside</strong> another operating system on disk <strong>%2</strong> (%3)." )
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
        else // multiple disk previews!
        {
            diskInfoLabel->setText( tr( "Disk <strong>%1</strong> (%2)" )
                                        .arg( info.deviceNode )
                                        .arg( info.deviceName ) );
        }
        formLayout->addRow( diskInfoLabel );

        PartitionBarsView* preview;
        PartitionLabelsView* previewLabels;
        QVBoxLayout* field;

        PartitionBarsView::NestedPartitionsMode mode = Calamares::JobQueue::instance()->globalStorage()->
                                                       value( "drawNestedPartitions" ).toBool() ?
                                                           PartitionBarsView::DrawNestedPartitions :
                                                           PartitionBarsView::NoNestedPartitions;
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
        jobsLines.append( job->prettyDescription() );
    }
    if ( !jobsLines.isEmpty() )
    {
        QLabel* jobsLabel = new QLabel( widget );
        mainLayout->addWidget( jobsLabel );
        jobsLabel->setText( jobsLines.join( "<br/>" ) );
        jobsLabel->setMargin( CalamaresUtils::defaultFontHeight() / 2 );
        QPalette pal;
        pal.setColor( QPalette::Background, pal.background().color().lighter( 108 ) );
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
            m_widget->setCurrentWidget( m_manualPartitionPage );
            if ( m_core->isDirty() )
                m_manualPartitionPage->onRevertClicked();
        }
        else if ( m_choicePage->currentChoice() == ChoicePage::Erase )
        {
            emit done();
            return;
        }
        else if ( m_choicePage->currentChoice() == ChoicePage::Alongside )
        {
            emit done();
            return;
        }
        else if ( m_choicePage->currentChoice() == ChoicePage::Replace )
        {
            emit done();
            return;
        }
        cDebug() << "Choice applied: " << m_choicePage->currentChoice();
        return;
    }
    emit done();
}


void
PartitionViewStep::back()
{
    if ( m_widget->currentWidget() != m_choicePage )
        m_widget->setCurrentWidget( m_choicePage );
}


bool
PartitionViewStep::isNextEnabled() const
{
    if ( m_choicePage && m_choicePage == m_widget->currentWidget() )
        return m_choicePage->isNextEnabled();

    if ( m_manualPartitionPage && m_manualPartitionPage == m_widget->currentWidget() )
        return m_core->hasRootMountPoint();

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
    if ( m_widget->currentWidget() == m_manualPartitionPage )
        return false;
    return true;
}


bool
PartitionViewStep::isAtEnd() const
{
    if ( m_choicePage == m_widget->currentWidget() )
    {
        if ( m_choicePage->currentChoice() == ChoicePage::Erase ||
             m_choicePage->currentChoice() == ChoicePage::Replace ||
             m_choicePage->currentChoice() == ChoicePage::Alongside )
            return true;
        return false;
    }
    return true;
}


void
PartitionViewStep::onActivate()
{
    // if we're coming back to PVS from the next VS
    if ( m_widget->currentWidget() == m_choicePage &&
         m_choicePage->currentChoice() == ChoicePage::Alongside )
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
            QString espMountPoint = Calamares::JobQueue::instance()->globalStorage()->
                                        value( "efiSystemPartition").toString();
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
            else if ( esp && !esp->activeFlags().testFlag( PartitionTable::FlagEsp ) )
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
                QMessageBox::warning( m_manualPartitionPage,
                                      message,
                                      description );
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
            if ( root_p->fileSystem().type() == FileSystem::Luks &&
                 boot_p->fileSystem().type() != FileSystem::Luks )
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

                QMessageBox::warning( m_manualPartitionPage,
                                      message,
                                      description );
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
    if ( configurationMap.contains( "efiSystemPartition" ) &&
         configurationMap.value( "efiSystemPartition" ).type() == QVariant::String &&
         !configurationMap.value( "efiSystemPartition" ).toString().isEmpty() )
    {
        gs->insert( "efiSystemPartition", configurationMap.value( "efiSystemPartition" ).toString() );
    }
    else
    {
        gs->insert( "efiSystemPartition", QStringLiteral( "/boot/efi" ) );
    }

    if ( configurationMap.contains( "ensureSuspendToDisk" ) &&
         configurationMap.value( "ensureSuspendToDisk" ).type() == QVariant::Bool )
    {
        gs->insert( "ensureSuspendToDisk", configurationMap.value( "ensureSuspendToDisk" ).toBool() );
    }
    else
    {
        gs->insert( "ensureSuspendToDisk", true );
    }

    if ( configurationMap.contains( "neverCreateSwap" ) &&
         configurationMap.value( "neverCreateSwap" ).type() == QVariant::Bool )
    {
        gs->insert( "neverCreateSwap", configurationMap.value( "neverCreateSwap" ).toBool() );
    }
    else
    {
        gs->insert( "neverCreateSwap", false );
    }

    if ( configurationMap.contains( "drawNestedPartitions" ) &&
         configurationMap.value( "drawNestedPartitions" ).type() == QVariant::Bool )
    {
        gs->insert( "drawNestedPartitions",
                    configurationMap.value( "drawNestedPartitions", false ).toBool() );
    }
    else
    {
        gs->insert( "drawNestedPartitions", false );
    }

    if ( configurationMap.contains( "alwaysShowPartitionLabels" ) &&
         configurationMap.value( "alwaysShowPartitionLabels" ).type() == QVariant::Bool )
    {
        gs->insert( "alwaysShowPartitionLabels",
                    configurationMap.value( "alwaysShowPartitionLabels", true ).toBool() );
    }
    else
    {
        gs->insert( "alwaysShowPartitionLabels", true );
    }

    if ( configurationMap.contains( "defaultFileSystemType" ) &&
         configurationMap.value( "defaultFileSystemType" ).type() == QVariant::String &&
         !configurationMap.value( "defaultFileSystemType" ).toString().isEmpty() )
    {
        QString typeString = configurationMap.value( "defaultFileSystemType" ).toString();
        gs->insert( "defaultFileSystemType", typeString );
        if ( FileSystem::typeForName( typeString ) == FileSystem::Unknown )
        {
            cDebug() << "WARNING: bad default filesystem configuration for partition module. Reverting to ext4 as default.";
            gs->insert( "defaultFileSystemType", "ext4" );
        }
    }
    else
    {
        gs->insert( "defaultFileSystemType", QStringLiteral( "ext4" ) );
    }

    if ( configurationMap.contains( "enableLuksAutomatedPartitioning" ) &&
         configurationMap.value( "enableLuksAutomatedPartitioning" ).type() == QVariant::Bool )
    {
        gs->insert( "enableLuksAutomatedPartitioning",
                    configurationMap.value( "enableLuksAutomatedPartitioning" ).toBool() );
    }
    else
    {
        gs->insert( "enableLuksAutomatedPartitioning", true );
    }


    // Now that we have the config, we load the PartitionCoreModule in the background
    // because it could take a while. Then when it's done, we can set up the widgets
    // and remove the spinner.
    QFutureWatcher< void >* watcher = new QFutureWatcher< void >();
    connect( watcher, &QFutureWatcher< void >::finished,
             this, [ this, watcher ]
    {
        continueLoading();
        watcher->deleteLater();
    } );

    QFuture< void > future =
            QtConcurrent::run( this, &PartitionViewStep::initPartitionCoreModule );
    watcher->setFuture( future );
}


QList< Calamares::job_ptr >
PartitionViewStep::jobs() const
{
    return m_core->jobs();
}


CALAMARES_PLUGIN_FACTORY_DEFINITION( PartitionViewStepFactory, registerPlugin<PartitionViewStep>(); )
