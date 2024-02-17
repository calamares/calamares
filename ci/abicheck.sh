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

# The base version can be a tag or git-hash; it will be checked-out
# in a worktree.
#
# Note that the hash here corresponds to v3.3.0 .
BASE_VERSION=1d8a1972422d83c36f2b934c2629ae1f564c0428

### Build a tree and cache the ABI info into ci/
#
#
do_build() {
	LABEL=$1
	SOURCE_DIR=$2

	BUILD_DIR=build-abi-$LABEL
	rm -rf $BUILD_DIR
	rm -f $BUILD_DIR.log

	cmake -S $SOURCE_DIR -B $BUILD_DIR -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-Og -g -gdwarf" -DCMAKE_C_FLAGS="-Og -g -gdwarf"  > /dev/null 2>&1
	test -f $BUILD_DIR/Makefile || { echo "! failed to CMake $LABEL" ; exit 1 ; }

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
