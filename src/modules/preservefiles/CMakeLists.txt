# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin(preservefiles
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Item.cpp
        PreserveFiles.cpp
    # REQUIRES mount  # To set the rootMountPoint
    SHARED_LIB
    EMERGENCY
)

calamares_add_test(preservefilestest SOURCES Item.cpp Tests.cpp)
