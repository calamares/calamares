<!-- SPDX-FileCopyrightText: no
     SPDX-License-Identifier: CC0-1.0
-->
# Calamares Core for RebornOS

> **Note**: This project should not carry any RebornOS-specific configuration except for the installer packaging files (PKGBUILD, build scripts), icons, and launch scripts. Use the [calamares-configuration](https://github.com/RebornOS-Developers/calamares-configuration) project for other RebornOS-specific configuration.

This is a fork of the [Calamares project](https://github.com/calamares/calamares). 

## Cloning

In order to download the source code to your local computer for testing, or for development, you can clone from the remote repository using either SSH, or HTTPS. Below are instructions on how to do so using Gitlab hosted code as remote.

### HTTPS

```bash
git clone https://github.com/RebornOS-Developers/calamares-core.git 
```

OR

### SSH

```bash
git clone git@github.com:RebornOS-Developers/calamares-core.git
```

## Local development

### (Optional) Clean-up old packages and directories

You usually do not need to do this unless the build fails.
The build process following cleanup is usually slow because it has to start from scratch. Change to the project directory (`cd calamares-core`) and run
```bash
sh scripts/clean.sh
```

### 1. Build

The below script will build the ISO image (and install any prerequisites). Change to the project directory (`cd calamares-core`) and run th below. You can specify any commandline parameters to `makepkg` by passing it to the below script

```bash
sh scripts/build.sh
```

### 2. Run
Change to the project directory (`cd calamares-core`) and run the below. You can specify any commandline parameters to `calamares` by passing it to the below script

```bash
sh scripts/run.sh
```

## Packaging

Change to the project directory (`cd calamares-core`) and run any of the below scripts:
- `sh packaging/setup.sh <MODE>`: Builds and installs a package
- `sh packaging/build-package.sh <MODE>`: Just builds a package without installing it locally
- `sh packaging/install-package.sh <MODE>`: Just installs a package locally, except if no built package is detected, a package is built.
where `<MODE>` can be one of the below
     1. `local`: Selects *calamares-core-local* from the local project that you have cloned already.
     2. `git`: Selects *calamares-core-git* from the latest git commit.
     3. `stable`: Selects *calamares-core* from the git tag corresponding to the [`pkgver` specified in the PKGBUILD](https://github.com/RebornOS-Developers/calamares-core/blob/main/packaging/calamares-core/PKGBUILD#L4). If `pkgver=3.3.0_alpha2_2`, then the git tag `v3.3.0_alpha2_2` is used for packaging. 
     
> **Note**: Any additional parameters passed to the above scripts are automatically sent to `makepkg` or `pacman` (whichever is applicable).

## Updating

To keep this project in sync with the upstream Calamares source, please follow the below steps. Change to the project directory (`cd calamares-core`) before continuing...

1. **Fetch changes from the upstream Github source**: The below script clones the [upstream Calamares source](https://github.com/calamares/calamares) to the `calamares` branch (force overwrites it).
```sh
sh scripts/update-calamares-branch.sh
```

2. **Merge upstream changes**
```sh
git checkout main

git merge calamares
```

3. **Manually handle merge conflicts**: Follow [this guide for commandline operations](https://www.atlassian.com/git/tutorials/using-branches/merge-conflicts) or [this guide if you are using *Visual Studio Code*](https://code.visualstudio.com/docs/sourcecontrol/overview#_merge-conflicts).

4. **Push updates back to the project**: After all the merge conflicts are handled and you stage all the changes, you are ready to push the updates with `git push`.

---

# Calamares: Distribution-Independent Installer Framework
---------

[![Current issue](https://img.shields.io/badge/issue-in_progress-FE9B48)](https://github.com/calamares/calamares/labels/hacking%3A%20in-progress)
[![GitHub release](https://img.shields.io/github/release/calamares/calamares.svg)](https://github.com/calamares/calamares/releases)
[![GitHub Build Status](https://img.shields.io/github/workflow/status/calamares/calamares/ci?label=GH%20build)](https://github.com/calamares/calamares/actions?query=workflow%3Aci)
[![GitHub license](https://img.shields.io/github/license/calamares/calamares.svg)](https://github.com/calamares/calamares/blob/calamares/LICENSES/GPL-3.0-or-later.txt)


| [Report a Bug](https://github.com/calamares/calamares/issues/new) | [Translate](https://www.transifex.com/projects/p/calamares/) | [Contribute](CONTRIBUTING.md) | [Matrix: #calamares:kde.org](https://webchat.kde.org/#/room/%23calamares:kde.org) | [IRC: Libera.Chat #calamares](https://kiwiirc.com/client/irc.libera.chat/#calamares) | [Wiki](https://github.com/calamares/calamares/wiki) |
|:--:|:--:|:--:|:--:|:--:|:--:|


> Calamares is a distribution-independent system installer, with an advanced partitioning
> feature for both manual and automated partitioning operations. Calamares is designed to
> be customizable by distribution maintainers without need for cumbersome patching,
> thanks to third party branding and external modules support.

## Target Audience

Calamares is a Linux installer; users who install Linux on a computer will hopefully
use it just **once**, to install their Linux distribution. Calamares is not
a "ready to use" application: distributions apply a huge amount of customisation
and configuration to Calamares, and the target audience for this repository
is those distributions, and the people who make those Linux distro's.

Calamares has some [generic user documentation](https://calamares.io/docs/users-guide/)
for end-users, but most of what we have is for distro developers.

## Getting Calamares

Clone Calamares from GitHub. The default branch is called *calamares*.

```
git clone https://github.com/calamares/calamares.git
```

Calamares is a KDE-Frameworks and Qt-based, C++17, CMake-built application.
The dependencies are explained in [CONTRIBUTING.md](CONTRIBUTING.md).

## Contributing to Calamares

Calamares welcomes PRs. New issues are welcome, too.
There are both the Calamares **core** repository (this one),
and an **extensions** repository ([Calamares extensions](https://github.com/calamares/calamares-extensions)).

Contributions to code, modules, documentation, the wiki and the website are all welcome.
There is more information in the [CONTRIBUTING.md](CONTRIBUTING.md) file.

## Join the Conversation

GitHub Issues are **one** place for discussing Calamares if there are concrete
problems or a new feature to discuss.

Regular Calamares development chit-chat happens in a [Matrix](https://matrix.org/)
room, `#calamares:kde.org`. The conversation is bridged with IRC
on [Libera.Chat](https://libera.chat/).
Responsiveness is best during the day
in Europe, but feel free to idle. If you use IRC, **DO NOT** ask-and-leave. Keep
that chat window open because it can easily take a few hours for
someone to notice a message.
Matrix is persistent, and we'll see your message eventually.

* [![Join us on Matrix](https://img.shields.io/badge/Matrix-%23calamares:kde.org-blue)](https://webchat.kde.org/#/room/%23calamares:kde.org) (needs a Matrix account)
* [![Chat on IRC](https://img.shields.io/badge/IRC-Libera.Chat%20%23calamares-green)](https://kiwiirc.com/client/irc.libera.chat/#calamares) (IRC supports guest accounts)
