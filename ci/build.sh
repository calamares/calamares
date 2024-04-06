#! /bin/sh
#
# Generic build. The build is driven by environment variables:
# - SRCDIR      (e.g. /src)
# - BUILDDIR    (e.g. /build)
# - CMAKE_ARGS  (e.g. "-DWITH_QT6=ON -DCMAKE_BUILD_TYPE=Debug")
#
# If SRCDIR is not set, it is assumed to be the directory above
# wherever this script is being run from (this script is in ci/).
#
# If BUILDDIR is not set, and /build exists (e.g. in the recommended
# Docker setup) then /build is used.
#
# If CMAKE_ARGS is not set, but the script is given an argument
# that exists as a workflow (e.g. "nightly-opensuse-qt6" or
# "nightly-debian.yml") and yq is installed, then the CMAKE_ARGS
# are extracted from that workflow file.
#
# Summary, pick one:
# - set environment variables, run "build.sh"
# - set no variables, run "build.sh <workflow-name>"

if test -z "$SRCDIR" ; then
	_d=$(dirname "$0" )
	_d=$(dirname "$_d" )
	test -f "$_d/CMakeLists.txt" && SRCDIR="$_d"
fi
if test -z "$BUILDDIR" ; then
	test -d "/build" && BUILDDIR=/build
fi
if test -z "$CMAKE_ARGS" -a -n "$1" ; then
	_d="$SRCDIR/.github/workflows/$1"
	test -f "$_d" || _d="$SRCDIR/.github/workflows/$1.yml"
	test -f "$_d" || { echo "! No workflow $1" ; exit 1 ; }

	if test -x "$(which yq)" ; then
		CMAKE_ARGS=$(yq ".env.CMAKE_ARGS" "$_d")
	else
		CMAKE_ARGS=$(python3 -c 'import yaml ; f=open("'$_d'","r"); print(yaml.safe_load(f)["env"]["CMAKE_ARGS"]);')
	fi

fi

# Sanity check
test -n "$BUILDDIR" || { echo "! \$BUILDDIR not set" ; exit 1 ; }
test -n "$SRCDIR" || { echo "! \$SRCDIR not set" ; exit 1 ; }
mkdir -p "$BUILDDIR"
test -f "$SRCDIR/CMakeLists.txt" || { echo "! Missing $SRCDIR/CMakeLists.txt" ; exit 1 ; }

BUILD_MESSAGE="No commit info"
test -n "$GIT_HASH" && BUILD_MESSAGE=$( git log -1 --abbrev-commit --pretty=oneline --no-decorate "$GIT_HASH" )

echo "::" ; echo ":: $BUILD_MESSAGE" ; echo "::"

cmake -S "$SRCDIR" -B "$BUILDDIR" -G Ninja $CMAKE_ARGS || exit 1
ninja -C "$BUILDDIR" || exit 1
ninja -C "$BUILDDIR" install || exit 1

echo "::" ; echo ":: $BUILD_MESSAGE" ; echo "::"
