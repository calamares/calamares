/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-FileCopyrightText: 2018 Raul Rodrigo Segura (raurodse)
 *   SPDX-FileCopyrightText: 2019 Collabora Ltd <arnaud.ferraris@collabora.com>
 *   SPDX-FileCopyrightText: 2020 Anubhav Choudhary <ac.10edu@gmail.com>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "CalamaresWindow.h"

#include "Branding.h"
#include "CalamaresConfig.h"
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
#ifdef WITH_QML
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQuickWidget>
#endif
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

/** @brief Expected orientation of the panels, based on their side
 *
 * Panels on the left and right are expected to be "vertical" style,
 * top and bottom should be "horizontal bars". This function maps
 * the sides to expected orientation.
 */
static inline Qt::Orientation
orientation( const Calamares::Branding::PanelSide s )
{
    using Side = Calamares::Branding::PanelSide;
    return ( s == Side::Left || s == Side::Right ) ? Qt::Orientation::Vertical : Qt::Orientation::Horizontal;
}

/** @brief Get a button-sized icon. */
static inline QPixmap
getButtonIcon( const QString& name )
{
    return Calamares::Branding::instance()->image( name, QSize( 22, 22 ) );
}

static inline void
setButtonIcon( QPushButton* button, const QString& name )
{
    auto icon = getButtonIcon( name );
    if ( button && !icon.isNull() )
    {
        button->setIcon( icon );
    }
}

static QWidget*
getWidgetSidebar( Calamares::DebugWindowManager* debug,
                  Calamares::ViewManager* viewManager,
                  QWidget* parent,
                  Qt::Orientation,
                  int desiredWidth )
{
    const Calamares::Branding* const branding = Calamares::Branding::instance();

    QWidget* sideBox = new QWidget( parent );
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
    tv->setModel( viewManager );
    tv->setFocusPolicy( Qt::NoFocus );
    sideLayout->addWidget( tv );

    QHBoxLayout* extraButtons = new QHBoxLayout;
    sideLayout->addLayout( extraButtons );

    const int defaultFontHeight = CalamaresUtils::defaultFontHeight();

    if ( /* About-Calamares Button enabled */ true )
    {
        QPushButton* aboutDialog = new QPushButton;
        aboutDialog->setObjectName( "aboutButton" );
        aboutDialog->setIcon( CalamaresUtils::defaultPixmap( CalamaresUtils::Information,
                                                             CalamaresUtils::Original,
                                                             2 * QSize( defaultFontHeight, defaultFontHeight ) ) );
        CALAMARES_RETRANSLATE_FOR(
            aboutDialog,
            aboutDialog->setText(
                QCoreApplication::translate( CalamaresWindow::staticMetaObject.className(), "About" ) );
            aboutDialog->setToolTip( QCoreApplication::translate( CalamaresWindow::staticMetaObject.className(),
                                                                  "Show information about Calamares" ) ); );
        extraButtons->addWidget( aboutDialog );
        aboutDialog->setFlat( true );
        aboutDialog->setCheckable( true );
        QObject::connect( aboutDialog, &QPushButton::clicked, debug, &Calamares::DebugWindowManager::about );
    }
    if ( debug && debug->enabled() )
    {
        QPushButton* debugWindowBtn = new QPushButton;
        debugWindowBtn->setObjectName( "debugButton" );
        debugWindowBtn->setIcon( CalamaresUtils::defaultPixmap(
            CalamaresUtils::Bugs, CalamaresUtils::Original, 2 * QSize( defaultFontHeight, defaultFontHeight ) ) );
        CALAMARES_RETRANSLATE_FOR( debugWindowBtn,
                                   debugWindowBtn->setText( QCoreApplication::translate(
                                       CalamaresWindow::staticMetaObject.className(), "Debug" ) );
                                   debugWindowBtn->setToolTip( QCoreApplication::translate(
                                       CalamaresWindow::staticMetaObject.className(), "Show debug information" ) ); );
        extraButtons->addWidget( debugWindowBtn );
        debugWindowBtn->setFlat( true );
        debugWindowBtn->setCheckable( true );
        QObject::connect( debugWindowBtn, &QPushButton::clicked, debug, &Calamares::DebugWindowManager::show );
        QObject::connect(
            debug, &Calamares::DebugWindowManager::visibleChanged, debugWindowBtn, &QPushButton::setChecked );
    }

    CalamaresUtils::unmarginLayout( sideLayout );
    return sideBox;
}

static QWidget*
getWidgetNavigation( Calamares::DebugWindowManager*,
                     Calamares::ViewManager* viewManager,
                     QWidget* parent,
                     Qt::Orientation,
                     int )
{
    QWidget* navigation = new QWidget( parent );
    QBoxLayout* bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();

    // Create buttons and sets an initial icon; the icons may change
    {
        auto* back
            = new QPushButton( getButtonIcon( QStringLiteral( "go-previous" ) ),
                               QCoreApplication::translate( CalamaresWindow::staticMetaObject.className(), "&Back" ),
                               navigation );
        back->setObjectName( "view-button-back" );
        back->setEnabled( viewManager->backEnabled() );
        QObject::connect( back, &QPushButton::clicked, viewManager, &Calamares::ViewManager::back );
        QObject::connect( viewManager, &Calamares::ViewManager::backEnabledChanged, back, &QPushButton::setEnabled );
        QObject::connect( viewManager, &Calamares::ViewManager::backLabelChanged, back, &QPushButton::setText );
        QObject::connect(
            viewManager, &Calamares::ViewManager::backIconChanged, [ = ]( QString n ) { setButtonIcon( back, n ); } );
        QObject::connect(
            viewManager, &Calamares::ViewManager::backAndNextVisibleChanged, back, &QPushButton::setVisible );
        bottomLayout->addWidget( back );
    }
    {
        auto* next
            = new QPushButton( getButtonIcon( QStringLiteral( "go-next" ) ),
                               QCoreApplication::translate( CalamaresWindow::staticMetaObject.className(), "&Next" ),
                               navigation );
        next->setObjectName( "view-button-next" );
        next->setEnabled( viewManager->nextEnabled() );
        QObject::connect( next, &QPushButton::clicked, viewManager, &Calamares::ViewManager::next );
        QObject::connect( viewManager, &Calamares::ViewManager::nextEnabledChanged, next, &QPushButton::setEnabled );
        QObject::connect( viewManager, &Calamares::ViewManager::nextLabelChanged, next, &QPushButton::setText );
        QObject::connect(
            viewManager, &Calamares::ViewManager::nextIconChanged, [ = ]( QString n ) { setButtonIcon( next, n ); } );
        QObject::connect(
            viewManager, &Calamares::ViewManager::backAndNextVisibleChanged, next, &QPushButton::setVisible );
        bottomLayout->addWidget( next );
    }
    bottomLayout->addSpacing( 12 );
    {
        auto* quit
            = new QPushButton( getButtonIcon( QStringLiteral( "dialog-cancel" ) ),
                               QCoreApplication::translate( CalamaresWindow::staticMetaObject.className(), "&Cancel" ),
                               navigation );
        quit->setObjectName( "view-button-cancel" );
        QObject::connect( quit, &QPushButton::clicked, viewManager, &Calamares::ViewManager::quit );
        QObject::connect( viewManager, &Calamares::ViewManager::quitEnabledChanged, quit, &QPushButton::setEnabled );
        QObject::connect( viewManager, &Calamares::ViewManager::quitLabelChanged, quit, &QPushButton::setText );
        QObject::connect(
            viewManager, &Calamares::ViewManager::quitIconChanged, [ = ]( QString n ) { setButtonIcon( quit, n ); } );
        QObject::connect( viewManager, &Calamares::ViewManager::quitTooltipChanged, quit, &QPushButton::setToolTip );
        QObject::connect( viewManager, &Calamares::ViewManager::quitVisibleChanged, quit, &QPushButton::setVisible );
        bottomLayout->addWidget( quit );
    }

    bottomLayout->setContentsMargins( 0, 0, 6, 6 );
    navigation->setLayout( bottomLayout );
    return navigation;
}

#ifdef WITH_QML

static inline void
setDimension( QQuickWidget* w, Qt::Orientation o, int desiredWidth )
{
    w->setSizePolicy( o == Qt::Orientation::Vertical ? QSizePolicy::MinimumExpanding : QSizePolicy::Expanding,
                      o == Qt::Orientation::Horizontal ? QSizePolicy::MinimumExpanding : QSizePolicy::Expanding );
    if ( o == Qt::Orientation::Vertical )
    {
        w->setFixedWidth( desiredWidth );
    }
    else
    {
        // If the QML itself sets a height, use that, otherwise go to 48 pixels
        // which seems to match what the widget navigation would use for height
        // (with *my* specific screen, style, etc. so YMMV).
        //
        // Bound between (16, 64) with a default of 48.
        qreal minimumHeight = qBound( qreal( 16 ), w->rootObject() ? w->rootObject()->height() : 48, qreal( 64 ) );
        w->setMinimumHeight( int( minimumHeight ) );
        w->setFixedHeight( int( minimumHeight ) );
    }
    w->setResizeMode( QQuickWidget::SizeRootObjectToView );
}


static QWidget*
getQmlSidebar( Calamares::DebugWindowManager* debug,
               Calamares::ViewManager*,
               QWidget* parent,
               Qt::Orientation o,
               int desiredWidth )
{
    CalamaresUtils::registerQmlModels();
    QQuickWidget* w = new QQuickWidget( parent );
    if ( debug )
    {
        w->engine()->rootContext()->setContextProperty( "debug", debug );
    }

    w->setSource( QUrl(
        CalamaresUtils::searchQmlFile( CalamaresUtils::QmlSearch::Both, QStringLiteral( "calamares-sidebar" ) ) ) );
    setDimension( w, o, desiredWidth );
    return w;
}

static QWidget*
getQmlNavigation( Calamares::DebugWindowManager* debug,
                  Calamares::ViewManager*,
                  QWidget* parent,
                  Qt::Orientation o,
                  int desiredWidth )
{
    CalamaresUtils::registerQmlModels();
    QQuickWidget* w = new QQuickWidget( parent );
    if ( debug )
    {
        w->engine()->rootContext()->setContextProperty( "debug", debug );
    }
    w->setSource( QUrl(
        CalamaresUtils::searchQmlFile( CalamaresUtils::QmlSearch::Both, QStringLiteral( "calamares-navigation" ) ) ) );
    setDimension( w, o, desiredWidth );
    return w;
}
#else
// Bogus to keep the linker happy
//
// Calls to flavoredWidget() still refer to these *names*
// even if they are subsequently not used.
static QWidget*
getQmlSidebar( Calamares::DebugWindowManager*,
               Calamares::ViewManager*,
               QWidget* parent,
               Qt::Orientation,
               int desiredWidth )
{
    return nullptr;
}
static QWidget*
getQmlNavigation( Calamares::DebugWindowManager*,
                  Calamares::ViewManager*,
                  QWidget* parent,
                  Qt::Orientation,
                  int desiredWidth )
{
    return nullptr;
}
#endif

/**@brief Picks one of two methods to call
 *
 * Calls method (member function) @p widget or @p qml with arguments @p a
 * on the given window, based on the flavor.
 */
template < typename widgetMaker, typename... args >
QWidget*
flavoredWidget( Calamares::Branding::PanelFlavor flavor,
                Qt::Orientation o,
                Calamares::DebugWindowManager* w,
                QWidget* parent,
                widgetMaker widget,
                widgetMaker qml,  // Only if WITH_QML is on
                args... a )
{
#ifndef WITH_QML
    Q_UNUSED( qml )
#endif
    auto* viewManager = Calamares::ViewManager::instance();
    switch ( flavor )
    {
    case Calamares::Branding::PanelFlavor::Widget:
        return widget( w, viewManager, parent, o, a... );
#ifdef WITH_QML
    case Calamares::Branding::PanelFlavor::Qml:
        return qml( w, viewManager, parent, o, a... );
#endif
    case Calamares::Branding::PanelFlavor::None:
        return nullptr;
    }
    __builtin_unreachable();
}

/** @brief Adds widgets to @p layout if they belong on this @p side
 */
static inline void
insertIf( QBoxLayout* layout,
          Calamares::Branding::PanelSide side,
          QWidget* first,
          Calamares::Branding::PanelSide firstSide )
{
    if ( first && side == firstSide )
    {
        layout->addWidget( first );
    }
}

CalamaresWindow::CalamaresWindow( QWidget* parent )
    : QWidget( parent )
    , m_debugManager( new Calamares::DebugWindowManager( this ) )
    , m_viewManager( nullptr )
{
    installEventFilter( CalamaresUtils::Retranslator::instance() );

    // If we can never cancel, don't show the window-close button
    if ( Calamares::Settings::instance()->disableCancel() )
    {
        setWindowFlag( Qt::WindowCloseButtonHint, false );
    }

    CALAMARES_RETRANSLATE( const auto* branding = Calamares::Branding::instance();
                           setWindowTitle( Calamares::Settings::instance()->isSetupMode()
                                               ? tr( "%1 Setup Program" ).arg( branding->productName() )
                                               : tr( "%1 Installer" ).arg( branding->productName() ) ); );

    const Calamares::Branding* const branding = Calamares::Branding::instance();
    using ImageEntry = Calamares::Branding::ImageEntry;

    using CalamaresUtils::windowMinimumHeight;
    using CalamaresUtils::windowMinimumWidth;
    using CalamaresUtils::windowPreferredHeight;
    using CalamaresUtils::windowPreferredWidth;

    using PanelSide = Calamares::Branding::PanelSide;

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

    QWidget* baseWidget = this;
    if ( !( branding->imagePath( ImageEntry::ProductWallpaper ).isEmpty() ) )
    {
        QWidget* label = new QWidget( this );
        QVBoxLayout* l = new QVBoxLayout;
        CalamaresUtils::unmarginLayout( l );
        l->addWidget( label );
        setLayout( l );
        label->setObjectName( "backgroundWidget" );
        label->setStyleSheet(
            QStringLiteral( "#backgroundWidget { background-image: url(%1); background-repeat: repeat-xy; }" )
                .arg( branding->imagePath( ImageEntry::ProductWallpaper ) ) );

        baseWidget = label;
    }

    m_viewManager = Calamares::ViewManager::instance( baseWidget );
    if ( branding->windowExpands() )
    {
        connect( m_viewManager, &Calamares::ViewManager::ensureSize, this, &CalamaresWindow::ensureSize );
    }
    // NOTE: Although the ViewManager has a signal cancelEnabled() that
    //       signals when the state of the cancel button changes (in
    //       particular, to disable cancel during the exec phase),
    //       we don't connect to it here. Changing the window flag
    //       for the close button causes uncomfortable window flashing
    //       and requires an extra show() (at least with KWin/X11) which
    //       is too annoying. Instead, leave it up to ignoring-the-quit-
    //       event, which is also the ViewManager's responsibility.

    QBoxLayout* mainLayout = new QHBoxLayout;
    QBoxLayout* contentsLayout = new QVBoxLayout;
    contentsLayout->setSpacing( 0 );

    QWidget* sideBox = flavoredWidget(
        branding->sidebarFlavor(),
        ::orientation( branding->sidebarSide() ),
        m_debugManager,
        baseWidget,
        ::getWidgetSidebar,
        ::getQmlSidebar,
        qBound( 100, CalamaresUtils::defaultFontHeight() * 12, w < windowPreferredWidth ? 100 : 190 ) );
    QWidget* navigation = flavoredWidget( branding->navigationFlavor(),
                                          ::orientation( branding->navigationSide() ),
                                          m_debugManager,
                                          baseWidget,
                                          ::getWidgetNavigation,
                                          ::getQmlNavigation,
                                          64 );

    // Build up the contentsLayout (a VBox) top-to-bottom
    // .. note that the bottom is mirrored wrt. the top
    insertIf( contentsLayout, PanelSide::Top, sideBox, branding->sidebarSide() );
    insertIf( contentsLayout, PanelSide::Top, navigation, branding->navigationSide() );
    contentsLayout->addWidget( m_viewManager->centralWidget() );
    insertIf( contentsLayout, PanelSide::Bottom, navigation, branding->navigationSide() );
    insertIf( contentsLayout, PanelSide::Bottom, sideBox, branding->sidebarSide() );

    // .. and then the mainLayout left-to-right
    insertIf( mainLayout, PanelSide::Left, sideBox, branding->sidebarSide() );
    insertIf( mainLayout, PanelSide::Left, navigation, branding->navigationSide() );
    mainLayout->addLayout( contentsLayout );
    insertIf( mainLayout, PanelSide::Right, navigation, branding->navigationSide() );
    insertIf( mainLayout, PanelSide::Right, sideBox, branding->sidebarSide() );

    // layout->count() returns number of things in it; above we have put
    // at **least** the central widget, which comes from the view manager,
    // both vertically and horizontally -- so if there's a panel along
    // either axis, the count in that axis will be > 1.
    m_viewManager->setPanelSides(
        ( contentsLayout->count() > 1 ? Qt::Orientations( Qt::Horizontal ) : Qt::Orientations() )
        | ( mainLayout->count() > 1 ? Qt::Orientations( Qt::Vertical ) : Qt::Orientations() ) );

    CalamaresUtils::unmarginLayout( mainLayout );
    CalamaresUtils::unmarginLayout( contentsLayout );
    baseWidget->setLayout( mainLayout );
    setStyleSheet( Calamares::Branding::instance()->stylesheet() );
}

void
CalamaresWindow::ensureSize( QSize size )
{
    auto mainGeometry = this->geometry();
    QSize availableSize = qApp->desktop()->availableGeometry( this ).size();

    // We only care about vertical sizes that are big enough
    int embiggenment = qMax( 0, size.height() - m_viewManager->centralWidget()->size().height() );
    if ( embiggenment < 6 )
    {
        return;
    }

    auto h = qBound( 0, mainGeometry.height() + embiggenment, availableSize.height() );
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
