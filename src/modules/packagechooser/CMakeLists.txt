find_package( Qt5 COMPONENTS Core Gui Widgets REQUIRED )

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
    SHARED_LIB
)

if( ECM_FOUND AND BUILD_TESTING )
    ecm_add_test(
            Tests.cpp
        TEST_NAME
            packagechooosertest
        LINK_LIBRARIES
            ${CALAMARES_LIBRARIES}
            Qt5::Core
            Qt5::Test
    )
    calamares_automoc( packagechooosertest)
endif()
