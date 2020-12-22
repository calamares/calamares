/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

/** @brief Command-line tool to enable or disable automounting
 *
 * This application uses Calamares methods to enable or disable
 * automount settings in the running system. This can be used to
 * test the automount-manipulating code without running
 * a full Calamares or doing an installation.
 *
 */

static const char usage[] = "Usage: calautomount <-e|-d>\n"
                            "\n"
                            "Enables (if `-e` is passed as command-line option) or\n"
                            "Disables (if `-d` is passed as command-line option)\n"
                            "\n"
                            "automounting of disks in the host system as best it can.\n"
                            "Exits with code 0 on success or 1 if an unknown option is\n"
                            "passed on the command-line.\n\n";

#include "AutoMount.h"
#include "Sync.h"
#include "utils/Logger.h"

#include <QCoreApplication>
#include <QDebug>

int
main( int argc, char** argv )
{
    QCoreApplication app( argc, argv );

    if ( ( argc != 2 ) || ( argv[ 1 ][ 0 ] != '-' ) || ( argv[ 1 ][ 1 ] != 'e' && argv[ 1 ][ 1 ] != 'd' ) )
    {
        qWarning() << usage;
        return 1;
    }

    Logger::setupLogfile();
    Logger::setupLogLevel( Logger::LOGDEBUG );
    CalamaresUtils::Partition::automountDisable( argv[ 1 ][ 1 ] == 'd' );

    return 0;
}
