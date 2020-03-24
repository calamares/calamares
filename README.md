### Calamares: Distribution-Independent Installer Framework
---------

[![GitHub release](https://img.shields.io/github/release/calamares/calamares.svg)](https://github.com/calamares/calamares/releases)
[![Travis Build Status](https://travis-ci.org/calamares/calamares.svg?branch=master)](https://travis-ci.org/calamares/calamares)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/5389/badge.svg)](https://scan.coverity.com/projects/5389)
[![GitHub license](https://img.shields.io/github/license/calamares/calamares.svg)](https://github.com/calamares/calamares/blob/master/LICENSE)

| [Report a Bug](https://github.com/calamares/calamares/issues/new) | [Translate](https://www.transifex.com/projects/p/calamares/) | [Contribute](https://github.com/calamares/calamares/wiki/Develop-Guide) | Freenode (IRC): #calamares | [Wiki](https://github.com/calamares/calamares/wiki) |
|:-----------------------------------------:|:----------------------:|:-----------------------:|:--------------------------:|:--------------------------:|

### Dependencies

Main:
* Compiler with C++14 support: GCC >= 5 or Clang >= 3.5.1
* CMake >= 3.3
* Qt >= 5.9
* yaml-cpp >= 0.5.1
* Python >= 3.3 (required for some modules)
* Boost.Python >= 1.55.0 (required for some modules)
* KDE extra-cmake-modules >= 5.18 (recommended; required for some modules;
  required for some tests)
* KDE Frameworks KCoreAddons (>= 5.58 recommended)
* PythonQt (optional, deprecated)

Modules:
* Individual modules may have their own requirements;
  these are listed in CMake output. Particular requirements (not complete):
* *fsresizer* KPMCore >= 3.3
* *partition* KPMCore >= 3.3
* *users* LibPWQuality (optional)

### Building

See [wiki](https://github.com/calamares/calamares/wiki) for up to date
[building](https://github.com/calamares/calamares/wiki/Develop-Guide)
and [deployment](https://github.com/calamares/calamares/wiki/Deploy-Guide)
instructions.
