# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# - Find libcrypt
# Find the libcrypt includes and the libcrypt libraries
# This module defines
# LIBCRYPT_INCLUDE_DIR, root crypt include dir. Include crypt with crypt.h
# LIBCRYPT_LIBRARY, the path to libcrypt
# LIBCRYPT_FOUND, whether libcrypt was found

if( CMAKE_SYSTEM MATCHES "FreeBSD" )
    # FreeBSD has crypt(3) declared in unistd.h, which lives in
    # libc; the libcrypt found here is not used.
    find_path( CRYPT_INCLUDE_DIR NAMES unistd.h )
    add_definitions( -DNO_CRYPT_H )
else()
    find_path( CRYPT_INCLUDE_DIR
        NAMES crypt.h
        HINTS
            ${CMAKE_INSTALL_INCLUDEDIR}
        NO_CACHE
    )
endif()

find_library( CRYPT_LIBRARIES
    NAMES crypt
    HINTS
        ${CMAKE_INSTALL_LIBDIR}
)

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args(
    Crypt
    REQUIRED_VARS CRYPT_LIBRARIES CRYPT_INCLUDE_DIR
)

mark_as_advanced( CRYPT_INCLUDE_DIR CRYPT_LIBRARIES )
