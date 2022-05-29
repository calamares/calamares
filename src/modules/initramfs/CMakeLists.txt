# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin(initramfs
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        InitramfsJob.cpp
    SHARED_LIB
)

calamares_add_test(
    initramfstest
    SOURCES Tests.cpp
    LIBRARIES
        calamares_job_initramfs # From above
        yamlcpp::yamlcpp
)
