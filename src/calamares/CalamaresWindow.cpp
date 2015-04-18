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

#include "CalamaresWindow.h"

#include "ViewManager.h"
#include "progresstree/ProgressTreeView.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/DebugWindow.h"
#include "utils/Retranslator.h"
#include "Settings.h"
#include "Branding.h"

#include <QApplication>
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QLabel>
#include <QTreeView>

CalamaresWindow::CalamaresWindow( QWidget* parent )
    : QWidget( parent )
    , m_debugWindow( nullptr )
{
    // Hide close button
    setWindowFlags( Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint );

    CALAMARES_RETRANSLATE(
        setWindowTitle( tr( "%1 Installer" )
                        .arg( Calamares::Branding::instance()->
                              string( Calamares::Branding::ProductName ) ) );
    )

    setMinimumSize( 1010, 520 );
    QSize availableSize = qApp->desktop()->screenGeometry( this ).size();
    int w = qBound( 1010, CalamaresUtils::defaultFontHeight() * 60, availableSize.width() );
    int h = qBound( 520,  CalamaresUtils::defaultFontHeight() * 36, availableSize.height() );

    cDebug() << "Proposed window size:" << w << h;
    resize( w, h );

    QBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    QWidget* sideBox = new QWidget( this );
    mainLayout->addWidget( sideBox );

    QBoxLayout* sideLayout = new QVBoxLayout;
    sideBox->setLayout( sideLayout );
    sideBox->setFixedWidth( qMax( 190, CalamaresUtils::defaultFontHeight() * 12 ) );
    sideBox->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    QHBoxLayout* logoLayout = new QHBoxLayout;
    sideLayout->addLayout( logoLayout );
    logoLayout->addStretch();
    QLabel* logoLabel = new QLabel( sideBox );
    {
        QPalette plt = sideBox->palette();
        sideBox->setAutoFillBackground( true );
        plt.setColor( sideBox->backgroundRole(), Calamares::Branding::instance()->
                      styleString( Calamares::Branding::SidebarBackground ) );
        plt.setColor( sideBox->foregroundRole(), Calamares::Branding::instance()->
                      styleString( Calamares::Branding::SidebarText ) );
        sideBox->setPalette( plt );
        logoLabel->setPalette( plt );
    }
    logoLabel->setAlignment( Qt::AlignCenter );
    logoLabel->setFixedSize( 80, 80 );
    logoLabel->setPixmap( Calamares::Branding::instance()->
                          image( Calamares::Branding::ProductIcon,
                                 logoLabel->size() ) );
    logoLayout->addWidget( logoLabel );
    logoLayout->addStretch();

    ProgressTreeView* tv = new ProgressTreeView( sideBox );
    sideLayout->addWidget( tv );
    tv->setFocusPolicy( Qt::NoFocus );

    if ( Calamares::Settings::instance()->debugMode() )
    {
        QPushButton* debugWindowBtn = new QPushButton;
        CALAMARES_RETRANSLATE(
            debugWindowBtn->setText( tr( "Show debug information" ) );
        )
        sideLayout->addWidget( debugWindowBtn );
        debugWindowBtn->setFlat( true );
        debugWindowBtn->setCheckable( true );
        connect( debugWindowBtn, &QPushButton::clicked,
                 [ this, debugWindowBtn ]( bool checked )
        {
            if ( checked )
            {
                m_debugWindow = new Calamares::DebugWindow();
                m_debugWindow->show();
                connect( m_debugWindow, &Calamares::DebugWindow::closed,
                         [ this, debugWindowBtn ]
                {
                    m_debugWindow->deleteLater();
                    debugWindowBtn->setChecked( false );
                } );
            }
            else
            {
                if ( m_debugWindow )
                {
                    m_debugWindow->deleteLater();
                }
            }
        } );
    }

    CalamaresUtils::unmarginLayout( sideLayout );
    CalamaresUtils::unmarginLayout( mainLayout );

    Calamares::ViewManager* vm = new Calamares::ViewManager( this );

    mainLayout->addWidget( vm->centralWidget() );
}
