<!-- SPDX-FileCopyrightText: no
     SPDX-License-Identifier: CC0-1.0
-->

# Calamares: Distribution-Independent Installer Framework
---------

[![GitHub release](https://img.shields.io/github/release/calamares/calamares.svg)](https://github.com/calamares/calamares/releases)
[![GitHub Build Status](https://img.shields.io/github/workflow/status/calamares/calamares/ci?label=GH%20build)](https://github.com/calamares/calamares/actions?query=workflow%3Aci)
[![Travis Build Status](https://travis-ci.org/calamares/calamares.svg?branch=calamares)](https://travis-ci.org/calamares/calamares)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/5389/badge.svg)](https://scan.coverity.com/projects/5389)
[![GitHub license](https://img.shields.io/github/license/calamares/calamares.svg)](https://github.com/calamares/calamares/blob/calamares/LICENSE)


| [Report a Bug](https://github.com/calamares/calamares/issues/new) | [Translate](https://www.transifex.com/projects/p/calamares/) | [Contribute](CONTRIBUTING.md) | [Freenode (IRC): #calamares](https://webchat.freenode.net/?channel=#calamares?nick=guest) | [Wiki](https://github.com/calamares/calamares/wiki) |
|:--:|:--:|:--:|:--:|:--:|


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

Calamares has some [generic user documentation](https://github.com/calamares/calamares/wiki/Use-Guide)
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
and an *extensions** repository ([Calamares extensions](https://github.com/calamares/calamares-extensions).

Contributions to code, modules, documentation, the wiki and the website are all welcome.
There is more information in the [CONTRIBUTING.md](CONTRIBUTING.md) file.

## Join the Conversation

GitHub Issues are **one** place for discussing Calamares if there are concrete
problems or a new feature to discuss.

Regular Calamares development chit-chat happens on old-school IRC
(no registration required). Responsiveness is best during the day
in Europe, but feel free to idle.

[![Visit our IRC channel](https://kiwiirc.com/buttons/webchat.freenode.net/calamares.png)](https://webchat.freenode.net/?channel=#calamares?nick=guest|)
