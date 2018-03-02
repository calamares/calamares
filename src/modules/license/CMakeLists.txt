include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( license

set_source_files_properties( PROPERTIES LANGUAGE CXX )

find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED DBus )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                       ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules )

    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        LicenseViewStep.cpp
        LicensePage.cpp
    UI
        LicensePage.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
