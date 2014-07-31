include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( users
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    CONFIG_FILE module.conf
    SOURCES
#        CreateUserJob.cpp
        UsersViewStep.cpp
        UsersPage.cpp
    UI
        page_usersetup.ui
    LINK_LIBRARIES
        calamaresui
    SHARED_LIB
)
