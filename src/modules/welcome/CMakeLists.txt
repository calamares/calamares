include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( welcome
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        WelcomeViewStep.cpp
        WelcomePage.cpp
    UI
        WelcomePage.ui
    LINK_LIBRARIES
        calamaresui
    SHARED_LIB
)
