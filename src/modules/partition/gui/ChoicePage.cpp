/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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
#include "core/partition.h"
#include "core/device.h"

#include "JobQueue.h"
#include "GlobalStorage.h"
#include "PrettyRadioButton.h"

#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"

#include <QBoxLayout>
#include <QButtonGroup>
#include <QLabel>

ChoicePage::ChoicePage( QWidget* parent )
    : QWidget( parent )
    , m_choice( NoChoice )
    , m_nextEnabled( false )
{
    QBoxLayout* mainLayout = new QVBoxLayout;
    setLayout( mainLayout );

    m_messageLabel = new QLabel;
    m_messageLabel->setWordWrap( true );

    m_itemsLayout = new QVBoxLayout;
    CalamaresUtils::unmarginLayout( m_itemsLayout );

    mainLayout->addSpacing( CalamaresUtils::defaultFontHeight() );
    mainLayout->addWidget( m_messageLabel );
    mainLayout->addLayout( m_itemsLayout );
    mainLayout->addStretch();
}


ChoicePage::~ChoicePage()
{}


void
ChoicePage::init( PartitionCoreModule* core, const QStringList& osproberLines )
{
    m_core = core;
    m_osproberLines = osproberLines;

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
    alongsideButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Information,
                                                             CalamaresUtils::Original,
                                                             iconSize ) );
    grp->addButton( alongsideButton->buttonWidget() );

    PrettyRadioButton* eraseButton = new PrettyRadioButton;
    eraseButton->setIconSize( iconSize );
    eraseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Magic,
                                                         CalamaresUtils::Original,
                                                         iconSize ) );
    grp->addButton( eraseButton->buttonWidget() );

    m_itemsLayout->addWidget( alongsideButton );
    m_itemsLayout->addWidget( eraseButton );
    m_itemsLayout->setSpacing( CalamaresUtils::defaultFontHeight() / 2 );

    cDebug() << "Osprober lines, clean:\n" << m_osproberLines.join( '\n' );

    if ( m_osproberLines.count() == 0 )
    {
        m_messageLabel->setText( tr( "This computer currently does not seem to have an operating system on it. "
                                     "What would you like to do?" ) );

        eraseButton->setText( tr( "<b>Erase disk and install %1</b><br/>"
                                  "<font color=\"red\">Warning: </font>This will delete all of your programs, "
                                  "documents, photos, music, and any other files." )
                                .arg( "$RELEASE" ) );

        alongsideButton->hide();
    }
    else if ( m_osproberLines.count() == 1 )
    {
        QStringList osLine = m_osproberLines.first().split( ':' );
        QString osName;
        if ( !osLine.value( 1 ).simplified().isEmpty() )
            osName = osLine.value( 1 ).simplified();
        else if ( !osLine.value( 2 ).simplified().isEmpty() )
            osName = osLine.value( 2 ).simplified();

        if ( canBeResized( osLine ) )
        {

            if ( !osName.isEmpty() )
            {
                m_messageLabel->setText( tr( "This computer currently has %1 on it. "
                                             "What would you like to do?" )
                                            .arg( osName ) );

                alongsideButton->setText( tr( "<b>Install %2 alongside %1</b><br/>"
                                              "Documents, music and other personal files will be kept. "
                                              "You can choose which operating system you want each time the "
                                              "computer starts up." )
                                            .arg( osName )
                                            .arg( "$RELEASE" ) );

                eraseButton->setText( tr( "<b>Replace %1 with %2</b><br/>"
                                          "<font color=\"red\">Warning: </font>This will erase the whole disk and "
                                          "delete all of your %1 programs, "
                                          "documents, photos, music, and any other files." )
                                        .arg( osName )
                                        .arg( "$RELEASE" ) );
            }
            else
            {
                m_messageLabel->setText( tr( "This computer already has an operating system on it. "
                                             "What would you like to do?" ) );

                alongsideButton->setText( tr( "<b>Install %1 alongside your current operating system</b><br/>"
                                              "Documents, music and other personal files will be kept. "
                                              "You can choose which operating system you want each time the "
                                              "computer starts up." )
                                            .arg( "$RELEASE" ) );

                eraseButton->setText( tr( "<b>Erase disk and install %1</b><br/>"
                                          "<font color=\"red\">Warning: </font>This will delete all of your Windows 7 programs, "
                                          "documents, photos, music, and any other files." )
                                        .arg( "$RELEASE" ) );
            }
        }
        else
            alongsideButton->hide();
    }
    else
    {
        // m_osproberLines has at least 2 items.

        bool atLeastOneCanBeResized = false;

        foreach ( QString line, m_osproberLines )
        {
            QStringList osLine = line.split( ':' );
            if ( canBeResized( osLine ) )
            {
                atLeastOneCanBeResized = true;
                break;
            }
        }

        if ( atLeastOneCanBeResized )
        {
            m_messageLabel->setText( tr( "This computer currently has multiple operating systems on it. "
                                         "What would you like to do?" ) );

            alongsideButton->setText( tr( "<b>Install %1 alongside your current operating systems</b><br/>"
                                          "Documents, music and other personal files will be kept. "
                                          "You can choose which operating system you want each time the "
                                          "computer starts up." )
                                        .arg( "$RELEASE" ) );

            eraseButton->setText( tr( "<b>Erase disk and install %1</b><br/>"
                                      "<font color=\"red\">Warning: </font>This will delete all of your Windows 7 programs, "
                                      "documents, photos, music, and any other files." )
                                    .arg( "$RELEASE" ) );
        }
        else
            alongsideButton->hide();
    }

    QFrame* hLine = new QFrame;
    hLine->setFrameStyle( QFrame::HLine );
    m_itemsLayout->addWidget( hLine );

    PrettyRadioButton* somethingElseButton = new PrettyRadioButton;
    somethingElseButton->setText( tr( "<b>Something else</b><br/>"
                                      "You can create or resize partitions yourself, or choose "
                                      "multiple partitions for %1." )
                                    .arg( "$RELEASE" ) );
    somethingElseButton->setIconSize( iconSize );
    somethingElseButton->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Partitions,
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

    connect( somethingElseButton->buttonWidget(), &QRadioButton::toggled,
             this, [ this ]( bool checked )
    {
        if ( checked )
            m_choice = Manual;
        setNextEnabled( true );
    } );
}


bool
ChoicePage::isNextEnabled()
{
    return m_nextEnabled;
}


ChoicePage::Choice
ChoicePage::currentChoice()
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


bool
ChoicePage::canBeResized( const QStringList& osproberLine )
{
    cDebug() << "checking if" << osproberLine << "can be resized.";
    QString partitionWithOs = osproberLine.value( 0 ).simplified();
    if ( partitionWithOs.startsWith( "/dev/" ) )
    {
        cDebug() << partitionWithOs << "seems like a good path";
        bool canResize = false;
        DeviceModel* dm = m_core->deviceModel();
        for ( int i = 0; i < dm->rowCount(); ++i )
        {
            Device* dev = dm->deviceForIndex( dm->index( i ) );
            PartitionModel* pm = m_core->partitionModelForDevice( dev );
            for ( int j = 0; j < pm->rowCount(); ++j )
            {
                QModelIndex index = pm->index( j, 0 );
                Partition* candidate = pm->partitionForIndex( index );
                if ( candidate->partitionPath() == partitionWithOs )
                {
                    cDebug() << "found Partition* for" << partitionWithOs;
                    bool ok = false;
                    double requiredStorageGB = Calamares::JobQueue::instance()
                                                    ->globalStorage()
                                                    ->value( "requiredStorageGB" )
                                                    .toDouble( &ok );

                    qint64 availableStorageB = candidate->available() * dev->logicalSectorSize();

                    // We require a little more for partitioning overhead and swap file
                    // TODO: maybe make this configurable?
                    qint64 requiredStorageB = ( requiredStorageGB + 0.1 + 2.0 ) * 1024 * 1024 * 1024;
                    cDebug() << "Required  storage B:" << requiredStorageB;
                    cDebug() << "Available storage B:" << availableStorageB;
                    if ( ok &&
                         availableStorageB > requiredStorageB )
                    {
                        canResize = true;
                    }
                }
                if ( canResize )
                    break;
            }
            if ( canResize )
                break;
        }

        cDebug() << "Partition" << osproberLine << "authorized for resize + autopartition install.";
        return canResize;
    }

    cDebug() << "Partition" << osproberLine << "CANNOT BE RESIZED FOR AUTOINSTALL.";
    return false;
}
