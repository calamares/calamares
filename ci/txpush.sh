#!/bin/sh

### LICENSE
# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2015-2016 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017-2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
#   This file is Free Software: you can redistribute it and/or modify
#   it under the terms of the 2-clause BSD License.
#
### END LICENSE

### USAGE
#
# Extract translations from Calamares source and send them
# to Transifex. Also (forcibly) updates the git "translation"
# tag to document that source texts were updated and sent;
# this is used by txcheck.sh to ensure that there's enough
# time between updates and releases, and that strings don't
# change between updates and releases.
#
# Run this at the top-level.
#
# Use the --no-tx option to do the extraction, but not the
# pushing-to-Transifex part. This can be useful to check for
# new strings or when testing the tools themselves.
#
### END USAGE

### SANITY CHECKING
#
# The script needs a .tx/config to talk to the Transifex server;
# it also checks that it is run from the top-level of a Calamares
# checkout. In order to use the system overall, you'll also need:
#  - ~/.gitconfig (For the git commits this does)
#  - ~/.transifexrc (Password token for Transifex)
#  - ~/.ssh (For git commits)
#
test -f "CMakeLists.txt" || { echo "! Not at Calamares top-level" ; exit 1 ; }
test -f ".tx/config" || { echo "! Not at Calamares top-level" ; exit 1 ; }
test -f "calamares.desktop" || { echo "! Not at Calamares top-level" ; exit 1 ; }

if test "x$1" = "x--no-tx" ; then
	# tx is the transifex command -- eat its arguments and do nothing
	tx() {
		echo "Skipped tx $*"
	}
	# txtag is used to tag in git to measure changes -- skip it too
	txtag() {
		echo "Skipped tx tagging."
	}
else
	# tx is the regular transifex command
	# txtag is used to tag in git to measure changes
	txtag() {
		git tag -f translation
		git push --force origin translation
	}
fi


### FIND EXECUTABLES
#
#
LUPDATE=""
for _lupdate in lupdate-qt5 lupdate
do
	export QT_SELECT=5
	$_lupdate -version > /dev/null 2>&1 || export QT_SELECT=qt5
	$_lupdate -version > /dev/null 2>&1 && LUPDATE=$_lupdate
	test -n "$LUPDATE" && break
done
test -n "$LUPDATE" || { echo "! No working lupdate" ; lupdate -version ; exit 1 ; }

XMLLINT=""
for _xmllint in xmllint
do
	$_xmllint --version > /dev/null 2>&1 && XMLLINT=$_xmllint
	test -n "$XMLLINT" && break
done
# XMLLINT is optional


### CREATE TRANSLATIONS
#
# Use local tools (depending on type of source) to create translation
# sources, then push to Transifex

# Don't pull branding translations in,
# those are done separately.
_srcdirs="src/calamares src/libcalamares src/libcalamaresui src/modules src/qml"
$LUPDATE -no-obsolete $_srcdirs -ts lang/calamares_en.ts
# Non-Transifex special-cases
#
# - timezone names can be translated, but that's 700+ strings I don't want
#   to inflict on translators normally
# - keyboard layouts can be translated, but that's 767 strings
#
# For both of these, the language / translation only needs to be updated
# when the source data is updated, which is very very rarely.
# $LUPDATE -no-obsolete -extensions cxxtr src/libcalamares/locale -ts lang/tz_en.ts
# $LUPDATE -no-obsolete -extensions cxxtr src/modules/keyboard -ts lang/kb_en.ts

if test -n "$XMLLINT" ; then
	TS_FILE="lang/calamares_en.ts"
	$XMLLINT --c14n11 "$TS_FILE" | { echo "<!DOCTYPE TS>" ; cat - ; } | $XMLLINT --format --encode utf-8 -o "$TS_FILE".new - && mv "$TS_FILE".new "$TS_FILE"
fi

tx push --source --no-interactive -r calamares.calamares
tx push --source --no-interactive -r calamares.fdo


### PYTHON MODULES
#
# The Python tooling depends on the underlying distro to provide
# gettext, and handles two cases:
#
# - python modules with their own lang/ subdir, for larger translations
# - python modules without lang/, which use one shared catalog
#

PYGETTEXT="xgettext --keyword=_n:1,2 -L python"

SHARED_PYTHON=""
for MODULE_DIR in $(find src/modules -maxdepth 1 -mindepth 1 -type d) ; do
	FILES=$(find "$MODULE_DIR" -name "*.py" -a -type f)
	if test -n "$FILES" ; then
		MODULE_NAME=$(basename ${MODULE_DIR})
		if [ -d ${MODULE_DIR}/lang ]; then
			${PYGETTEXT} -p ${MODULE_DIR}/lang -d ${MODULE_NAME} -o ${MODULE_NAME}.pot ${MODULE_DIR}/*.py
			POTFILE="${MODULE_DIR}/lang/${MODULE_NAME}.pot"
			if [ -f "$POTFILE" ]; then
				sed -i'' '/^"Content-Type/s/CHARSET/UTF-8/' "$POTFILE"
				tx set -r calamares.${MODULE_NAME} --source -l en "$POTFILE"
				tx push --source --no-interactive -r calamares.${MODULE_NAME}
			fi
		else
			SHARED_PYTHON="$SHARED_PYTHON $FILES"
		fi
	fi
done

if test -n "$SHARED_PYTHON" ; then
	${PYGETTEXT} -p lang -d python -o python.pot $SHARED_PYTHON
	POTFILE="lang/python.pot"
	sed -i'' '/^"Content-Type/s/CHARSET/UTF-8/' "$POTFILE"
	tx set -r calamares.python --source -l en "$POTFILE"
	tx push --source --no-interactive -r calamares.python
fi

txtag
exit 0
