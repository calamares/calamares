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


#include "CalamaresApplication.h"

#include "kdsingleapplicationguard/kdsingleapplicationguard.h"
#include "utils/Logger.h"

#include <QCommandLineParser>
#include <QDebug>

int
main( int argc, char *argv[] )
{
    CalamaresApplication a( argc, argv );

    QCommandLineParser parser;
    parser.setApplicationDescription( "Distribution-independent installer framework" );
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption verboseOption( QStringList() << "v" << "verbose",
                                      "Verbose output for debugging purposes." );
    parser.addOption( verboseOption );

    parser.process( a );

    KDSingleApplicationGuard guard( KDSingleApplicationGuard::AutoKillOtherInstances );
    QObject::connect( &guard, SIGNAL( instanceStarted( KDSingleApplicationGuard::Instance ) ), &a, SLOT( instanceStarted( KDSingleApplicationGuard::Instance ) ) );

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
