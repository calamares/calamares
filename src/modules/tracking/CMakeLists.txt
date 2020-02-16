calamares_add_plugin( tracking
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        TrackingJobs.cpp
        TrackingPage.cpp
        TrackingViewStep.cpp
    UI
        page_trackingstep.ui
    RESOURCES
        page_trackingstep.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)

