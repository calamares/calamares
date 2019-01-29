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

#include "utils/Logger.h"
#include "utils/YamlUtils.h"
#include "modulesystem/Module.h"

#include "GlobalStorage.h"
#include "Job.h"
#include "JobQueue.h"
#include "Settings.h"

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QFileInfo>

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
} ;

static ModuleConfig
handle_args( QCoreApplication& a )
{
    QCommandLineOption debugLevelOption( QStringLiteral("D"),
                                          "Verbose output for debugging purposes (0-8).", "level" );
    QCommandLineOption globalOption( QStringList() << QStringLiteral( "g" ) << QStringLiteral( "global "),
                                     QStringLiteral( "Global settings document" ), "global.yaml" );
    QCommandLineOption jobOption( QStringList() << QStringLiteral( "j" ) << QStringLiteral( "job"),
                                  QStringLiteral( "Job settings document" ), "job.yaml" );
    QCommandLineOption langOption( QStringList() << QStringLiteral( "l" ) << QStringLiteral( "language" ),
                                   QStringLiteral( "Language (global)" ), "languagecode" );

    QCommandLineParser parser;
    parser.setApplicationDescription( "Calamares module tester" );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption( debugLevelOption );
    parser.addOption( globalOption );
    parser.addOption( jobOption );
    parser.addOption( langOption );
    parser.addPositionalArgument( "module", "Path or name of module to run." );
    parser.addPositionalArgument( "job.yaml", "Path of job settings document to use.", "[job.yaml]");

    parser.process( a );

    if ( parser.isSet( debugLevelOption ) )
    {
        bool ok = true;
        int l = parser.value( debugLevelOption ).toInt( &ok );
        unsigned int dlevel = 0;
        if ( !ok || ( l < 0 ) )
            dlevel = Logger::LOGVERBOSE;
        else
            dlevel = l;
        Logger::setupLogLevel( dlevel );
    }

    const QStringList args = parser.positionalArguments();
    if ( args.isEmpty() )
    {
        cError() << "Missing <module> path.\n";
        parser.showHelp();
        return ModuleConfig();  // NOTREACHED
    }
    if ( args.size() > 2 )
    {
        cError() << "More than one <module> path.\n";
        parser.showHelp();
        return ModuleConfig();  // NOTREACHED
    }

    QString jobSettings( parser.value( jobOption ) );
    if ( jobSettings.isEmpty() && ( args.size() == 2 ) )
        jobSettings = args.at(1);

    return ModuleConfig{ args.first(), jobSettings, parser.value( globalOption ), parser.value( langOption ) };
}


static Calamares::Module*
load_module( const ModuleConfig& moduleConfig )
{
    QString moduleName = moduleConfig.moduleName();
    QFileInfo fi;

    bool ok = false;
    QVariantMap descriptor;

    for ( const QString& prefix : QStringList{ "./", "src/modules/", "modules/" } )
    {
        // Could be a complete path, eg. src/modules/dummycpp/module.desc
        fi = QFileInfo( prefix + moduleName );
        if ( fi.exists() && fi.isFile() )
            descriptor = CalamaresUtils::loadYaml( fi, &ok );
        if ( ok )
            break;

        // Could be a path without module.desc
        fi = QFileInfo( prefix + moduleName );
        if ( fi.exists() && fi.isDir() )
        {
            fi = QFileInfo( prefix + moduleName + "/module.desc" );
            if ( fi.exists() && fi.isFile() )
                descriptor = CalamaresUtils::loadYaml( fi, &ok );
            if ( ok ) break;
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
    QString configFile(
        moduleConfig.configFile().isEmpty()
        ? moduleDirectory + '/' + name + ".conf"
        : moduleConfig.configFile() );

    cDebug() << "Module" << moduleName << "job-configuration:" << configFile;

    Calamares::Module* module = Calamares::Module::fromDescriptor(
        descriptor, name, configFile, moduleDirectory );

    return module;
}

int
main( int argc, char* argv[] )
{
    QCoreApplication a( argc, argv );

    ModuleConfig module = handle_args( a );
    if ( module.moduleName().isEmpty() )
        return 1;

    std::unique_ptr< Calamares::Settings > settings_p( new Calamares::Settings( QString(), true ) );
    std::unique_ptr< Calamares::JobQueue > jobqueue_p( new Calamares::JobQueue( nullptr ) );

    auto gs = jobqueue_p->globalStorage();
    if ( !module.globalConfigFile().isEmpty() )
        gs->loadYaml( module.globalConfigFile() );
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

    if ( !m->isLoaded() )
        m->loadSelf();

    if ( !m->isLoaded() )
    {
        cError() << "Module" << module.moduleName() << "could not be loaded.";
        return 1;
    }

    using TR = Logger::DebugRow<const char*, const QString&>;

    cDebug() << "Module metadata"
        << TR( "name", m->name() )
        << TR( "type", m->typeString() )
        << TR( "interface", m->interfaceString() );

    cDebug() << "Job outputs:";
    Calamares::JobList jobList = m->jobs();
    unsigned int count = 1;
    for ( const auto& p : jobList )
    {
        cDebug() << "Job #" << count << "name" << p->prettyName();
        Calamares::JobResult r = p->exec();
        if ( !r )
        {
            using TR = Logger::DebugRow<QString, QString>;
            cDebug() << count << ".. failed"
                << TR( "summary", r.message() )
                << TR( "details", r.details() );
        }
        ++count;
    }

    return 0;
}
