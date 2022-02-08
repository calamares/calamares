# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
set(CALA_WEBVIEW_LINK_LIBRARIES "")

option(WEBVIEW_FORCE_WEBKIT "Always build webview with WebKit instead of WebEngine regardless of Qt version." OFF)

set(_reason "")

message(STATUS "Found Qt version ${Qt5Core_VERSION}")
if(Qt5Core_VERSION VERSION_LESS 5.6 OR WEBVIEW_FORCE_WEBKIT)
    message(STATUS " .. using webkit")
    find_package(Qt5 ${QT_VERSION} CONFIG COMPONENTS WebKit WebKitWidgets)

    if(Qt5WebKit_FOUND AND Qt5WebKitWidgets_FOUND)
        list(APPEND CALA_WEBVIEW_INCLUDE_DIRECTORIES ${QT_QTWEBKIT_INCLUDE_DIR})
        list(APPEND CALA_WEBVIEW_LINK_LIBRARIES Qt5::WebKit Qt5::WebKitWidgets)
        set(WEBVIEW_WITH_WEBKIT 1)
    else()
        set(_reason "No suitable WebKit")
    endif()
else()
    message(STATUS " .. using webengine")
    find_package(Qt5 ${QT_VERSION} CONFIG COMPONENTS WebEngine WebEngineWidgets)

    if(Qt5WebEngine_FOUND AND Qt5WebEngineWidgets_FOUND)
        list(APPEND CALA_WEBVIEW_INCLUDE_DIRECTORIES ${QT_QTWEBENGINE_INCLUDE_DIR})
        list(APPEND CALA_WEBVIEW_LINK_LIBRARIES Qt5::WebEngine Qt5::WebEngineWidgets)
        set(WEBVIEW_WITH_WEBENGINE 1)
    else()
        set(_reason "No suitable WebEngine")
    endif()
endif()

if(NOT _reason)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/WebViewConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/WebViewConfig.h)

    calamares_add_plugin(webview
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            WebViewStep.cpp
        LINK_PRIVATE_LIBRARIES
            ${CALA_WEBVIEW_LINK_LIBRARIES}
        SHARED_LIB
    )
else()
    calamares_skip_module( "webview (${_reason})" )
endif()
