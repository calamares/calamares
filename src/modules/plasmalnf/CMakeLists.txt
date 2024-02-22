# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2024 Anke Boersma <demm@kaosx.us>
#   SPDX-License-Identifier: BSD-2-Clause
#

# Requires a sufficiently recent Plasma framework, but also
# needs a runtime support component (which we don't test for).

if(WITH_QT6)
    set(PLASMA_VERSION "5.93.0")
    set(_plasma_libraries "Plasma::Plasma")
    set(_plasma_name "Plasma")
    find_package(${kfname} ${KF_VERSION} QUIET COMPONENTS Config Package)
    find_package(Plasma ${PLASMA_VERSION})
else()
    set(_plasma_libraries "${kfname}::Plasma")
    set(_plasma_name "KF5Plasma")
    find_package(${kfname} ${KF_VERSION} QUIET COMPONENTS Config Plasma Package)
endif()

set_package_properties(${kfname}Config PROPERTIES PURPOSE "For finding default Plasma Look-and-Feel")
set_package_properties(${_plasma_name} PROPERTIES PURPOSE "For Plasma Look-and-Feel selection")
set_package_properties(${kfname}Package PROPERTIES PURPOSE "For Plasma Look-and-Feel selection")

if(${_plasma_name}_FOUND AND ${kfname}Package_FOUND)
    calamares_add_plugin(plasmalnf
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        COMPILE_DEFINITIONS
            ${option_defs}
        SOURCES
            Config.cpp
            PlasmaLnfViewStep.cpp
            PlasmaLnfPage.cpp
            PlasmaLnfJob.cpp
            ThemeInfo.cpp
        RESOURCES
            page_plasmalnf.qrc
        UI
            page_plasmalnf.ui
        LINK_PRIVATE_LIBRARIES
            ${kfname}::Package
            ${_plasma_libraries}
        SHARED_LIB
    )
    if(${kfname}Config_FOUND)
        target_compile_definitions(calamares_viewmodule_plasmalnf PRIVATE WITH_KCONFIG)
    endif()
else()
    calamares_skip_module( "plasmalnf (missing requirements)" )
endif()
