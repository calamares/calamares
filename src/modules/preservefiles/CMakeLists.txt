# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( preservefiles
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        PreserveFiles.cpp
    # REQUIRES mount  # To set the rootMountPoint
    SHARED_LIB
    EMERGENCY
)
