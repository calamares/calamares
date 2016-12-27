include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( summary
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        SummaryViewStep.cpp
        SummaryPage.cpp
    UI
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
