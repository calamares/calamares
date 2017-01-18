include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( extrapackages
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ExtraPackagesViewStep.cpp
        ExtraPackagesPage.cpp
        InstallPackageJob.cpp
        SetSourcesJob.cpp
    UI
        ExtraPackagesPage.ui
    LINK_LIBRARIES
        calamaresui
    SHARED_LIB
)
