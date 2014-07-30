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


def chroot_call(root_mount_point, cmd):
    subprocess.check_call(["chroot", root_mount_point] + cmd)


def install_grub(root_mount_point, boot_loader):
    install_path = boot_loader["installPath"]
    chroot_call(root_mount_point, ["grub-install", install_path])
    chroot_call(root_mount_point, ["grub-mkconfig", "-o", "/boot/grub/grub.cfg"])


def run():
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    boot_loader = libcalamares.globalstorage.value("bootLoader")
    install_grub(root_mount_point, boot_loader)
    return None
