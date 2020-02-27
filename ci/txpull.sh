#!/bin/sh
#
# Fetch the Transifex translations for Calamares and incorporate them
# into the source tree, adding commits of the different files.
#
# Run this (occasionally) at the top-level directory to get
# new translations. See also CMakeLists.txt and ci/txstats.py
# for update instructions.

### INITIAL SETUP
#
# This stuff needs to be done once; in a real CI environment where it
# runs regularly in a container, the setup needs to be done when
# creating the container.
#
#
# cp ~/jenkins-master/.transifexrc ~  # Transifex user settings
# cp ~/jenkins-master/.gitconfig ~    # Git config, user settings
# cp -R ~/jenkins-master/.ssh ~       # SSH, presumably for github
#
# cd "$WORKSPACE"
# git config --global http.sslVerify false

test -f "CMakeLists.txt" || { echo "! Not at Calamares top-level" ; exit 1 ; }
test -f ".tx/config" || { echo "! Not at Calamares top-level" ; exit 1 ; }
test -f "calamares.desktop" || { echo "! Not at Calamares top-level" ; exit 1 ; }


### FIND EXECUTABLES
#
#
XMLLINT=""
for _xmllint in xmllint
do
  $_xmllint --version > /dev/null 2>&1 && XMLLINT=$_xmllint
  test -n "$XMLLINT" && break
done
# XMLLINT is optional


### FETCH TRANSLATIONS
#
# Use Transifex client to get translations; this depends on the
# .tx/config file to locate files, and overwrites them in the
# filesystem with new (merged) translations.
export QT_SELECT=5
tx pull --force --source --all


### CLEANUP TRANSLATIONS
#
# Some languages have been deprecated. They may still exist in Transifex,
# so clean them up after pulling.
#
drop_language() {
  rm -rf lang/python/"$1" src/modules/dummypythonqt/lang/"$1" lang/calamares_"$1".ts
  grep -v "\\[$1]" calamares.desktop > calamares.desktop.new
  mv calamares.desktop.new calamares.desktop
}

drop_language es_ES
drop_language pl_PL

# Also fix the .desktop file, which has some fields removed by Transifex.
#
{ cat calamares.desktop.in ; grep "\\[[a-zA-Z_@]*]=" calamares.desktop ; } > calamares.desktop.new
mv calamares.desktop.new calamares.desktop

# And fixup the XML files like in txpush.sh
if test -n "$XMLLINT" ; then
  for TS_FILE in lang/calamares_*.ts
  do
    $XMLLINT --c14n11 "$TS_FILE" | { echo "<!DOCTYPE TS>" ; cat - ; } | $XMLLINT --format --encode utf-8 -o "$TS_FILE".new - && mv "$TS_FILE".new "$TS_FILE"
  done
fi


### COMMIT TRANSLATIONS
#
# Produce multiple commits (for the various parts of the i18n
# infrastructure used by Calamares) of the updated translations.
# Try to be a little smart about not committing trivial changes.

# Who is credited with these CI commits
AUTHOR="--author='Calamares CI <groot@kde.org>'"
# Message to put after the module name
BOILERPLATE="Automatic merge of Transifex translations"

git add --verbose lang/calamares*.ts
git commit "$AUTHOR" --message="i18n: [calamares] $BOILERPLATE" | true

rm -f lang/desktop*.desktop
awk '
	BEGIN {skip=0;}
	/^# Translations/ {skip=1;}
	{if (!skip || (length($0)>1 && $0 != "# Translations")) {
		skip=0; print $0;
	}}' < calamares.desktop > calamares.desktop.new
mv calamares.desktop.new calamares.desktop
git add --verbose calamares.desktop
git commit "$AUTHOR" --message="i18n: [desktop] $BOILERPLATE" | true

# Transifex updates the PO-Created timestamp also when nothing interesting
# has happened, so drop the files which have just 1 line changed (the
# PO-Created line). This applies only to modules which use po-files.
git diff --numstat src/modules | awk '($1==1 && $2==1){print $3}' | xargs git checkout --

# Go through the Python modules; those with a lang/ subdir have their
# own complete gettext-based setup.
for MODULE_DIR in $(find src/modules -maxdepth 1 -mindepth 1 -type d) ; do
  FILES=$(find "$MODULE_DIR" -name "*.py" -a -type f)
  if test -n "$FILES" ; then
    MODULE_NAME=$(basename ${MODULE_DIR})
    if [ -d ${MODULE_DIR}/lang ]; then
      # Convert PO files to MO files
      for POFILE in $(find ${MODULE_DIR} -name "*.po") ; do
        sed -i'' '/^"Content-Type/s/CHARSET/UTF-8/' $POFILE
        msgfmt -o ${POFILE%.po}.mo $POFILE
      done
      git add --verbose ${MODULE_DIR}/lang/*
      git commit "$AUTHOR" --message="i18n: [${MODULE_NAME}] $BOILERPLATE" | true
    fi
  fi
done

for POFILE in $(find lang -name "python.po") ; do
  sed -i'' '/^"Content-Type/s/CHARSET/UTF-8/' $POFILE
  msgfmt -o ${POFILE%.po}.mo $POFILE
done
git add --verbose lang/python*
git commit "$AUTHOR" --message="i18n: [python] $BOILERPLATE" | true

# git push --set-upstream origin master
