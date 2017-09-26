include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( locale
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        LCLocaleDialog.cpp
        LocaleConfiguration.cpp
        LocalePage.cpp
        LocaleViewStep.cpp
        SetTimezoneJob.cpp
        timezonewidget/timezonewidget.cpp
        timezonewidget/localeglobal.cpp
    UI
    RESOURCES
        locale.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        Qt5::Network
        ${YAMLCPP_LIBRARY}
    SHARED_LIB
)
