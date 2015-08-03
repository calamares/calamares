### Calamares: Distribution-Independent Installer Framework
---------

[![GitHub release](https://img.shields.io/github/release/calamares/calamares.svg)](https://github.com/calamares/calamares/releases)
[![Build Status](https://calamares.io/ci/buildStatus/icon?job=calamares-master)](https://calamares.io/ci/job/calamares-master/)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/5389/badge.svg)](https://scan.coverity.com/projects/5389)
[![GitHub license](https://img.shields.io/github/license/calamares/calamares.svg)](https://github.com/calamares/calamares/blob/master/LICENSE)

| [Report a Bug](https://calamares.io/bugs/) | [Contribute](https://github.com/calamares/calamares/blob/master/HACKING.md) | [Translate](https://www.transifex.com/projects/p/calamares/) | Freenode (IRC): #calamares |
|:-----------------------------------------:|:----------------------:|:-----------------------:|:--------------------------:|

### Dependencies

Compiler with C++11 support: GCC >= 4.8.4 or Clang >= 3.5.1

| Main | Welcome module | Partitioning module | Bootloader module | Unpackfs module |
|:----:|:--------------:|:-------------------:|:-----------------:|:---------------:|
| CMake >= 2.8.12 | NetworkManager | extra-cmake-modules | systemd-boot or GRUB2 | squashfs-tools |
| Qt >= 5.3 | UPower | kconfig (part of KF5) | sgdisk | rsync |
| yaml-cpp >= 0.5.1 | | solid (part of KF5) | | |
| Python >= 3.3 | | kcoreaddons (part of KF5) | | |
| Boost.Python >= 1.55.0 | | ki18n (part of KF5) | | |
| dmidecode | | sgdisk | | |

### Deployment
[__Setting up branding__](https://github.com/calamares/calamares/blob/master/src/branding/README.md)

[__Working with modules__](https://github.com/calamares/calamares/blob/master/src/modules/README.md)


### Building
Clone Calamares from GitHub and `cd` into the calamares directory, then:
```
$ git submodule init
$ git submodule update
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
$ make
```

#### Supported variables for CMake
 * `WITH_PYTHON` - if this is set to false, the Python module interface will not be built. Default is true.
 * `SKIP_MODULES` - takes a space-separated list of module names that should not be built even if present in `src/modules` (e.g. `cmake -DSKIP_MODULES="partition mount umount welcome" ..`). Default is empty.

### Design Notes
Calamares is currently split as follows:
 1. __libcalamares__ - The back-end library.
   * Only depends on QtCore, yaml-cpp, Python and Boost.Python.
   * Provides a job queue and generic jobs.
   * Comes with 3 job interfaces: C++, Python and process (the latter is very limited).
 2. __libcalamaresui__ - The front-end library.
   * Same dependencies as libcalamares, plus QtWidgets and other Qt modules.
   * Comes with a module loading system, for different kinds of plugins.
   * Supports branding components.
   * Presents a bunch of pages in a scripted order, enqueues jobs in the back-end library.
 3. __calamares__ - The main executable.
   * A thin wrapper around libcalamaresui; starts up and plugs together all the parts.
