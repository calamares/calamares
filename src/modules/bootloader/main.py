#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
#   SPDX-FileCopyrightText: 2014 Anke Boersma <demm@kaosx.us>
#   SPDX-FileCopyrightText: 2014 Daniel Hillenbrand <codeworkx@bbqlinux.org>
#   SPDX-FileCopyrightText: 2014 Benjamin Vaudour <benjamin.vaudour@yahoo.fr>
#   SPDX-FileCopyrightText: 2014-2019 Kevin Kofler <kevin.kofler@chello.at>
#   SPDX-FileCopyrightText: 2015-2018 Philip Mueller <philm@manjaro.org>
#   SPDX-FileCopyrightText: 2016-2017 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Alf Gaida <agaida@siduction.org>
#   SPDX-FileCopyrightText: 2017-2019 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2017 Gabriel Craciunescu <crazy@frugalware.org>
#   SPDX-FileCopyrightText: 2017 Ben Green <Bezzy1999@hotmail.com>
#   SPDX-FileCopyrightText: 2021 Neal Gompa <ngompa13@gmail.com>
#   SPDX-License-Identifier: GPL-3.0-or-later
#
#   Calamares is Free Software: see the License-Identifier above.
#

import os
import shutil
import subprocess

import libcalamares

from libcalamares.utils import check_target_env_call


import gettext
_ = gettext.translation("calamares-python",
                        localedir=libcalamares.utils.gettext_path(),
                        languages=libcalamares.utils.gettext_languages(),
                        fallback=True).gettext

# This is the sanitizer used all over to tidy up filenames
# to make identifiers (or to clean up names to make filenames).
file_name_sanitizer = str.maketrans(" /()", "_-__")

def pretty_name():
    return _("Install bootloader.")


def get_uuid():
    """
    Checks and passes 'uuid' to other routine.

    :return:
    """
    partitions = libcalamares.globalstorage.value("partitions")

    for partition in partitions:
        if partition["mountPoint"] == "/":
            libcalamares.utils.debug("Root partition uuid: \"{!s}\"".format(partition["uuid"]))
            return partition["uuid"]

    return ""


def get_bootloader_entry_name():
    """
    Passes 'bootloader_entry_name' to other routine based
    on configuration file.

    :return:
    """
    if "bootloaderEntryName" in libcalamares.job.configuration:
        return libcalamares.job.configuration["bootloaderEntryName"]
    else:
        branding = libcalamares.globalstorage.value("branding")
        return branding["bootloaderEntryName"]


def get_kernel_line(kernel_type):
    """
    Passes 'kernel_line' to other routine based on configuration file.

    :param kernel_type:
    :return:
    """
    if kernel_type == "fallback":
        if "fallbackKernelLine" in libcalamares.job.configuration:
            return libcalamares.job.configuration["fallbackKernelLine"]
        else:
            return " (fallback)"
    else:
        if "kernelLine" in libcalamares.job.configuration:
            return libcalamares.job.configuration["kernelLine"]
        else:
            return ""


def get_zfs_root():
    """
    Looks in global storage to find the zfs root

    :return: A string containing the path to the zfs root or None if it is not found
    """

    zfs = libcalamares.globalstorage.value("zfsDatasets")

    if not zfs:
        libcalamares.utils.warning("Failed to locate zfs dataset list")
        return None

    # Find the root dataset
    for dataset in zfs:
        try:
            if dataset["mountpoint"] == "/":
                return dataset["zpool"] + "/" + dataset["dsName"]
        except KeyError:
            # This should be impossible
            libcalamares.utils.warning("Internal error handling zfs dataset")
            raise

    return None


def is_btrfs_root(partition):
    """ Returns True if the partition object refers to a btrfs root filesystem

    :param partition: A partition map from global storage
    :return: True if btrfs and root, False otherwise
    """
    return partition["mountPoint"] == "/" and partition["fs"] == "btrfs"


def is_zfs_root(partition):
    """ Returns True if the partition object refers to a zfs root filesystem

    :param partition: A partition map from global storage
    :return: True if zfs and root, False otherwise
    """
    return partition["mountPoint"] == "/" and partition["fs"] == "zfs"


def create_systemd_boot_conf(installation_root_path, efi_dir, uuid, entry, kernel, kernel_type, kernel_version):
    """
    Creates systemd-boot configuration files based on given parameters.

    :param installation_root_path: A string containing the absolute path to the root of the installation
    :param efi_dir: A string containing the path to the efi dir relative to the root of the installation
    :param uuid: A string containing the UUID of the root volume
    :param entry: A string containing the name of the entry as it will be displayed on boot
    :param kernel: A string containing the path to the kernel relative to the root of the installation
    :param kernel_type: A string which should be set if there is a special version of the entry, for example "fallback"
    :param kernel_version: The kernel version string
    """
    kernel_params = ["quiet"]

    partitions = libcalamares.globalstorage.value("partitions")
    swap_uuid = ""
    swap_outer_mappername = None

    cryptdevice_params = []

    # Take over swap settings:
    #  - unencrypted swap partition sets swap_uuid
    #  - encrypted root sets cryptdevice_params
    for partition in partitions:
        if partition["fs"] == "linuxswap" and not partition.get("claimed", None):
            continue
        has_luks = "luksMapperName" in partition
        if partition["fs"] == "linuxswap" and not has_luks:
            swap_uuid = partition["uuid"]

        if (partition["fs"] == "linuxswap" and has_luks):
            swap_outer_mappername = partition["luksMapperName"]

        if partition["mountPoint"] == "/" and has_luks:
            cryptdevice_params = ["cryptdevice=UUID="
                                  + partition["luksUuid"]
                                  + ":"
                                  + partition["luksMapperName"],
                                  "root=/dev/mapper/"
                                  + partition["luksMapperName"]]

    for partition in partitions:
        # systemd-boot with a BTRFS root filesystem needs to be told abouut the root subvolume.
        # If a btrfs root subvolume wasn't set, it means the root is directly on the partition
        # and this option isn't needed
        if is_btrfs_root(partition):
            btrfs_root_subvolume = libcalamares.globalstorage.value("btrfsRootSubvolume")
            if btrfs_root_subvolume:
                kernel_params.append("rootflags=subvol=" + btrfs_root_subvolume)

        # zfs needs to be told the location of the root dataset
        if is_zfs_root(partition):
            zfs_root_path = get_zfs_root()
            if zfs_root_path is not None:
                kernel_params.append("zfs=" + zfs_root_path)
            else:
                # Something is really broken if we get to this point
                libcalamares.utils.warning("Internal error handling zfs dataset")
                raise Exception("Internal zfs data missing, please contact your distribution")

    if cryptdevice_params:
        kernel_params.extend(cryptdevice_params)
    else:
        kernel_params.append("root=UUID={!s}".format(uuid))

    if swap_uuid:
        kernel_params.append("resume=UUID={!s}".format(swap_uuid))

    if swap_outer_mappername:
        kernel_params.append("resume=/dev/mapper/{!s}".format(
            swap_outer_mappername))

    libcalamares.utils.debug("Configure: \"{!s}\"".format(f"{entry} {kernel_version}"))

    if kernel_type == "fallback":
        version_string = kernel_version + "-fallback"
        initrd = "initrd-fallback"
    else:
        version_string = kernel_version
        initrd = "initrd"

    # get the machine-id
    with open(os.path.join(installation_root_path, "etc", "machine-id"), 'r') as machineid_file:
        machine_id = machineid_file.read().rstrip('\n')

    # Copy kernel to a subdirectory of /efi partition
    machine_dir = os.path.join(installation_root_path + efi_dir, machine_id)
    os.makedirs(machine_dir, exist_ok=True)

    target_efi_files_dir = os.path.join(machine_dir, kernel_version)
    os.makedirs(target_efi_files_dir, exist_ok=True)

    kernel_path = os.path.join(installation_root_path, kernel)
    kernel_name = os.path.basename(kernel_path)
    shutil.copyfile(kernel_path, os.path.join(target_efi_files_dir, "linux"))

    # write the entry
    lines = [
        '## Generated by Calamares\n',
        '\n',
        "title      {!s}\n".format(entry),
        "version    {!s}\n".format(version_string),
        "machine-id {!s}\n".format(machine_id),
        "linux      {!s}\n".format(os.path.join("/", machine_id, kernel_version, "linux")),
    ]

    try:
        additional_initrd_files = libcalamares.job.configuration["additionalInitrdFiles"]
        for initrd_file in additional_initrd_files:
            libcalamares.utils.debug("Attempting to handle initrd image " + initrd_file)
            if os.path.isfile(os.path.join(installation_root_path, initrd_file.lstrip('/'))):
                libcalamares.utils.debug("Found image " + initrd_file)
                shutil.copyfile(os.path.join(installation_root_path, initrd_file.lstrip('/')), os.path.join(target_efi_files_dir, os.path.basename(initrd_file)))
                lines.append("initrd     {!s}\n".format(os.path.join("/", machine_id, kernel_version, os.path.basename(initrd_file))))
    except KeyError: # If the configuration option isn't set, we can just move on
        libcalamares.utils.debug("Failed to find key additionalInitrdFiles")
        pass

    lines.append("initrd     {!s}\n".format(os.path.join("/", machine_id, kernel_version, initrd)))
    lines.append("options    {!s} rw\n".format(" ".join(kernel_params)))

    conf_path = os.path.join(installation_root_path + efi_dir,
                             "loader",
                             "entries",
                             machine_id + "-" + version_string + ".conf")

    with open(conf_path, 'w') as conf_file:
        for line in lines:
            conf_file.write(line)


def create_loader(loader_path, entry):
    """
    Writes configuration for loader.

    :param loader_path:
    :param entry:
    """
    timeout = libcalamares.job.configuration["timeout"]
    lines = [
        "timeout {!s}\n".format(timeout),
        "default {!s}\n".format(entry),
    ]

    with open(loader_path, 'w') as loader_file:
        for line in lines:
            loader_file.write(line)


class suffix_iterator(object):
    """
    Wrapper for one of the "generator" classes below to behave like
    a proper Python iterator. The iterator is initialized with a
    maximum number of attempts to generate a new suffix.
    """
    def __init__(self, attempts, generator):
        self.generator = generator
        self.attempts = attempts
        self.counter = 0

    def __iter__(self):
        return self

    def __next__(self):
        self.counter += 1
        if self.counter <= self.attempts:
            return self.generator.next()
        raise StopIteration


class serialEfi(object):
    """
    EFI Id generator that appends a serial number to the given name.
    """
    def __init__(self, name):
        self.name = name
        # So the first call to next() will bump it to 0
        self.counter = -1

    def next(self):
        self.counter += 1
        if self.counter > 0:
            return "{!s}{!s}".format(self.name, self.counter)
        else:
            return self.name


def render_in_base(value, base_values, length=-1):
    """
    Renders @p value in base-N, where N is the number of
    items in @p base_values. When rendering, use the items
    of @p base_values (e.g. use "0123456789" to get regular decimal
    rendering, or "ABCDEFGHIJ" for letters-as-numbers 'encoding').

    If length is positive, pads out to at least that long with
    leading "zeroes", whatever base_values[0] is.
    """
    if value < 0:
        raise ValueError("Cannot render negative values")
    if len(base_values) < 2:
        raise ValueError("Insufficient items for base-N rendering")
    if length < 1:
        length = 1
    digits = []
    base = len(base_values)
    while value > 0:
        place = value % base
        value = value // base
        digits.append(base_values[place])
    while len(digits) < length:
        digits.append(base_values[0])
    return "".join(reversed(digits))


class randomEfi(object):
    """
    EFI Id generator that appends a random 4-digit hex number to the given name.
    """
    def __init__(self, name):
        self.name = name
        # So the first call to next() will bump it to 0
        self.counter = -1

    def next(self):
        self.counter += 1
        if self.counter > 0:
            import random
            v = random.randint(0, 65535)  # 16 bits
            return "{!s}{!s}".format(self.name, render_in_base(v, "0123456789ABCDEF", 4))
        else:
            return self.name


class phraseEfi(object):
    """
    EFI Id generator that appends a random phrase to the given name.
    """
    words = ("Sun", "Moon", "Mars", "Soyuz", "Falcon", "Kuaizhou", "Gaganyaan")

    def __init__(self, name):
        self.name = name
        # So the first call to next() will bump it to 0
        self.counter = -1

    def next(self):
        self.counter += 1
        if self.counter > 0:
            import random
            desired_length = 1 + self.counter // 5
            v = random.randint(0, len(self.words) ** desired_length)
            return "{!s}{!s}".format(self.name, render_in_base(v, self.words))
        else:
            return self.name


def get_efi_suffix_generator(name):
    """
    Handle EFI bootloader Ids with @@<something>@@ for suffix-processing.
    """
    if "@@" not in name:
        raise ValueError("Misplaced call to get_efi_suffix_generator, no @@")
    parts = name.split("@@")
    if len(parts) != 3:
        raise ValueError("EFI Id {!r} is malformed".format(name))
    if parts[2]:
        # Supposed to be empty because the string ends with "@@"
        raise ValueError("EFI Id {!r} is malformed".format(name))
    if parts[1] not in ("SERIAL", "RANDOM", "PHRASE"):
        raise ValueError("EFI suffix {!r} is unknown".format(parts[1]))

    generator = None
    if parts[1] == "SERIAL":
        generator = serialEfi(parts[0])
    elif parts[1] == "RANDOM":
        generator = randomEfi(parts[0])
    elif parts[1] == "PHRASE":
        generator = phraseEfi(parts[0])
    if generator is None:
        raise ValueError("EFI suffix {!r} is unsupported".format(parts[1]))

    return generator


def change_efi_suffix(efi_directory, bootloader_id):
    """
    Returns a label based on @p bootloader_id that is usable within
    @p efi_directory. If there is a @@<something>@@ suffix marker
    in the given id, tries to generate a unique label.
    """
    if bootloader_id.endswith("@@"):
        # Do 10 attempts with any suffix generator
        g = suffix_iterator(10, get_efi_suffix_generator(bootloader_id))
    else:
        # Just one attempt
        g = [bootloader_id]

    for candidate_name in g:
        if not os.path.exists(os.path.join(efi_directory, candidate_name)):
            return candidate_name
    return bootloader_id


def efi_label(efi_directory):
    """
    Returns a sanitized label, possibly unique, that can be
    used within @p efi_directory.
    """
    if "efiBootloaderId" in libcalamares.job.configuration:
        efi_bootloader_id = change_efi_suffix( efi_directory, libcalamares.job.configuration["efiBootloaderId"] )
    else:
        branding = libcalamares.globalstorage.value("branding")
        efi_bootloader_id = branding["bootloaderEntryName"]

    return efi_bootloader_id.translate(file_name_sanitizer)


def efi_word_size():
    # get bitness of the underlying UEFI
    try:
        sysfile = open("/sys/firmware/efi/fw_platform_size", "r")
        efi_bitness = sysfile.read(2)
    except Exception:
        # if the kernel is older than 4.0, the UEFI bitness likely isn't
        # exposed to the userspace so we assume a 64 bit UEFI here
        efi_bitness = "64"
    return efi_bitness


def efi_boot_next():
    """
    Tell EFI to definitely boot into the just-installed
    system next time.
    """
    boot_mgr = libcalamares.job.configuration["efiBootMgr"]
    boot_entry = None
    efi_bootvars = subprocess.check_output([boot_mgr], text=True)
    for line in efi_bootvars.split('\n'):
        if not line:
            continue
        words = line.split()
        if len(words) >= 2 and words[0] == "BootOrder:":
            boot_entry = words[1].split(',')[0]
            break
    if boot_entry:
        subprocess.call([boot_mgr, "-n", boot_entry])

def get_kernels(installation_root_path):
    """
    Gets a list of kernels and associated values for each kernel.  This will work as is for many distros.
    If not, it should be safe to modify it to better support your distro

    :param installation_root_path: A string with the absolute path to the root of the installation

    Returns a list of 3-tuples

    Each 3-tuple contains the kernel, kernel_type and kernel_version
    """
    kernel_search_path = libcalamares.job.configuration["kernelSearchPath"]
    source_kernel_name = libcalamares.job.configuration["kernelName"]
    kernel_list = []

    # find all the installed kernels and generate default and fallback entries for each
    for root, dirs, files in os.walk(os.path.join(installation_root_path, kernel_search_path.lstrip('/'))):
        for file in files:
            if file == source_kernel_name:
                rel_root = os.path.relpath(root, installation_root_path)
                kernel_list.append((os.path.join(rel_root, file),"default",os.path.basename(root)))
                kernel_list.append((os.path.join(rel_root, file),"fallback",os.path.basename(root)))

    return kernel_list

def install_systemd_boot(efi_directory):
    """
    Installs systemd-boot as bootloader for EFI setups.

    :param efi_directory:
    """
    libcalamares.utils.debug("Bootloader: systemd-boot")
    installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
    install_efi_directory = installation_root_path + efi_directory
    uuid = get_uuid()
    distribution = get_bootloader_entry_name()
    distribution_translated = distribution.translate(file_name_sanitizer)
    loader_path = os.path.join(install_efi_directory,
                               "loader",
                               "loader.conf")
    subprocess.call(["bootctl",
                     "--path={!s}".format(install_efi_directory),
                     "install"])

    for (kernel, kernel_type, kernel_version) in get_kernels(installation_root_path):
        create_systemd_boot_conf(installation_root_path,
                                efi_directory,
                                uuid,
                                distribution,
                                kernel,
                                kernel_type,
                                kernel_version)

    create_loader(loader_path, distribution_translated)

def get_grub_efi_parameters():
    """
    Returns a 3-tuple of suitable parameters for GRUB EFI installation,
    depending on the host machine architecture. The return is
        - target name
        - grub.efi name
        - boot.efi name
    all three are strings. May return None if there is no suitable
    set for the current machine. May return unsuitable values if the
    host architecture is unknown (e.g. defaults to x86_64).
    """
    import platform
    efi_bitness = efi_word_size()
    cpu_type = platform.machine()

    if efi_bitness == "32":
        # Assume all 32-bitters are legacy x86
        return ("i386-efi", "grubia32.efi", "bootia32.efi")
    elif efi_bitness == "64" and cpu_type == "aarch64":
        return ("arm64-efi", "grubaa64.efi", "bootaa64.efi")
    elif efi_bitness == "64" and cpu_type == "loongarch64":
        return ("loongarch64-efi", "grubloongarch64.efi", "bootloongarch64.efi")
    elif efi_bitness == "64":
        # If it's not ARM, must by AMD64
        return ("x86_64-efi", "grubx64.efi", "bootx64.efi")
    libcalamares.utils.warning("Could not find GRUB parameters for bits {b} and cpu {c}".format(b=repr(efi_bitness), c=repr(cpu_type)))
    return None


def run_grub_mkconfig(partitions, output_file):
    """
    Runs grub-mkconfig in the target environment

    :param partitions: The partitions list from global storage
    :param output_file: A string containing the path to the generating grub config file
    :return:
    """

    # zfs needs an environment variable set for grub-mkconfig
    if any([is_zfs_root(partition) for partition in partitions]):
        check_target_env_call(["sh", "-c", "ZPOOL_VDEV_NAME_PATH=1 " +
                               libcalamares.job.configuration["grubMkconfig"] + " -o " + output_file])
    else:
        # The input file /etc/default/grub should already be filled out by the
        # grubcfg job module.
        check_target_env_call([libcalamares.job.configuration["grubMkconfig"], "-o", output_file])


def run_grub_install(fw_type, partitions, efi_directory):
    """
    Runs grub-install in the target environment

    :param fw_type: A string which is "efi" for UEFI installs.  Any other value results in a BIOS install
    :param partitions: The partitions list from global storage
    :param efi_directory: The path of the efi directory relative to the root of the install
    :return:
    """

    is_zfs = any([is_zfs_root(partition) for partition in partitions])

    # zfs needs an environment variable set for grub
    if is_zfs:
        check_target_env_call(["sh", "-c", "echo ZPOOL_VDEV_NAME_PATH=1 >> /etc/environment"])

    if fw_type == "efi":
        assert efi_directory is not None
        efi_bootloader_id = efi_label(efi_directory)
        efi_target, efi_grub_file, efi_boot_file = get_grub_efi_parameters()

        if is_zfs:
            check_target_env_call(["sh", "-c", "ZPOOL_VDEV_NAME_PATH=1 " + libcalamares.job.configuration["grubInstall"]
                                   + " --target=" + efi_target + " --efi-directory=" + efi_directory
                                   + " --bootloader-id=" + efi_bootloader_id + " --force"])
        else:
            check_target_env_call([libcalamares.job.configuration["grubInstall"],
                                   "--target=" + efi_target,
                                   "--efi-directory=" + efi_directory,
                                   "--bootloader-id=" + efi_bootloader_id,
                                   "--force"])
    else:
        assert efi_directory is None
        if libcalamares.globalstorage.value("bootLoader") is None:
            return

        boot_loader = libcalamares.globalstorage.value("bootLoader")
        if boot_loader["installPath"] is None:
            return

        if is_zfs:
            check_target_env_call(["sh", "-c", "ZPOOL_VDEV_NAME_PATH=1 "
                                   + libcalamares.job.configuration["grubInstall"]
                                   + " --target=i386-pc --recheck --force "
                                   + boot_loader["installPath"]])
        else:
            check_target_env_call([libcalamares.job.configuration["grubInstall"],
                                   "--target=i386-pc",
                                   "--recheck",
                                   "--force",
                                   boot_loader["installPath"]])


def install_grub(efi_directory, fw_type):
    """
    Installs grub as bootloader, either in pc or efi mode.

    :param efi_directory:
    :param fw_type:
    """
    # get the partition from global storage
    partitions = libcalamares.globalstorage.value("partitions")
    if not partitions:
        libcalamares.utils.warning(_("Failed to install grub, no partitions defined in global storage"))
        return

    if fw_type == "efi":
        libcalamares.utils.debug("Bootloader: grub (efi)")
        installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
        install_efi_directory = installation_root_path + efi_directory

        if not os.path.isdir(install_efi_directory):
            os.makedirs(install_efi_directory)

        efi_bootloader_id = efi_label(efi_directory)

        efi_target, efi_grub_file, efi_boot_file = get_grub_efi_parameters()

        run_grub_install(fw_type, partitions, efi_directory)

        # VFAT is weird, see issue CAL-385
        install_efi_directory_firmware = (vfat_correct_case(
                                              install_efi_directory,
                                              "EFI"))
        if not os.path.exists(install_efi_directory_firmware):
            os.makedirs(install_efi_directory_firmware)

        # there might be several values for the boot directory
        # most usual they are boot, Boot, BOOT

        install_efi_boot_directory = (vfat_correct_case(
                                          install_efi_directory_firmware,
                                          "boot"))
        if not os.path.exists(install_efi_boot_directory):
            os.makedirs(install_efi_boot_directory)

        # Workaround for some UEFI firmwares
        fallback = "installEFIFallback"
        libcalamares.utils.debug("UEFI Fallback: " + str(libcalamares.job.configuration.get(fallback, "<unset>")))
        if libcalamares.job.configuration.get(fallback, True):
            libcalamares.utils.debug("  .. installing '{!s}' fallback firmware".format(efi_boot_file))
            efi_file_source = os.path.join(install_efi_directory_firmware,
                                           efi_bootloader_id,
                                           efi_grub_file)
            efi_file_target = os.path.join(install_efi_boot_directory, efi_boot_file)

            shutil.copy2(efi_file_source, efi_file_target)
    else:
        libcalamares.utils.debug("Bootloader: grub (bios)")
        run_grub_install(fw_type, partitions, None)

    run_grub_mkconfig(partitions, libcalamares.job.configuration["grubCfg"])


def install_secureboot(efi_directory):
    """
    Installs the secureboot shim in the system by calling efibootmgr.
    """
    efi_bootloader_id = efi_label(efi_directory)

    installation_root_path = libcalamares.globalstorage.value("rootMountPoint")
    install_efi_directory = installation_root_path + efi_directory

    if efi_word_size() == "64":
        install_efi_bin = "shimx64.efi"
    elif efi_word_size() == "32":
        install_efi_bin = "shimia32.efi"

    # Copied, roughly, from openSUSE's install script,
    # and pythonified. *disk* is something like /dev/sda,
    # while *drive* may return "(disk/dev/sda,gpt1)" ..
    # we're interested in the numbers in the second part
    # of that tuple.
    efi_drive = subprocess.check_output([
        libcalamares.job.configuration["grubProbe"],
        "-t", "drive", "--device-map=", install_efi_directory]).decode("ascii")
    efi_disk = subprocess.check_output([
        libcalamares.job.configuration["grubProbe"],
        "-t", "disk", "--device-map=", install_efi_directory]).decode("ascii")

    efi_drive_partition = efi_drive.replace("(","").replace(")","").split(",")[1]
    # Get the first run of digits from the partition
    efi_partition_number = None
    c = 0
    start = None
    while c < len(efi_drive_partition):
        if efi_drive_partition[c].isdigit() and start is None:
            start = c
        if not efi_drive_partition[c].isdigit() and start is not None:
            efi_partition_number = efi_drive_partition[start:c]
            break
        c += 1
    if efi_partition_number is None:
        raise ValueError("No partition number found for %s" % install_efi_directory)

    subprocess.call([
        libcalamares.job.configuration["efiBootMgr"],
        "-c",
        "-w",
        "-L", efi_bootloader_id,
        "-d", efi_disk,
        "-p", efi_partition_number,
        "-l", install_efi_directory + "/" + install_efi_bin])

    efi_boot_next()

    # The input file /etc/default/grub should already be filled out by the
    # grubcfg job module.
    check_target_env_call([libcalamares.job.configuration["grubMkconfig"],
                           "-o", os.path.join(efi_directory, "EFI",
                                              efi_bootloader_id, "grub.cfg")])


def vfat_correct_case(parent, name):
    for candidate in os.listdir(parent):
        if name.lower() == candidate.lower():
            return os.path.join(parent, candidate)
    return os.path.join(parent, name)


def prepare_bootloader(fw_type):
    """
    Prepares bootloader.
    Based on value 'efi_boot_loader', it either calls systemd-boot
    or grub to be installed.

    :param fw_type:
    :return:
    """
    efi_boot_loader = libcalamares.job.configuration["efiBootLoader"]
    efi_directory = libcalamares.globalstorage.value("efiSystemPartition")

    if efi_boot_loader == "systemd-boot" and fw_type == "efi":
        install_systemd_boot(efi_directory)
    elif efi_boot_loader == "sb-shim" and fw_type == "efi":
        install_secureboot(efi_directory)
    elif efi_boot_loader == "grub" or fw_type != "efi":
        install_grub(efi_directory, fw_type)
    else:
        libcalamares.utils.debug( "WARNING: the combination of "
            "boot-loader '{!s}' and firmware '{!s}' "
            "is not supported.".format(efi_boot_loader, fw_type) )


def run():
    """
    Starts procedure and passes 'fw_type' to other routine.

    :return:
    """

    fw_type = libcalamares.globalstorage.value("firmwareType")

    if libcalamares.globalstorage.value("bootLoader") is None:
        # Don't want a bootloader, but do log that this has an effect:
        if fw_type != "efi":
            libcalamares.utils.warning( "Non-EFI system, and no bootloader is set." )
        else:
            libcalamares.utils.warning( "EFI system, and no bootloader is set." )
        return None

    partitions = libcalamares.globalstorage.value("partitions")
    if fw_type == "efi":
        efi_system_partition = libcalamares.globalstorage.value("efiSystemPartition")
        esp_found = [ p for p in partitions if p["mountPoint"] == efi_system_partition ]
        if not esp_found:
            libcalamares.utils.warning( "EFI system, but nothing mounted on {!s}".format(efi_system_partition) )
            return None

    try:
        prepare_bootloader(fw_type)
    except subprocess.CalledProcessError as e:
        libcalamares.utils.warning(str(e))
        libcalamares.utils.debug("stdout:" + str(e.stdout))
        libcalamares.utils.debug("stderr:" + str(e.stderr))
        return (_("Bootloader installation error"),
                _("The bootloader could not be installed. The installation command <pre>{!s}</pre> returned error code {!s}.")
                .format(e.cmd, e.returncode))

    return None
