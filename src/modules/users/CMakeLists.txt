find_package( Qt5 COMPONENTS Core REQUIRED )
find_package( Crypt REQUIRED )

# Add optional libraries here
set( USER_EXTRA_LIB )

find_package( LibPWQuality )
set_package_properties(
    LibPWQuality PROPERTIES
    PURPOSE "Extra checks of password quality"
)

if( LibPWQuality_FOUND )
    list( APPEND USER_EXTRA_LIB ${LibPWQuality_LIBRARIES} )
    include_directories( ${LibPWQuality_INCLUDE_DIRS} )
    add_definitions( -DCHECK_PWQUALITY -DHAVE_LIBPWQUALITY )
endif()

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( users
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        CreateUserJob.cpp
        SetPasswordJob.cpp
        UsersViewStep.cpp
        UsersPage.cpp
        SetHostNameJob.cpp
        CheckPWQuality.cpp
    UI
        page_usersetup.ui
    RESOURCES
        users.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${CRYPT_LIBRARIES}
        ${USER_EXTRA_LIB}
    SHARED_LIB
)

calamares_add_test(
    passwordtest
    SOURCES
        PasswordTests.cpp
        SetPasswordJob.cpp
    LIBRARIES
        ${CRYPT_LIBRARIES}
)
