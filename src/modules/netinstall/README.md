# Netinstall module

The netinstall module allows distribution maintainers to ship minimal ISOs with only a basic set of preinstall packages. At installation time, the user is presented with the choice to install groups of packages from a predefined list.

Calamares will then invoke the correct backend to install the packages.

## How are packages configured?
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

Two more keys are supported, *hidden* (if true, do not show the group on the page) and *selected* (if true, display the group as selected). Both default to false if not present.
If both keys are set to true for the same group, you are basically creating a "default" group of packages which will always be installed in the user's system.
