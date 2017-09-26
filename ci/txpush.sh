#!/bin/sh
#
# Fetch the Transifex translations for Calamares and incorporate them
# into the source tree, adding commits of the different files.

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

if test "x$1" = "x--no-tx" ; then
  tx() {
    echo "Skipped tx $*"
  }
fi

### CREATE TRANSLATIONS
#
# Use local tools (depending on type of source) to create translation
# sources, then push to Transifex

export QT_SELECT=5
lupdate src/ -ts -no-obsolete lang/calamares_en.ts

tx push --source --no-interactive -r calamares.calamares-master
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
