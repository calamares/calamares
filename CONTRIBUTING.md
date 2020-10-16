<!-- SPDX-FileCopyrightText: no
     SPDX-License-Identifier: CC0-1.0
-->

# Contributing to Calamares

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

Individual modules may have their own requirements;
these are listed in CMake output.
Particular requirements (not complete):

* *fsresizer* KPMCore >= 3.3 (>= 4.2 recommended)
* *partition* KPMCore >= 3.3 (>= 4.2 recommended)
* *users* LibPWQuality (optional)

### Building

See [wiki](https://github.com/calamares/calamares/wiki) for up to date
[building](https://github.com/calamares/calamares/wiki/Develop-Guide)
and [deployment](https://github.com/calamares/calamares/wiki/Deploy-Guide)
instructions.

