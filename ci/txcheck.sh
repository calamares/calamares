#! /bin/sh

# Does the translation tag (from a previous txpush) exist?
# This assumes that the release host has also locally done
# a translations push, which works for the current development
# workflow .. but it could be improved by looking for one of
# the typical txpush log messages instead of the tag.
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
# No unsaved changes, collect names of relevant files
test -f ".tx/config" || { echo "! No Transifex configuration is present." ; exit 1 ; }
# Print part after = for each source_file line and delete all the rest
TX_FILE_LIST=$( sed -e '/^source_file/s+.*=++p' -e d .tx/config )
for f in $TX_FILE_LIST ; do
	test -f $f || { echo "! Translation file '$f' does not exist." ; exit 1 ; }
done

# The state of translations here
HEAD_SUM=$( cat $TX_FILE_LIST | sha256sum )

# Check from the translation tag as well
git worktree add build-txcheck translation
( cd build-txcheck && sh ci/txpush.sh --no-tx ) || { echo "! Could not re-create translations." ; exit 1 ; }
PREV_SUM=$( cd build-txcheck && cat $TX_FILE_LIST | sha256sum )

if test "$HEAD_SUM" = "$PREV_SUM" ; then
	:
else
	echo "! Translations have changed."
	for f in $TX_FILE_LIST ; do
		echo "! $f"
		diff -u build-txcheck/$f $f
	done
	exit 1
fi

exit 0
