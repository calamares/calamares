find_package(ECM ${ECM_VERSION} NO_MODULE)
if( ECM_FOUND )
    include( ECMAddTests )
endif()

find_package( Qt5 COMPONENTS Core Test REQUIRED )
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

if( ECM_FOUND )
    ecm_add_test(
            PasswordTests.cpp
            SetPasswordJob.cpp
        TEST_NAME
            passwordtest
        LINK_LIBRARIES
            ${CALAMARES_LIBRARIES}
            Qt5::Core
            Qt5::Test
            ${CRYPT_LIBRARIES}
    )
    set_target_properties( passwordtest PROPERTIES AUTOMOC TRUE )
endif()
