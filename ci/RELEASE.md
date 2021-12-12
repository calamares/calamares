# Calamares Release Process

<!-- SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
     SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
     SPDX-License-Identifier: GPL-3.0-or-later
-->

> Calamares releases are now rolling when-they-are-ready releases.
> Releases are made from *calamares* and tagged there. When, in future,
> LTS releases resume, these steps may be edited again.
>
> Most things are automated through the release script [RELEASE.sh](RELEASE.sh)

## (0) During a release cycle

* Fetch latest translations from Transifex. We only push / pull translations
  from *calamares* branch, so longer-lived branches (e.g. 3.1.x) don't get
  translation updates. This is to keep the translation workflow simple.
  The script automatically commits changes to the translations. It's ok
  to do this during a release cycle. Run `sh ci/txpull.sh`
  to fetch translations and commit the changes in one go.
* Push the strings to Transifex. From a checkout, run `ci/txpush.sh`
* Update the list of enabled translation languages in `CMakeLists.txt`.
  Check the [translation site][transifex] for the list of languages with
  fairly complete translations, or use `ci/txstats.py --edit` for an automated
  suggestion. If there are changes, commit them.

## (1) Preparation

* Double-check the *CALAMARES_VERSION* value at the top of `CMakeLists.txt`.
* Set *CALAMARES_RELEASE_MODE* to `ON` in `CMakeLists.txt`.
* Edit `CHANGES-*` and set the date of the release. Pick the right
  file for the release-stream.
* Commit both. This is usually done with commit-message
  *Changes: pre-release housekeeping*.

## (2) Release Preparation

* Make sure all tests pass.
  ```
    make
    make test
  ```
  Note that *all* means all-that-make-sense. The partition-manager tests need
  an additional environment variable to be set for some tests, which will
  destroy an attached disk. This is not always desirable. There are some
  sample config-files that are empty and which fail the config-tests.
  Note that the release script (see below) also runs the tests and
  will bail out if any fail.
* Make sure the translations are up-to-date. There is logic to check
  for changes in translations: a movable tag *translations* indicates
  when translations were last pushed, and the logic tries to enforce a
  week of latency between push-translations and a release, to allow
  translators to catch up. Run `ci/txcheck.sh` to confirm this.
  Run `ci/txcheck.sh --cleanup` to tidy up afterwards, and possibly pass
  `-T` to the release script to skip the translation-age check if you
  feel it is warranted.
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

## (3) Release

Follow the instructions printed by the release script.

* Push the tags.
* Create a new release on GitHub.
* Upload tarball and signature.
* Publish release article on `calamares.io`.
* Close associated milestone on GitHub if it's entirely done.
* Update topic on #calamares IRC channel.

## (4) Post-Release

* Bump the version number in `CMakeLists.txt` in *CALAMARES_VERSION*.
* Set *CALAMARES_RELEASE_MODE* back to `OFF`.
* Add a placeholder entry for the next release in `CHANGES-*` with date
  text *not released yet*. See the text below, "Placeholder Release".
  Add the placeholder to the right file for the release-stream.
* Commit and push that, usually with the message
  *Changes: post-release housekeeping*.

# Related Material

> This section isn't directly related to any specific release,
> but bears on all releases.

## GPG Key Maintainence

Calamares uses GPG Keys for signing the tarballs and some commits
(tags, mostly). Calamares uses the **maintainer's** personal GPG
key for this. This section details some GPG activities that the
maintainer should do with those keys.

- Signing sub-key. It's convenient to use a signing sub-key specifically
  for the signing of Calamares. To do so, add a key to the private key.
  It's recommended to use key expiry, and to update signing keys periodically.
  - Run `gpg -K` to find the key ID of your personal GPG secret key.
  - Run `gpg --edit-key <keyid>` to edit that personal GPG key.
  - In gpg edit-mode, use `addkey`, then pick a key type that is *sign-only*
    (e.g. type 4, *RSA (sign only)*), then pick a keysize (3072 seems ok
    as of 2020) and set a key expiry time, (e.g. in 18 months time).
  - After generation, the secret key information is printed again, now
    including the new signing subkey:
    ```
ssb  rsa3072/0xCFDDC96F12B1915C
     created: 2020-07-11  expires: 2022-01-02  usage: S
```
- Update the `RELEASE.sh` script with a new signing sub-key ID when a new
  one is generated. Also announce the change of signing sub-key (e.g. on
  the Calmares site or as part of a release announcement).
  - Send the updated key to keyservers with `gpg --send-keys <keyid>`
  - Optional: sanitize the keyring for use in development machines.
    Export the current subkeys of the primary key and keep **only** those
    secret keys around. There is documentation
    [here](https://blog.tinned-software.net/create-gnupg-key-with-sub-keys-to-sign-encrypt-authenticate/)
    but be careful.
  - Export the public key material with `gpg --export --armor <keyid>`,
    possibly also setting an output file.
  - Upload that public key to the relevant GitHub profile.
  - Upload that public key to the Calamares site.

## Placeholder Release Notes

```
# 3.2.XX (unreleased) #

This release contains contributions from (alphabetically by first name):
 - No external contributors yet

## Core ##
 - No core changes yet

## Modules ##
 - No module changes yet
```

