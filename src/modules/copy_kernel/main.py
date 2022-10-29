#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import os
import shutil

import libcalamares
from libcalamares.utils import *


def run():
    """ Copy kernel and install scripts to target system.

    :return:
    """

    kernel_path = "/run/archiso/bootmnt/arch/boot/x86_64/"
    kernel_root = "vmlinuz"
    ucode_tail = "ucode.img"

    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")
    if not root_mount_point:
        return ("No mount point for root partition in globalstorage",
                "globalstorage does not contain a \"rootMountPoint\" key, "
                "doing nothing")

    if not os.path.exists(root_mount_point):
        return ("Bad mount point for root partition in globalstorage",
                "globalstorage[\"rootMountPoint\"] is \"{}\", which does not "
                "exist, doing nothing".format(root_mount_point))

    try:
        # Copy any kernels and ucode available to /boot in the target
        for file in os.listdir(kernel_path):
            if file.startswith(kernel_root) or file.endswith(ucode_tail):
                shutil.copy2(file, os.path.join(root_mount_point, "boot", os.path.basename(file)))
    except Exception as e:
        return "File copy failed", "kernel-copy failed to copy file with error " + format(e)

    return None
