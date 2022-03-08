#! /usr/bin/env sh

SCRIPT_DIRECTORY="$(dirname -- "$(readlink -f -- "$0")")"
PROJECT_DIRECTORY="$(dirname -- "$SCRIPT_DIRECTORY")"
BUILD_DIRECTORY="$PROJECT_DIRECTORY"/build

if ls "$SCRIPT_DIRECTORY"/packaging/*.pkg.tar.* > /dev/null 2>&1;then
    set -o xtrace
    sudo pacman -U "$@" "$SCRIPT_DIRECTORY"/packaging/*.pkg.tar.zst
    set +o xtrace
else
    set -o xtrace
    sh "$SCRIPT_DIRECTORY"/build_package.sh --install "$@"
    set +o xtrace
fi