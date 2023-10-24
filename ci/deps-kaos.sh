#! /bin/sh
#
# Install dependencies for building on KaOS
#
# There is no docker image for KaOS, and the live ISO comes
# with many useful things already installed, so the list
# here is short.
#
pacman -Sy --noconfirm git cmake ninja # No jq available
pacman -S --noconfirm \
	"gcc" \
	"boost" \
	"qt5-tools" \
	"yaml-cpp" \
	"kpmcore" \
	"icu"
pacman -S --noconfirm \
	"extra-cmake-modules" \
	"kiconthemes" \
	"kservice" \
	"kio" \
	"kparts" \
	"qtwebengine"

