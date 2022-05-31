# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# Because LUKS Open Swap Hook (Job) is such a mouthful, we'll
# use LOSH all over the place as a shorthand.
calamares_add_plugin(luksopenswaphookcfg
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        LOSHJob.cpp
    SHARED_LIB
)

calamares_add_test(luksopenswaphooktest SOURCES LOSHJob.cpp Tests.cpp)
