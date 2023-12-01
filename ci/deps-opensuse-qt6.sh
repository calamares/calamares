#! /bin/sh
# 
# Install dependencies for the nightly-opensuse-qt6 build
#
# Add a Qt6/KF6 repo
zypper --non-interactive addrepo -f -G https://download.opensuse.org/repositories/KDE:/Unstable:/Frameworks/openSUSE_Factory/KDE:Unstable:Frameworks.repo
zypper --non-interactive addrepo -f -G https://download.opensuse.org/repositories/KDE:/Qt6/openSUSE_Tumbleweed/KDE:Qt6.repo

zypper --non-interactive refresh
zypper --non-interactive up
zypper --non-interactive in git-core jq curl ninja
# From deploycala.py
zypper --non-interactive in bison flex git make cmake gcc-c++
zypper --non-interactive in yaml-cpp-devel libpwquality-devel parted-devel python3-devel
zypper --non-interactive in libicu-devel libatasmart-devel
# Qt6/KF6 dependencies
zypper --non-interactive in kf6-extra-cmake-modules
zypper --non-interactive in "qt6-declarative-devel" "cmake(Qt6Concurrent)" "cmake(Qt6Gui)" "cmake(Qt6Network)" "cmake(Qt6Svg)" "cmake(Qt6Linguist)"
zypper --non-interactive in "cmake(KF6CoreAddons)" "cmake(KF6DBusAddons)" "cmake(KF6Crash)"
zypper --non-interactive in "cmake(KF6Parts)" # Also installs KF5 things
zypper --non-interactive in "cmake(PolkitQt6-1)"
true
