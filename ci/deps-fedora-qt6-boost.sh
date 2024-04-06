#! /bin/sh
#
# Install dependencies for the nightly-fedora-qt6-boost build
#

yum install -y bison flex git make cmake gcc-c++ ninja-build
yum install -y yaml-cpp-devel libpwquality-devel parted-devel python-devel gettext gettext-devel python3-pyyaml
yum install -y libicu-devel libatasmart-devel
yum install -y boost-devel
# Qt6/KF6 dependencies
yum install -y qt6-qtbase-devel qt6-linguist qt6-qtbase-private-devel qt6-qtdeclarative-devel qt6-qtsvg-devel qt6-qttools-devel
yum install -y extra-cmake-modules kf6-kcoreaddons-devel kf6-kdbusaddons-devel kf6-kcrash-devel
yum install -y kf6-kconfig-devel kf6-ki18n-devel kf6-kwidgetsaddons-devel kf6-kservice-devel
yum install -y polkit-qt6-1-devel appstream-qt-devel
# Runtime dependencies for QML modules
yum install -y kf6-kirigami2-devel || true
yum install -y qt6-qt5compat-devel || true
true
