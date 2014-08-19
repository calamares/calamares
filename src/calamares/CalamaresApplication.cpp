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
#include <QDesktopWidget>
#include "CalamaresApplication.h"

#include "CalamaresWindow.h"
#include "CalamaresVersion.h"
#include "CalamaresInstallDirs.h"
#include "progresstree/ProgressTreeView.h"
#include "progresstree/ProgressTreeModel.h"

#include "modulesystem/ModuleManager.h"
#include "utils/CalamaresUtilsGui.h"
#include "utils/Logger.h"
#include "JobQueue.h"
#include "Settings.h"
#include "viewpages/ViewStep.h"
#include "ViewManager.h"

#include <QDir>
#include <QFileInfo>


CalamaresApplication::CalamaresApplication( int& argc, char *argv[] )
    : QApplication( argc, argv )
    , m_mainwindow( 0 )
{
    setOrganizationName( QLatin1String( CALAMARES_ORGANIZATION_NAME ) );
    setOrganizationDomain( QLatin1String( CALAMARES_ORGANIZATION_DOMAIN ) );
    setApplicationName( QLatin1String( CALAMARES_APPLICATION_NAME ) );
    setApplicationVersion( QLatin1String( CALAMARES_VERSION ) );

    CalamaresUtils::installTranslator( this );

    QFont f = font();

    cDebug() << "Default font ====="
             << "\nPixel size:   " << f.pixelSize()
             << "\nPoint size:   " << f.pointSize()
             << "\nPoint sizeF:  " << f.pointSizeF()
             << "\nFont family:  " << f.family()
             << "\nMetric height:" << QFontMetrics( f ).height();
    // The following line blocks for 15s on Qt 5.1.0
    cDebug() << "Font height:" << QFontMetrics( f ).height();
    CalamaresUtils::setDefaultFontSize( f.pointSize() );
}


void
CalamaresApplication::init()
{
    qDebug() << "CalamaresApplication thread:" << thread();

    //TODO: Icon loader
    Logger::setupLogfile();

    setQuitOnLastWindowClosed( false );

    initSettings();

    initBranding();

    setWindowIcon( QIcon( "from branding" ) );

    initPlugins();
}


CalamaresApplication::~CalamaresApplication()
{
    cDebug( LOGVERBOSE ) << "Shutting down Calamares...";

//    if ( JobQueue::instance() )
//        JobQueue::instance()->stop();

//    delete m_mainwindow;

//    delete JobQueue::instance();

    cDebug( LOGVERBOSE ) << "Finished shutdown.";
}


CalamaresApplication*
CalamaresApplication::instance()
{
    return qobject_cast< CalamaresApplication* >( QApplication::instance() );
}


void
CalamaresApplication::setDebug( bool enabled )
{
    m_debugMode = enabled;
}


bool
CalamaresApplication::isDebug()
{
    return m_debugMode;
}


CalamaresWindow*
CalamaresApplication::mainWindow()
{
    return m_mainwindow;
}


void
CalamaresApplication::startPhase( Calamares::Phase phase )
{
    m_moduleManager->loadModules( phase );
}


void
CalamaresApplication::initSettings()
{
    QFileInfo settingsFile;
    if ( CalamaresUtils::isAppDataDirOverridden() )
    {
        settingsFile = QFileInfo( CalamaresUtils::appDataDir().absoluteFilePath( "settings.conf" ) );
        if ( !settingsFile.exists() || !settingsFile.isReadable() )
        {
            cLog() << "FATAL ERROR: explicitly configured application data directory"
                   << CalamaresUtils::appDataDir().absolutePath()
                   << "does not contain a valid settings.conf file."
                   << "\nCowardly refusing to continue startup without settings.";
            ::exit( EXIT_FAILURE );
        }
    }
    else
    {
        QStringList settingsFileCandidatesByPriority;
        if ( isDebug() )
        {
            settingsFileCandidatesByPriority.append(
                QDir::currentPath() +
                QDir::separator() +
                "settings.conf" );
        }
        settingsFileCandidatesByPriority.append( INSTALL_SYSCONFDIR "/calamares/settings.conf" );
        settingsFileCandidatesByPriority.append( "/etc/calamares/settings.conf" );
        settingsFileCandidatesByPriority.append( CalamaresUtils::appDataDir()
                                                    .absoluteFilePath( "settings.conf" ) );

        foreach ( const QString& path, settingsFileCandidatesByPriority )
        {
            QFileInfo pathFi( path );
            if ( pathFi.exists() && pathFi.isReadable() )
            {
                settingsFile = pathFi;
                break;
            }
        }

        if ( !settingsFile.exists() || !settingsFile.isReadable() )
        {
            cLog() << "FATAL ERROR: none of the expected configuration file paths ("
                   << settingsFileCandidatesByPriority.join( ", " )
                   << ") contain a valid settings.conf file."
                   << "\nCowardly refusing to continue startup without settings.";
            ::exit( EXIT_FAILURE );
        }
    }

    new Calamares::Settings( settingsFile.absoluteFilePath(), isDebug(), this );
}


void
CalamaresApplication::initBranding()
{

}


void
CalamaresApplication::initPlugins()
{
    m_moduleManager = new Calamares::ModuleManager(
        Calamares::Settings::instance()->modulesSearchPaths(), this );
    connect( m_moduleManager, &Calamares::ModuleManager::initDone,
             this,            &CalamaresApplication::onPluginsReady );
    m_moduleManager->init();

    connect( m_moduleManager, &Calamares::ModuleManager::modulesLoaded,
             this, [this]( Calamares::Phase phase )
    {
        if ( phase == Calamares::Prepare )
        {
            m_mainwindow->show();

            ProgressTreeModel* m = new ProgressTreeModel( this );
            ProgressTreeView::instance()->setModel( m );
        }
        else if ( phase == Calamares::Install )
        {
            Calamares::ViewManager* vm = Calamares::ViewManager::instance();
            Calamares::JobQueue* queue = Calamares::JobQueue::instance();

            for( const QString& name : Calamares::Settings::instance()->modules( Calamares::Install ) )
            {
                Calamares::Module* module = m_moduleManager->module( name );
                queue->enqueue( module->jobs() );
            }
            connect( queue, &Calamares::JobQueue::failed,
                     vm, &Calamares::ViewManager::onInstallationFailed );

            queue->start();
        }
    });
}


void
CalamaresApplication::onPluginsReady()
{
    initJobQueue();

    m_mainwindow = new CalamaresWindow(); //also creates ViewManager
    connect( Calamares::ViewManager::instance(), &Calamares::ViewManager::phaseChangeRequested,
             this, &CalamaresApplication::startPhase );

    startPhase( Calamares::Prepare );
    m_mainwindow->move(
        this->desktop()->availableGeometry().center() - m_mainwindow->rect().center()
    );
}


void
CalamaresApplication::initJobQueue()
{
    new Calamares::JobQueue( this );
}
