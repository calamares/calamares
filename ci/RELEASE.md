# Calamares Release Process

> Calamares releases are now rolling when-they-are-ready releases.
> Releases are made from *master* and tagged there. When, in future,
> LTS releases resume, these steps may be edited again.
>
> Most things are automated through the release script [RELEASE.sh](RELEASE.sh)

## (0) A week in advance

* Run [Coverity scan][coverity], fix what's relevant. The Coverity scan runs
  automatically once a week on master. The badge is displayed on the
  project front page and in the wiki.
* Build with clang -Weverything, fix what's relevant.
  ```
    rm -rf build ; mkdir build ; cd build
    CC=clang CXX=clang++ cmake .. && make
  ```
* Make sure all tests pass.
  ```
    make
    make test
  ```
  Note that *all* means all-that-make-sense. The partition-manager tests need
  an additional environment variable to be set for some tests, which will
  destroy an attached disk. This is not always desirable. There are some
  sample config-files that are empty and which fail the config-tests.
* Notify [translators][transifex]. In the dashboard there is an *Announcements*
  link that you can use to send a translation announcement. Note that regular
  use of `txpush.sh` will notify translators as well of any changes.

[coverity]: https://scan.coverity.com/projects/calamares-calamares?tab=overview
[transifex]: https://www.transifex.com/calamares/calamares/dashboard/


## (1) Preparation

* Pull latest translations from Transifex. We only push / pull translations
  from master, so longer-lived branches (e.g. 3.1.x) don't get translation
  updates. This is to keep the translation workflow simple. The script
  automatically commits changes to the translations.
  ```
    sh ci/txpull.sh
  ```
* Update the list of enabled translation languages in `CMakeLists.txt`.
  Check the [translation site][transifex] for the list of languages with
  fairly complete translations, or use `ci/txstats.py` for an automated
  suggestion. If there are changes, commit them.
* Push the changes.
* Drop the RC variable to 0 in `CMakeLists.txt`, *CALAMARES_VERSION_RC*.
* Check `README.md` and the
  [Coding Guide](https://github.com/calamares/calamares/wiki/Develop-Code),
  make sure it's all still
  relevant. Run `ci/calamaresstyle` to check the C++ code style.
  Run pycodestyle on recently-modified Python modules, fix what makes sense.
* Check defaults in `settings.conf` and other configuration files.
* Edit `CHANGES` and set the date of the release.
* Commit both. This is usually done with commit-message
  *Changes: pre-release housekeeping*.


## (2) Release Day

* Run the helper script `ci/RELEASE.sh` or follow steps below.
  The script checks:
  - for uncommitted local changes,
  - if translations are up-to-date and translators
    have had enough time to chase new strings,
  - that the build is successful (with gcc and clang, if available),
  - tests pass,
  - tarball can be created,
  - tarball can be signed.
  On success, it prints out a suitable signature- and SHA256 blurb
  for use in the release announcement.

### (2.1) Buld and Test

* Build with gcc. If available, build again with Clang and double-check
  any warnings Clang produces.
* Run the tests; `make test` in the build directory should have no
  failures (or if there are, know why they are there).

### (2.2) Tag

* `git tag -s v1.1.0` Make sure the signing key is known in GitHub, so that the
  tag is shown as a verified tag. Do not sign -rc tags.
  You can use `make show-version` in the build directory to get the right
  version number -- this will fail if you didn't follow step (1).

### (2.3) Tarball

* Create tarball: `git-archive-all -v calamares-1.1-rc1.tar.gz` or without
  the helper script,
  ```
    V=calamares-3.1.5
    git archive -o $V.tar.gz --prefix $V/ master
  ```
  Double check that the tarball matches the version number.
* Test tarball (e.g. unpack somewhere else and run the tests from step 0).


## (3) Housekeeping

* Generate MD5 and SHA256 checksums.
* Upload tarball.
* Announce on mailing list, notify packagers.
* Write release article.
* Publish tarball.
* Update download page.
* Publish release article on `calamares.io`.
* Publicize on social networks.
* Close associated milestone on GitHub if this is the actual release.
* Publish blog post.

## (4) Post-Release

* Bump the version number in `CMakeLists.txt` in the `project()` command.
* Set *CALAMARES_VERSION_RC* back to 1.
* Add a placeholder entry for the next release in `CHANGES` with date
  text *not released yet*.
* Commit and push that, usually with the message
  *Changes: post-release housekeeping*.

```
# 3.2.XX (unreleased) #

This release contains contributions from (alphabetically by first name):
 - No external contributors yet

## Core ##
 - No core changes yet

## Modules ##
 - No module changes yet
```
