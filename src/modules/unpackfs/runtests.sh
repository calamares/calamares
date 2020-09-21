#! /bin/sh
#
# SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
# SPDX-License-Identifier: BSD-2-Clause
#
# Test preparation for unpackfs; since there's a bunch
# of fiddly bits than need to be present for the tests,
# do that in a script rather than entirely in CTest.
#
SRCDIR=$( dirname "$0" )

# For test 3
mkdir /tmp/unpackfs-test-run-rootdir3

# For test 7
mkdir /tmp/unpackfs-test-run-rootdir3/realdest

# For test 9
mkdir /tmp/unpackfs-test-run-rootdir3/smalldest
if test 0 = $( id -u ) ; then
    mount -t tmpfs -o size=32M tmpfs /tmp/unpackfs-test-run-rootdir3/smalldest
    dd if=/dev/zero of=/tmp/unpackfs-test-run-rootdir3/smalldest/bogus.zero bs=1M count=1
fi

# Run tests
sh "$SRCDIR/../testpythonrun.sh" unpackfs

# Cleanup test 9
if test 0 = $( id -u ) ; then
    umount /tmp/unpackfs-test-run-rootdir3/smalldest
fi

# Cleanup test 7
rm -rf /tmp/unpackfs-test-run-rootdir3/realdest

# Cleanup test 3
rmdir /tmp/unpackfs-test-run-rootdir3
