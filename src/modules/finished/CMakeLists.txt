include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( finished
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        FinishedViewStep.cpp
        FinishedPage.cpp
    UI
        FinishedPage.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
