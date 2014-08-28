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

import os
import shutil
import glob
import subprocess

import libcalamares

def run():
    """ Setup graphics drivers and sound """
    
    install_path = libcalamares.globalstorage.value( "rootMountPoint" )
    
    # remove any db.lck
    db_lock = os.path.join(install_path, "var/lib/pacman/db.lck")
    if os.path.exists(db_lock):
        with misc.raised_privileges():
            os.remove(db_lock)

    # setup alsa volume levels, alsa blacklist for the pc speaker, 
    # blacklist for broken realtek nics
    print('setup alsa config')
    files_to_copy = ['/etc/asound.state', '/etc/modprobe.d/alsa_blacklist.conf',
                     '/etc/modprobe.d/realtek_blacklist.conf']
    for f in files_to_copy:
        if os.path.exists(f):
            shutil.copy2(f, os.path.join(install_path))

    # setup proprietary drivers, if detected
    print('setup proprietary drivers')
    if os.path.exists('/tmp/nvidia'):
        print('nvidia detected')
        print('removing unneeded packages')
        libcalamares.utils.chroot_call(['pacman', '-Rdd', '--noconfirm', 'libgl'])
        libcalamares.utils.chroot_call(['pacman', '-Rdd', '--noconfirm', 'xf86-video-nouveau'])
        print('installing driver')
        shutil.copytree('/opt/kdeos/pkgs', '%s/opt/kdeos/pkgs' % (install_path))
        for nvidia_utils in glob.glob('/opt/kdeos/pkgs/nvidia-utils-34*'):
            libcalamares.utils.chroot_call(['pacman', '-Ud', '--force', '--noconfirm', nvidia_utils])
        for nvidia in glob.glob('/opt/kdeos/pkgs/nvidia-34*'):
            libcalamares.utils.chroot_call(['pacman', '-Ud', '--force', '--noconfirm', nvidia])
        shutil.rmtree('%s/opt/kdeos/pkgs' % (install_path))
    elif os.path.exists('/tmp/nvidia-304xx'):
        print('nvidia-304xx detected')
        print('removing unneeded packages')
        libcalamares.utils.chroot_call(['pacman', '-Rdd', '--noconfirm', 'libgl'])
        libcalamares.utils.chroot_call(['pacman', '-Rdd', '--noconfirm', 'xf86-video-nouveau'])
        print('installing driver')
        shutil.copytree('/opt/kdeos/pkgs', '%s/opt/kdeos/pkgs' % (install_path))
        for nvidia_304_utils in glob.glob('/opt/kdeos/pkgs/nvidia-304xx-utils*'):
            libcalamares.utils.chroot_call(['pacman', '-Ud', '--force', '--noconfirm', nvidia_304_utils])
        for nvidia_304 in glob.glob('/opt/kdeos/pkgs/nvidia-304xx-3*'):
            libcalamares.utils.chroot_call(['pacman', '-Ud', '--force', '--noconfirm', nvidia_304])
        shutil.rmtree('%s/opt/kdeos/pkgs' % (install_path))
  
    print('done setting up hardware')
    
    return None
