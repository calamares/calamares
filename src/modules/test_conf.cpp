/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

/**
 * This is a test-application that just checks the YAML config-file
 * shipped with each module for correctness -- well, for parseability.
 */

#include <unistd.h>
#include <stdlib.h>

#include <iostream>

#include <yaml-cpp/yaml.h>

#include <QFile>
#include <QByteArray>

using std::cerr;

static const char usage[] = "Usage: test_conf [-v] [-b] <file> ...\n";

int main(int argc, char** argv)
{
    bool verbose = false;
    bool bytes = false;

    int opt;
    while ((opt = getopt(argc, argv, "vb")) != -1) {
        switch (opt) {
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

    const char* filename = argv[optind];
    try
    {
        YAML::Node doc;
        if ( bytes )
        {
            QFile f( filename );
            if ( f.open( QFile::ReadOnly | QFile::Text ) )
                doc = YAML::Load( f.readAll().constData() );
        }
        else
            doc = YAML::LoadFile( filename );

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
                cerr << i->first.as<std::string>() << '\n';
        }
    }
    catch ( YAML::Exception& e )
    {
        cerr << "WARNING:" << filename  << '\n';
        cerr << "WARNING: YAML parser error " << e.what() << '\n';
        return 1;
    }

    return 0;
}
