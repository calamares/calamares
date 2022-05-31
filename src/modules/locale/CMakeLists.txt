# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# When debugging the timezone widget, add this debugging definition
# to have a debugging-friendly timezone widget, debug logging,
# and no intrusive timezone-setting while clicking around.
option(DEBUG_TIMEZONES "Debug-friendly timezone widget." OFF)
if(DEBUG_TIMEZONES)
    add_definitions(-DDEBUG_TIMEZONES)
endif()

include_directories(${PROJECT_BINARY_DIR}/src/libcalamaresui)

calamares_add_plugin(locale
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${geoip_src}
        Config.cpp
        LCLocaleDialog.cpp
        LocaleConfiguration.cpp
        LocalePage.cpp
        LocaleViewStep.cpp
        SetTimezoneJob.cpp
        timezonewidget/timezonewidget.cpp
        timezonewidget/TimeZoneImage.cpp
    UI
    RESOURCES
        locale.qrc
    LINK_PRIVATE_LIBRARIES
        Qt5::Network
        ${geoip_libs}
        yamlcpp::yamlcpp
    SHARED_LIB
)

calamares_add_test(
    localetest
    SOURCES Tests.cpp Config.cpp LocaleConfiguration.cpp SetTimezoneJob.cpp timezonewidget/TimeZoneImage.cpp
    DEFINITIONS SOURCE_DIR="${CMAKE_CURRENT_LIST_DIR}/images" DEBUG_TIMEZONES=1
    LIBRARIES Qt5::Gui
)
