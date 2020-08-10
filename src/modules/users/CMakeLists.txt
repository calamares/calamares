find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED Core DBus Network )
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
        Config.cpp
    UI
        page_usersetup.ui
    RESOURCES
        users.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${CRYPT_LIBRARIES}
        ${USER_EXTRA_LIB}
        Qt5::DBus
    SHARED_LIB
)

calamares_add_test(
    userspasswordtest
    SOURCES
        TestPasswordJob.cpp
        SetPasswordJob.cpp
    LIBRARIES
        ${CRYPT_LIBRARIES}
)

calamares_add_test(
    userscreatetest
    SOURCES
        TestCreateUserJob.cpp
        CreateUserJob.cpp
)

calamares_add_test(
    usershostnametest
    SOURCES
        TestSetHostNameJob.cpp
        SetHostNameJob.cpp
    LIBRARIES
        Qt5::DBus
)

calamares_add_test(
    userstest
    SOURCES
        Tests.cpp
        Config.cpp
        CheckPWQuality.cpp
    LIBRARIES
        ${USER_EXTRA_LIB}
)
