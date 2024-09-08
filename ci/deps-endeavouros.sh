#! /bin/sh
#
# Install dependencies for building on EndeavourOS
#
# There is no docker image for EndeavoudOS, and the live ISO
# for Cassini Nova is KF5 / Qt5 based, but we can build there.
# It even has most of the build-deps already installed.
pacman -Syu --noconfirm jq
pacman -S --noconfirm git cmake ninja jq || exit 1
pacman -S --noconfirm gcc yaml-cpp icu || exit 1
pacman -S --noconfirm extra-cmake-modules || exit 1
pacman -S --noconfirm python-jsonschema || exit 1

