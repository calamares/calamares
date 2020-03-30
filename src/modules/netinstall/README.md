# Netinstall module

The netinstall module allows distribution maintainers to ship minimal ISOs with
only a basic set of preinstalled packages. At installation time, the user is
presented with the choice to install groups of packages from a predefined list.

Calamares will then use the *packages* module to install the packages.


## Module Configuration

The `netinstall.conf` file is self-describing, and at the very
least should contain a *groupsUrl* key:

```
    ----
    groupsUrl: <URL to YAML file>
```

The URL must point to a YAML file, the *groups* file. See below for
the format of that groups file. The URL may be a local file (e.g.
scheme `file:///`) or a regular HTTP(s) URL. The URL has one special
case: the literal string `local` is used to indicate that the groups
data is contained in the `netinstall.conf` file itself.


## Groups Configuration

Here is a short example of how the YAML file should look.

```
    - name: "Group name"
      description: "Description of the group"
      packages:
        - lsb-release
        - avahi
        - grub
    - name: "Second group name"
      ...
```


The file is composed of a list of entries, each describing one group. The
keys *name*, *description* and *packages* are required for each group.

More keys (per group) are supported:

 - *hidden*: if true, do not show the group on the page. Defaults to false.
 - *selected*: if true, display the group as selected. Defaults to false.
 - *critical*: if true, make the installation process fail if installing
   any of the packages in the group fails. Otherwise, just log a warning.
   Defaults to false. If not set in a subgroup (see below), inherits from
   the parent group.
 - *immutable*: if true, the state of the group (and all its subgroups)
   cannot be changed; it really only makes sense in combination
   with *selected* set to true. This only affects the user-interface.
 - *expanded*: if true, the group is shown in an expanded form (that is,
   not-collapsed) in the treeview on start. This only affects the user-
   interface. Only top-level groups are show expanded-initially.
 - *immutable*: if true, the group cannot be changed (packages selected
   or deselected) and no checkboxes are shown for the group.
 - *subgroups*: if present this follows the same structure as the top level
   of the YAML file, allowing there to be sub-groups of packages to an
   arbitary depth
 - *pre-install*: an optional command to run within the new system before
   the group's packages are installed. It will run before each package in
   the group is installed.
 - *post-install*: an optional command to run within the new system after
   the group's packages are installed. It will run after each package in
   the group is installed.

If you set both *hidden* and *selected* for a group, you are basically creating
a "default" group of packages which will always be installed in the user's
system.

> The note below applies to Calamares up-to-and-including 3.2.13, but will
> change in a later release.

The *pre-install* and *post-install* commands are **not** passed to
a shell; see the **packages** module configuration (i.e. `packages.conf`)
for details. To use a full shell pipeline, call the shell explicitly.



## Overall Configuration

Here is the set of instructions to have the module work in your Calamares.

First, if the module is used, we need to require a working Internet connection,
otherwise the module will be unable to fetch the package groups and to perform
the installation. Requirements for the Calamares instance are configured in the
`welcome.conf` file (configuration for the **welcome** module). Make sure
*internet* is listed under the *required* checks.

In the `settings.conf` file, decide where the **netinstall** page should be
displayed. I put it just after the **welcome** page, but any position between
that and just before **partition** should make no difference.

If not present, add the **packages** job in the *exec* list. This is the job
that calls the package manager to install packages. Make sure it is configured
to use the correct package manager for your distribution; this is configured in
`packages.conf`.

The *exec* list in `settings.conf` should contain the following items in
order (it's ok for other jobs to be listed inbetween them, though):

```
  - unpackfs
  - networkcfg
  - packages
```

**unpackfs** creates the chroot where the installation is performed, and unpacks
the root image with the filesystem structure; **networkcfg** set ups a working
network in the chroot; and finally **packages** can install packages in the
chroot.

## Common issues

If launching the package manager command returns you negative exit statuses and
nothing is actually invoked, this is likely an error in the setup of the chroot;
check that the parameter **rootMountPoint** is set to the correct value in the
Calamares configuration.

If the command is run, but exits with error, check that the network is
working in the chroot. Make sure `/etc/resolv.conf` exists and that
it's not empty.
