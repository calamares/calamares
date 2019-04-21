include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( license
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        LicensePage.cpp
        LicenseViewStep.cpp
        LicenseWidget.cpp
    UI
        LicensePage.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
