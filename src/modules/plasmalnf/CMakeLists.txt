# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

# Requires a sufficiently recent Plasma framework, but also
# needs a runtime support component (which we don't test for).
set(lnf_ver 5.41)

find_package(KF5Config ${lnf_ver})
set_package_properties(KF5Config PROPERTIES PURPOSE "For finding default Plasma Look-and-Feel")

find_package(KF5Plasma ${lnf_ver})
set_package_properties(KF5Plasma PROPERTIES PURPOSE "For Plasma Look-and-Feel selection")

find_package(KF5Package ${lnf_ver})
set_package_properties(KF5Package PROPERTIES PURPOSE "For Plasma Look-and-Feel selection")

if(KF5Plasma_FOUND AND KF5Package_FOUND)
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
            KF5::Package
            KF5::Plasma
        SHARED_LIB
    )
    if(KF5Config_FOUND)
        target_compile_definitions(calamares_viewmodule_plasmalnf PRIVATE WITH_KCONFIG)
    endif()
else()
    calamares_skip_module( "plasmalnf (missing requirements)" )
endif()
