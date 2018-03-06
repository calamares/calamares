/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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


#include "CalamaresApplication.h"

#include "CalamaresConfig.h"
#include "kdsingleapplicationguard/kdsingleapplicationguard.h"
#include "utils/CalamaresUtils.h"
#include "utils/Logger.h"
#include "CalamaresConfig.h"

#ifdef WITH_KCRASH
#include <KF5/KCrash/KCrash>
#include <KF5/KCoreAddons/KAboutData>
#endif

#include <QCommandLineParser>
#include <QDebug>
#include <QDir>

static void
handle_args( CalamaresApplication& a )
{
    QCommandLineOption debugOption( QStringList{ "d", "debug"},
                                    "Also look in current directory for configuration. Implies -D8." );
    QCommandLineOption debugLevelOption( QStringLiteral("D"),
                                          "Verbose output for debugging purposes (0-8).", "level" );
    QCommandLineOption configOption( QStringList{ "c", "config"},
                                     "Configuration directory to use, for testing purposes.", "config" );

    QCommandLineParser parser;
    parser.setApplicationDescription( "Distribution-independent installer framework" );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption( debugOption );
    parser.addOption( debugLevelOption );
    parser.addOption( configOption );

    parser.process( a );

    a.setDebug( parser.isSet( debugOption ) );
    if ( parser.isSet( debugOption ) )
        Logger::setupLogLevel( Logger::LOGVERBOSE );
    else if ( parser.isSet( debugLevelOption ) )
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
    if ( parser.isSet( configOption ) )
        CalamaresUtils::setAppDataDir( QDir( parser.value( configOption ) ) );
}

int
main( int argc, char* argv[] )
{
    CalamaresApplication a( argc, argv );

#ifdef WITH_KCRASH
    KAboutData aboutData( "calamares",
                          "Calamares",
                          a.applicationVersion(),
                          "The universal system installer",
                          KAboutLicense::GPL_V3,
                          QString(),
                          QString(),
                          "https://calamares.io",
                          "https://github.com/calamares/calamares/issues" );
    KAboutData::setApplicationData( aboutData );
    KCrash::initialize();
    // KCrash::setCrashHandler();
    KCrash::setDrKonqiEnabled( true );
    KCrash::setFlags( KCrash::SaferDialog | KCrash::AlwaysDirectly );
    // TODO: umount anything in /tmp/calamares-... as an emergency save function
    a.setApplicationDisplayName( QString() );
#endif

    handle_args( a );
    KDSingleApplicationGuard guard( KDSingleApplicationGuard::AutoKillOtherInstances );

    int returnCode = 0;
    if ( guard.isPrimaryInstance() )
    {
        a.init();
        returnCode = a.exec();
    }
    else
        qDebug() << "Calamares is already running, shutting down.";

    return returnCode;
}
