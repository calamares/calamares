/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

/**
 * This is a test-application that just checks the YAML config-file
 * shipped with each module for correctness -- well, for parseability.
 */

#include "utils/Yaml.h"

#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include <QByteArray>
#include <QFile>

using std::cerr;

static const char usage[] = "Usage: test_conf [-v] [-b] <file> ...\n";

int
main( int argc, char** argv )
{
    bool verbose = false;
    bool bytes = false;

    int opt;
    while ( ( opt = getopt( argc, argv, "vb" ) ) != -1 )
    {
        switch ( opt )
        {
        case 'v':
            verbose = true;
            break;
        case 'b':
            bytes = true;
            break;
        default: /* '?' */
            cerr << usage;
            return 1;
        }
    }

    if ( optind >= argc )
    {
        cerr << usage;
        return 1;
    }

    const char* filename = argv[ optind ];
    try
    {
        YAML::Node doc;
        if ( bytes )
        {
            QFile f( filename );
            if ( f.open( QFile::ReadOnly | QFile::Text ) )
            {
                doc = YAML::Load( f.readAll().constData() );
            }
        }
        else
        {
            doc = YAML::LoadFile( filename );
        }

        if ( doc.IsNull() )
        {
            // Special case: empty config files are valid,
            // but aren't a map. For the example configs,
            // this is still an error.
            cerr << "WARNING:" << filename << '\n';
            cerr << "WARNING: empty YAML\n";
            return 1;
        }

        if ( !doc.IsMap() )
        {
            cerr << "WARNING:" << filename << '\n';
            cerr << "WARNING: not-a-YAML-map (type=" << doc.Type() << ")\n";
            return 1;
        }

        if ( verbose )
        {
            cerr << "Keys:\n";
            for ( auto i = doc.begin(); i != doc.end(); ++i )
            {
                cerr << i->first.as< std::string >() << '\n';
            }
        }
    }
    catch ( YAML::Exception& e )
    {
        cerr << "WARNING:" << filename << '\n';
        cerr << "WARNING: YAML parser error " << e.what() << '\n';
        return 1;
    }

    return 0;
}
