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
#include <QDir>
#include <QLabel>
#include <QListView>

ChoicePage::ChoicePage( QWidget* parent )
    : QWidget( parent )
    , m_choice( NoChoice )
    , m_nextEnabled( false )
    , m_core( nullptr )
{
    QBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    m_messageLabel = new QLabel;
    m_messageLabel->setWordWrap( true );

    m_itemsLayout = new QVBoxLayout;
    CalamaresUtils::unmarginLayout( m_itemsLayout );

    /// Drive selector + preview
    QLabel* driveLabel = new QLabel( this );
    mainLayout->addWidget( driveLabel );
    CALAMARES_RETRANSLATE( driveLabel->setText( tr( "Select drive:" ) ); )

    m_drivesView = new QListView;
    mainLayout->addWidget( m_drivesView );
    m_drivesView->setViewMode( QListView::IconMode );
    m_drivesView->setWrapping( false );
    m_drivesView->setFlow( QListView::LeftToRight );
    m_drivesView->setSelectionRectVisible( false );
    m_drivesView->setWordWrap( true );
    m_drivesView->setUniformItemSizes( true );
    m_drivesView->setSelectionMode( QAbstractItemView::SingleSelection );

    m_drivesView->setIconSize( CalamaresUtils::defaultIconSize() * 3 );
    m_drivesView->setGridSize( QSize( CalamaresUtils::defaultFontHeight() * 8,
                                      m_drivesView->iconSize().height() +
                                      CalamaresUtils::defaultFontHeight() * 4 ) );
    m_drivesView->setMinimumHeight( m_drivesView->gridSize().height() +
                                    CalamaresUtils::defaultFontHeight() / 2 );
    m_drivesView->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred );

    m_previewFrame = new QWidget;
    m_previewFrame->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Expanding );
    mainLayout->addWidget( m_previewFrame );
    // end

    //mainLayout->addSpacing( CalamaresUtils::defaultFontHeight() );
    mainLayout->addWidget( m_messageLabel );
    mainLayout->addLayout( m_itemsLayout );
    mainLayout->addStretch();
}


ChoicePage::~ChoicePage()
{}


void
ChoicePage::updatePreviews()
{
    QMutexLocker locker( &m_previewsMutex );

    cDebug() << "Updating partitioning preview widgets.";
    qDeleteAll( m_previewFrame->children() );
    m_previewFrame->layout()->deleteLater();

    if ( m_drivesView->selectionModel()->currentIndex() == QModelIndex() )
    {
        cDebug() << "No disk selected, bailing out.";
        return;
    }

    Device* dev = m_core->deviceModel()->deviceForIndex( m_drivesView->selectionModel()->currentIndex() );

    QVBoxLayout* layout = new QVBoxLayout;
    m_previewFrame->setLayout( layout );
    layout->setMargin( 0 );

    PartitionPreview* preview = new PartitionPreview( m_previewFrame );
    preview->setLabelsVisible( true );
    PartitionModel* model = new PartitionModel( m_previewFrame );
    model->init( dev );
    preview->setModel( model );
    layout->addWidget( preview );
}


void
ChoicePage::init( PartitionCoreModule* core, const OsproberEntryList& osproberEntries )
{
    m_core = core;

    // Drive selector + preview
    m_drivesView->setModel( core->deviceModel() );

    connect( m_drivesView->selectionModel(), &QItemSelectionModel::currentChanged,
             this, [ this ]( const QModelIndex& index,
                             const QModelIndex& oldIndex )
    {
        updatePreviews();
    } );
    // end

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

    PrettyRadioButton* alongsideButton = new PrettyRadioButton;
    alongsideButton->setIconSize( iconSize );
    alongsideButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionAlongside,
                                                             CalamaresUtils::Original,
                                                             iconSize ) );
    grp->addButton( alongsideButton->buttonWidget() );

    PrettyRadioButton* eraseButton = new PrettyRadioButton;
    eraseButton->setIconSize( iconSize );
    eraseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionEraseAuto,
                                                         CalamaresUtils::Original,
                                                         iconSize ) );
    grp->addButton( eraseButton->buttonWidget() );

    PrettyRadioButton* replaceButton = new PrettyRadioButton;
    replaceButton->setIconSize( iconSize );
    replaceButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionReplaceOs,
                                                           CalamaresUtils::Original,
                                                           iconSize ) );
    grp->addButton( replaceButton->buttonWidget() );

    m_itemsLayout->addWidget( alongsideButton );
    m_itemsLayout->addWidget( replaceButton );
    m_itemsLayout->addWidget( eraseButton );
    m_itemsLayout->setSpacing( CalamaresUtils::defaultFontHeight() / 2 );

    if ( osproberEntries.count() == 0 )
    {
        CALAMARES_RETRANSLATE(
            m_messageLabel->setText( tr( "This computer currently does not seem to have an operating system on it. "
                                         "What would you like to do?" ) );

            if ( core->deviceModel()->rowCount() < 2 )
                eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                          "<font color=\"red\">Warning: </font>This will delete all of your programs, "
                                          "documents, photos, music, and any other files." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            else
                eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                          "You will be offered a choice of which disk to erase." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
        )

        replaceButton->hide();
        alongsideButton->hide();
    }
    else if ( osproberEntries.count() == 1 )
    {
        QString osName = osproberEntries.first().prettyName;

        if ( !osName.isEmpty() )
        {
            CALAMARES_RETRANSLATE(
                m_messageLabel->setText( tr( "This computer currently has %1 on it. "
                                             "What would you like to do?" )
                                            .arg( osName ) );

                alongsideButton->setText( tr( "<strong>Install %2 alongside %1</strong><br/>"
                                              "The installer will shrink the %1 volume to make room for %2. "
                                              "You can choose which operating system you want each time the "
                                              "computer starts up." )
                                            .arg( osName )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                if ( core->deviceModel()->rowCount() < 2 )
                    eraseButton->setText( tr( "<strong>Erase entire disk with %1 and install %2</strong><br/>"
                                              "<font color=\"red\">Warning: </font>This will erase the whole disk and "
                                              "delete all of your %1 programs, "
                                              "documents, photos, music, and any other files." )
                                            .arg( osName )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );
                else
                    eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                              "You will be offered a choice of which disk to erase." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                replaceButton->setText( tr( "<strong>Replace a partition with %1</strong><br/>"
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

                alongsideButton->setText( tr( "<strong>Install %1 alongside your current operating system</strong><br/>"
                                              "The installer will shrink an existing volume to make room for %2. "
                                              "You can choose which operating system you want each time the "
                                              "computer starts up." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortProductName ) ) );

                if ( core->deviceModel()->rowCount() < 2 )
                    eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                              "<font color=\"red\">Warning: </font>This will delete all of your programs, "
                                              "documents, photos, music, and any other files." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );
                else
                    eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                              "You will be offered a choice of which disk to erase." )
                                            .arg( Calamares::Branding::instance()->
                                                  string( Calamares::Branding::ShortVersionedName ) ) );

                replaceButton->setText( tr( "<strong>Replace a partition with %1</strong><br/>"
                                            "You will be offered a choice of which partition to erase." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            )
        }
        if ( !osproberEntries.first().canBeResized )
            alongsideButton->hide();
    }
    else
    {
        // m_osproberLines has at least 2 items.

        bool atLeastOneCanBeResized = false;

        foreach ( const OsproberEntry& entry, osproberEntries )
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

            alongsideButton->setText( tr( "<strong>Install %1 alongside your current operating systems</strong><br/>"
                                          "The installer will shrink an existing volume to make room for %2. "
                                          "You can choose which operating system you want each time the "
                                          "computer starts up." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortProductName ) ) );

            if ( core->deviceModel()->rowCount() < 2 )
                eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                          "<font color=\"red\">Warning: </font>This will delete all of your programs, "
                                          "documents, photos, music, and any other files." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
            else
                eraseButton->setText( tr( "<strong>Erase disk and install %1</strong><br/>"
                                          "You will be offered a choice of which disk to erase." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );

            replaceButton->setText( tr( "<strong>Replace a partition with %1</strong><br/>"
                                        "You will be offered a choice of which partition to erase." )
                                    .arg( Calamares::Branding::instance()->
                                          string( Calamares::Branding::ShortVersionedName ) ) );
        )

        if ( !atLeastOneCanBeResized )
            alongsideButton->hide();
    }

    bool isEfi = QDir( "/sys/firmware/efi/efivars" ).exists();
    bool efiSystemPartitionFound = !m_core->efiSystemPartitions().isEmpty();

    if ( isEfi && !efiSystemPartitionFound )
    {
        cDebug() << "WARNING: system is EFI but there's not EFI system partition, "
                    "DISABLING alongside and replace features.";
        alongsideButton->hide();
        replaceButton->hide();
    }

    QFrame* hLine = new QFrame;
    hLine->setFrameStyle( QFrame::HLine );
    m_itemsLayout->addWidget( hLine );

    PrettyRadioButton* somethingElseButton = new PrettyRadioButton;
    CALAMARES_RETRANSLATE(
        somethingElseButton->setText( tr( "<strong>Manual partitioning</strong><br/>"
                                          "You can create or resize partitions yourself, or choose "
                                          "multiple partitions for %1." )
                                        .arg( Calamares::Branding::instance()->
                                              string( Calamares::Branding::ShortVersionedName ) ) );
    )
    somethingElseButton->setIconSize( iconSize );
    somethingElseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::PartitionManual,
                                                                 CalamaresUtils::Original,
                                                                 iconSize ) );
    m_itemsLayout->addWidget( somethingElseButton );
    grp->addButton( somethingElseButton->buttonWidget() );

    connect( alongsideButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
            m_choice = Alongside;
        setNextEnabled( true );
    } );

    connect( eraseButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
            m_choice = Erase;
        setNextEnabled( true );
    } );

    connect( replaceButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
            m_choice = Replace;
        setNextEnabled( true );
    } );

    connect( somethingElseButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
            m_choice = Manual;
        setNextEnabled( true );
    } );
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

