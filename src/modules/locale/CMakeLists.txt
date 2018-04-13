find_package(ECM ${ECM_VERSION} NO_MODULE)
if( ECM_FOUND AND BUILD_TESTING )
    include( ECMAddTests )
    find_package( Qt5 COMPONENTS Core Test REQUIRED )
endif()

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

set( geoip_src GeoIP.cpp GeoIPFreeGeoIP.cpp )
set( geoip_libs )

find_package(Qt5 COMPONENTS Xml)
if( Qt5Xml_FOUND )
    list( APPEND geoip_src GeoIPXML.cpp )
    list( APPEND geoip_libs Qt5::Xml )
    add_definitions( -DHAVE_XML )
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

if( ECM_FOUND AND BUILD_TESTING )
    ecm_add_test(
            GeoIPTests.cpp
            ${geoip_src}
        TEST_NAME
            geoiptest
        LINK_LIBRARIES
            calamaresui
            Qt5::Network
            Qt5::Test
            ${geoip_libs}
            ${YAMLCPP_LIBRARY}
    )
    set_target_properties( geoiptest PROPERTIES AUTOMOC TRUE )
endif()

if( BUILD_TESTING )
    add_executable( test_geoip test_geoip.cpp ${geoip_src} )
    target_link_libraries( test_geoip calamaresui Qt5::Network ${geoip_libs} ${YAMLCPP_LIBRARY} )
endif()
