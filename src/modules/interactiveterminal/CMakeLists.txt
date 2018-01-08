find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

include(KDEInstallDirs)
include(GenerateExportHeader)

find_package( KF5 REQUIRED Service Parts )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui
                     ${QTERMWIDGET_INCLUDE_DIR} )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                       ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules )


calamares_add_plugin( interactiveterminal
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        InteractiveTerminalViewStep.cpp
        InteractiveTerminalPage.cpp
    LINK_PRIVATE_LIBRARIES
        calamaresui
    LINK_LIBRARIES
        KF5::Service
        KF5::Parts
    SHARED_LIB
)
