The Calamares release process
=============================

#### (0) A week in advance
* Run Coverity scan, fix what's relevant.
* Build with clang -Weverything, fix what's relevant.
* Make sure all tests pass.
* Notify translators.

#### (1) Preparation
* Check `README.md` and everything in `hacking`, make sure it's all still relevant.
* Update `CHANGELOG.md`.
* Update submodules.
* Pull latest translations from Transifex.
* Bump version in `CMakeLists.txt`, commit.

#### (2) Tarball
* Create tarball with `git-archive-all`.
* Test tarball.

#### (3) Tag
* `git tag -s v1.1.0`
* Generate MD5 and SHA1 checksums.
* Upload tarball.
* Announce on mailing list, notify packagers.
* Write release article.

#### (4) Release day
* Publish tarball.
* Update download page.
* Publish release article on `calamares.io`.
* Publicize on social networks.
* Update release date on JIRA.
* Publish blog post.
