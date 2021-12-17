#! /usr/bin/env sh

SCRIPT_DIRECTORY="$(dirname -- "$(readlink -f -- "$0")")"
PROJECT_DIRECTORY="$(dirname -- "$SCRIPT_DIRECTORY")"
BUILD_DIRECTORY="$PROJECT_DIRECTORY"/build

# Clean and pass-through any options supplied (for example, -f to prevent a confirmation prompt)
set -o xtrace
rm -r "$@" -- "$BUILD_DIRECTORY"
set +o xtrace