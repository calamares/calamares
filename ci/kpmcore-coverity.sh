#!/bin/bash

#Hack for Coverity build, so the compiler doesn't complain about InheritanceChecker
sudo cp ~/jenkins-master/kpluginfactory.h /usr/include/KF5/KCoreAddons

cd "$WORKSPACE"
wget https://scan.coverity.com/download/cxx/linux64 --no-check-certificate \
     --post-data "token=cyOjQZx5EOFLdhfo7ZDa4Q&project=KDE+Partition+Manager+Core+Library+-+KPMcore" \
     -O coverity_tool.tar.gz
mkdir "$WORKSPACE/coveritytool"
tar xvf coverity_tool.tar.gz -C "$WORKSPACE/coveritytool" --strip-components 2
export PATH="$WORKSPACE/coveritytool/bin:$PATH"

rm -Rf "$WORKSPACE/build"
mkdir "$WORKSPACE/build"
cd "$WORKSPACE/build"

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr ..
nice -n 18 cov-build --dir cov-int make -j2

tar cavf kpmcore-ci.tar.xz cov-int

cat cov-int/build-log.txt

curl -k --form token=cyOjQZx5EOFLdhfo7ZDa4Q \
  --form email=teo@kde.org \
  --form file=@kpmcore-ci.tar.xz \
  --form version="master-`date -u +%Y%m%d`" \
  --form description="master on `date -u`" \
  https://scan.coverity.com/builds?project=KDE+Partition+Manager+Core+Library+-+KPMcore
