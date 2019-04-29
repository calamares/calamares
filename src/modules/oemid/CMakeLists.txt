calamares_add_plugin( oemid
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        IDJob.cpp
        OEMViewStep.cpp
    UI
        OEMPage.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
        Qt5::Widgets
    SHARED_LIB
)
