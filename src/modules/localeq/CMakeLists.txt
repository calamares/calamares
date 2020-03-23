# When debugging the timezone widget, add this debugging definition
# to have a debugging-friendly timezone widget, debug logging,
# and no intrusive timezone-setting while clicking around.
option( DEBUG_TIMEZONES "Debug-friendly timezone widget." OFF )
if( DEBUG_TIMEZONES )
    add_definitions( -DDEBUG_TIMEZONES )
endif()

set( _locale ${CMAKE_CURRENT_SOURCE_DIR}/../locale )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui ${CMAKE_CURRENT_SOURCE_DIR}/../../libcalamares ${_locale} )

calamares_add_plugin( localeq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${geoip_src}
        LocaleQmlViewStep.cpp
		${_locale}/LocaleConfiguration.cpp
		${_locale}/Config.cpp
        ${_locale}/SetTimezoneJob.cpp
		${_locale}/timezonewidget/localeglobal.cpp
    RESOURCES
        locale.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        Qt5::Network
        ${geoip_libs}
        ${YAMLCPP_LIBRARY}
    SHARED_LIB
)

# add_executable( localeqmltest qmlmain.cpp Config.cpp LocaleQmlViewStep.cpp LocaleConfiguration.cpp timezonewidget/localeglobal.cpp SetTimezoneJob.cpp ${geoip_src} )
# target_link_libraries( localeqmltest PRIVATE calamaresui Qt5::Core Qt5::Network Qt5::DBus ${geoip_libs})
# set_target_properties( localeqmltest
#     PROPERTIES
#         ENABLE_EXPORTS TRUE
#         RUNTIME_OUTPUT_NAME localeqmltest
# )
# calamares_automoc( localeqmltest )
# calamares_autouic( localeqmltest )

