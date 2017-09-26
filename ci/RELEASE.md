The Calamares release process
=============================

#### (0) A week in advance
* Run [Coverity scan][coverity], fix what's relevant. The Coverity scan runs
  automatically once a week on master.
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
  destroy an attached disk. This is not always desirable.
* Notify [translators][transifex]. In the dashboard there is an *Announcements*
  link that you can use to send a translation announcement.

[coverity]: https://scan.coverity.com/projects/calamares-calamares?tab=overview
[transifex]: https://www.transifex.com/calamares/calamares/dashboard/

#### (1) Preparation

* Bump version in `CMakeLists.txt`, *CALAMARES_VERSION* variables, and set
  RC to a non-zero value (e.g. doing -rc1, -rc2, ...). Push that.
* Check `README.md` and everything in `hacking`, make sure it's all still
  relevant. Run `hacking/calamaresstyle` to check the C++ code style.
  Python code is checked as part of the Travis CI builds.
* Check defaults in `settings.conf` and other configuration files.
* Pull latest translations from Transifex. This is done nightly on Jenkins,
  so a manual pull is rarely necessary.
* Update the list of enabled translation languages in `CMakeLists.txt`.
  Check the [translation site][transifex] for the list of languages with
  fairly complete translations.

#### (2) Tarball
* Create tarball: `git-archive-all -v calamares-1.1-rc1.tar.gz` or without
  the helper script,
  ```
    V=calamares-3.1.5
    git archive -o $V.tar.gz --prefix $V/ master
  ```
  Double check that the tarball matches the version number.
* Test tarball.

#### (3) Tag
* Set RC to zero in `CMakeLists.txt` if this is the actual release.
* `git tag -s v1.1.0` Make sure the signing key is known in GitHub, so that the
  tag is shown as a verified tag. Do not sign -rc tags.
* Generate MD5 and SHA256 checksums.
* Upload tarball.
* Announce on mailing list, notify packagers.
* Write release article.

#### (4) Release day
* Publish tarball.
* Update download page.
* Publish release article on `calamares.io`.
* Publicize on social networks.
* Close associated milestone on GitHub if this is the actual release.
* Publish blog post.
