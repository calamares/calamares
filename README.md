<!-- SPDX-FileCopyrightText: no
     SPDX-License-Identifier: CC0-1.0
-->

# Calamares: Distribution-Independent Installer Framework
---------

[![Current issue](https://img.shields.io/badge/issue-in_progress-FE9B48)](https://github.com/calamares/calamares/labels/hacking%3A%20in-progress)
[![GitHub release](https://img.shields.io/github/release/calamares/calamares.svg)](https://github.com/calamares/calamares/releases)
[![GitHub Build Status](https://img.shields.io/github/workflow/status/calamares/calamares/ci?label=GH%20build)](https://github.com/calamares/calamares/actions?query=workflow%3Aci)
[![GitHub license](https://img.shields.io/github/license/calamares/calamares.svg)](https://github.com/calamares/calamares/blob/calamares/LICENSE)


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

* [![Join us on Matrix](https://img.shields.io/badge/Matrix-%23calamares:kde.org-blue)](https://webchat.kde.org/#/room/%23calamares:kde.org)
* [![Chat on IRC](https://img.shields.io/badge/IRC-Libera.Chat%20%23calamares-green)](https://kiwiirc.com/client/irc.libera.chat/#calamares)
