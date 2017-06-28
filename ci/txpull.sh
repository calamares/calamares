#!/bin/bash

# Make sure we can make Transifex and git operations from the Calamares Docker+Jenkins environment.
cp ~/jenkins-master/.transifexrc ~
cp ~/jenkins-master/.gitconfig ~
cp -R ~/jenkins-master/.ssh ~

cd "$WORKSPACE"
git config --global http.sslVerify false

export QT_SELECT=5
tx pull --force --source --all
git add --verbose lang/calamares*.ts
git commit --author='Calamares CI <groot@kde.org>' --message='[core] Automatic merge of Transifex translations' | true

for MODULE_DIR in `find src/modules -maxdepth 1 -mindepth 1 -type d`; do
  FILES=(${MODULE_DIR}/*.py)
  if [ ${#FILES[@]} -gt 0 ]; then
    MODULE_NAME=$(basename ${MODULE_DIR})
    if [ -d ${MODULE_DIR}/lang ]; then
      # Convert PO files to MO files
      for POFILE in `find . -name "*.po"` ; do
        msgfmt -o ${POFILE/.po/.mo} $POFILE
      done
      git add --verbose ${MODULE_DIR}/lang/*
      git commit --author='Calamares CI <groot@kde.org>' --message="[${MODULE_NAME}] Automatic merge of Transifex translations" | true
    fi
  fi
done

git push --set-upstream origin master
