# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# Locate libpwquality
#   https://github.com/libpwquality/libpwquality
#
# This module defines
#  LibPWQuality_FOUND
#  LibPWQuality_LIBRARIES, where to find the library
#  LibPWQuality_INCLUDE_DIRS, where to find pwquality.h
#
find_package(PkgConfig)
include(FindPackageHandleStandardArgs)

if(PkgConfig_FOUND)
    pkg_search_module(pc_pwquality QUIET pwquality)
else()
    # It's just possible that the find_path and find_library will
    # find it **anyway**, so let's pretend it was there.
    set(pc_pwquality_FOUND ON)
endif()

find_path(LibPWQuality_INCLUDE_DIR
    NAMES pwquality.h
    PATHS ${pc_pwquality_INCLUDE_DIRS}
)
find_library(LibPWQuality_LIBRARY
    NAMES pwquality
    PATHS ${pc_pwquality_LIBRARY_DIRS}
)
if(pc_pwquality_FOUND)
    set(LibPWQuality_LIBRARIES ${LibPWQuality_LIBRARY})
    set(LibPWQuality_INCLUDE_DIRS ${LibPWQuality_INCLUDE_DIR} ${pc_pwquality_INCLUDE_DIRS})
endif()

find_package_handle_standard_args(LibPWQuality DEFAULT_MSG
    LibPWQuality_INCLUDE_DIRS
    LibPWQuality_LIBRARIES
)
mark_as_advanced(LibPWQuality_INCLUDE_DIRS LibPWQuality_LIBRARIES)

set_package_properties(
    LibPWQuality PROPERTIES
    DESCRIPTION "Password quality checking library"
    URL "https://github.com/libpwquality/libpwquality"
)
