include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" )
find_package( Crypt )

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
    LINK_LIBRARIES
        calamaresui
        ${CRYPT_LIBRARIES}
    SHARED_LIB
)
