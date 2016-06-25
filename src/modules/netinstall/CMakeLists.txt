#include(KDEInstallDirs)
#include(KDECMakeSettings)
#include(KDECompilerSettings)

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

list( APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" )

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
list( APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

set(KF5_MIN_VERSION "5.2.0")
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    KIO             # KIO
)

calamares_add_plugin( netinstall
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        NetInstallViewStep.cpp
        NetInstallPage.cpp
        widgets/groupselectionwidget.cpp
    UI
        page_netinst.ui
        widgets/groupselectionwidget.ui
    RESOURCES
        netinstall.qrc
    LINK_LIBRARIES
        calamaresui
        KF5::KIOCore
    SHARED_LIB
)
