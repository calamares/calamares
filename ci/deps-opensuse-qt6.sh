#! /bin/sh
# 
# Install dependencies for the nightly-opensuse-qt6 build
#
# Add a Qt6/KF6 repo
zypper --non-interactive addrepo -G https://download.opensuse.org/repositories/home:krop:kf6/openSUSE_Tumbleweed/home:krop:kf6.repo
zypper --non-interactive addrepo -G https://download.opensuse.org/repositories/home:/krop:/Qt6:/Release/openSUSE_Tumbleweed/home:krop:Qt6:Release.repo

zypper --non-interactive refresh
zypper --non-interactive up
zypper --non-interactive in git-core jq curl ninja
# From deploycala.py
zypper --non-interactive in bison flex git make cmake gcc-c++
zypper --non-interactive in yaml-cpp-devel libpwquality-devel parted-devel python-devel libboost_headers-devel libboost_python3-devel
zypper --non-interactive in libicu-devel libatasmart-devel
# Qt6/KF6 dependencies
zypper --non-interactive in qt6-concurrent-devel qt6-gui-devel qt6-linguist-devel qt6-network-devel qt6-svg-devel qt6-declarative-devel
zypper --non-interactive in kf6-kcoreaddons-devel kf6-kdbusaddons-devel kf6-kcrash-devel
zypper --non-interactive in kf6-kparts-devel # Also installs KF5 things
zypper --non-interactive in libpolkit-qt6-1-devel
