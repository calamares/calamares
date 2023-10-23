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
Issues are not a help channel.
Visit Matrix for help with configuration or compilation.

Regular Calamares development chit-chat happens in a [Matrix](https://matrix.org/)
room, `#calamares:kde.org`. Responsiveness is best during the day
in Europe, but feel free to idle.
Matrix is persistent, and we'll see your message eventually.

**Note:** You need an account to access Matrix. It doesn't have to be a KDE account,
it can be on any Matrix homeserver.

* [![Join us on Matrix](https://img.shields.io/badge/Matrix-%23calamares:kde.org-blue)](https://webchat.kde.org/#/room/%23calamares:kde.org)


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

If you are doing cool stuff, let us know (on Matrix or through issues).

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

### Simple Build in Docker

You may have success with the Docker images that the CI system uses.
Pick one (or more) of these images which are also used in CI:
- `docker pull docker://opensuse/tumbleweed`
- `docker pull kdeneon/plasma:user`
- `docker pull fedora:38`

Then start a container with the right image, from the root of Calamares
source checkout. Start with this command and substitute `opensuse/tumbleweed`
or `kdeneon/plasma:user` for the `$IMAGE` part.

```
docker run -ti \
    --tmpfs /build:rw,exec \
    --user 0:0 \
    -e DISPLAY=:0 \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v .:/src \
    $IMAGE \
    bash
```

This starts a container with the chosen image with a temporary build
directory in `/build` and the Calamaressources mounted as `/src`.

Run the script to install dependencies: you could use `deploycala.py`
or one of the shell scripts in `ci/` to install the right
dependencies for the image (in this example, for openSUSE and Qt6).
- `cd /src`
- `./ci/deps-opensuse-qt6.sh`

Then run CMake (add any CMake options you like at the end) and ninja.
There is a script `ci/build.sh` that does this, too (without options).
- `cmake -S /src -B /build -G Ninja`
- `ninja -C /build`

To run Calamares inside the container, or e.g. `loadmodule` to test
individual modules, you may need to configure X authentication; a
simple and insecure way of doing that is to run `xhost +` in the host
environment of the Docker containers.

### Dependencies for Calamares 3.3

> The dependencies for Calamares 3.3 reflect "resonably current"
> software as of September 2023. For Calamares 3.2 dependencies,
> which are 2017-era, see the `CONTRIBUTING` file in that branch.

Main:
* Compiler with C++17 support
* CMake >= 3.16
* yaml-cpp >= 0.5.1
* Qt >= 5.15 or Qt >= 6.5
* KDE Frameworks KCoreAddons >= 5.78
* KDE extra-cmake-modules >= 5.78 (recommended; required for some modules;
  required for some tests)
* Python >= 3.6 (required for some modules)
* Boost.Python >= 1.72.0 (required for some modules if WITH_PYBIND11 is OFF)

Individual modules may have their own requirements;
these are listed in CMake output.
Particular requirements (not complete):

* *fsresizer* KPMCore >= 20.04
* *partition* KPMCore >= 20.04
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

