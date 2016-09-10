#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014 - 2016, Philip Müller <philm@manjaro.org>
#   Copyright 2016, Artoo <artoo@manjaro.org>
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

import os
import shutil
import distutils.dir_util

from os.path import join, exists
from libcalamares.utils import target_env_call, check_target_env_call

class ConfigController:
    def __init__(self):
        self.__root = libcalamares.globalstorage.value( "rootMountPoint" )
        self.__keyrings = libcalamares.job.configuration.get('keyrings', [])
        
    @property
    def root(self):
        return self.__root
    
    @property
    def keyrings(self):
        return self.__keyrings
      
    def init_keyring(self):
        check_target_env_call(["pacman-key", "--init"])

    def populate_keyring(self):
        check_target_env_call(["pacman-key", "--populate"] + self.keyrings)
        
    def terminate(self, proc):
        target_env_call(['killall', '-9', proc])
        
    def copy_file(self, file):
        if exists("/" + file):
            shutil.copy2("/" + file, join(self.root, file))

    def copy_folder(self, source, target):
        if exists("/" + source):
            distutils.dir_util.copy_tree("/" + source, join(self.root, target))
    
    def remove_pkg(self, pkg, path):
        if exists(join(self.root, path)):
            target_env_call(['pacman', '-R', '--noconfirm', pkg])
    
    def run(self):
        self.init_keyring()
        self.populate_keyring()

        # Remove calamares
        self.remove_pkg("calamares", "usr/bin/calamares")

        # Generate mirror list
        if exists(join(self.root, "usr/bin/pacman-mirrors")):
            target_env_call(["pacman-mirrors", "-g"])
        else:
            self.copy_file('etc/pacman.d/mirrorlist')

        # Copy skel to root
        self.copy_folder('etc/skel', 'root')
        
        # Workaround for pacman-key bug FS#45351 https://bugs.archlinux.org/task/45351
        # We have to kill gpg-agent because if it stays around we can't reliably unmount
        # the target partition.
        self.terminate('gpg-agent')
        
        # Update grub.cfg
        if exists(join(self.root, "usr/bin/update-grub")) and libcalamares.globalstorage.value("bootLoader") is not None:
            target_env_call(["update-grub"])
        
        return None
    
def run():
    """ Misc postinstall configurations """

    config = ConfigController()
    
    return config.run()
