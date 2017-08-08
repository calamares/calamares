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

git add --verbose lang/desktop*.desktop calamares.desktop
git commit --author='Calamares CI <groot@kde.rg>' --message='[desktop] Automatic merge of Transifex translations' | true

# Transifex updates the PO-Created timestamp also when nothing interesting
# has happened, so drop the files which have just 1 line changed (the
# PO-Created line). This applies only to modules which use po-files.
git diff --numstat src/modules | awk '($1==1 && $2==1){print $3}' | xargs git checkout --

for MODULE_DIR in `find src/modules -maxdepth 1 -mindepth 1 -type d`; do
  FILES=(${MODULE_DIR}/*.py)
  if [ ${#FILES[@]} -gt 0 ]; then
    MODULE_NAME=$(basename ${MODULE_DIR})
    if [ -d ${MODULE_DIR}/lang ]; then
      # Convert PO files to MO files
      for POFILE in `find ${MODULE_DIR} -name "*.po"` ; do
        msgfmt -o ${POFILE/.po/.mo} $POFILE
      done
      git add --verbose ${MODULE_DIR}/lang/*
      git commit --author='Calamares CI <groot@kde.org>' --message="[${MODULE_NAME}] Automatic merge of Transifex translations" | true
    fi
  fi
done

# git push --set-upstream origin master
