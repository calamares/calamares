include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( locale
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        LCLocaleDialog.cpp
        LocaleViewStep.cpp
        LocalePage.cpp
        SetTimezoneJob.cpp
        timezonewidget/timezonewidget.cpp
        timezonewidget/localeglobal.cpp
    UI
    RESOURCES
        locale.qrc
    LINK_LIBRARIES
        calamaresui
    SHARED_LIB
)
