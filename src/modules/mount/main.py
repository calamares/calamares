#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Aurélien Gâteau <agateau@kde.org>
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

import libcalamares
import tempfile
import os
import subprocess
import sys


def mount( devicePath, mountPoint, fs ):
    if not os.path.exists( mountPoint ):
        os.makedirs( mountPoint )
    assert devicePath
    assert mountPoint
    assert fs
    subprocess.check_call( [ "mount", "-t", fs, devicePath, mountPoint ] )


def mountPartitions( rootMountPoint, partitions ):
    lst = [ x for x in partitions if x[ "mountPoint" ] == "/" ]
    assert lst, "No root partition found"
    root = lst[ 0 ]

    mount( root[ "device" ], rootMountPoint, root[ "fs" ] )

    for partition in partitions:
        # Skip / and partitions which have no mount points
        if partition[ "mountPoint" ] in ( "/", "" ):
            continue
        mount( partition[ "device" ], rootMountPoint + partition[ "mountPoint" ], partition[ "fs" ])


def calamares_main():
    rootMountPoint = tempfile.mkdtemp( prefix="calamares-root-" )
    mountPartitions( rootMountPoint, libcalamares.global_storage.value( "partitions" ) )
    libcalamares.global_storage.insert( "rootMountPoint", rootMountPoint )
    return "all done, mounted at {}".format( rootMountPoint )


def main( args ):
    partitions = (
        {
            "device": "/dev/sdb1",
            "mountPoint": "/",
            "fs": "ext4",
        },
        {
            "device": "/dev/sdb2",
            "mountPoint": "/home",
            "fs": "ext4",
        },
        {
            "device": "/dev/sdb3",
            "mountPoint": "",
            "fs": "linuxswap",
        },
    )
    rootMountPoint = "/tmp/mount"
    mountPartitions( rootMountPoint, partitions )
    return 0


if __name__ == "__main__":
    sys.exit( main( sys.argv ) )
