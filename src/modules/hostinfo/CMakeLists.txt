# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# Configuration for hostinfo
#
# There isn't anything to configure for the hostinfo module.
#
# Hostinfo puts information about the host system into Calamares
# GlobalStorage. This information is generally unchanging. Put
# this module somewhere early in the exec: section to pick up
# the variables. Use a contextualprocess module later to
# react to the values, if needed.
#
# GlobalStorage keys:
#
#   - *hostOS* the OS this module was built under; value is "Linux" or
#       "FreeBSD" or blank.
#   - *hostOSName* the NAME value from /etc/os-release if it exists,
#       otherwise the same as *hostOS*.
#   - *hostCPU* the make (brand) of the CPU, if it can be determined.
#       Values are "Intel" or "AMD" or blank.

calamares_add_plugin(hostinfo
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        HostInfoJob.cpp
    SHARED_LIB
    NO_CONFIG
)

if(KF5CoreAddons_FOUND AND KF5CoreAddons_VERSION VERSION_GREATER_EQUAL 5.58)
    target_compile_definitions(calamares_job_hostinfo PRIVATE WITH_KOSRelease)
    target_link_libraries(calamares_job_hostinfo PRIVATE KF5::CoreAddons)
endif()

calamares_add_test(hostinfotest SOURCES Tests.cpp HostInfoJob.cpp LIBRARIES yamlcpp::yamlcpp)
