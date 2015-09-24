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
git commit --author='Calamares CI <teo@kde.org>' --message='Automatic merge of Transifex translations' | true
git push --set-upstream origin master
