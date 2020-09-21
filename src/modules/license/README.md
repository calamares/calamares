### License Approval Module

<!-- SPDX-FileCopyrightText: 2015 Anke Boersma
     SPDX-FileCopyrightText: 2015 Teo Mrnjavac <teo@kde.org>
     SPDX-License-Identifier: GPL-3.0-or-later
-->

For distributions shipping proprietary software, this module creates a
Global Storage entry when the user accepts or declines one or more of
the End User License Agreements files that are presented here.

The number of licenses shown are configurable.  The `license.conf` file
has a few examples of how to add URLs.

If you do not want to include this module in your Calamares build,
add `-DSKIP_MODULES="license"` to your build settings (CMake call).

How to implement the removal or not installing of proprietary software is
up to any distribution to implement.  For example, proprietary graphics
drivers cannot simply be removed in the packages module, a free version
will need to be installed.

An example of where the licenseAgree globalstorage entry is used:
https://github.com/KaOSx/calamares/blob/master/src/modules/nonfree_drivers/main.py

![License Page](http://wstaw.org/m/2015/09/14/Screenshot_20150914_113333.png)
