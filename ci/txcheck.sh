#! /bin/sh

# Does the translation tag (from a previous txpush) exist?
# This assumes that the release host has also locally done
# a translations push, which works for the current development
# workflow .. but it could be improved by looking for one of
# the typical txpush log messages instead of the tag.
#
# Use --cleanup as an argument to clean things up.

tx_cleanup()
{
    # Cleanup artifacs of checking
    git worktree remove --force build-txcheck-head
    git worktree remove --force build-txcheck-prev
    git branch -D build-txcheck-head > /dev/null 2>&1
}

if test "x$1" = "x--cleanup" ; then
    tx_cleanup
    exit 0
fi
test -z "$1" || { echo "! Usage: txcheck.sh [--cleanup]" ; exit 1 ; }

if git describe translation > /dev/null 2>&1 ; then
	:
else
	echo "! No 'translation' tag exists for enforcing the string-freeze."
	exit 1
fi
# The tag exists, so now check that there's no unsaved changes
if test `git describe` = `git describe --dirty` ; then
	:
else
	echo "! There are local changes."
	exit 1
fi
# No unsaved changes; enforce a string freeze of one week
DATE_PREV=$( git log -1 translation --date=unix | sed -e '/^Date:/s+.*:++p' -e d )
DATE_HEAD=$( date +%s -d "1 week ago" )
test "$DATE_PREV" -le "$DATE_HEAD" || { echo "! Translation tag has not aged enough." ; git log -1 translation ; exit 1 ; }

# Tag is good, do real work of checking strings: collect names of relevant files
test -f ".tx/config" || { echo "! No Transifex configuration is present." ; exit 1 ; }
# Print part after = for each source_file line and delete all the rest
TX_FILE_LIST=$( sed -e '/^source_file/s+.*=++p' -e d .tx/config )
for f in $TX_FILE_LIST ; do
	test -f $f || { echo "! Translation file '$f' does not exist." ; exit 1 ; }
done

# The state of translations
tx_sum()
{
	WORKTREE_NAME="$1"
	WORKTREE_TAG="$2"

	git worktree add $WORKTREE_NAME $WORKTREE_TAG > /dev/null 2>&1 || { echo "! Could not create worktree." ; exit 1 ; }
	( cd $WORKTREE_NAME && sh ci/txpush.sh --no-tx ) > /dev/null 2>&1 || { echo "! Could not re-create translations." ; exit 1 ; }
	( cd $WORKTREE_NAME && sed -i'' -e '/<location filename/d' $TX_FILE_LIST )
	_SUM=$( cd $WORKTREE_NAME && cat $TX_FILE_LIST | sha256sum )
	echo "$_SUM"
}

# Check from the translation tag as well
HEAD_SUM=`tx_sum build-txcheck-head ""`
PREV_SUM=`tx_sum build-txcheck-prev translation`

# An error message will have come from the shell function
test -d build-txcheck-head || { echo "$HEAD_SUM" ; exit 1 ; }
test -d build-txcheck-prev || { echo "$PREV_SUM" ; exit 1 ; }

if test "$HEAD_SUM" = "$PREV_SUM" ; then
	:
else
	echo "! Translations have changed."
	for f in $TX_FILE_LIST ; do
		echo "! $f"
		diff -u build-txcheck-prev/$f build-txcheck-head/$f
	done
	exit 1
fi

tx_cleanup

exit 0
