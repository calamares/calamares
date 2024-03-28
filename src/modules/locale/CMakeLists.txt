# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# When debugging the timezone widget, add this debugging definition
# to have a debugging-friendly timezone widget, debug logging,
# and no intrusive timezone-setting while clicking around.
option(DEBUG_TIMEZONES "Debug-friendly timezone widget." OFF)

include_directories(${PROJECT_BINARY_DIR}/src/libcalamaresui)

calamares_add_plugin(locale
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        Config.cpp
        LCLocaleDialog.cpp
        LocaleConfiguration.cpp
        LocaleNames.cpp
        LocalePage.cpp
        LocaleViewStep.cpp
        SetTimezoneJob.cpp
        timezonewidget/timezonewidget.cpp
        timezonewidget/TimeZoneImage.cpp
    UI
    RESOURCES
        locale.qrc
    LINK_PRIVATE_LIBRARIES
        ${qtname}::Network
        yamlcpp::yamlcpp
    SHARED_LIB
)
if(DEBUG_TIMEZONES)
    target_compile_definitions(${locale_TARGET} PRIVATE DEBUG_TIMEZONES)
endif()

calamares_add_test(
    localetest
    SOURCES
        Tests.cpp
        Config.cpp
        LocaleConfiguration.cpp
        LocaleNames.cpp
        SetTimezoneJob.cpp
        timezonewidget/TimeZoneImage.cpp
    DEFINITIONS SOURCE_DIR="${CMAKE_CURRENT_LIST_DIR}/images" DEBUG_TIMEZONES=1
    LIBRARIES ${qtname}::Gui
)
