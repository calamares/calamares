#!/usr/bin/env python3

import os
import subprocess
import shutil
import time

import libcalamares
from libcalamares.utils import gettext_path, gettext_languages

import gettext

_translation = gettext.translation("calamares-python",
                                   localedir=gettext_path(),
                                   languages=gettext_languages(),
                                   fallback=True)
_ = _translation.gettext
_n = _translation.ngettext

custom_status_message = None
status_update_time = 0


class PacmanError(Exception):
    """Exception raised when the call to pacman returns a non-zero exit code

    Attributes:
        message -- explanation of the error
    """

    def __init__(self, message):
        self.message = message


def pretty_name():
    return _("Install base system")


def pretty_status_message():
    if custom_status_message is not None:
        return custom_status_message


def line_cb(line):
    """
    Writes every line to the debug log and displays it in calamares
    :param line: The line of output text from the command
    """
    global custom_status_message
    global status_update_time
    custom_status_message = line.strip()
    libcalamares.utils.debug("pacstrap: " + line.strip())
    if (time.time() - status_update_time) > 0.5:
        libcalamares.job.setprogress(0)
        status_update_time = time.time()


def run_in_host(command, line_func):
    proc = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True,
                            bufsize=1)
    for line in proc.stdout:
        if line.strip():
            line_func(line)
    proc.wait()
    if proc.returncode != 0:
        raise PacmanError("Failed to run pacman")


def run():
    """
    Installs the base system packages and copies files post-installation

    """
    root_mount_point = libcalamares.globalstorage.value("rootMountPoint")

    if not root_mount_point:
        return ("No mount point for root partition in globalstorage",
                "globalstorage does not contain a \"rootMountPoint\" key, "
                "doing nothing")

    if not os.path.exists(root_mount_point):
        return ("Bad mount point for root partition in globalstorage",
                "globalstorage[\"rootMountPoint\"] is \"{}\", which does not "
                "exist, doing nothing".format(root_mount_point))

    if libcalamares.job.configuration:
        if "basePackages" in libcalamares.job.configuration:
            base_packages = libcalamares.job.configuration["basePackages"]
        else:
            return "Package List Missing", "Cannot continue without list of packages to install"
    else:
        return "No configuration found", "Aborting due to missing configuration"

    # run the pacstrap
    pacstrap_command = ["/etc/calamares/scripts/pacstrap_calamares", "-c", root_mount_point] + base_packages

    try:
        run_in_host(pacstrap_command, line_cb)
    except subprocess.CalledProcessError as cpe:
        return "Failed to run pacstrap", "Pacstrap failed with error {!s}".format(cpe.stderr)
    except PacmanError as pe:
        return "Failed to run pacstrap", format(pe)

    # copy files post install
    if "postInstallFiles" in libcalamares.job.configuration:
        files_to_copy = libcalamares.job.configuration["postInstallFiles"]
        for source_file in files_to_copy:
            if os.path.exists(source_file):
                try:
                    libcalamares.utils.debug("Copying file {!s}".format(source_file))
                    dest = os.path.normpath(root_mount_point + source_file)
                    os.makedirs(os.path.dirname(dest), exist_ok=True)
                    shutil.copy2(source_file, dest)
                except Exception as e:
                    libcalamares.utils.warning("Failed to copy file {!s}, error {!s}".format(source_file, e))

    libcalamares.globalstorage.insert("online", True)

    libcalamares.job.setprogress(1.0)

    return None
