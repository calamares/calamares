# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
if(NOT WITH_QML)
    calamares_skip_module( "localeq (QML is not supported in this build)" )
    return()
endif()

# When debugging the timezone widget, add this debugging definition
# to have a debugging-friendly timezone widget, debug logging,
# and no intrusive timezone-setting while clicking around.
option(DEBUG_TIMEZONES "Debug-friendly timezone widget." OFF)

find_package(${qtname}Location CONFIG)
set_package_properties(${qtname}Location PROPERTIES DESCRIPTION "Used for rendering the map" TYPE RUNTIME)
find_package(${qtname}Positioning CONFIG)
set_package_properties(${qtname}Positioning PROPERTIES DESCRIPTION "Used for GeoLocation and GeoCoding" TYPE RUNTIME)

# Because we're sharing sources with the regular locale module
set(_locale ${CMAKE_CURRENT_SOURCE_DIR}/../locale)

calamares_add_plugin(localeq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        LocaleQmlViewStep.cpp
        ${_locale}/Config.cpp
        ${_locale}/LocaleConfiguration.cpp
        ${_locale}/LocaleNames.cpp
        ${_locale}/SetTimezoneJob.cpp
    RESOURCES
        localeq${QT_VERSION_SUFFIX}.qrc
    LINK_PRIVATE_LIBRARIES
        ${qtname}::Network
    SHARED_LIB
)
target_include_directories(${localeq_TARGET} PRIVATE ${_locale})
if(DEBUG_TIMEZONES)
    target_compile_definitions(${localeq_TARGET} PRIVATE DEBUG_TIMEZONES)
endif()
