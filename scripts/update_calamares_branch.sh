#! /usr/bin/env sh

SCRIPT_DIRECTORY="$(dirname -- "$(readlink -f -- "$0")")"
PROJECT_DIRECTORY="$(dirname -- "$SCRIPT_DIRECTORY")"
BUILD_DIRECTORY="$PROJECT_DIRECTORY"/build

NUMBER_OF_PROCESSORS="$(nproc)"

set -o xtrace

INITIAL_BRANCH="$(git branch --show-current)"

(
    cd "$PROJECT_DIRECTORY" \
    && git fetch --all \
    && {
        git checkout --track origin/calamares \
        || git checkout calamares
    } \
    && {
        git remote add upstream https://github.com/calamares/calamares \
        || {
            git reset --hard upstream/calamares \
            && git push --force origin calamares
        }
    }    
)

git checkout "$INITIAL_BRANCH"

set +o xtrace