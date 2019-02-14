#! /bin/sh
SRCDIR=$( dirname "$0" )

# For test 3
mkdir /tmp/unpackfs-test-run-rootdir3

# For test 7
mkdir /tmp/unpackfs-test-run-rootdir3/realdest

# Run tests
sh "$SRCDIR/../testpythonrun.sh" unpackfs

# Cleanup test 7
rm -rf /tmp/unpackfs-test-run-rootdir3/realdest

# Cleanup test 3
rmdir /tmp/unpackfs-test-run-rootdir3
