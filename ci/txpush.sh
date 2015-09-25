#!/bin/bash

# Make sure we can make Transifex and git operations from the Calamares Docker+Jenkins environment.
cp ~/jenkins-master/.transifexrc ~
cp ~/jenkins-master/.gitconfig ~
cp -R ~/jenkins-master/.ssh ~

cd "$WORKSPACE"
git config --global http.sslVerify false

export QT_SELECT=5
lupdate src/ -ts -no-obsolete lang/calamares_en.ts
tx push --force --source --no-interactive
