#! /bin/sh
#
# Install dependencies for building on KaOS
#
# There is no docker image for KaOS, and the live ISO comes
# with many useful things already installed, so the list
# here is short. Use pacman -Syu once to update the whole
# system to get latest libraries.
#
pacman -Syu --noconfirm git cmake ninja # No jq available
pacman -S --noconfirm \
	"gcc" \
	"boost" \
	"qt6-tools" \
	"yaml-cpp" \
	"kpmcore" \
	"icu"
pacman -S --noconfirm \
	"extra-cmake-modules" \
	"kiconthemes6" \
	"kservice6" \
	"kio6" \
	"kparts6" \
	"qt6-webengine"
true
