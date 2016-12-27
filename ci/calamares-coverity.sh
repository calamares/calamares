#!/bin/bash

# Make sure we can make git operations from the Calamares Docker+Jenkins environment.
cp ~/jenkins-master/.gitconfig ~
cp -R ~/jenkins-master/.ssh ~

cd "$WORKSPACE"
git config --global http.sslVerify false

rm -Rf "$WORKSPACE/prefix"
mkdir "$WORKSPACE/prefix"

git clone git://anongit.kde.org/kpmcore "$WORKSPACE/kpmcore"
cd "$WORKSPACE/kpmcore"
mkdir "$WORKSPACE/kpmcore/build"
cd "$WORKSPACE/kpmcore/build"
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr ..
nice -n 18 make -j2
make DESTDIR="$WORKSPACE/prefix" install

cd "$WORKSPACE"

wget https://scan.coverity.com/download/cxx/linux64 --no-check-certificate \
     --post-data "token=ll90T04noQ4cORJx_zczKA&project=calamares%2Fcalamares" \
     -O coverity_tool.tar.gz
mkdir "$WORKSPACE/coveritytool"
tar xvf coverity_tool.tar.gz -C "$WORKSPACE/coveritytool" --strip-components 2
export PATH="$WORKSPACE/coveritytool/bin:$PATH"

rm -Rf "$WORKSPACE/build"
mkdir "$WORKSPACE/build"
cd "$WORKSPACE/build"

CMAKE_PREFIX_PATH="$WORKSPACE/prefix/usr" cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr -DWEBVIEW_FORCE_WEBKIT=1 ..
nice -n 18 cov-build --dir cov-int make -j2

tar caf calamares-ci.tar.xz cov-int

curl -k --form token=ll90T04noQ4cORJx_zczKA \
  --form email=teo@kde.org \
  --form file=@calamares-ci.tar.xz \
  --form version="master-`date -u +%Y%m%d`" \
  --form description="master on `date -u`" \
  https://scan.coverity.com/builds?project=calamares%2Fcalamares
