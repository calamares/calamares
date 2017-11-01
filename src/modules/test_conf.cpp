/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
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

/**
 * This is a test-application that just checks the YAML config-file
 * shipped with each module for correctness -- well, for parseability.
 */

#include <iostream>
#include <yaml-cpp/yaml.h>

using std::cerr;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "Usage: test_conf <file.conf>\n";
        return 1;
    }

    try
    {
        YAML::Node doc = YAML::LoadFile( argv[1] );

        if ( doc.IsNull() )
        {
            // Special case: empty config files are valid,
            // but aren't a map. For the example configs,
            // this is still an error.
            cerr << "WARNING:" << argv[1] << '\n';
            cerr << "WARNING: empty YAML\n";
            return 1;
        }

        if ( !doc.IsMap() )
        {
            cerr << "WARNING:" << argv[1] << '\n';
            cerr << "WARNING: not-a-YAML-map\n";
            return 1;
        }
    }
    catch ( YAML::Exception& e )
    {
        cerr << "WARNING:" << argv[1]  << '\n';
        cerr << "WARNING: YAML parser error " << e.what() << '\n';
        return 1;
    }

    return 0;
}
