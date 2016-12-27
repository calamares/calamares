#!/bin/bash

# Make sure we can make Transifex and git operations from the Calamares Docker+Jenkins environment.
cp ~/jenkins-master/.transifexrc ~
cp ~/jenkins-master/.gitconfig ~
cp -R ~/jenkins-master/.ssh ~

cd "$WORKSPACE"
git config --global http.sslVerify false

export QT_SELECT=5
lupdate src/ -ts -no-obsolete lang/calamares_en.ts

# Arch
# PYGETTEXT=/usr/lib/python3.5/Tools/i18n/pygettext.py

# Ubuntu
PYGETTEXT=pygettext3

for MODULE_DIR in `find src/modules -maxdepth 1 -mindepth 1 -type d`; do
  FILES=(${MODULE_DIR}/*.py)
  if [ ${#FILES[@]} -gt 0 ]; then
    MODULE_NAME=$(basename ${MODULE_DIR})
    if [ -d ${MODULE_DIR}/lang ]; then
      ${PYGETTEXT} -p ${MODULE_DIR}/lang -d ${MODULE_NAME} ${MODULE_DIR}/*.py
      if [ -f ${MODULE_DIR}/lang/${MODULE_NAME}.pot ]; then
        tx set -r calamares.${MODULE_NAME} --source -l en ${MODULE_DIR}/lang/${MODULE_NAME}.pot
        tx push --force --source --no-interactive -r calamares.${MODULE_NAME}
      fi
    fi
  fi
done

tx push --force --source --no-interactive -r calamares.calamares-master
