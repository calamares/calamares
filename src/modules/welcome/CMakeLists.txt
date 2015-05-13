include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( greeting
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        GreetingViewStep.cpp
        GreetingPage.cpp
    UI
        GreetingPage.ui
    LINK_LIBRARIES
        calamaresui
    SHARED_LIB
)
