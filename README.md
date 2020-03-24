### Calamares: Distribution-Independent Installer Framework
---------

[![GitHub release](https://img.shields.io/github/v/release/sereneteam/alterlinux-calamares?color=%234169e1&include_prereleases&style=flat-square)](https://github.com/sereneteam/alterlinux-calamares/releases)
[![GitHub license](https://img.shields.io/github/license/sereneteam/alterlinux-calamares?style=flat-square&logo=gnu)](https://github.com/sereneteam/alterlinux-calamares/blob/master/LICENSE)

[If you find a Bug, please report a Bug](https://github.com/SereneTeam/alterlinux-calamares/issues/new/choose)

***

### Dependencies

Main:
* Compiler with C++14 support: [GCC](https://www.archlinux.org/packages/core/x86_64/gcc/) >= 5 or [Clang](https://www.archlinux.org/packages/extra/x86_64/clang/) >= 3.5.1
* [CMake](https://www.archlinux.org/packages/extra/x86_64/cmake/) >= 3.3
* [Qt](https://www.archlinux.org/packages/extra/x86_64/qt5-base/) >= 5.9
* [yaml-cpp](https://www.archlinux.org/packages/community/x86_64/yaml-cpp/) >= 0.5.1
* [Python](https://www.archlinux.org/packages/extra/x86_64/python/) >= 3.3 (required for some modules)
* [Boost.Python](https://www.archlinux.org/packages/extra/x86_64/boost/) and [Boost-libs](https://www.archlinux.org/packages/extra/x86_64/boost-libs/) >= 1.55.0 (required for some modules)
* [KDE extra-cmake-modules](https://www.archlinux.org/packages/extra/any/extra-cmake-modules/) >= 5.18 (recommended; required for some modules;
  required for some tests)
* [KDE Frameworks KCoreAddons](https://www.archlinux.org/packages/extra/x86_64/kcoreaddons/) (>= 5.58 recommended)
* ~~PythonQt (optional, deprecated)~~ (Not available)

Modules:
* Individual modules may have their own requirements;
  these are listed in CMake output. Particular requirements (not complete):
* *fsresizer* [KPMCore](https://www.archlinux.org/packages/community/x86_64/kpmcore/) >= 3.3
* *partition* [KPMCore](https://www.archlinux.org/packages/community/x86_64/kpmcore/) >= 3.3
* *users* [LibPWQuality](https://www.archlinux.org/packages/extra/x86_64/libpwquality/)

### Building (Vanilla)

See [wiki](https://github.com/calamares/calamares/wiki) for up to date
[building](https://github.com/calamares/calamares/wiki/Develop-Guide)
and [deployment](https://github.com/calamares/calamares/wiki/Deploy-Guide)
instructions.
