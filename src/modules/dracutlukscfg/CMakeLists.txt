# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin( dracutlukscfg
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        DracutLuksCfgJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
    NO_CONFIG
)
