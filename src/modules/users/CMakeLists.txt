include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" )
find_package( Crypt )

calamares_add_plugin( users
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    CONFIG_FILE module.conf
    SOURCES
        CreateUserJob.cpp
        SetPasswordJob.cpp
        UsersViewStep.cpp
        UsersPage.cpp
    UI
        page_usersetup.ui
    LINK_LIBRARIES
        calamaresui
        ${CRYPT_LIBRARIES}
    SHARED_LIB
)
