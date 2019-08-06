find_package( Qt5 COMPONENTS Core Gui Widgets REQUIRED )
set( _extra_libraries "" )

### OPTIONAL AppData XML support in PackageModel
#
#
find_package(Qt5 COMPONENTS Xml)
if ( Qt5Xml_FOUND )
    add_definitions( -DHAVE_XML )
    list( APPEND _extra_libraries Qt5::Xml )
endif()
    

calamares_add_plugin( packagechooser
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        PackageChooserPage.cpp
        PackageChooserViewStep.cpp
        PackageModel.cpp
    RESOURCES
        packagechooser.qrc
    UI
        page_package.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${_extra_libraries}
    SHARED_LIB
)

if( ECM_FOUND AND BUILD_TESTING )
    ecm_add_test(
            Tests.cpp
        TEST_NAME
            packagechoosertest
        LINK_LIBRARIES
            ${CALAMARES_LIBRARIES}
            calamares_viewmodule_packagechooser
            Qt5::Core
            Qt5::Test
            Qt5::Gui
            ${_extra_libraries}
    )
    calamares_automoc( packagechoosertest)
endif()
