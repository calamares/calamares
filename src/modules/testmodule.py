#!/usr/bin/env python3
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Teo Mrnjavac <teo@kde.org>
#
#   Calamares is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Calamares is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Calamares. If not, see <http://www.gnu.org/licenses/>.

import os
import sys
import yaml
libcalamarespath = os.path.abspath( sys.argv[ 1 ] )
sys.path.append( libcalamarespath )
import libcalamares

class Job:
    def __init__( self, workingPath, doc ):
        self.prettyName = "Testing job " + doc[ "name" ]
        self.workingPath = workingPath
        self.configuration = doc[ "configuration" ]

# Usage: ./testmodule.py <libcalamares.so dir> <python module dir> [global_storage yaml file]
def main( args ):
    moduledirpath = os.path.abspath( sys.argv[ 2 ] )
    print( "Importing libcalamares from: " + libcalamares.__file__ )
    print( "Testing module in: " + moduledirpath )

    confpath = os.path.join( moduledirpath, "module.conf" )

    conffile = open( confpath, 'r' )
    doc = yaml.load( conffile )

    if not doc[ "type" ] == "job" or not doc[ "interface" ] == "python":
        print( "Only Python jobs can be tested." )
        return 1

    libcalamares.__dict__[ "job" ] = Job( moduledirpath, doc )
    libcalamares.__dict__[ "global_storage" ] = libcalamares.GlobalStorage()

    # if a file for simulating global_storage contents is provided, load it
    if len( sys.argv ) > 3:
        doc = yaml.load( open( os.path.abspath( sys.argv[ 3 ] ), 'r' ) )
        for key, value in doc.items():
            libcalamares.global_storage.insert( key, value )

    scriptpath = os.path.abspath( moduledirpath )
    sys.path.append( scriptpath )
    import main

    print( "Output from module:" )
    print( main.calamares_main() )

    return 0


if __name__ == "__main__":
    sys.exit( main( sys.argv ) )