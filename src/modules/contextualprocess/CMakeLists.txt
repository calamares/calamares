# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
calamares_add_plugin(contextualprocess
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ContextualProcessJob.cpp
    SHARED_LIB
)

calamares_add_test(
    contextualprocesstest
    SOURCES
        Tests.cpp
        ContextualProcessJob.cpp # Builds it a second time
    LIBRARIES yamlcpp::yamlcpp
)
