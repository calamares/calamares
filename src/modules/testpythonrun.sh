#! /bin/sh

### Command-line validation
#
#
SRCDIR=$( dirname "$0" )
test -d "$SRCDIR" || { echo "! Can't find source directory." ; exit 1 ; }

MODULE="$1"
test -n "$MODULE" || { echo "! Usage: $0 <module>" ; exit 1 ; }

### Run-time validation
#
# .. switch SRCDIR to the module that has been found
BINDIR="$SRCDIR"  # Keep original SRCDIR
SRCDIR="$SRCDIR/$MODULE"
XSRCDIR="src/modules/$MODULE"  # In builddir
TESTDIR="$SRCDIR/tests"

test -x "$BINDIR/testmodule.py" || { echo "! No support script $BINDIR/testmodule.py" ; exit 1 ; }
test -d "$SRCDIR" || { echo "! Source $SRCDIR is not a directory." ; exit 1 ; }
test -f "$TESTDIR/1.global" || { echo "! Source $SRCDIR has no tests." ; exit 1 ; }

test -f "libcalamares.so" || { echo "! Run the tests from the build-directory." ; exit 1 ; }
test -d "$XSRCDIR" || { echo "! No module directory $XSRCDIR in build-dir." ; exit 1 ; }

### Python setup
#
#
export PYTHONPATH=".:$PYTHONPATH"
PYTHON=$( which python3 2> /dev/null )
if test -z "$PYTHON" ; then
	PYTHON=$( which python 2> /dev/null )
fi
test -x "$PYTHON" || { echo "! No suitable Python executable found." ; exit 1 ; }

### Test-execution
#
#
C=0
while true ; do
	# Might use shell arithmetic, but need other shebang then
	C=$( expr "$C" + 1 )

	G_CFG="$TESTDIR/$C.global"
	J_CFG="$TESTDIR/$C.job"

	test -f "$G_CFG" || break
	if test -f "$J_CFG" ; then
		$PYTHON "$BINDIR/testmodule.py" "$XSRCDIR" "$G_CFG" "$J_CFG"
	else
		$PYTHON "$BINDIR/testmodule.py" "$XSRCDIR" "$G_CFG"
	fi
done

