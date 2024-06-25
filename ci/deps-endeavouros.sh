#! /bin/sh
#
# Install dependencies for building on EndeavourOS
#
# There is no docker image for EndeavoudOS, and the live ISO
# for Cassini Nova is KF5 / Qt5 based, but we can build there.
# It even has most of the build-deps already installed.
pacman -Syu --noconfirm git cmake ninja jq
pacman -S --noconfirm gcc yaml-cpp icu
pacman -S --noconfirm extra-cmake-modules

