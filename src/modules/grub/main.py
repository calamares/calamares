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
from libcalamares.utils import check_chroot_call


def install_grub(boot_loader):
    install_path = boot_loader["installPath"]
    check_chroot_call([libcalamares.job.configuration["grubInstall"], install_path])
    check_chroot_call([libcalamares.job.configuration["grubMkconfig"], "-o", libcalamares.job.configuration["grubCfg"]])


def run():
    boot_loader = libcalamares.globalstorage.value("bootLoader")
    install_grub(boot_loader)
    return None
