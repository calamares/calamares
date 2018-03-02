/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "InteractiveTerminalPage.h"

#include "viewpages/ViewStep.h"
#include "utils/Retranslator.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"

#include <KF5/KService/kservice.h>
#include <KF5/KParts/kde_terminal_interface.h>
#include <KF5/KParts/kparts/readonlypart.h>

#include <QApplication>
#include <QDir>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>


InteractiveTerminalPage::InteractiveTerminalPage( QWidget* parent )
    : QWidget( parent )
    , m_layout( new QVBoxLayout( this ) )
    , m_termHostWidget( nullptr )
{
    setLayout( m_layout );
    m_layout->setContentsMargins( 0, 0, 0, 0 );

    m_headerLabel = new QLabel( this );
    m_layout->addWidget( m_headerLabel );
}

void
InteractiveTerminalPage::errorKonsoleNotInstalled()
{
    QMessageBox::critical( this,
                           tr( "Konsole not installed"),
                           tr( "Please install KDE Konsole and try again!" ),
                           QMessageBox::Ok );
}

void
InteractiveTerminalPage::onActivate()
{
    if ( m_termHostWidget )
        return;
    // For whatever reason, instead of simply linking against a library we
    // need to do a runtime query to KService just to get a sodding terminal
    // widget.
    KService::Ptr service = KService::serviceByDesktopName( "konsolepart" );
    if ( !service )
    {
        // And all of this hoping the Konsole application is installed. If not,
        // tough cookies.
        errorKonsoleNotInstalled();
        return ;
    }

    // Create one instance of konsolepart.
    KParts::ReadOnlyPart* p =
        service->createInstance< KParts::ReadOnlyPart >( this,
                                                         this,
                                                         {} );
    if ( !p )
    {
        // One more opportunity for the loading operation to fail.
        errorKonsoleNotInstalled();
        return;
    }

    // Cast the konsolepart to the TerminalInterface...
    TerminalInterface* t = qobject_cast< TerminalInterface* >( p );
    if ( !t )
    {
        // This is why we can't have nice things.
        errorKonsoleNotInstalled();
        return;
    }

    // Make the widget persist even if the KPart goes out of scope...
    p->setAutoDeleteWidget( false );
    // ... but kill the KPart if the widget goes out of scope.
    p->setAutoDeletePart( true );

    m_termHostWidget = p->widget();
    m_layout->addWidget( m_termHostWidget );
    cDebug() << "Part widget ought to be"
             << m_termHostWidget->metaObject()->className();

    t->showShellInDir( QDir::home().path() );
    t->sendInput( QString( "%1\n" ).arg( m_command ) );
}


void
InteractiveTerminalPage::setCommand( const QString& command )
{
    m_command = command;
    CALAMARES_RETRANSLATE(
        m_headerLabel->setText( tr( "Executing script: &nbsp;<code>%1</code>" )
                                .arg( m_command ) );
    )
}
