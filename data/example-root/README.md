# Example Filesystem

<!-- SPDX-FileCopyrightText: no
     SPDX-License-Identifier: CC0-1.0
-->

This is a filesystem that will be used as / in an example distro,
*if* you build the `example-distro` target and use the default
unpackfs configuration. It should hold files and configuration
bits that need to be on the target system for example purposes.

It should *not* have a bin/, lib/, sbin/ or lib64/ directory,
since those are copied into the example-distro filesystem
from the build host.

