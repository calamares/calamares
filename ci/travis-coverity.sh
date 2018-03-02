#! /bin/sh
#
# Travis CI script for weekly (cron) use:
#  - use the coverity tool to build and and upload results
#
test -n "$COVERITY_SCAN_TOKEN" || exit 1
test -n "$BUILDDIR" || exit 1
test -n "$SRCDIR" || exit 1

test -d $BUILDDIR || exit 1
test -d $SRCDIR || exit 1
test -f $SRCDIR/CMakeLists.txt || exit 1

cd $BUILDDIR || exit 1

curl -k -o coverity_tool.tar.gz \
  -d "token=$COVERITY_SCAN_TOKEN&project=calamares%2Fcalamares" \
  https://scan.coverity.com/download/cxx/linux64 || exit 1
mkdir "$BUILDDIR/coveritytool"
tar xvf coverity_tool.tar.gz -C "$BUILDDIR/coveritytool" --strip-components 2
export PATH="$BUILDDIR/coveritytool/bin:$PATH"


cmake -DCMAKE_BUILD_TYPE=Debug -DWEBVIEW_FORCE_WEBKIT=1 -DKDE_INSTALL_USE_QT_SYS_PATHS=ON $SRCDIR || exit 1
cov-build --dir cov-int make -j2

tar caf calamares-ci.tar.xz cov-int

curl -k --form token=$COVERITY_SCAN_TOKEN \
  --form email=groot@kde.org \
  --form file=@calamares-ci.tar.xz \
  --form version="master-`date -u +%Y%m%d`" \
  --form description="master on `date -u`" \
  https://scan.coverity.com/builds?project=calamares%2Fcalamares
