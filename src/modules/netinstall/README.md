# Netinstall module

The netinstall module allows distribution maintainers to ship minimal ISOs with only a basic set of preinstall packages.
At installation time, the user is presented with the choice to install groups of packages from a predefined list.

Calamares will then invoke the correct backend to install the packages.

## Configuration of the packages
Every distribution can choose which groups to display and which packages should be in the groups.

The *netinstall.conf* file should have this format:

    ----
    groupsUrl: <URL to YAML file>

The URL must point to a YAML file. Here is a short example of how the YAML file should look.

      - name: "Group name"
        description: "Description of the group"
        packages:
          - lsb-release
          - avahi
          - grub
      - name: "Second group name"
      ...


The file is composed of a list of entry, each describing one group. The keys *name*, *description* and *packages* are required.

More keys are supported:

      - hidden: if true, do not show the group on the page. Defaults to false.
      - selected: if true, display the group as selected. Defaults to false.
      - critical: if true, make the installation process fail if installing
        any of the packages in the group fails. Otherwise, just log a warning.
        Defaults to false.
      - subgroups: if present this follows the same structure as the top level
        of the YAML file, allowing there to be sub-groups of packages to an
        arbitary depth
      - pre-install: an optional command to run within the new system before
        the group's packages are installed. It will run before each package in
        the group is installed.
      - post-install: an optional command to run within the new system after
        the group's packages are installed. It will run after each package in
        the group is installed.

If you set both *hidden* and *selected* for a group, you are basically creating a "default" group of packages
which will always be installed in the user's system.

## Configuration of the module
Here is the set of instructions to have the module work in your Calamares. As of July 2016, this has been successfully 
tested using the live installation of Chakra Fermi.

First, if the module is used, we need to require a working Internet connection, otherwise the module will be
unable to fetch the package groups and to perform the installation. Requirements for the Calamares instance
are configured in the **welcome.conf** file (configuration for the **welcome** module). Make sure *internet*
is listed below *required*.

In the *settings.conf* file, decide where the **netinstall** page should be displayed. I put it just after the
**welcome** page, but any position between that and just before **partition** should make no difference.

If not present, add the **packages** job in the **exec** list. This is the job that calls the package manager
to install packages. Make sure it is configured to use the correct package manager for your distribution; this
is configured in src/modules/packages/packages.conf.

The exec list should be:

  - unpackfs
  - networkcfg
  - packages

**unpackfs** creates the chroot where the installation is performed, and unpacks the root image with the filesystem
structure; **networkcfg** set ups a working network in the chroot; and finally **packages** can install packages
in the chroot.

## Common issues
If launching the package manager command returns you negative exit statuses and nothing is actually invoked, this
is likely an error in the setup of the chroot; check that the parameter **rootMountPoint** is set to the correct
value in the Calamares configuration.

If the command is run, but exits with error, check that the network is working in the chroot. Make sure /etc/resolv.conf
exists and that it's not empty.

