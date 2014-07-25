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

import os
import subprocess

import libcalamares


def listMounts( rootMountPoint ):
    lst = []
    for line in open( "/etc/mtab" ).readlines():
        device, mountPoint, _ = line.split( " ", 2 )
        if mountPoint.startswith( rootMountPoint ):
            lst.append( ( device, mountPoint ) )
    return lst


def run():
    rootMountPoint = libcalamares.globalStorage.value( "rootMountPoint" )
    if not rootMountPoint:
        return "GlobalStorage does not contain a \"rootMountPoint\" key, doing nothing"
    if not os.path.exists( rootMountPoint ):
        return "GlobalStorage[\"rootMountPoint\"] is \"{}\", which does not exist, doing nothing".format( rootMountPoint )

    lst = listMounts( rootMountPoint )
    # Sort the list by mount point in decreasing order. This way we can be sure
    # we unmount deeper dirs first.
    lst.sort( key = lambda x: x[ 1 ], reverse = True )

    for device, mountPoint in lst:
        subprocess.check_call( [ "umount", mountPoint ] )

    os.rmdir( rootMountPoint )
    return "All done"
