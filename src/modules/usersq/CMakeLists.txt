# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
if(NOT WITH_QML)
    calamares_skip_module( "usersq (QML is not supported in this build)" )
    return()
endif()

find_package(Qt5 ${QT_VERSION} CONFIG REQUIRED Core DBus Network)
find_package(Crypt REQUIRED)

# Add optional libraries here
set(USER_EXTRA_LIB)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../users)

find_package(LibPWQuality)
set_package_properties(LibPWQuality PROPERTIES PURPOSE "Extra checks of password quality")

if(LibPWQuality_FOUND)
    list(APPEND USER_EXTRA_LIB ${LibPWQuality_LIBRARIES})
    include_directories(${LibPWQuality_INCLUDE_DIRS})
    add_definitions(-DCHECK_PWQUALITY -DHAVE_LIBPWQUALITY)
endif()

#needed for ${_users}/Config.cpp
find_package(ICU COMPONENTS uc i18n)
set_package_properties(ICU PROPERTIES PURPOSE "Transliteration support for full name to username conversion")

if(ICU_FOUND)
    list(APPEND USER_EXTRA_LIB ICU::uc ICU::i18n)
    include_directories(${ICU_INCLUDE_DIRS})
    add_definitions(-DHAVE_ICU)
endif()

calamares_add_plugin(usersq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        UsersQmlViewStep.cpp
    RESOURCES
        usersq.qrc
    LINK_PRIVATE_LIBRARIES
        users_internal
        ${CRYPT_LIBRARIES}
        ${USER_EXTRA_LIB}
        Qt5::DBus
    SHARED_LIB
)
