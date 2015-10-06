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

#include "core/PartitionCoreModule.h"
#include "core/DeviceModel.h"
#include "core/PartitionModel.h"
#include "core/OsproberEntry.h"

#include "PrettyRadioButton.h"
#include "PartitionPreview.h"

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


#define drivesList  qobject_cast< QListView* >( m_drivesView )
#define drivesCombo qobject_cast< QComboBox* >( m_drivesView )

ChoicePage::ChoicePage( bool compactMode, QWidget* parent )
    : QWidget( parent )
    , m_compactMode( compactMode )
    , m_choice( NoChoice )
    , m_nextEnabled( false )
    , m_core( nullptr )
    , m_alongsideButton( nullptr )
    , m_eraseButton( nullptr )
    , m_replaceButton( nullptr )
    , m_somethingElseButton( nullptr )
{
    setupUi( this );
    if ( m_compactMode )
    {
        m_mainLayout->setDirection( QBoxLayout::TopToBottom );
        m_drivesView = new QComboBox( this );
        m_mainLayout->setStretchFactor( m_drivesLayout, 0 );
        m_mainLayout->setStretchFactor( m_rightLayout, 1 );
    }
    else
    {
        m_drivesView = new QListView( this );

        drivesList->setViewMode( QListView::ListMode );
        drivesList->setWrapping( false );
        drivesList->setFlow( QListView::TopToBottom );
        drivesList->setSelectionRectVisible( false );
        drivesList->setWordWrap( true );
        drivesList->setUniformItemSizes( true );
        drivesList->setSelectionMode( QAbstractItemView::SingleSelection );
        drivesList->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

        drivesList->setIconSize( CalamaresUtils::defaultIconSize() / 2 );
    }
    m_drivesLayout->addWidget( m_drivesView );

    m_messageLabel->setWordWrap( true );

    CalamaresUtils::unmarginLayout( m_itemsLayout );

    // Drive selector + preview
    CALAMARES_RETRANSLATE( m_drivesLabel->setText( tr( "Select drive:" ) ); )

    m_previewFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    // end
}


ChoicePage::~ChoicePage()
{}


void
ChoicePage::init( PartitionCoreModule* core,
                  const OsproberEntryList& osproberEntries )
{
    m_core = core;
    m_osproberEntries = osproberEntries;

    setupChoices();

    if ( compact() )
    {
        drivesCombo->setModel( core->deviceModel() );
        connect( drivesCombo,
                 static_cast< void ( QComboBox::* )( int ) >( &QComboBox::currentIndexChanged ),
                 this, &ChoicePage::applyDeviceChoice );
    }
    else
    {
        drivesList->setModel( core->deviceModel() );
        connect( drivesList->selectionModel(),
                 &QItemSelectionModel::currentChanged,
                 this, &ChoicePage::applyDeviceChoice );
    }
    ChoicePage::applyDeviceChoice();
}


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

    QSize iconSize( CalamaresUtils::defaultIconSize().width() * 3,
                    CalamaresUtils::defaultIconSize().height() * 3 );
    QButtonGroup* grp = new QButtonGroup( this );

    m_alongsideButton = new PrettyRadioButton;
    m_alongsideButton->setIconSize( iconSize );
    m_alongsideButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionAlongside,
                                                               CalamaresUtils::Original,
                                                               iconSize ) );
    grp->addButton( m_alongsideButton->buttonWidget() );

    m_eraseButton = new PrettyRadioButton;
    m_eraseButton->setIconSize( iconSize );
    m_eraseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionEraseAuto,
                                                           CalamaresUtils::Original,
                                                           iconSize ) );
    grp->addButton( m_eraseButton->buttonWidget() );

    m_replaceButton = new PrettyRadioButton;
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
            m_choice = Alongside;
        setNextEnabled( true );
    } );

    connect( m_eraseButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
            m_choice = Erase;
        setNextEnabled( true );
    } );

    connect( m_replaceButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
            m_choice = Replace;
        setNextEnabled( true );
    } );

    connect( m_somethingElseButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
            m_choice = Manual;
        setNextEnabled( true );
    } );

    m_rightLayout->setStretchFactor( m_itemsLayout, 1 );
    m_rightLayout->setStretchFactor( m_previewFrame, 0 );
}


void
ChoicePage::applyDeviceChoice()
{
    QMutexLocker locker( &m_previewsMutex );

    cDebug() << "Updating partitioning preview widgets.";
    qDeleteAll( m_previewFrame->children() );
    m_previewFrame->layout()->deleteLater();

    if ( !compact() &&
         drivesList->selectionModel()->currentIndex() == QModelIndex() )
    {
        cDebug() << "No disk selected, bailing out.";
        return;
    }

    Device* dev = nullptr;
    if ( compact() )
    {
        dev = m_core->deviceModel()->deviceForIndex(
                  m_core->deviceModel()->index(
                      drivesCombo->currentIndex() ) );
    }
    else
    {
        dev = m_core->deviceModel()->deviceForIndex(
                  drivesList->selectionModel()->currentIndex() );
    }
    if ( !dev )
        return;

    QVBoxLayout* layout = new QVBoxLayout;
    m_previewFrame->setLayout( layout );
    layout->setMargin( 0 );

    PartitionPreview* preview = new PartitionPreview( m_previewFrame );
    preview->setLabelsVisible( true );
    PartitionModel* model = new PartitionModel( m_previewFrame );
    model->init( dev );
    preview->setModel( model );
    layout->addWidget( preview );

    // Preview setup done. Now we show/hide choices as needed.

    if ( m_osproberEntries.count() == 0 )
    {
        CALAMARES_RETRANSLATE(
            m_messageLabel->setText( tr( "This computer currently does not seem to have an operating system on it. "
                                         "What would you like to do?" ) );

            if ( m_core->deviceModel()->rowCount() < 2 )
                m_eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                            "<font color=\"red\">Warning: </font>This will delete all of your programs, "
                                            "documents, photos, music, and any other files." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            else
                m_eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                            "You will be offered a choice of which disk to erase." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
        )

        m_replaceButton->hide();
        m_alongsideButton->hide();
    }
    else if ( m_osproberEntries.count() == 1 )
    {
        QString osName = m_osproberEntries.first().prettyName;

        if ( !osName.isEmpty() )
        {
            CALAMARES_RETRANSLATE(
                m_messageLabel->setText( tr( "This computer currently has %1 on it. "
                                             "What would you like to do?" )
                                            .arg( osName ) );

                m_alongsideButton->setText( tr( "<strong>Install %2 alongside %1</strong><br/>"
                                                "The installer will shrink the %1 volume to make room for %2. "
                                                "You can choose which operating system you want each time the "
                                                "computer starts up." )
                                            .arg( osName )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                if ( m_core->deviceModel()->rowCount() < 2 )
                    m_eraseButton->setText( tr( "<strong>Erase entire disk with %1 and install %2</strong><br/>"
                                                "<font color=\"red\">Warning: </font>This will erase the whole disk and "
                                                "delete all of your %1 programs, "
                                                "documents, photos, music, and any other files." )
                                            .arg( osName )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );
                else
                    m_eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                                "You will be offered a choice of which disk to erase." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                m_replaceButton->setText( tr( "<strong>Replace a partition with %1</strong><br/>"
                                              "You will be offered a choice of which partition to erase." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            )
        }
        else
        {
            CALAMARES_RETRANSLATE(
                m_messageLabel->setText( tr( "This computer already has an operating system on it. "
                                             "What would you like to do?" ) );

                m_alongsideButton->setText( tr( "<strong>Install %1 alongside your current operating system</strong><br/>"
                                                "The installer will shrink an existing volume to make room for %2. "
                                                "You can choose which operating system you want each time the "
                                                "computer starts up." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortProductName ) ) );

                if ( m_core->deviceModel()->rowCount() < 2 )
                    m_eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                                "<font color=\"red\">Warning: </font>This will delete all of your programs, "
                                                "documents, photos, music, and any other files." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );
                else
                    m_eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                                "You will be offered a choice of which disk to erase." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                m_replaceButton->setText( tr( "<strong>Replace a partition with %1</strong><br/>"
                                              "You will be offered a choice of which partition to erase." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            )
        }
        if ( !m_osproberEntries.first().canBeResized )
            m_alongsideButton->hide();
    }
    else
    {
        // m_osproberLines has at least 2 items.

        bool atLeastOneCanBeResized = false;

        foreach ( const OsproberEntry& entry, m_osproberEntries )
        {
            if ( entry.canBeResized )
            {
                atLeastOneCanBeResized = true;
                break;
            }
        }

        CALAMARES_RETRANSLATE(
            m_messageLabel->setText( tr( "This computer currently has multiple operating systems on it. "
                                         "What would you like to do?" ) );

            m_alongsideButton->setText( tr( "<strong>Install %1 alongside your current operating systems</strong><br/>"
                                            "The installer will shrink an existing volume to make room for %2. "
                                            "You can choose which operating system you want each time the "
                                            "computer starts up." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortProductName ) ) );

            if ( m_core->deviceModel()->rowCount() < 2 )
                m_eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                            "<font color=\"red\">Warning: </font>This will delete all of your programs, "
                                            "documents, photos, music, and any other files." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            else
                m_eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                            "You will be offered a choice of which disk to erase." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );

            m_replaceButton->setText( tr( "<strong>Replace a partition with %1</strong><br/>"
                                          "You will be offered a choice of which partition to erase." )
                                    .arg( Calamares::Branding::instance()->
                                          string( Calamares::Branding::ShortVersionedName ) ) );
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


bool
ChoicePage::compact()
{
    if ( m_compactMode )
    {
        Q_ASSERT( drivesCombo );
        Q_ASSERT( !drivesList );
        return true;
    }
    else
    {
        Q_ASSERT( drivesList );
        Q_ASSERT( !drivesCombo );
        return false;
    }
}


void
ChoicePage::setNextEnabled( bool enabled )
{
    if ( enabled == m_nextEnabled )
        return;

    m_nextEnabled = enabled;
    emit nextStatusChanged( enabled );
}

