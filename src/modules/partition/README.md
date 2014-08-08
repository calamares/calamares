# Architecture

## PartitionCoreModule

## Partition and PartitionInfo

# Tests

The module comes with unit tests for the partition jobs. Those tests need to
run on a disk, USB stick or whatever storage device which does not contain any
data you care about.

To build them:

    cd $top_build_dir/src/modules/partitions/tests
    make buildtests

To run them you need to define the `CALAMARES_TEST_DISK` environment variable.
It should contain the device path to the test disk. For example, assuming you
plugged a test USB stick identified as `/dev/sdb`, you would run the tests like
this:

    sudo CALAMARES_TEST_DISK=/dev/sdb $top_build_dir/partitiontests

# TODO

- PartitionPreview
    - Show used space
    - Highlight selected partition
    - Make the partitions clickable

- Expose PartitionInfo::format in PartitionModel and add a column for it in the tree view

- Support resizing extended partitions. ResizePartitionJob should already
  support this but the UI prevents editing of extended partitions for now.
