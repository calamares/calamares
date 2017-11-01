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

cmake -DWEBVIEW_FORCE_WEBKIT=1 -DKDE_INSTALL_USE_QT_SYS_PATHS=ON $SRCDIR && make -j2 && make install DESTDIR=/build/INSTALL_ROOT
