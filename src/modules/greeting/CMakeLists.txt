include_directories( ${PROJECT_BINARY_DIR}/src/calamares )
calamares_add_plugin( greeting
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    CONFIG_FILE module.conf
    SOURCES
        GreetingViewPlugin.cpp
        GreetingPage.cpp
    UI
    LINK_LIBRARIES
        ${CALAMARES_LIBRARIES}
        calamares_bin
    SHARED_LIB
)
