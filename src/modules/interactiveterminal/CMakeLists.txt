find_package(ECM 0.0.13 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})

include(KDEInstallDirs)       # this seems to be necessary for KF5::CoreAddons
include(GenerateExportHeader) # this too, because KDE frameworks always want omnomnom more stuff

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
    LINK_LIBRARIES
        calamaresui
        KF5::Service
        KF5::Parts
    SHARED_LIB
)
