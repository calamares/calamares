# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin(initcpio
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        InitcpioJob.cpp
    SHARED_LIB
)

calamares_add_test(
    initcpiotest
    SOURCES Tests.cpp
    LIBRARIES
        calamares_job_initcpio # From above
        yamlcpp::yamlcpp
)
