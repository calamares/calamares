<!-- SPDX-FileCopyrightText: no
     SPDX-License-Identifier: CC0-1.0
-->

# Contributing to Calamares

Welcome to Calamares! We're happy that you would like to add
something to Calamares. This contribution guide should help you
get started. The guide is not exhaustive: most of it points
to other documents that you will need.


## Code of Conduct

The Calamares community -- of developers, translators, and downstream (distro) users --
aims to be courteous, professional, and inclusive. Harrassment, discriminatory
statements and abuse are not tolerated. In general, we apply the
[KDE Code of Conduct](https://www.kde.org/code-of-conduct/) and the
[GNOME Code of Conduct](https://wiki.gnome.org/Foundation/CodeOfConduct) (the
rules of decent behavior in both communities are pretty much the same).

> See the [CoC section on the wiki](https://github.com/calamares/calamares/wiki#code-of-conduct)
> for a longer text. To report a problem, please contact the maintainer,
> Adriaan de Groot, or the KDE Community Working Group.


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


## General Guidelines

Pull Requests are welcome!

It is often a good idea to start a Pull Request early, with just work-in-progress,
so that the overall approach can be discussed before you put a lot of work
into something. Or file an issue describing what you would like to do.

If you are writing code, stick to the existing coding style and apply
the coding-style tool before you commit. It's not my favorite style,
but at least all of Calamares is consistent and the tool helps it
stay that way.

If you are writing documentation, use *en_US* spelling.

If you are doing cool stuff, let us know (on IRC or through issues).

**Do** fork Calamares to try new things, **don't** keep your fork to
yourself, **do** upstream things as much as you can. When you make cool
new things, it's best for the whole Calamares-using-community
to build new things that are configurable and applicable to other
distributions than your own. So keep other folk in mind. There is
also the [extensions](https://github.com/calamares/calamares-extensions)
repository for somewhat-more-specialized modules and examples.


## Building Calamares

Up to date
[building-Calamares](https://github.com/calamares/calamares/wiki/Develop-Guide)
instructions are on the wiki.

### Dependencies

Main:
* Compiler with C++17 support
* CMake >= 3.16
* Qt >= 5.15
* yaml-cpp >= 0.5.1
* Python >= 3.6 (required for some modules)
* Boost.Python >= 1.67.0 (required for some modules)
* KDE extra-cmake-modules >= 5.18 (recommended; required for some modules;
  required for some tests)
* KDE Frameworks KCoreAddons (>= 5.58 recommended)

Individual modules may have their own requirements;
these are listed in CMake output.
Particular requirements (not complete):

* *fsresizer* KPMCore >= 3.3 (>= 4.2 recommended)
* *partition* KPMCore >= 3.3 (>= 4.2 recommended)
* *users* LibPWQuality (optional)


## Configuring and Deploying Calamares

[Deployment](https://github.com/calamares/calamares/wiki/Deploy-Guide)
instructions are on the wiki.


## Translating Calamares

Calamares translations are done on Transifex.
The [translator's guide](https://github.com/calamares/calamares/wiki/Translate-Guide)
on the wiki explains how to get involved there.


## Testing Calamares

There is a [testing guide](https://github.com/calamares/calamares/wiki/Test-Guide)
on the wiki. It is possible to test most parts of Calamares in isolation,
but the real proof of the pudding comes with an actual installation
of *some* distro using Calamares.

The UI components should get some specific usability testing instructions soon.

