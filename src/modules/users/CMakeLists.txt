# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(Qt5 ${QT_VERSION} CONFIG REQUIRED Core DBus Network)
find_package(Crypt REQUIRED)

# Add optional libraries here
set(USER_EXTRA_LIB)

find_package(LibPWQuality)
set_package_properties(LibPWQuality PROPERTIES PURPOSE "Extra checks of password quality")

if(LibPWQuality_FOUND)
    list(APPEND USER_EXTRA_LIB ${LibPWQuality_LIBRARIES})
    include_directories(${LibPWQuality_INCLUDE_DIRS})
    add_definitions(-DCHECK_PWQUALITY -DHAVE_LIBPWQUALITY)
endif()

find_package(ICU COMPONENTS uc i18n)
set_package_properties(ICU PROPERTIES PURPOSE "Transliteration support for full name to username conversion")

if(ICU_FOUND)
    list(APPEND USER_EXTRA_LIB ICU::uc ICU::i18n)
    include_directories(${ICU_INCLUDE_DIRS})
    add_definitions(-DHAVE_ICU)
endif()

include_directories(${PROJECT_BINARY_DIR}/src/libcalamaresui)

set(_users_src
    # Jobs
    CreateUserJob.cpp
    MiscJobs.cpp
    SetPasswordJob.cpp
    SetHostNameJob.cpp
    # Configuration
    CheckPWQuality.cpp
    Config.cpp
)

# This part of the code is shared with the usersq module
calamares_add_library(
    users_internal
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    TARGET_TYPE STATIC
    NO_INSTALL
    NO_VERSION
    SOURCES
        ${_users_src}
    LINK_LIBRARIES
        KF5::CoreAddons
        Qt5::DBus
        ${CRYPT_LIBRARIES}
)

calamares_add_plugin(users
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        UsersViewStep.cpp
        UsersPage.cpp
    UI
        page_usersetup.ui
    RESOURCES
        users.qrc
    LINK_PRIVATE_LIBRARIES
        users_internal
        ${CRYPT_LIBRARIES}
        ${USER_EXTRA_LIB}
    SHARED_LIB
)

calamares_add_test(userspasswordtest SOURCES TestPasswordJob.cpp SetPasswordJob.cpp LIBRARIES ${CRYPT_LIBRARIES})

calamares_add_test(
    usersgroupstest
    SOURCES
        TestGroupInformation.cpp
        ${_users_src} # Build again with test-visibility
    LIBRARIES
        KF5::CoreAddons
        Qt5::DBus # HostName job can use DBus to systemd
        ${CRYPT_LIBRARIES} # SetPassword job uses crypt()
        ${USER_EXTRA_LIB}
)

calamares_add_test(
    usershostnametest
    SOURCES TestSetHostNameJob.cpp SetHostNameJob.cpp
    LIBRARIES
        Qt5::DBus # HostName job can use DBus to systemd
)

calamares_add_test(
    userstest
    SOURCES
        Tests.cpp
        ${_users_src} # Build again with test-visibility
    LIBRARIES
        KF5::CoreAddons
        Qt5::DBus # HostName job can use DBus to systemd
        ${CRYPT_LIBRARIES} # SetPassword job uses crypt()
        ${USER_EXTRA_LIB}
)
