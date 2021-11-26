## zfs Module Notes

<!-- SPDX-FileCopyrightText: 2021 Evan James <dalto@fastmail.com>
     SPDX-License-Identifier: GPL-3.0-or-later
-->

There are a few considerations to be aware of when enabling the zfs module
* You must provide zfs kernel modules or kernel support on the ISO for the zfs module to function
    * The zfs kernel module must be loaded prior to the partition module running
    * One way to achieve this is by running `modprobe zfs`
* Support for zfs in the partition module is conditional on the zfs module being enabled
* The config for the default pools and datasets is configured and described in modules/zfs.conf
* If you use grub with zfs, you must have `ZPOOL_VDEV_NAME_PATH=1` in your environment when running grub-install or grub-mkconfig.
   * Calamares will ensure this happens during the bootloader module.
   * It will also add it to `/etc/environment` so it will be available in the installation
   * If you have an scripts or other processes that trigger grub-mkconfig during the install process, be sure to add that to the environment
* In most cases, you will need to enable services for zfs support appropriate to your distro.  For example, when testing on Arch the following services were enabled:
   * zfs.target
   * zfs-import-cache
   * zfs-mount
   * zfs-import.target
