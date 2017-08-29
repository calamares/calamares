calamares_add_plugin( tracking
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        TrackingViewStep.cpp
        TrackingPage.cpp
    UI
        page_trackingstep.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)

