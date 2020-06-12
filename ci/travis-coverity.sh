#! /bin/sh
#
# Travis CI script for weekly (cron) use:
#  - use the coverity tool to build and and upload results
#
test -n "$COVERITY_SCAN_TOKEN" || { echo "! Missing Coverity token" ; exit 1 ; }
test -n "$BUILDDIR" || { echo "! \$BUILDDIR not set" ; exit 1 ; }
test -n "$SRCDIR" || { echo "! \$SRCDIR not set" ; exit 1 ; }

test -d $BUILDDIR || { echo "! $BUILDDIR not a directory" ; exit 1 ; }
test -d $SRCDIR || { echo "! $SRCDIR not a directory" ; exit 1 ; }
test -f $SRCDIR/CMakeLists.txt || { echo "! Missing $SRCDIR/CMakeLists.txt" ; exit 1 ; }

cd $BUILDDIR || exit 1

curl -k -o coverity_tool.tar.gz \
  -d "token=$COVERITY_SCAN_TOKEN&project=calamares%2Fcalamares" \
  https://scan.coverity.com/download/cxx/linux64 || exit 1
mkdir "$BUILDDIR/coveritytool"
tar xvf coverity_tool.tar.gz -C "$BUILDDIR/coveritytool" --strip-components 2
export PATH="$BUILDDIR/coveritytool/bin:$PATH"

echo "# cmake -DCMAKE_BUILD_TYPE=Debug $CMAKE_ARGS $SRCDIR"
cmake -DCMAKE_BUILD_TYPE=Debug $CMAKE_ARGS $SRCDIR || exit 1
cov-build --dir cov-int make -j2

tar caf calamares-ci.tar.xz cov-int

curl -k --form token=$COVERITY_SCAN_TOKEN \
  --form email=groot@kde.org \
  --form file=@calamares-ci.tar.xz \
  --form version="calamares-`date -u +%Y%m%d`" \
  --form description="calamares on `date -u`" \
  https://scan.coverity.com/builds?project=calamares%2Fcalamares
