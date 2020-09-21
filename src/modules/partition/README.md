# Architecture

<!-- SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
     SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
     SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
     SPDX-License-Identifier: GPL-3.0-or-later
-->

## Overview

The heart of the module is the PartitionCoreModule class. It holds Qt models for
the various elements and can create Calamares jobs representing the changes to
be performed at install time.

PartitionPage is the main UI class. It represents the module main page, the one
with the device combo box, partition list and action buttons. It reacts to the
buttons by creating various dialogs (the (...)Dialog classes) and tell
PartitionCoreModule what to do.


## Use of KPMcore

This module depends on KPMcore, the same library used by [KDE Partition Manager][kpm].

[kpm]: http://sourceforge.net/projects/partitionman/


## Partition and PartitionInfo

Calamares needs to store some information about partitions which is not
available in Partition Manager's Partition class.

This includes the install mount point and a boolean to mark whether an existing
partition should be formatted.

Reusing the existing `Partition::mountPoint` property was not an option because
it stores the directory where a partition is currently mounted, which is a
different concept from the directory where the user wants the partition to be
mounted on the installed system. We can't hijack this to store our install mount
point because whether the partition is currently mounted is an important
information which should be taken into account later to prevent any modification
on an installed partition.

The way this extra information is stored is a bit unusual: the functions in the
PartitionInfo namespace takes advantage of Qt dynamic properties methods to add
Calamares-specific properties to the Partition instances: setting the install
mount point is done with `PartitionInfo::setMountPoint(partition, "/")`,
retrieving it is done with `mountPoint = PartitionInfo::mountPoint(partition)`.

The rational behind this unusual design is simplicity: the alternative would
have been to keep a separate PartitionInfo object and a map linking each
Partition to its PartitionInfo instance. Such a design makes things more
complicated. It complicates memory management: if a Partition goes away, its
matching PartitionInfo must be removed. It also leads to uglier APIs: code which
needs access to extra partition information must be passed both Partition and
PartitionInfo instances or know a way to get a PartitionInfo from a Partition.

The other alternative would have been to add Calamares-specific information to
the real Partition object. This would have worked and would have made for a less
surprising API, but it would mean more Calamares-specific patches on KPMcore.


# Tests

The module comes with unit tests for the partition jobs. Those tests need to
run on storage device which does not contain any data you care about.

To build them:

    cd $top_build_dir
    make buildtests

To run them you need to define the `CALAMARES_TEST_DISK` environment variable.
It should contain the device path to the test disk. For example, assuming you
plugged a test USB stick identified as `/dev/sdb`, you would run the tests like
this:

    sudo CALAMARES_TEST_DISK=/dev/sdb $top_build_dir/partitionjobtests


# TODO

- Support resizing extended partitions. ResizePartitionJob should already
  support this but the UI prevents editing of extended partitions for now.

- Use os-prober to find out the installed OS. This information could then be
  used in PartitionModel and in the partition views.

- PartitionBarsView
    - Show used space
    - Highlight selected partition
    - Make the partitions clickable
    - Match appearance with PartResizerWidget appearance

- Expose PartitionInfo::format in PartitionModel and add a column for it in the
  tree view
