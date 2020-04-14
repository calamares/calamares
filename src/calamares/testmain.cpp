/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
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

/*
 * This executable loads and runs a Calamares Python module
 * within a C++ application, in order to test the different
 * bindings.
 */

#include "modulesystem/Module.h"
#include "utils/Logger.h"
#include "utils/Yaml.h"

#include "Branding.h"
#include "GlobalStorage.h"
#include "Job.h"
#include "JobQueue.h"
#include "Settings.h"
#include "ViewManager.h"

#include "modulesystem/ModuleManager.h"

#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QFileInfo>
#include <QLabel>
#include <QMainWindow>

#include <memory>

struct ModuleConfig
{
    QString moduleName() const { return m_module; }
    QString configFile() const { return m_jobConfig; }
    QString language() const { return m_language; }
    QString globalConfigFile() const { return m_globalConfig; }

    QString m_module;
    QString m_jobConfig;
    QString m_globalConfig;
    QString m_language;
    QString m_branding;
    bool m_ui;
};

static ModuleConfig
handle_args( QCoreApplication& a )
{
    QCommandLineOption debugLevelOption(
        QStringLiteral( "D" ), "Verbose output for debugging purposes (0-8), ignored.", "level" );
    QCommandLineOption globalOption( QStringList() << QStringLiteral( "g" ) << QStringLiteral( "global " ),
                                     QStringLiteral( "Global settings document" ),
                                     "global.yaml" );
    QCommandLineOption jobOption( QStringList() << QStringLiteral( "j" ) << QStringLiteral( "job" ),
                                  QStringLiteral( "Job settings document" ),
                                  "job.yaml" );
    QCommandLineOption langOption( QStringList() << QStringLiteral( "l" ) << QStringLiteral( "language" ),
                                   QStringLiteral( "Language (global)" ),
                                   "languagecode" );
    QCommandLineOption brandOption( QStringList() << QStringLiteral( "b" ) << QStringLiteral( "branding" ),
                                    QStringLiteral( "Branding directory" ),
                                    "path/to/branding.desc",
                                    "src/branding/default/branding.desc" );
    QCommandLineOption uiOption( QStringList() << QStringLiteral( "U" ) << QStringLiteral( "ui" ),
                                 QStringLiteral( "Enable UI" ) );

    QCommandLineParser parser;
    parser.setApplicationDescription( "Calamares module tester" );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption( debugLevelOption );
    parser.addOption( globalOption );
    parser.addOption( jobOption );
    parser.addOption( langOption );
    parser.addOption( brandOption );
    parser.addOption( uiOption );
    parser.addPositionalArgument( "module", "Path or name of module to run." );
    parser.addPositionalArgument( "job.yaml", "Path of job settings document to use.", "[job.yaml]" );

    parser.process( a );

    const QStringList args = parser.positionalArguments();
    if ( args.isEmpty() )
    {
        cError() << "Missing <module> path.\n";
        parser.showHelp();
    }
    else if ( args.size() > 2 )
    {
        cError() << "More than one <module> path.\n";
        parser.showHelp();
    }
    else
    {
        QString jobSettings( parser.value( jobOption ) );
        if ( jobSettings.isEmpty() && ( args.size() == 2 ) )
        {
            jobSettings = args.at( 1 );
        }

        return ModuleConfig { args.first(),
                              jobSettings,
                              parser.value( globalOption ),
                              parser.value( langOption ),
                              parser.value( brandOption ),
                              parser.isSet( uiOption ) };
    }
}


static Calamares::Module*
load_module( const ModuleConfig& moduleConfig )
{
    QString moduleName = moduleConfig.moduleName();
    QFileInfo fi;

    bool ok = false;
    QVariantMap descriptor;

    for ( const QString& prefix : QStringList { "./", "src/modules/", "modules/" } )
    {
        // Could be a complete path, eg. src/modules/dummycpp/module.desc
        fi = QFileInfo( prefix + moduleName );
        if ( fi.exists() && fi.isFile() )
        {
            descriptor = CalamaresUtils::loadYaml( fi, &ok );
        }
        if ( ok )
        {
            break;
        }

        // Could be a path without module.desc
        fi = QFileInfo( prefix + moduleName );
        if ( fi.exists() && fi.isDir() )
        {
            fi = QFileInfo( prefix + moduleName + "/module.desc" );
            if ( fi.exists() && fi.isFile() )
            {
                descriptor = CalamaresUtils::loadYaml( fi, &ok );
            }
            if ( ok )
            {
                break;
            }
        }
    }

    if ( !ok )
    {
        cWarning() << "No suitable module descriptor found.";
        return nullptr;
    }

    QString name = descriptor.value( "name" ).toString();
    if ( name.isEmpty() )
    {
        cWarning() << "No name found in module descriptor" << fi.absoluteFilePath();
        return nullptr;
    }

    QString moduleDirectory = fi.absolutePath();
    QString configFile( moduleConfig.configFile().isEmpty() ? moduleDirectory + '/' + name + ".conf"
                                                            : moduleConfig.configFile() );

    cDebug() << "Module" << moduleName << "job-configuration:" << configFile;

    Calamares::Module* module = Calamares::moduleFromDescriptor( descriptor, name, configFile, moduleDirectory );

    return module;
}

/** @brief Create the right kind of QApplication
 *
 * Does primitive parsing of argv[] to find the --ui option and returns
 * a UI-enabled application if it does.
 *
 * @p argc must be a reference (to main's argc) because the QCoreApplication
 * constructors take a reference as well, and that would otherwise be a
 * reference to a temporary.
 */
QCoreApplication*
createApplication( int& argc, char* argv[] )
{
    for ( int i = 1; i < argc; ++i )
    {
        if ( !qstrcmp( argv[ i ], "--ui" ) || !qstrcmp( argv[ i ], "-U" ) )
        {
            auto* aw = new QApplication( argc, argv );
            aw->setQuitOnLastWindowClosed( true );
            return aw;
        }
    }
    return new QCoreApplication( argc, argv );
}

int
main( int argc, char* argv[] )
{
    QCoreApplication* aw = createApplication( argc, argv );

    Logger::setupLogLevel( Logger::LOGVERBOSE );

    ModuleConfig module = handle_args( *aw );
    if ( module.moduleName().isEmpty() )
    {
        return 1;
    }

    std::unique_ptr< Calamares::Settings > settings_p( Calamares::Settings::init( QString() ) );
    std::unique_ptr< Calamares::JobQueue > jobqueue_p( new Calamares::JobQueue( nullptr ) );
    QMainWindow* mw = nullptr;

    auto* gs = jobqueue_p->globalStorage();
    if ( !module.globalConfigFile().isEmpty() )
    {
        gs->loadYaml( module.globalConfigFile() );
    }
    if ( !module.language().isEmpty() )
    {
        QVariantMap vm;
        vm.insert( "LANG", module.language() );
        gs->insert( "localeConf", vm );
    }

    cDebug() << "Calamares module-loader testing" << module.moduleName();
    Calamares::Module* m = load_module( module );
    if ( !m )
    {
        cError() << "Could not load module" << module.moduleName();
        return 1;
    }

    cDebug() << " .. got" << m->name() << m->typeString() << m->interfaceString();
    if ( m->type() == Calamares::Module::Type::View )
    {
        mw = module.m_ui ? new QMainWindow() : nullptr;

        (void)new Calamares::Branding( module.m_branding );
        (void)new Calamares::ModuleManager( QStringList(), nullptr );
        (void)Calamares::ViewManager::instance( mw );
    }

    if ( !m->isLoaded() )
    {
        m->loadSelf();
    }

    if ( !m->isLoaded() )
    {
        cError() << "Module" << module.moduleName() << "could not be loaded.";
        return 1;
    }

    if ( mw )
    {
        auto* vm = Calamares::ViewManager::instance();
        vm->onInitComplete();
        QWidget* w = vm->currentStep()->widget();
        w->setParent( mw );
        mw->setCentralWidget( w );
        w->show();
        mw->show();
        return aw->exec();
    }

    using TR = Logger::DebugRow< const char*, const QString >;

    cDebug() << "Module metadata" << TR( "name", m->name() ) << TR( "type", m->typeString() )
             << TR( "interface", m->interfaceString() );

    cDebug() << "Job outputs:";
    Calamares::JobList jobList = m->jobs();
    unsigned int failure_count = 0;
    unsigned int count = 1;
    for ( const auto& p : jobList )
    {
        cDebug() << "Job #" << count << "name" << p->prettyName();
        Calamares::JobResult r = p->exec();
        if ( !r )
        {
            cError() << "Job #" << count << "failed" << TR( "summary", r.message() ) << TR( "details", r.details() );
            if ( r.errorCode() > 0 )
            {
                ++failure_count;
            }
        }
        ++count;
    }

    if ( aw )
    {
        delete aw;
    }

    return failure_count ? 1 : 0;
}
