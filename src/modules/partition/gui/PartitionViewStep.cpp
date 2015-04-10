/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

#include <gui/PartitionViewStep.h>

#include <core/DeviceModel.h>
#include <core/PartitionCoreModule.h>
#include <core/PartitionModel.h>
#include <core/PMUtils.h>
#include "core/partition.h"
#include "core/device.h"
#include <gui/ChoicePage.h>
#include <gui/EraseDiskPage.h>
#include <gui/AlongsidePage.h>
#include <gui/PartitionPage.h>
#include <gui/ReplacePage.h>
#include <gui/PartitionPreview.h>
#include "OsproberEntry.h"

#include "CalamaresVersion.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Retranslator.h"
#include "widgets/WaitingWidget.h"
#include "GlobalStorage.h"
#include "JobQueue.h"
#include "Job.h"

// Qt
#include <QApplication>
#include <QFormLayout>
#include <QLabel>
#include <QProcess>
#include <QStackedWidget>
#include <QTimer>

PartitionViewStep::PartitionViewStep( QObject* parent )
    : Calamares::ViewStep( parent )
    , m_widget( new QStackedWidget() )
    , m_core( new PartitionCoreModule( this ) )
    , m_choicePage( new ChoicePage() )
    , m_erasePage( new EraseDiskPage() )
    , m_alongsidePage( new AlongsidePage() )
    , m_manualPartitionPage( new PartitionPage( m_core ) )
    , m_replacePage( new ReplacePage( m_core ) )
{
    m_widget->setContentsMargins( 0, 0, 0, 0 );

    WaitingWidget* waitingWidget = new WaitingWidget( QString() );
    m_widget->addWidget( waitingWidget );
    CALAMARES_RETRANSLATE( waitingWidget->setText( tr( "Gathering system information..." ) ); )

    QTimer* timer = new QTimer;
    timer->setSingleShot( true );
    connect( timer, &QTimer::timeout,
             [=]()
    {
        QString osproberOutput;
        QProcess osprober;
        osprober.setProgram( "os-prober" );
        osprober.setProcessChannelMode( QProcess::SeparateChannels );
        osprober.start();
        if ( !osprober.waitForStarted() )
        {
            cDebug() << "ERROR: os-prober cannot start.";
        }
        else if ( !osprober.waitForFinished( 60000 ) )
        {
            cDebug() << "ERROR: os-prober timed out.";
        }
        else
        {
            osproberOutput.append(
                QString::fromLocal8Bit(
                    osprober.readAllStandardOutput() ).trimmed() );
        }

        QString osProberReport( "Osprober lines, clean:\n" );
        QStringList osproberCleanLines;
        OsproberEntryList osproberEntries;
        foreach ( const QString& line, osproberOutput.split( '\n' ) )
        {
            if ( !line.simplified().isEmpty() )
            {
                QStringList lineColumns = line.split( ':' );
                QString prettyName;
                if ( !lineColumns.value( 1 ).simplified().isEmpty() )
                    prettyName = lineColumns.value( 1 ).simplified();
                else if ( !lineColumns.value( 2 ).simplified().isEmpty() )
                    prettyName = lineColumns.value( 2 ).simplified();

                QString path = lineColumns.value( 0 ).simplified();
                if ( !path.startsWith( "/dev/" ) ) //basic sanity check
                    continue;

                osproberEntries.append( { prettyName, path, canBeResized( path ), lineColumns } );
                osproberCleanLines.append( line );
            }
        }
        osProberReport.append( osproberCleanLines.join( '\n' ) );
        cDebug() << osProberReport;
        Calamares::JobQueue::instance()->globalStorage()->insert( "osproberLines", osproberCleanLines );

        m_choicePage->init( m_core, osproberEntries );
        m_erasePage->init( m_core );
        m_alongsidePage->init( m_core, osproberEntries );

        m_widget->addWidget( m_choicePage );
        m_widget->addWidget( m_manualPartitionPage );
        m_widget->addWidget( m_alongsidePage );
        m_widget->addWidget( m_erasePage );
        m_widget->addWidget( m_replacePage );
        m_widget->removeWidget( waitingWidget );
        waitingWidget->deleteLater();

        timer->deleteLater();
    } );
    timer->start( 0 );

    connect( m_core,            &PartitionCoreModule::hasRootMountPointChanged,
             this,              &PartitionViewStep::nextStatusChanged );
    connect( m_choicePage,      &ChoicePage::nextStatusChanged,
             this,              &PartitionViewStep::nextStatusChanged );
    connect( m_erasePage,       &EraseDiskPage::nextStatusChanged,
             this,              &PartitionViewStep::nextStatusChanged );
    connect( m_alongsidePage,   &AlongsidePage::nextStatusChanged,
             this,              &PartitionViewStep::nextStatusChanged );
    connect( m_replacePage,     &ReplacePage::nextStatusChanged,
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
    QFormLayout* formLayout = new QFormLayout( widget );
    const int MARGIN = CalamaresUtils::defaultFontHeight() / 2;
    formLayout->setContentsMargins( MARGIN, 0, MARGIN, MARGIN );
    mainLayout->addLayout( formLayout );

    QList< PartitionCoreModule::SummaryInfo > list = m_core->createSummaryInfo();
    for ( const auto& info : list )
    {
        QLabel* diskInfoLabel = new QLabel( tr( "Disk <strong>%1</strong> (%2)" )
                                            .arg( info.deviceNode )
                                            .arg( info.deviceName ) );
        formLayout->addRow( diskInfoLabel );

        PartitionPreview* preview;

        preview = new PartitionPreview;
        preview->setModel( info.partitionModelBefore );
        info.partitionModelBefore->setParent( widget );
        formLayout->addRow( tr( "Before:" ), preview );

        preview = new PartitionPreview;
        preview->setModel( info.partitionModelAfter );
        info.partitionModelAfter->setParent( widget );
        formLayout->addRow( tr( "After:" ), preview );
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
        int m = CalamaresUtils::defaultFontHeight() / 2;
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
            m_widget->setCurrentWidget( m_manualPartitionPage );
        else if ( m_choicePage->currentChoice() == ChoicePage::Erase )
        {
            if ( m_core->isDirty() )
                m_core->revert();
            m_widget->setCurrentWidget( m_erasePage );
        }
        else if ( m_choicePage->currentChoice() == ChoicePage::Alongside )
        {
            if ( m_core->isDirty() )
                m_core->revert();
            m_widget->setCurrentWidget( m_alongsidePage );
        }
        else if ( m_choicePage->currentChoice() == ChoicePage::Replace )
        {
            if ( m_core->isDirty() )
                m_core->revert();
            m_widget->setCurrentWidget( m_replacePage );
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

    if ( m_erasePage && m_erasePage == m_widget->currentWidget() )
    {
        return m_erasePage->isNextEnabled() &&
               m_core->hasRootMountPoint();
    }

    if ( m_alongsidePage && m_alongsidePage == m_widget->currentWidget() )
        return m_alongsidePage->isNextEnabled();

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
    if ( m_widget->currentWidget() == m_manualPartitionPage ||
         m_widget->currentWidget() == m_erasePage ||
         m_widget->currentWidget() == m_alongsidePage ||
         m_widget->currentWidget() == m_replacePage )
        return false;
    return true;
}


bool
PartitionViewStep::isAtEnd() const
{
    if ( m_choicePage == m_widget->currentWidget() )
        return false;
    return true;
}


void
PartitionViewStep::onLeave()
{
    if ( m_widget->currentWidget() == m_alongsidePage )
    {
        m_alongsidePage->applyChanges();
    }
    else if ( m_widget->currentWidget() == m_replacePage )
    {
        m_replacePage->applyChanges();
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
}


QList< Calamares::job_ptr >
PartitionViewStep::jobs() const
{
    return m_core->jobs();
}


bool
PartitionViewStep::canBeResized( const QString& partitionPath )
{
    //FIXME: check for max partitions count on DOS MBR
    cDebug() << "checking if" << partitionPath << "can be resized.";
    QString partitionWithOs = partitionPath;
    if ( partitionWithOs.startsWith( "/dev/" ) )
    {
        cDebug() << partitionWithOs << "seems like a good path";
        bool canResize = false;
        DeviceModel* dm = m_core->deviceModel();
        for ( int i = 0; i < dm->rowCount(); ++i )
        {
            Device* dev = dm->deviceForIndex( dm->index( i ) );
            Partition* candidate = PMUtils::findPartitionByPath( { dev }, partitionWithOs );
            if ( candidate )
            {
                cDebug() << "found Partition* for" << partitionWithOs;
                if ( !candidate->fileSystem().supportGrow() ||
                     !candidate->fileSystem().supportShrink() )
                    return false;

                bool ok = false;
                double requiredStorageGB = Calamares::JobQueue::instance()
                                                ->globalStorage()
                                                ->value( "requiredStorageGB" )
                                                .toDouble( &ok );

                qint64 availableStorageB = candidate->available();

                // We require a little more for partitioning overhead and swap file
                // TODO: maybe make this configurable?
                qint64 requiredStorageB = ( requiredStorageGB + 0.1 + 2.0 ) * 1024 * 1024 * 1024;
                cDebug() << "Required  storage B:" << requiredStorageB
                         << QString( "(%1GB)" ).arg( requiredStorageB / 1024 / 1024 / 1024 );
                cDebug() << "Available storage B:" << availableStorageB
                         << QString( "(%1GB)" ).arg( availableStorageB / 1024 / 1024 / 1024 );

                if ( ok &&
                     availableStorageB > requiredStorageB )
                {
                    cDebug() << "Partition" << partitionWithOs << "authorized for resize + autopartition install.";

                    return true;
                }
            }
        }
    }

    cDebug() << "Partition" << partitionWithOs << "CANNOT BE RESIZED FOR AUTOINSTALL.";
    return false;
}
