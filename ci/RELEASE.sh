#! /bin/sh
#
# Release script for Calamares
#
# This attempts to perform the different steps of the RELEASE.md
# document automatically. It's not tested on other machines or
# setups other than [ade]'s development VM.
#
# Assumes that the version in CMakeLists.txt has been bumped,
# and that a release of that version is desired.
#
# None of the "update stuff" is done by this script; in preparation
# for the release, you should have already done:
#   - updating the version
#   - pulling translations
#   - updating the language list
#   - switching to the right branch

test -d .git || { echo "Not at top-level." ; exit 1 ; }
test -d src/modules || { echo "No src/modules." ; exit 1 ; }

which cmake > /dev/null 2>&1 || { echo "No cmake(1) available." ; exit 1 ; }

### Build with default compiler
#
#
BUILDDIR=$(mktemp -d --suffix=-build --tmpdir=.)
rm -rf "$BUILDDIR"
mkdir "$BUILDDIR" || { echo "Could not create build directory." ; exit 1 ; }
( cd "$BUILDDIR" && cmake .. && make -j4 ) || { echo "Could not perform test-build." ; exit 1 ; }
( cd "$BUILDDIR" && make test ) || { echo "Tests failed." ; exit 1 ; }

### Build with clang
#
#
if which clang++ > /dev/null 2>&1 ; then
    # Do build again with clang
    rm -rf "$BUILDDIR"
    mkdir "$BUILDDIR" || { echo "Could not create build directory." ; exit 1 ; }
    ( cd "$BUILDDIR" && CC=clang CXX=clang++ cmake .. && make -j4 ) || { echo "Could not perform test-build." ; exit 1 ; }
    ( cd "$BUILDDIR" && make test ) || { echo "Tests failed." ; exit 1 ; }
fi

### Get version number for this release
#
#
V=$( cd "$BUILDDIR" && make show-version | grep ^CALAMARES_VERSION | sed s/^[A-Z_]*=// )
test -n "$V" || { echo "Could not obtain version." ; exit 1 ; }

### Create signed tag
#
# This is the signing key ID associated with the GitHub account adriaandegroot,
# which is used to create all "verified" tags in the Calamares repo.
KEY_ID="128F00873E05AF1D"
git tag -u "$KEY_ID" -m "Release v$V" "v$V" || { echo "Could not sign tag v$V." ; exit 1 ; }

### Create the tarball
#
#
TAR_V="calamares-$V"
TAR_FILE="$TAR_V.tar.gz"
git archive -o "$TAR_FILE" --prefix "$TAR_V/" "v$V" || { echo "Could not create tarball." ; exit 1 ; }
test -f "$TAR_FILE" || { echo "Tarball was not created." ; exit 1 ; }
SHA256=$(sha256sum "$TAR_FILE" | cut -d" " -f1)

### Build the tarball
#
#
D=$(date +%Y%m%d-%H%M%S)
TMPDIR=$(mktemp -d --suffix="-calamares-$D")
test -d "$TMPDIR" || { echo "Could not create tarball-build directory." ; exit 1 ; }
tar xzf "$TAR_FILE" -C "$TMPDIR" || { echo "Could not unpack tarball." ; exit 1 ; }
test -d "$TMPDIR/$TAR_V" || { echo "Tarball did not contain source directory." ; exit 1 ; }
( cd "$TMPDIR/$TAR_V" && cmake . && make -j4 && make test ) || { echo "Tarball build failed." ; exit 1 ; }

### Cleanup
#
rm -rf "$BUILDDIR"  # From test-builds
rm -rf "$TMPDIR"  # From tarball

### Print subsequent instructions
#
#
cat <<EOF
# Next steps for this release:
  git push --tags
  gpg -s -u $KEY_ID --detach --armor $TAR_FILE  # Sign the tarball
  # Upload tarball $TAR_FILE and the signature $TAR_FILE.asc
  # Announce via https://github.com/calamares/calamares/releases/new
  # SHA256: $SHA256
EOF

exit 0
