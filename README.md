### Calamares: Distribution-Independent Installer Framework
---------

[![GitHub release](https://img.shields.io/github/release/calamares/calamares.svg)](https://github.com/calamares/calamares/releases)
[![Build Status](https://calamares.io/ci/buildStatus/icon?job=calamares-post_commit)](https://calamares.io/ci/job/calamares-post_commit/)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/5389/badge.svg)](https://scan.coverity.com/projects/5389)
[![GitHub license](https://img.shields.io/github/license/calamares/calamares.svg)](https://github.com/calamares/calamares/blob/master/LICENSE)

| [Report a Bug](https://calamares.io/bugs/) | [Contribute](https://github.com/calamares/calamares/blob/master/HACKING.md) | [Translate](https://www.transifex.com/projects/p/calamares/) | Freenode (IRC): #calamares |
|:-----------------------------------------:|:----------------------:|:-----------------------:|:--------------------------:|

### Dependencies

Main:
* Compiler with C++11 support: GCC >= 4.9.0 or Clang >= 3.5.1
* CMake >= 2.8.12
* Qt >= 5.3
* yaml-cpp >= 0.5.1
* Python >= 3.3
* Boost.Python >= 1.55.0
* dmidecode

Modules:
* welcome:
 * NetworkManager
 * UPower
* partition:
 * extra-cmake-modules
 * KF5: KCoreAddons, KConfig, KI18n, KIconThemes, KIO, KService
 * KPMcore >= 2.0
 * sgdisk
* bootloader:
 * systemd-boot or GRUB
 * sgdisk
* unpackfs:
 * squashfs-tools
 * rsync


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
