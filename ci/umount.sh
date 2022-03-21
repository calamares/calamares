#! /bin/sh

### LICENSE
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2022 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
#   This file is Free Software: you can redistribute it and/or modify
#   it under the terms of the 2-clause BSD License.
#
### END LICENSE

#
# This is an "unmount" script that tries to unmount whatever
# filesystems Calamares might have left mounted (e.g. because of
# a crash, or ^C'ing the installer, or ..).
#

# Swap may have become enabled on the disks just used; assume
# we're in a live session where we don't want any.
sudo swapoff -a
# In Arch-based systems, there may be a gpg-agent started by
# pacman during installation, which lives in the chroot. Kill
# them all; again assume we're in a live session where it doesn't matter.
sudo pkill gpg-agent
# Unmount the filesystems in *reverse* order, since we need to ditch
# e.g. /run/udev before /run before the root filesystem.
sudo umount $( LC_ALL=C mount | awk '/calamares-root/{print $3}' | LC_ALL=C sort -r )
