#! /usr/bin/env sh

SCRIPT_DIRECTORY=$(dirname -- $(readlink -f -- "$0"))
PROJECT_DIRECTORY=$(dirname -- "$SCRIPT_DIRECTORY")
BUILD_DIRECTORY="$PROJECT_DIRECTORY/build"

# Create build directory if it does not exist
set -o xtrace
mkdir -p "$BUILD_DIRECTORY"
set +o xtrace

# Configure and pass-through any options supplied. Default options are overridden if any options are supplied
if [ $# -eq 0 ];then
    set -o xtrace
    cmake \
        -DCMAKE_BUILD_TYPE=Debug \
        -DCMAKE_INSTALL_PREFIX=/usr \
        -DCMAKE_INSTALL_LIBDIR=lib \
        -B "$BUILD_DIRECTORY" -S "$PROJECT_DIRECTORY"
    set +o xtrace
else
    set -o xtrace
    cmake \
        "$@" \
        -B "$BUILD_DIRECTORY" -S "$PROJECT_DIRECTORY"
    set +o xtrace
fi
