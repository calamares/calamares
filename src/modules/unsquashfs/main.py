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
import re
import shutil
import subprocess
import sys
import tempfile
from collections import namedtuple

from libcalamares import *

UnpackEntry = namedtuple( 'UnpackEntry', [ 'source', 'destination', 'sourceDir' ] )
UnpackStatusEntry = namedtuple( 'UnpackStatusEntry', [ 'copied', 'total' ] )

ON_POSIX = 'posix' in sys.builtin_module_names


def fileCopy( source, dest, progress_cb ):
    # Environment used for executing rsync properly
    # Setting locale to C (fix issue with tr_TR locale)
    at_env = os.environ
    at_env["LC_ALL"] = "C"

    process = subprocess.Popen( [ 'rsync', '-ar', '--progress', source, dest ],
                                env=self.at_env,
                                bufsize=1,
                                stdout=subprocess.PIPE,
                                close_fds=ON_POSIX )

    for line in iter( self.process.stdout.readline, b'' ):
        # small comment on this regexp.
        # rsync outputs three parameters in the progress.
        # xfer#x => i try to interpret it as 'file copy try no. x'
        # to-check=x/y, where:
        #  - x = number of files yet to be checked
        #  - y = currently calculated total number of files.
        # but if you're copying directory with some links in it, the xfer# might not be a
        # reliable counter. ( for one increase of xfer, many files may be created)
        # In case of manjaro, we pre-compute the total number of files.
        # therefore we can easily subtract x from y in order to get real files copied / processed count.
        m = re.findall( r'xfr#(\d+), ir-chk=(\d+)/(\d+)', line.decode() )
        if m:
            # we've got a percentage update
            num_files_remaining = int(m[0][1])
            num_files_total_local = int(m[0][2])
            # adjusting the offset so that progressbar can be continuesly drawn
            num_files_copied = num_files_total_local - num_files_remaining


            # I guess we're updating every 100 files...
            if num_files_copied % 100 == 0:
                progress_cb( num_files_copied )


class UnsquashOperation:
    def __init__( self, unpack ):
        self.unpacklist = unpack
        self.unpackstatus = dict()
        for entry in unpack:
            self.unpackstatus[ entry.source ] = UnpackStatusEntry( copied=0, total=0 )


    def updateCopyProgress( self, source, nfiles ):
        if source in self.unpackstatus:
            self.unpackstatus[ source ].copied = nfiles
            self.reportProgress()


    def reportProgress( self ):
        progress = float( 0 )
        for statusEntry in self.unpackstatus:
            if statusEntry.total == 0:
                continue

            partialProgress = 0.05 # Having a total !=0 gives 5%

            partialProgress += 0.95 * ( statusEntry.copied / float( statusEntry.total ) )
            progress += partialProgress / len( self.unpackstatus )

        job.setprogress( progress )


    def run( self ):
        sourceMountPath = tempfile.mkdtemp()
        try:
            for entry in self.unpacklist:
                sqfsList = subprocess.check_output( [ "unsquashfs", "-l", entry.source ] )
                filesCount = sqfsList.splitlines().count()
                self.unpackstatus[ entry.source ].total = filesCount

                imgBaseName = os.path.splitext( os.path.basename( entry.source ) )[ 0 ]
                imgMountDir = sourceMountPath + os.sep + imgBaseName
                os.mkdir( imgMountDir )
                entry.sourceDir = imgMountDir
                self.reportProgress()
                self.unsquashImage( entry )
        finally:
            shutil.rmtree( sourceMountPath )


    def unsquashImage( self, entry ):
        subprocess.check_call( [ "mount", entry.source, entry.sourceDir, "-t", "squashfs", "-o", "loop" ] )
        try:
            fileCopy( entry.sourceDir, entry.destination, self.reportProgress )
        finally:
            subprocess.check_call( [ "umount", "-l", entry.sourceDir ] )


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
    if not rootMountPoint:
        return ( "No mount point for root partition in GlobalStorage",
                 "GlobalStorage does not contain a \"rootMountPoint\" key, doing nothing" )
    if not os.path.exists( rootMountPoint ):
        return ( "Bad mount point for root partition in GlobalStorage",
                 "GlobalStorage[\"rootMountPoint\"] is \"{}\", which does not exist, doing nothing".format( rootMountPoint ) )
    unpack = list()

    for entry in job.configuration[ "unpack" ]:
        source = os.path.abspath( entry[ "source" ] )
        destination = os.path.abspath( os.path.join( rootMountPoint, entry[ "destination" ] ) )

        if not os.path.isfile( source ) or not os.path.isdir( destination ):
            return ( "Bad source or destination",
                     "source=\"{}\"\ndestination=\"{}\"".format( source, destination ) )

        unpack.append( UnpackEntry( source, destination ) )

    unsquashop = UnsquashOperation( unpack )
    return unsquashop.run()
