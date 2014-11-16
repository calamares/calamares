# GlobalStorage keys

The GlobalStorage structure contains information which is shared among jobs.
Jobs are free to define their own keys, but some keys have been standardized.
Here they are:

## bootLoader

A dictionary with the following keys:

- `installPath`: device where the boot loader should be installed ("/dev/sda", "/dev/sdb1"...)

## branding

A dictionary with the following keys (loaded from branding.desc):

- `productName`: distribution unversioned product name (long version)
- `shortProductName`: distribution unversioned product name (short version)
- `version`: distribution version number (long version)
- `shortVersion`: distribution version number (short version)
- `versionedName`: distribution product name and version (long version)
- `shortVersionedName`: distribution product name and version (short version)

## partitions

A list of dictionaries, one per partition. The dictionary contains the following keys:

- `device`: path to the partition device
- `fs`: the name of the file system
- `mountPoint`: where the device should be mounted
- `uuid`: the UUID of the partition device

## rootMountPoint

A string which contains the path where the root file system has been mounted.
This key is set by the `mount` job.
