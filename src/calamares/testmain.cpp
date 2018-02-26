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

#include "Settings.h"

#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QFileInfo>

#include <memory>

static QString
handle_args( QCoreApplication& a )
{
    QCommandLineOption debugLevelOption( QStringLiteral("D"),
                                          "Verbose output for debugging purposes (0-8).", "level" );

    QCommandLineParser parser;
    parser.setApplicationDescription( "Calamares module tester" );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption( debugLevelOption );
    parser.addPositionalArgument( "module", "Path or name of module to run." );

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
        return QString();  // NOTREACHED
    }
    if ( args.size() > 1 )
    {
        cError() << "More than one <module> path.\n";
        parser.showHelp();
        return QString();  // NOTREACHED
    }

    return args.first();
}


static Calamares::Module*
load_module( const QString& moduleName )
{
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
    QString configFile = moduleDirectory + '/' + name + ".conf";

    Calamares::Module* module = Calamares::Module::fromDescriptor(
        descriptor, name, configFile, moduleDirectory );

    return module;
}

int
main( int argc, char* argv[] )
{
    QCoreApplication a( argc, argv );

    QString module = handle_args( a );
    if ( module.isEmpty() )
        return 1;

    std::unique_ptr< Calamares::Settings > settings_p( new Calamares::Settings( QString(), true ) );
    cDebug() << "Calamares test module-loader" << module;
    Calamares::Module* m = load_module( module );
    if ( !m )
    {
        cError() << "No module.desc data found in" << module;
        return 1;
    }

    return 0;
}
