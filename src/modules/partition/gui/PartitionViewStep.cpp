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

#include "gui/PartitionViewStep.h"

#include "core/DeviceModel.h"
#include "core/PartitionCoreModule.h"
#include "core/PartitionModel.h"
#include "core/KPMHelpers.h"
#include "core/OsproberEntry.h"
#include "core/PartUtils.h"
#include "gui/ChoicePage.h"
#include "gui/AlongsidePage.h"
#include "gui/PartitionPage.h"
#include "gui/ReplacePage.h"
#include "gui/PartitionPreview.h"

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
    , m_choicePage( nullptr )
    , m_alongsidePage( new AlongsidePage() )
    , m_manualPartitionPage( new PartitionPage( m_core ) )
    , m_replacePage( new ReplacePage( m_core ) )
    , m_compactMode( true )
{
    m_widget->setContentsMargins( 0, 0, 0, 0 );

    m_waitingWidget = new WaitingWidget( QString() );
    m_widget->addWidget( m_waitingWidget );
    CALAMARES_RETRANSLATE( qobject_cast< WaitingWidget* >( m_waitingWidget )->setText( tr( "Gathering system information..." ) ); )

    // We're not done loading, but we need the configuration map first.
}


void
PartitionViewStep::continueLoading()
{
    OsproberEntryList osproberEntries = PartUtils::runOsprober( m_core );

    Q_ASSERT( !m_choicePage );
    m_choicePage = new ChoicePage( m_compactMode );

    m_choicePage->init( m_core, osproberEntries );
    m_alongsidePage->init( m_core, osproberEntries );

    m_widget->addWidget( m_choicePage );
    m_widget->addWidget( m_manualPartitionPage );
    m_widget->addWidget( m_alongsidePage );
    m_widget->addWidget( m_replacePage );
    m_widget->removeWidget( m_waitingWidget );
    m_waitingWidget->deleteLater();
    m_waitingWidget = nullptr;

    connect( m_core,            &PartitionCoreModule::hasRootMountPointChanged,
             this,              &PartitionViewStep::nextStatusChanged );
    connect( m_choicePage,      &ChoicePage::nextStatusChanged,
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
                       .arg( Calamares::Branding::instance()->
                             string( Calamares::Branding::ShortVersionedName ) );
            break;
        case ChoicePage::Erase:
            modeText = tr( "<strong>Erase</strong> disk and install %1." )
                       .arg( Calamares::Branding::instance()->
                             string( Calamares::Branding::ShortVersionedName ) );
            break;
        case ChoicePage::Replace:
            modeText = tr( "<strong>Replace</strong> a partition with %1." )
                       .arg( Calamares::Branding::instance()->
                             string( Calamares::Branding::ShortVersionedName ) );
            break;
        default:
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
                           .arg( Calamares::Branding::instance()->
                                 string( Calamares::Branding::ShortVersionedName ) )
                           .arg( info.deviceNode )
                           .arg( info.deviceName );
                break;
            case ChoicePage::Erase:
                modeText = tr( "<strong>Erase</strong> disk <strong>%2</strong> (%3) and install %1." )
                           .arg( Calamares::Branding::instance()->
                                 string( Calamares::Branding::ShortVersionedName ) )
                           .arg( info.deviceNode )
                           .arg( info.deviceName );
                break;
            case ChoicePage::Replace:
                modeText = tr( "<strong>Replace</strong> a partition on disk <strong>%2</strong> (%3) with %1." )
                           .arg( Calamares::Branding::instance()->
                                 string( Calamares::Branding::ShortVersionedName ) )
                           .arg( info.deviceNode )
                           .arg( info.deviceName );
                break;
            default:
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

        PartitionPreview* preview;

        preview = new PartitionPreview;
        preview->setLabelsVisible( true );
        preview->setModel( info.partitionModelBefore );
        info.partitionModelBefore->setParent( widget );
        formLayout->addRow( tr( "Before:" ), preview );

        preview = new PartitionPreview;
        preview->setLabelsVisible( true );
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
            emit done();
            return;
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
         m_widget->currentWidget() == m_alongsidePage ||
         m_widget->currentWidget() == m_replacePage )
        return false;
    return true;
}


bool
PartitionViewStep::isAtEnd() const
{
    if ( m_choicePage == m_widget->currentWidget() )
    {
        if ( m_choicePage->currentChoice() == ChoicePage::Erase )
            return true;
        return false;
    }
    return true;
}


void
PartitionViewStep::onActivate()
{
    // if we're coming back to PVS from the next VS
    if ( m_widget->currentWidget() == m_replacePage )
    {
        m_replacePage->reset();
    }
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

    if ( configurationMap.contains( "ensureSuspendToDisk" ) &&
         configurationMap.value( "ensureSuspendToDisk" ).type() == QVariant::Bool )
    {
        gs->insert( "ensureSuspendToDisk", configurationMap.value( "ensureSuspendToDisk" ).toBool() );
    }
    else
    {
        gs->insert( "ensureSuspendToDisk", true );
    }

    if ( configurationMap.contains( "compactMode" ) &&
         configurationMap.value( "compactMode" ).type() == QVariant::Bool )
    {
        m_compactMode = configurationMap.value( "compactMode", true ).toBool();
    }

    QTimer::singleShot( 0, this, &PartitionViewStep::continueLoading );
}


QList< Calamares::job_ptr >
PartitionViewStep::jobs() const
{
    return m_core->jobs();
}


CALAMARES_PLUGIN_FACTORY_DEFINITION( PartitionViewStepFactory, registerPlugin<PartitionViewStep>(); )
