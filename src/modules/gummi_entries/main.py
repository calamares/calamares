#!/usr/bin/env python3
# encoding: utf-8
# === This file is part of Calamares - <http://github.com/calamares> ===
#
#   Copyright 2014, Anke Boersma <demm@kaosx.us>
#   Copyright 2014, Benjamin Vaudour <benjamin.vaudour@yahoo.fr>
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
from libcalamares.utils import check_chroot_call
 
import subprocess
import os
import glob
 
install_path = libcalamares.globalstorage.value("rootMountPoint")
menu_entries = []
 
def read_grub():
    global menu_entries
    grub_path = os.path.join(install_path, 'boot', 'grub', 'grub.cfg')
    o = False
    with open(grub_path, 'r') as f:
        for l in f:
            if l.strip()[:9] == 'menuentry' and l[-2] == '{':
                o = True
                e = {}
                e["title"] = l[11:18]
            elif l.lstrip()[:5] == 'linux':
                l = l.lstrip()[5:].lstrip()
                i = l.find(' ')
                e["linux"] = l[:i]
                e["options"] = l[i+1:].rstrip('\n')
            elif l.lstrip()[:6] == 'initrd':
                e["initrd"] = l.lstrip()[6:].strip().rstrip('\n')
            elif '}' in l and o:
                o = False
                menu_entries.append(e)
                break
    f.close() 
 
# Write the menu entry .conf  
def write_conf(e):
    lines = [
            '## This is just an example config file.\n',
            '## Please edit the paths and kernel parameters according to your system.\n',
            '\n',
            'title   %s\n' % e["title"],
            'linux   %s\n' % e["linux"],
            'initrd  %s\n' % e["initrd"],
            'options %s\n' % e["options"],
        ]
    path = os.path.join(install_path, "boot", "loader", "entries", "%s.conf" % e["title"])
    with open(path, 'w') as f:
        for l in lines:
            f.write(l)
    f.close()
 
def run():
    fw_type = libcalamares.globalstorage.value("firmwareType")
    if fw_type == 'efi':
        read_grub()
        print(menu_entries)
        for e in menu_entries:
            write_conf(e)
 
run()
