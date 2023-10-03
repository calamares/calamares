#! /bin/sh
#
# Install dependencies for the nightly-fedora-qt6 build
#

# Add the KF6 repo
dnf install -y 'dnf-command(copr)'
dnf copr enable -y @kdesig/kde-nightly-qt6

yum install -y bison flex git make cmake gcc-c++ ninja-build
yum install -y yaml-cpp-devel libpwquality-devel parted-devel python-devel gettext gettext-devel
yum install -y libicu-devel libatasmart-devel
# Qt6/KF6 dependencies
yum install -y qt6-qtbase-devel qt6-linguist qt6-qtbase-private-devel qt6-qtdeclarative-devel qt6-qtsvg-devel qt6-qttools-devel
yum install -y kf6-kcoreaddons-devel kf6-kdbusaddons-devel kf6-kcrash-devel
yum install -y polkit-qt6-1-devel appstream-qt-devel
# Runtime dependencies for QML modules
yum install -y kf6-kirigami2-devel qt6-qt5compat-devel
