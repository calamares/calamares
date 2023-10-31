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
	"libqt5-qtdeclarative-devel" \
	"cmake(Qt5LinguistTools)" \
	"cmake(Qt5Svg)" \
	"cmake(Qt5WebEngine)" \
	"cmake(PolkitQt5-1)" \
	"yaml-cpp-devel" \
	"libpwquality-devel" \
	"parted-devel" \
	"python311-devel" \
	"libboost_headers-devel" \
	"libboost_python3-devel"
zypper --non-interactive in \
	"extra-cmake-modules" \
	"cmake(KF5Crash)" \
	"cmake(KF5DBusAddons)" \
	"cmake(KF5Package)" \
	"cmake(KF5Parts)" \
	"cmake(KF5Plasma)" \
	"cmake(KF5Service)" \
	"cmake(KPMcore)" \
	"cmake(LibKWorkspace)"
# Additional dependencies
zypper --non-interactive in \
	libicu-devel \
	libAppStreamQt-devel \
	libatasmart-devel

# Not actual dependencies, but good to have
zypper --non-interactive in python311-PyYAML python311-jsonschema
true
