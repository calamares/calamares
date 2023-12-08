# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(${qtname} ${QT_VERSION} CONFIG REQUIRED Core DBus Network)
find_package(Crypt REQUIRED)

# Provide modern alias for -lcrypt
add_library(crypt_crypt INTERFACE)
add_library(crypt::crypt ALIAS crypt_crypt)
if(Crypt_FOUND)
    target_link_libraries(crypt_crypt INTERFACE ${CRYPT_LIBRARIES})
endif()

# Check for crypt_gensalt
if(Crypt_FOUND)
    set(_old_CRL "${CMAKE_REQUIRED_LIBRARIES}")
    list(APPEND CMAKE_REQUIRED_LIBRARIES crypt)
    include(CheckSymbolExists)
    check_symbol_exists(crypt_gensalt crypt.h HAS_CRYPT_GENSALT)
    set(CMAKE_REQUIRED_LIBRARIES "${_old_CRL}")

    if(HAS_CRYPT_GENSALT)
        target_compile_definitions(crypt_crypt INTERFACE HAVE_CRYPT_GENSALT)
    endif()
endif()

# Add optional libraries here
set(USER_EXTRA_LIB
    ${kfname}::CoreAddons
    ${qtname}::DBus
    crypt::crypt
)

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
add_library(users_internal
    OBJECT
        ${_users_src}
)
target_link_libraries(users_internal
    PRIVATE
        ${USER_EXTRA_LIB}
        ${Calamares_LIBRARIES}
        ${qtname}::Core
        ${qtname}::Gui
        ${qtname}::Widgets
)
target_compile_definitions(users_internal PUBLIC PLUGINDLLEXPORT_PRO)
target_compile_options(users_internal PUBLIC -fPIC)
calamares_automoc(users_internal)

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
        crypt::crypt
        ${USER_EXTRA_LIB}
    SHARED_LIB
)

if(NOT HAS_CRYPT_GENSALT)
    # Test checks characteristics of the generated hash, but
    # when HAVE_CRYPT_GENSALT is used, the chosen hash is the "best"
    # one -- difficult to set expectations in the tests, so skip it.
    calamares_add_test(userspasswordtest SOURCES TestPasswordJob.cpp SetPasswordJob.cpp LIBRARIES crypt::crypt)
endif()

calamares_add_test(
    usersgroupstest
    SOURCES
        TestGroupInformation.cpp
        ${_users_src} # Build again with test-visibility
    LIBRARIES
        ${kfname}::CoreAddons
        ${qtname}::DBus # HostName job can use DBus to systemd
        crypt::crypt # SetPassword job uses crypt()
        ${USER_EXTRA_LIB}
)

calamares_add_test(
    usershostnametest
    SOURCES TestSetHostNameJob.cpp SetHostNameJob.cpp
    LIBRARIES
        ${qtname}::DBus # HostName job can use DBus to systemd
)

calamares_add_test(
    userstest
    SOURCES
        Tests.cpp
        ${_users_src} # Build again with test-visibility
    LIBRARIES
        ${kfname}::CoreAddons
        ${qtname}::DBus # HostName job can use DBus to systemd
        crypt::crypt # SetPassword job uses crypt()
        ${USER_EXTRA_LIB}
)
