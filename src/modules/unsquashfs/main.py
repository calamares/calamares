#!/usr/bin/env python3
# encoding: utf-8
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
import subprocess
import tempfile

from libcalamares import *
from filecopy import FileCopyThread


class UnsquashOperation:
    def __init__( self, unpack ):
        self.unpacklist = unpack
        self.unpackstatus = dict()
        for entry in unpack:
            self.unpackstatus[ entry[ "source" ] ] = { 'copied': 0, 'total': 0 }


    def updateCopyProgress( self, source, nfiles ):
        if source in self.unpackstatus:
            self.unpackstatus[ source ][ 'copied' ] = nfiles
            self.reportProgress()


    def reportProgress( self ):
        progress = float( 0 )
        for entry in self.unpackstatus:
            partialProgress = float( 0 )
            if entry[ 'total' ] is not 0:
                partialProgress += 0.05
            else:
                continue

            partialProgress += 0.95 * ( entry[ 'copied' ] / float( entry[ 'total' ] ) )
            progress += partialProgress / len( self.unpackstatus )

        job.setprogress( progress )


    def run( self ):
        sourceMountPath = tempfile.mkdtemp()
        try:
            for entry in self.unpacklist:
                try:
                    unsqfsProcess = subprocess.Popen( [ "unsquashfs", "-l", entry[ "source" ] ], stdout = subprocess.PIPE )
                    wcProcess = subprocess.Popen( [ "wc", "-l" ], stdin = unsqfsProcess.stdout, stdout = subprocess.PIPE )
                    countString = wcProcess.communicate()[ 0 ]
                    filesCount = int( float( countString ) )
                    self.unpackstatus[ entry[ "source" ] ][ 'total' ] = filesCount

                    imgBaseName = os.path.splitext( os.path.basename( entry[ "source" ] ) )[ 0 ]
                    imgMountDir = sourceMountPath + os.sep + imgBaseName
                    os.mkdir( imgMountDir )

                    entry[ "sourceDir" ] = imgMountDir

                    self.reportProgress()

                    self.unsquashImage( entry )
                finally:
                    os.rmdir( imgMountDir )
        finally:
            os.rmdir( sourceMountPath )

    def unsquashImage( self, entry ):
        try:
            subprocess.check_call( [ "mount", entry[ "source" ], entry[ "sourceDir" ], "-t", "squashfs", "-o", "loop" ] )

            t = FileCopyThread( entry[ "sourceDir" ], entry[ "destination" ], self.reportProgress )
            t.start()
            t.join()
        finally:
            subprocess.check_call( [ "umount", "-l", entry[ "sourceDir" ] ] )



def run():
    # from globalStorage: rootMountPoint
    # from job.configuration:
    # the path to where to mount the source image(s) for copying
    # an ordered list of unpack mappings for sqfs file <-> target dir relative
    # to rootMountPoint, e.g.:
    # configuration:
    #     unpack:
    #         - source: "/path/to/squashfs/image.sqfs"
    #           destination: ""
    #         - source: "/path/to/another/image.sqfs"
    #           destination: ""

    rootMountPoint = globalStorage.value( "rootMountPoint" )

    unpack = list()

    for entry in job.configuration[ "unpack" ]:
        source = os.path.abspath( entry[ "source" ] )
        destination = os.path.abspath( os.path.join( rootMountPoint, entry[ "destination" ] ) )

        if not os.path.isfile( source ) or not os.path.isdir( destination ):
            return "Error: bad source or destination"

        unpack.append( { 'source': source, 'destination': destination } )

    unsquashop = UnsquashOperation( unpack )
    return unsquashop.run()
