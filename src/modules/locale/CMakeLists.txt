include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

set( geoip_src GeoIP.cpp GeoIPFreeGeoIP.cpp )
set( geoip_libs )

find_package(Qt5 COMPONENTS Xml)
if( Qt5Xml_FOUND )
    list( APPEND geoip_src GeoIPXML.cpp )
    list( APPEND geoip_libs Qt5::Xml )
endif()

calamares_add_plugin( locale
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${geoip_src}
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
        ${geoip_libs}
        ${YAMLCPP_LIBRARY}
    SHARED_LIB
)
