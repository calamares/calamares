include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( greeting
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    CONFIG_FILE module.conf
    SOURCES
        GreetingViewStep.cpp
        GreetingPage.cpp
    UI
    LINK_LIBRARIES
        ${CALAMARES_LIBRARIES}
        calamaresui
        ${CALAMARESUI_LIBRARIES}
    SHARED_LIB
)
