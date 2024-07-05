#! /bin/sh
#
# SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
# SPDX-License-Identifier: BSD-2-Clause
#
# Compares the ABI of the current working tree with the ABI
# from a base-version. Uses libabigail for the actual comparison.
#
# To use the tool, just run the script. It will build Calamares at
# least once, maybe twice (if it needs the base-version ABI information
# and hasn't cached it).

# The build settings can be influenced via environment variables:
#   * QT_VERSION    set to nothing (uses default), 5 or 6

case "$QT_VERSION" in
	5) extra_cmake_args="-DWITH_QT6=OFF" ;;
	6) extra_cmake_args="-DWITH_QT6=ON" ;;
	"") extra_cmake_args="" ;;
	*) echo "Invalid QT_VERSION environment '${QT_VERSION}'" ; exit 1 ; ;;
esac

# The base version can be a tag or git-hash; it will be checked-out
# in a worktree.
#
# Note that the hash here corresponds to v3.3.3 . That was a release
# with hidden visibility enabled and a first step towards more-stable ABI.
BASE_VERSION=8741c7ec1a94ee5f27e98ef3663d1a8f4738d2c2

### Build a tree and cache the ABI info into ci/
#
#
do_build() {
	LABEL=$1
	SOURCE_DIR=$2

	BUILD_DIR=build-abi-$LABEL
	rm -rf $BUILD_DIR
	rm -f $BUILD_DIR.log

	echo "# Running CMake for $LABEL"
	cmake -S $SOURCE_DIR -B $BUILD_DIR -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-Og -g -gdwarf" -DCMAKE_C_FLAGS="-Og -g -gdwarf" $extra_cmake_args > /dev/null 2>&1
	test -f $BUILD_DIR/Makefile || { echo "! failed to CMake $LABEL" ; exit 1 ; }

	echo "# Running make for $LABEL"
	# Two targets make knows about at top-level
	if make -C $BUILD_DIR -j12 calamares calamaresui > $BUILD_DIR.log 2>&1
	then
		ls -1 $BUILD_DIR/libcalamares*.so.*
		# Copy the un-versioned files; .so is a symlink to the just-built one
		for lib in $BUILD_DIR/libcalamares*.so
		do
			cp $lib ci/`basename $lib`.$LABEL
		done
		rm -rf $BUILD_DIR $BUILD_DIR.log
		echo "# .. build successful for $LABEL"
	else
		echo "! failed to build $LABEL"
		exit 1
	fi
}

### Build current tree and get ABI info
#
#
do_build current .

### Build ABI base version
#
# We cache this to save on some build time, if we are chasing a
# single branch from an unchanging base version.
#
if test -f ci/libcalamares.so.$BASE_VERSION
then
	# The ABI version is cached, so we're good
	:
else
	git worktree remove --force tree-abi-$BASE_VERSION > /dev/null 2>&1
	git worktree add tree-abi-$BASE_VERSION $BASE_VERSION > /dev/null 2>&1 || { echo "! could not create worktree for $BASE_VERSION" ; exit 1 ; }
	do_build $BASE_VERSION tree-abi-$BASE_VERSION
	git worktree remove --force tree-abi-$BASE_VERSION > /dev/null 2>&1
fi

### Compare & Report
#
# abidiff compares the Application Binary Interfaces (ABI) of two
# shared libraries in ELF format. It emits a meaningful report describing
# the differences between the two ABIs.
#
# -l prints only the leaf changes, leaving out explanations of why.
#
abidiff -l ci/libcalamares.so.$BASE_VERSION ci/libcalamares.so.current
