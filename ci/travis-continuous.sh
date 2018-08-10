#! /bin/sh
#
# Travis CI script for use on every-commit:
#  - build and install Calamares
#
test -n "$BUILDDIR" || exit 1
test -n "$SRCDIR" || exit 1

test -d $BUILDDIR || exit 1
test -d $SRCDIR || exit 1
test -f $SRCDIR/CMakeLists.txt || exit 1

cd $BUILDDIR || exit 1

cmake $CMAKE_ARGS $SRCDIR && make -j2 && make install DESTDIR=/build/INSTALL_ROOT
