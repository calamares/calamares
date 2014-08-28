#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014 KaOS (http://kaosx.us)
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
#  MA 02110-1301, USA.

import os
import shutil
import subprocess 

import libcalamares

def run():
    """ Clean up unused drivers """

    print('cleaning up video drivers')
    
    install_path = libcalamares.globalstorage.value( "rootMountPoint" )

    # remove any db.lck
    db_lock = os.path.join(install_path, "var/lib/pacman/db.lck")
    if os.path.exists(db_lock):
        with misc.raised_privileges():
            os.remove(db_lock)
  
    if os.path.exists("/tmp/used_drivers"):
        with open("/tmp/used_drivers", "r") as searchfile:
            for line in searchfile:
                if "intel" in line:
                    print(line)
                else:
                    try:
                        libcalamares.utils.chroot_call(['pacman', '-R', '--noconfirm', 
                                                        'xf86-video-vmware'])
                    except Exception as e:
                        pass
                if "nouveau" in line:
                    print(line)
                else:
                    try:
                        libcalamares.utils.chroot_call(['pacman', '-R', '--noconfirm', 
                                                        'xf86-video-nouveau', 'xf86-video-vmware'])
                    except Exception as e:
                        pass
                if "ati" in line or "radeon" in line:
                    print(line)
                else:
                    try:
                        libcalamares.utils.chroot_call(['pacman', '-R', '--noconfirm', 
                                                        'xf86-video-ati', 'xf86-video-vmware'])
                    except Exception as e:
                        pass
        searchfile.close()
    else:
        try:
            libcalamares.utils.chroot_call(['pacman', '-R', '--noconfirm', 'xf86-video-ati', 
                                            'xf86-video-vmware'])
        except Exception as e:
            pass

    print('video driver removal complete')

    print('cleaning up input drivers')

    xorg = open("/var/log/Xorg.0.log").read()
    if 'synaptics' in xorg:
        print('synaptics in use')
    else:
        try:
            libcalamares.utils.chroot_call(['pacman', '-Rncs', '--noconfirm',
                                            'xf86-input-synaptics'])
        except Exception as e:
            pass
    if 'wacom' in xorg:
        print('wacom in use')
    else:
        try:
            libcalamares.utils.chroot_call(['pacman', '-Rncs', '--noconfirm', 
                                             'xf86-input-wacom'])
        except Exception as e:
            pass

    print('input driver removal complete')

    print('job_cleanup_drivers')
    
    return None
