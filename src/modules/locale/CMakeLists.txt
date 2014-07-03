include_directories( ${PROJECT_BINARY_DIR}/src/calamares )
calamares_add_plugin( locale
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    CONFIG_FILE module.conf
    SOURCES
        LocaleViewStep.cpp
        LocalePage.cpp
        QtWaitingSpinner.cpp
        timezonewidget/timezonewidget.cpp
        timezonewidget/localeglobal.cpp
    UI
    LINK_LIBRARIES
        ${CALAMARES_LIBRARIES}
    SHARED_LIB
)
