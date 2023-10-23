#! /bin/sh
#
# Install dependencies for building on KaOS
#
# There is no docker image for KaOS, and the live ISO comes
# with many useful things already installed, so the list
# here is short.
#
pacman -Sy git cmake ninja # No jq available
pacman -Sy \
	"gcc" \
	"boost" \
	"qt5-tools" \
	"yaml-cpp" \
	"kpmcore" \
	"icu"
pacman -Sy \
	"extra-cmake-modules" \
	"kiconthemes" \
	"kservice" \
	"kio" \
	"kparts" \
	"qtwebengine"

