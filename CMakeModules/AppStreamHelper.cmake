# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# Finds AppStream-Qt suitable for the Qt version that is in use.
# Creates target calamares::appstreamqt to alias whatever is found.
# Sets AppStreamQt_FOUND appropriately, regardless of the underlying
# variables (e.g. might be AppStreamQt6_FOUND).
#

option(BUILD_APPSTREAM "Support appstream: items in PackageChooser (requires libappstream-qt)" OFF)

if(TARGET calaappstream)
    if(TARGET calamares::appstreamqt)
        message(STATUS "AppStreamQt has already been found")
        set(AppStreamQt_FOUND TRUE)
    else()
        message(STATUS "AppStreamQt has been searched-for and not found")
        set(AppStreamQt_FOUND FALSE)
    endif()
    return()
endif()
if(NOT BUILD_APPSTREAM)
    return()
endif()

### FIND APPSTREAM
#
# First, look for a Qt-versioned variety of the package.
# If that is not found, look for an unversioned one.
set(HAVE_APPSTREAM OFF)
find_package(AppStream${qtname})
# Not everyone renames the variables consistently
if(AppStream${qtname}_FOUND OR AppStreamQt_FOUND)
    set(_appstream_name AppStream${qtname})
    set(HAVE_APPSTREAM ON)
else()
    find_package(AppStreamQt)
    if(AppStreamQt_FOUND)
        set(_appstream_name AppStreamQt)
        # TODO: how to check underlying Qt version?
        set(HAVE_APPSTREAM ON)
    endif()
endif()

if(HAVE_APPSTREAM)
    # Look for the directory name containing the headers
    find_file(_appstream_header NAMES ${_appstream_name}/pool.h AppStreamQt/pool.h)
    if(NOT _appstream_header)
        set(HAVE_APPSTREAM OFF)
    else()
        if(_appstream_header MATCHES /${_appstream_name}/)
            set(_appstream_header_directory ${_appstream_name})
        else()
            set(_appstream_header_directory AppStreamQt)
        endif()
    endif()
else()
    # Placeholder name
    set(_appstream_name AppStreamQt)
endif()

set(_appstream_dependency_type OPTIONAL)
if(BUILD_APPSTREAM)
    set(_appstream_dependency_type REQUIRED)
endif()

set_package_properties(
    ${_appstream_name}
    PROPERTIES
    DESCRIPTION "Support for AppStream (cache) data"
    URL "https://github.com/ximion/appstream"
    PURPOSE "AppStream provides package data"
    TYPE ${_appstream_dependency_type}
)

add_library(calaappstream INTERFACE) # Always, but might not be populated
if(HAVE_APPSTREAM)
    target_compile_definitions(calaappstream INTERFACE HAVE_APPSTREAM_VERSION=${${_appstream_name}_VERSION_MAJOR} HAVE_APPSTREAM_HEADERS=${_appstream_header_directory})
    target_link_libraries(calaappstream INTERFACE ${_appstream_name})
    add_library(calamares::appstreamqt ALIAS calaappstream)
endif()
set(AppStreamQt_FOUND ${HAVE_APPSTREAM})
