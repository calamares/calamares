#! /bin/sh
#
# Install dependencies for the nightly-opensuse build
#
zypper --non-interactive up
zypper --non-interactive in git-core jq curl ninja
# From deploycala.py
zypper --non-interactive in \
	"bison" \
	"flex" \
	"git" \
	"make" \
	"cmake" \
	"gcc-c++"
zypper --non-interactive in \
	"libqt5-qtbase-devel" \
	"libqt5-linguist-devel" \
	"libqt5-qtsvg-devel" \
	"libqt5-qtdeclarative-devel" \
	"libqt5-qtwebengine-devel" \
	"yaml-cpp-devel" \
	"libpolkit-qt5-1-devel" \
	"libpwquality-devel" \
	"parted-devel" \
	"python-devel" \
	"libboost_headers-devel" \
	"libboost_python3-devel"
zypper --non-interactive in \
	"extra-cmake-modules" \
	"kdbusaddons-devel" \
	"kservice-devel" \
	"kpackage-devel" \
	"kparts-devel" \
	"kcrash-devel" \
	"kpmcore-devel" \
	"plasma5-workspace-devel" \
	"plasma-framework-devel"
# Additional dependencies
zypper --non-interactive in \
	libicu-devel \
	libAppStreamQt-devel \
	libatasmart-devel
