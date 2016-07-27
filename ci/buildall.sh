#!/bin/bash

rm -Rf "$WORKSPACE/prefix"
mkdir "$WORKSPACE/prefix"

git clone git://anongit.kde.org/kpmcore "$WORKSPACE/kpmcore"
cd "$WORKSPACE/kpmcore"
mkdir "$WORKSPACE/kpmcore/build"
cd "$WORKSPACE/kpmcore/build"
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr ..
nice -n 18 make -j2
make DESTDIR="$WORKSPACE/prefix" install

rm -Rf "$WORKSPACE/build"
mkdir "$WORKSPACE/build"
cd "$WORKSPACE/build"

CMAKE_PREFIX_PATH="$WORKSPACE/prefix/usr" cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=/usr -DWEBVIEW_FORCE_WEBKIT=1 ..
nice -n 18 make -j2
