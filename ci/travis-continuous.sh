#! /bin/sh
#
# Travis CI script for use on every-commit:
#  - build and install Calamares
#
test -n "$BUILDDIR" || { echo "! \$BUILDDIR not set" ; exit 1 ; }
test -n "$SRCDIR" || { echo "! \$SRCDIR not set" ; exit 1 ; }

test -d $BUILDDIR || { echo "! $BUILDDIR not a directory" ; exit 1 ; }
test -d $SRCDIR || { echo "! $SRCDIR not a directory" ; exit 1 ; }
test -f $SRCDIR/CMakeLists.txt || { echo "! Missing $SRCDIR/CMakeLists.txt" ; exit 1 ; }

cd $BUILDDIR || exit 1

echo "###"
echo "### cmake $CMAKE_ARGS $SRCDIR"
echo "###"
cmake $CMAKE_ARGS $SRCDIR || { echo "! CMake failed" ; exit 1 ; }

echo -e "###\n### make\n###"
make -j2 || { make -j1 VERBOSE=1 ; echo "! Make failed" ; exit 1 ; }

echo -e "###\n### make install\n###"
echo "# Build results"
find "$BUILDDIR" -name '*.so'

echo "# Install"
DESTDIR=/build/INSTALL_ROOT
mkdir -p "$DESTDIR"

result=true
make install VERBOSE=1 DESTDIR="$DESTDIR" || result=false

echo "# Install results"
find "$DESTDIR" -type f
$result  # Result of make install, above
