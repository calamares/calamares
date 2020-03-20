/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
 *   Copyright 2018, Raul Rodrigo Segura (raurodse)
 *   Copyright 2019, Collabora Ltd <arnaud.ferraris@collabora.com>
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

#include "Branding.h"
#include "DebugWindow.h"
#include "Settings.h"
#include "ViewManager.h"
#include "progresstree/ProgressTreeView.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "utils/Qml.h"
#include "utils/Retranslator.h"

#include <QApplication>
#include <QBoxLayout>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QQuickWidget>
#include <QTreeView>

static inline int
windowDimensionToPixels( const Calamares::Branding::WindowDimension& u )
{
    if ( !u.isValid() )
    {
        return 0;
    }
    if ( u.unit() == Calamares::Branding::WindowDimensionUnit::Pixies )
    {
        return static_cast< int >( u.value() );
    }
    if ( u.unit() == Calamares::Branding::WindowDimensionUnit::Fonties )
    {
        return static_cast< int >( u.value() * CalamaresUtils::defaultFontHeight() );
    }
    return 0;
}


QWidget*
CalamaresWindow::getWidgetSidebar( int desiredWidth )
{
    const Calamares::Branding* const branding = Calamares::Branding::instance();

    QWidget* sideBox = new QWidget( this );
    sideBox->setObjectName( "sidebarApp" );

    QBoxLayout* sideLayout = new QVBoxLayout;
    sideBox->setLayout( sideLayout );
    // Set this attribute into qss file
    sideBox->setFixedWidth( desiredWidth );
    sideBox->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    QHBoxLayout* logoLayout = new QHBoxLayout;
    sideLayout->addLayout( logoLayout );
    logoLayout->addStretch();
    QLabel* logoLabel = new QLabel( sideBox );
    logoLabel->setObjectName( "logoApp" );
    //Define all values into qss file
    {
        QPalette plt = sideBox->palette();
        sideBox->setAutoFillBackground( true );
        plt.setColor( sideBox->backgroundRole(), branding->styleString( Calamares::Branding::SidebarBackground ) );
        plt.setColor( sideBox->foregroundRole(), branding->styleString( Calamares::Branding::SidebarText ) );
        sideBox->setPalette( plt );
        logoLabel->setPalette( plt );
    }
    logoLabel->setAlignment( Qt::AlignCenter );
    logoLabel->setFixedSize( 80, 80 );
    logoLabel->setPixmap( branding->image( Calamares::Branding::ProductLogo, logoLabel->size() ) );
    logoLayout->addWidget( logoLabel );
    logoLayout->addStretch();

    ProgressTreeView* tv = new ProgressTreeView( sideBox );
    tv->setModel( Calamares::ViewManager::instance() );
    tv->setFocusPolicy( Qt::NoFocus );
    sideLayout->addWidget( tv );

    if ( Calamares::Settings::instance()->debugMode() || ( Logger::logLevel() >= Logger::LOGVERBOSE ) )
    {
        QPushButton* debugWindowBtn = new QPushButton;
        debugWindowBtn->setObjectName( "debugButton" );
        CALAMARES_RETRANSLATE( debugWindowBtn->setText( tr( "Show debug information" ) ); )
        sideLayout->addWidget( debugWindowBtn );
        debugWindowBtn->setFlat( true );
        debugWindowBtn->setCheckable( true );
        connect( debugWindowBtn, &QPushButton::clicked, this, [=]( bool checked ) {
            if ( checked )
            {
                m_debugWindow = new Calamares::DebugWindow();
                m_debugWindow->show();
                connect( m_debugWindow.data(), &Calamares::DebugWindow::closed, this, [=]() {
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
    return sideBox;
}

QWidget*
CalamaresWindow::getQmlSidebar( int desiredWidth )
{
    CalamaresUtils::registerCalamaresModels();
    QQuickWidget* w = new QQuickWidget( this );
    w->setFixedWidth( desiredWidth );
    w->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    w->setSource( QUrl(
        CalamaresUtils::searchQmlFile( CalamaresUtils::QmlSearch::Both, QStringLiteral( "calamares-sidebar" ) ) ) );
    return w;
}

CalamaresWindow::CalamaresWindow( QWidget* parent )
    : QWidget( parent )
    , m_debugWindow( nullptr )
    , m_viewManager( nullptr )
{
    // If we can never cancel, don't show the window-close button
    if ( Calamares::Settings::instance()->disableCancel() )
    {
        setWindowFlag( Qt::WindowCloseButtonHint, false );
    }

    CALAMARES_RETRANSLATE( setWindowTitle( Calamares::Settings::instance()->isSetupMode()
                                               ? tr( "%1 Setup Program" ).arg( *Calamares::Branding::ProductName )
                                               : tr( "%1 Installer" ).arg( *Calamares::Branding::ProductName ) ); )

    const Calamares::Branding* const branding = Calamares::Branding::instance();

    using CalamaresUtils::windowMinimumHeight;
    using CalamaresUtils::windowMinimumWidth;
    using CalamaresUtils::windowPreferredHeight;
    using CalamaresUtils::windowPreferredWidth;

    // Needs to match what's checked in DebugWindow
    this->setObjectName( "mainApp" );

    QSize availableSize = qApp->desktop()->availableGeometry( this ).size();
    QSize minimumSize( qBound( windowMinimumWidth, availableSize.width(), windowPreferredWidth ),
                       qBound( windowMinimumHeight, availableSize.height(), windowPreferredHeight ) );
    setMinimumSize( minimumSize );

    cDebug() << "Available desktop" << availableSize << "minimum size" << minimumSize;

    auto brandingSizes = branding->windowSize();

    int w = qBound( minimumSize.width(), windowDimensionToPixels( brandingSizes.first ), availableSize.width() );
    int h = qBound( minimumSize.height(), windowDimensionToPixels( brandingSizes.second ), availableSize.height() );

    cDebug() << Logger::SubEntry << "Proposed window size:" << w << h;
    resize( w, h );

    m_viewManager = Calamares::ViewManager::instance( this );

    QBoxLayout* mainLayout = new QHBoxLayout;
    setLayout( mainLayout );

    QWidget* sideBox = nullptr;
    switch ( branding->sidebarFlavor() )
    {
    case Calamares::Branding::SidebarFlavor::Widget:
        sideBox = getWidgetSidebar(
            qBound( 100, CalamaresUtils::defaultFontHeight() * 12, w < windowPreferredWidth ? 100 : 190 ) );
        break;
    case Calamares::Branding::SidebarFlavor::Qml:
        sideBox = getQmlSidebar(
            qBound( 100, CalamaresUtils::defaultFontHeight() * 12, w < windowPreferredWidth ? 100 : 190 ) );
        break;
    case Calamares::Branding::SidebarFlavor::None:
        sideBox = nullptr;
    }
    if ( sideBox )
    {
        mainLayout->addWidget( sideBox );
    }

    if ( branding->windowExpands() )
    {
        connect( m_viewManager, &Calamares::ViewManager::enlarge, this, &CalamaresWindow::enlarge );
    }
    // NOTE: Although the ViewManager has a signal cancelEnabled() that
    //       signals when the state of the cancel button changes (in
    //       particular, to disable cancel during the exec phase),
    //       we don't connect to it here. Changing the window flag
    //       for the close button causes uncomfortable window flashing
    //       and requires an extra show() (at least with KWin/X11) which
    //       is too annoying. Instead, leave it up to ignoring-the-quit-
    //       event, which is also the ViewManager's responsibility.

    mainLayout->addWidget( m_viewManager->centralWidget() );
    CalamaresUtils::unmarginLayout( mainLayout );
    setStyleSheet( Calamares::Branding::instance()->stylesheet() );
}

void
CalamaresWindow::enlarge( QSize enlarge )
{
    auto mainGeometry = this->geometry();
    QSize availableSize = qApp->desktop()->availableGeometry( this ).size();

    auto h = qBound( 0, mainGeometry.height() + enlarge.height(), availableSize.height() );
    auto w = this->size().width();

    resize( w, h );
}

void
CalamaresWindow::closeEvent( QCloseEvent* event )
{
    if ( ( !m_viewManager ) || m_viewManager->confirmCancelInstallation() )
    {
        event->accept();
        qApp->quit();
    }
    else
    {
        event->ignore();
    }
}
