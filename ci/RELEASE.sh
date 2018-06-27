#! /bin/sh
#
# Release script for Calamares
#
# This attempts to perform the different steps of the RELEASE.md
# document automatically. It's not tested on other machines or
# setups other than [ade]'s development VM.
# 
# Assumes that the version in CMakeLists.txt has been bumped,
# and that a release of that version is desired.

test -d .git || { echo "Not at top-level." ; exit 1 ; }
test -d src/modules || { echo "No src/modules." ; exit 1 ; }

which cmake > /dev/null 2>&1 || { echo "No cmake(1) available." ; exit 1 ; }

rm -rf build
mkdir build || { echo "Could not create build directory." ; exit 1 ; }
( cd build && cmake .. && make -j4 ) || { echo "Could not perform test-build." ; exit 1 ; }
( cd build && make test ) || { echo "Tests failed." ; exit 1 ; }



