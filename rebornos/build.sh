#! /usr/bin/env sh

SCRIPT_DIRECTORY=$(dirname -- $(readlink -f -- "$0"))
PROJECT_DIRECTORY=$(dirname -- "$SCRIPT_DIRECTORY")
BUILD_DIRECTORY="$PROJECT_DIRECTORY/build"

NUMBER_OF_PROCESSORS="$(nproc)"

# Run configure.sh if the build directory does not exist
if [ ! -d "$BUILD_DIRECTORY" ];then
    set -o xtrace
    sh "$SCRIPT_DIRECTORY"/configure.sh
    set +o xtrace
fi

# Build and pass-through any options supplied. Default options are overridden if any options are supplied
if [ $# -eq 0 ];then
    set -o xtrace
    cmake --build "$BUILD_DIRECTORY" --parallel "$NUMBER_OF_PROCESSORS"
    set +o xtrace
else
    set -o xtrace
    cmake --build "$BUILD_DIRECTORY" "$@"
    set +o xtrace
fi