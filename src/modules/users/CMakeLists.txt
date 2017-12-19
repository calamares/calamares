find_package(ECM ${ECM_VERSION} NO_MODULE)
if( ECM_FOUND )
    include( ECMAddTests )
endif()

find_package( Qt5 COMPONENTS Core Test REQUIRED )
find_package( Crypt REQUIRED )

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
    UI
        page_usersetup.ui
    RESOURCES
        users.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${CRYPT_LIBRARIES}
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
