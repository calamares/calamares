include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" )
find_package( Crypt )

calamares_add_plugin( users
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        jobs/CreateUserJob.cpp
        jobs/SetPasswordJob.cpp
        UsersViewStep.cpp
        gui/UsersPage.cpp
        jobs/SetHostNameJob.cpp
        jobs/SetAvatarJob.cpp
        gui/AddUserDialog.cpp
    UI
        gui/page_usersetup.ui
        gui/adduserdialog.ui
    RESOURCES
        users.qrc
    LINK_LIBRARIES
        calamaresui
        ${CRYPT_LIBRARIES}
    SHARED_LIB
)
