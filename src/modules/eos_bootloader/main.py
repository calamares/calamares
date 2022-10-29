#!/usr/bin/env python3

import os
import subprocess
import shutil

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
name = "Prepare for bootloader"
user_output = False


def pretty_name():
    return _(name)


def pretty_status_message():
    if custom_status_message is not None:
        return custom_status_message


def get_local_packages(packages):
    try:
        package_location = libcalamares.job.configuration["packageLocation"]
    except KeyError:
        return "Configuration Error", "No package location defined in config"

    if not os.path.exists(package_location):
        return ("Package location missing",
                f"{package_location} is not currently available")

    try:
        installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
    except KeyError:
        libcalamares.utils.warning('Global storage value "rootMountPoint" missing')

    package_files = []
    for root, dirs, files in os.walk(os.path.join(installation_root_path, package_location.lstrip('/'))):
        for file in files:
            for package in packages:
                if file.startswith(package + "-") and file.endswith(".zst"):
                    package_files.append(os.path.join(package_location, file))

    return package_files


def run_dracut():
    kernel_search_path = "/usr/lib/modules"

    try:
        installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
    except KeyError:
        libcalamares.utils.warning('Global storage value "rootMountPoint" missing')

    # find all the installed kernels and run dracut
    for root, dirs, files in os.walk(os.path.join(installation_root_path, kernel_search_path.lstrip('/'))):
        for file in files:
            if file == "pkgbase":
                kernel_version = os.path.basename(root)
                # run dracut
                pkgbase_location = os.path.join(root, file)
                with open(pkgbase_location, 'r') as pkgbase_file:
                    kernel_suffix = pkgbase_file.read().rstrip()
                try:
                    libcalamares.utils.target_env_process_output(["dracut", "--force", "--hostonly",
                                                                  "--no-hostonly-cmdline",
                                                                  f"/boot/initramfs-{kernel_suffix}.img",
                                                                  kernel_version])
                    libcalamares.utils.target_env_process_output(["dracut", "--force", "--no-hostonly",
                                                                  f"/boot/initramfs-{kernel_suffix}-fallback.img",
                                                                  kernel_version])
                except subprocess.CalledProcessError as cpe:
                    libcalamares.utils.warning(f"dracut failed with error: {cpe.stderr}")

                kernel_name = f"vmlinuz-{kernel_suffix}"
                # copy kernel to boot
                shutil.copy2(os.path.join(root, "vmlinuz"), os.path.join(installation_root_path, "boot", kernel_name))


def run():
    if not libcalamares.job.configuration:
        return "No configuration found", "Aborting due to missing configuration"

    try:
        gs_name = libcalamares.job.configuration["gsName"]
    except KeyError:
        return "Missing global storage value", "gsname not found in configuration file"

    try:
        offline = libcalamares.job.configuration["offline"]
    except KeyError:
        offline = False
        pass

    bootloaders = libcalamares.job.configuration.get("bootloader", [])

    if libcalamares.globalstorage.contains(gs_name):
        bootloader_name = libcalamares.globalstorage.value(gs_name)
    else:
        return f"Key missing", f"Failed to find {gs_name} in global storage"

    packages = None

    for bootloader in bootloaders:
        try:
            if bootloader["name"].casefold() == bootloader_name.casefold():
                packages = bootloader["packages"]
        except KeyError:
            return f"Configuration error", f"Missing key 'name' in configuration"

    # remove mkinitcpio
    try:
        libcalamares.utils.target_env_process_output(["pacman", "--noconfirm", "-Rcn", "mkinitcpio"])
    except subprocess.CalledProcessError:
        pass

    # install packages
    if offline:
        package_files = get_local_packages(packages)
        if package_files is not None:
            try:
                libcalamares.utils.target_env_process_output(["pacman", "--noconfirm", "-U"] + package_files)
            except subprocess.CalledProcessError as cpe:
                return f"Failed to install packages for {bootloader_name}", f"The install failed with error: {cpe.stderr}"
    else:
        if packages is not None:
            try:
                libcalamares.utils.target_env_process_output(["pacman", "--noconfirm", "-S"] + packages)
            except subprocess.CalledProcessError as cpe:
                return f"Failed to install packages for {bootloader_name}", f"The install failed with error: {cpe.stderr}"

    # Run dracut unless we are using systemd-boot since kernel-install handles that
    if bootloader_name.casefold().strip() != "systemd-boot":
        run_dracut()

    return None
