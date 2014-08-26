include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules )
find_package( LIBPARTED REQUIRED )
find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED DBus )

set_source_files_properties( partman_devices.c PROPERTIES LANGUAGE CXX )

calamares_add_plugin( prepare
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        PrepareCheckWidget.cpp
        PreparePage.cpp
        PrepareViewStep.cpp
        partman_devices.c
    UI
    LINK_LIBRARIES
        calamaresui
        ${LIBPARTED_LIBS}
        Qt5::DBus
    SHARED_LIB
)
