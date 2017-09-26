### Calamares: Distribution-Independent Installer Framework
---------

[![GitHub release](https://img.shields.io/github/release/calamares/calamares.svg)](https://github.com/calamares/calamares/releases)
[![Build Status](https://calamares.io/ci/buildStatus/icon?job=calamares-post_commit)](https://calamares.io/ci/job/calamares-post_commit/)
[![Travis Build Status](https://travis-ci.org/calamares/calamares.svg?branch=master)](https://travis-ci.org/calamares/calamares)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/5389/badge.svg)](https://scan.coverity.com/projects/5389)
[![GitHub license](https://img.shields.io/github/license/calamares/calamares.svg)](https://github.com/calamares/calamares/blob/master/LICENSE)

| [Report a Bug](https://github.com/calamares/calamares/issues/new) | [Contribute](https://github.com/calamares/calamares/blob/master/ci/HACKING.md) | [Translate](https://www.transifex.com/projects/p/calamares/) | Freenode (IRC): #calamares | [Wiki](https://github.com/calamares/calamares/wiki) |
|:-----------------------------------------:|:----------------------:|:-----------------------:|:--------------------------:|:--------------------------:|

### Dependencies

Main:
* Compiler with C++11 support: GCC >= 4.9.0 or Clang >= 3.5.1
* CMake >= 3.2
* Qt >= 5.6
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
  * KPMcore >= 3.0.3
* bootloader:
  * systemd-boot or GRUB
* unpackfs:
  * squashfs-tools
  * rsync

### Building

See [wiki](https://github.com/calamares/calamares/wiki) for up to date building and deployment instructions.
