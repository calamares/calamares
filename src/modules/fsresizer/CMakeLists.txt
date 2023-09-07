# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
include(KPMcoreHelper)

if(KPMcore_FOUND)
    include_directories(${KPMCORE_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/modules/partition)

    # The PartitionIterator is a small class, and it's easiest -- but also a
    # gross hack -- to just compile it again from the partition module tree.
    calamares_add_plugin(fsresizer
        TYPE job
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            ResizeFSJob.cpp
        LINK_PRIVATE_LIBRARIES
            calamares::kpmcore
        COMPILE_DEFINITIONS ${KPMcore_API_DEFINITIONS}
        SHARED_LIB
    )

    calamares_add_test(
        fsresizertest
        SOURCES Tests.cpp
        LIBRARIES
            calamares_job_fsresizer # From above
            yamlcpp::yamlcpp
        DEFINITIONS ${KPMcore_API_DEFINITIONS}
    )
else()
    if(NOT KPMcore_FOUND)
        calamares_skip_module( "fsresizer (missing suitable KPMcore)" )
    else()
        calamares_skip_module( "fsresizer (missing dependencies for KPMcore)" )
    endif()
endif()
