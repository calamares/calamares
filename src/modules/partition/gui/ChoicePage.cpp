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

#include "PrettyRadioButton.h"

#include "utils/CalamaresUtilsGui.h"

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

    m_cleanOsproberLines.clear();
    foreach ( const QString& line, osproberLines )
    {
        if ( !line.simplified().isEmpty() )
            m_cleanOsproberLines.append( line );
    }

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

    if ( m_cleanOsproberLines.count() == 0 )
    {
        m_messageLabel->setText( tr( "This computer currently does not seem to have an operating system on it. "
                                     "What would you like to do?" ) );

        eraseButton->setText( tr( "<b>Erase disk and install %1</b><br/>"
                                  "<font color=\"red\">Warning: </font>This will delete all of your programs, "
                                  "documents, photos, music, and any other files." )
                                .arg( "$RELEASE" ) );

        alongsideButton->hide();
    }
    else if ( m_cleanOsproberLines.count() == 1 )
    {
        QStringList osLine = m_cleanOsproberLines.first().split( ':' );
        QString osName;
        if ( !osLine.value( 1 ).simplified().isEmpty() )
            osName = osLine.value( 1 ).simplified();
        else if ( !osLine.value( 2 ).simplified().isEmpty() )
            osName = osLine.value( 2 ).simplified();

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

    m_itemsLayout->addStretch();

    QFrame* hLine = new QFrame;
    hLine->setFrameStyle( QFrame::HLine );
    m_itemsLayout->addWidget( hLine );

    m_itemsLayout->addStretch();

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
