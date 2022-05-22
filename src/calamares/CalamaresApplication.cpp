/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "CalamaresApplication.h"

#include "CalamaresConfig.h"
#include "CalamaresVersionX.h"
#include "CalamaresWindow.h"
#include "progresstree/ProgressTreeView.h"

#include "Branding.h"
#include "JobQueue.h"
#include "Settings.h"
#include "ViewManager.h"
#include "modulesystem/ModuleManager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/CalamaresUtilsSystem.h"
#include "utils/Dirs.h"
#include "utils/Logger.h"
#ifdef WITH_QML
#include "utils/Qml.h"
#endif
#include "utils/Retranslator.h"
#include "viewpages/ViewStep.h"

#include <QDesktopWidget>
#include <QDir>
#include <QFileInfo>
#include <QScreen>
#include <QTimer>

/// @brief Convenience for "are the settings in debug mode"
static bool
isDebug()
{
    return Calamares::Settings::instance() && Calamares::Settings::instance()->debugMode();
}

CalamaresApplication::CalamaresApplication( int& argc, char* argv[] )
    : QApplication( argc, argv )
    , m_mainwindow( nullptr )
    , m_moduleManager( nullptr )
{
    // Setting the organization name makes the default cache
    // directory -- where Calamares stores logs, for instance --
    // <org>/<app>/, so we end up with ~/.cache/Calamares/calamares/
    // which is excessively squidly.
    //
    // setOrganizationName( QStringLiteral( CALAMARES_ORGANIZATION_NAME ) );
    setOrganizationDomain( QStringLiteral( CALAMARES_ORGANIZATION_DOMAIN ) );
    setApplicationName( QStringLiteral( CALAMARES_APPLICATION_NAME ) );
    setApplicationVersion( QStringLiteral( CALAMARES_VERSION ) );

    QFont f = font();
    CalamaresUtils::setDefaultFontSize( f.pointSize() );
}


void
CalamaresApplication::init()
{
    Logger::setupLogfile();
    cDebug() << "Calamares version:" << CALAMARES_VERSION;
    cDebug() << Logger::SubEntry << "languages:" << QString( CALAMARES_TRANSLATION_LANGUAGES ).replace( ";", ", " );

    if ( !Calamares::Settings::instance() )
    {
        cError() << "Must create Calamares::Settings before the application.";
        ::exit( 1 );
    }
    initQmlPath();
    initBranding();

    CalamaresUtils::installTranslator();

    setQuitOnLastWindowClosed( false );
    setWindowIcon( QIcon( Calamares::Branding::instance()->imagePath( Calamares::Branding::ProductIcon ) ) );

    cDebug() << Logger::SubEntry << "STARTUP: initSettings, initQmlPath, initBranding done";

    initModuleManager();  //also shows main window

    cDebug() << Logger::SubEntry << "STARTUP: initModuleManager: module init started";
}


CalamaresApplication::~CalamaresApplication()
{
    Logger::CDebug( Logger::LOGVERBOSE ) << "Shutting down Calamares...";
    Logger::CDebug( Logger::LOGVERBOSE ) << Logger::SubEntry << "Finished shutdown.";
}


CalamaresApplication*
CalamaresApplication::instance()
{
    return qobject_cast< CalamaresApplication* >( QApplication::instance() );
}


CalamaresWindow*
CalamaresApplication::mainWindow()
{
    return m_mainwindow;
}


static QStringList
brandingFileCandidates( bool assumeBuilddir, const QString& brandingFilename )
{
    QStringList brandingPaths;
    if ( CalamaresUtils::isAppDataDirOverridden() )
    {
        brandingPaths << CalamaresUtils::appDataDir().absoluteFilePath( brandingFilename );
    }
    else
    {
        if ( assumeBuilddir )
        {
            brandingPaths << ( QDir::currentPath() + QStringLiteral( "/src/" ) + brandingFilename );
        }
        if ( CalamaresUtils::haveExtraDirs() )
            for ( auto s : CalamaresUtils::extraDataDirs() )
            {
                brandingPaths << ( s + brandingFilename );
            }
        brandingPaths << QDir( CMAKE_INSTALL_FULL_SYSCONFDIR "/calamares/" ).absoluteFilePath( brandingFilename );
        brandingPaths << CalamaresUtils::appDataDir().absoluteFilePath( brandingFilename );
    }

    return brandingPaths;
}


void
CalamaresApplication::initQmlPath()
{
#ifdef WITH_QML
    if ( !CalamaresUtils::initQmlModulesDir() )
    {
        ::exit( EXIT_FAILURE );
    }
#endif
}


void
CalamaresApplication::initBranding()
{
    QString brandingComponentName = Calamares::Settings::instance()->brandingComponentName();
    if ( brandingComponentName.simplified().isEmpty() )
    {
        cError() << "FATAL: branding component not set in settings.conf";
        ::exit( EXIT_FAILURE );
    }

    QString brandingDescriptorSubpath = QString( "branding/%1/branding.desc" ).arg( brandingComponentName );
    QStringList brandingFileCandidatesByPriority = brandingFileCandidates( isDebug(), brandingDescriptorSubpath );

    QFileInfo brandingFile;
    bool found = false;

    foreach ( const QString& path, brandingFileCandidatesByPriority )
    {
        QFileInfo pathFi( path );
        if ( pathFi.exists() && pathFi.isReadable() )
        {
            brandingFile = pathFi;
            found = true;
            break;
        }
    }

    if ( !found || !brandingFile.exists() || !brandingFile.isReadable() )
    {
        cError() << "Cowardly refusing to continue startup without branding."
                 << Logger::DebugList( brandingFileCandidatesByPriority );
        if ( CalamaresUtils::isAppDataDirOverridden() )
        {
            cError() << "FATAL: explicitly configured application data directory is missing" << brandingComponentName;
        }
        else
        {
            cError() << "FATAL: none of the expected branding descriptor file paths exist.";
        }
        ::exit( EXIT_FAILURE );
    }

    new Calamares::Branding( brandingFile.absoluteFilePath(), this );
}


void
CalamaresApplication::initModuleManager()
{
    m_moduleManager = new Calamares::ModuleManager( Calamares::Settings::instance()->modulesSearchPaths(), this );
    connect( m_moduleManager, &Calamares::ModuleManager::initDone, this, &CalamaresApplication::initView );
    m_moduleManager->init();
}

/** @brief centers the widget @p w on (a) screen
 *
 * This tries to duplicate the (deprecated) qApp->desktop()->availableGeometry()
 * placement by iterating over screens and putting Calamares in the first
 * one where it fits; this is *generally* the primary screen.
 *
 * With debugging, it would look something like this (2 screens attached,
 * primary at +1080+240 because I have a very strange X setup). Before
 * being mapped, the Calamares window is at +0+0 but does have a size.
 * The first screen's geometry includes the offset from the origin in
 * screen coordinates.
 *
 *  Proposed window size: 1024 520
 *  Window QRect(0,0 1024x520)
 *  Screen QRect(1080,240 2560x1440)
 *  Moving QPoint(1848,700)
 *  Screen QRect(0,0 1080x1920)
 *
 */
static void
centerWindowOnScreen( QWidget* w )
{
    QList< QScreen* > screens = qApp->screens();
    QPoint windowCenter = w->rect().center();
    QSize windowSize = w->rect().size();

    for ( const auto* screen : screens )
    {
        QSize screenSize = screen->availableGeometry().size();
        if ( ( screenSize.width() >= windowSize.width() ) && ( screenSize.height() >= windowSize.height() ) )
        {
            w->move( screen->availableGeometry().center() - windowCenter );
            break;
        }
    }
}

void
CalamaresApplication::initView()
{
    cDebug() << "STARTUP: initModuleManager: all modules init done";
    initJobQueue();
    cDebug() << "STARTUP: initJobQueue done";

    m_mainwindow = new CalamaresWindow();  //also creates ViewManager

    connect( m_moduleManager, &Calamares::ModuleManager::modulesLoaded, this, &CalamaresApplication::initViewSteps );
    connect( m_moduleManager, &Calamares::ModuleManager::modulesFailed, this, &CalamaresApplication::initFailed );

    QTimer::singleShot( 0, m_moduleManager, &Calamares::ModuleManager::loadModules );

    if ( Calamares::Branding::instance() && Calamares::Branding::instance()->windowPlacementCentered() )
    {
        centerWindowOnScreen( m_mainwindow );
    }
    cDebug() << "STARTUP: CalamaresWindow created; loadModules started";
}


void
CalamaresApplication::initViewSteps()
{
    cDebug() << "STARTUP: loadModules for all modules done";
    m_moduleManager->checkRequirements();
    if ( Calamares::Branding::instance()->windowMaximize() )
    {
        m_mainwindow->setWindowFlag( Qt::FramelessWindowHint );
        m_mainwindow->showMaximized();
    }
    else
    {
        m_mainwindow->show();
    }

    cDebug() << "STARTUP: Window now visible and ProgressTreeView populated";
    cDebug() << Logger::SubEntry << Calamares::ViewManager::instance()->viewSteps().count() << "view steps loaded.";
    Calamares::ViewManager::instance()->onInitComplete();
}

void
CalamaresApplication::initFailed( const QStringList& l )
{
    cError() << "STARTUP: failed modules are" << l;
    m_mainwindow->show();
}

void
CalamaresApplication::initJobQueue()
{
    Calamares::JobQueue* jobQueue = new Calamares::JobQueue( this );
    new CalamaresUtils::System( Calamares::Settings::instance()->doChroot(), this );
    Calamares::Branding::instance()->setGlobals( jobQueue->globalStorage() );
}
