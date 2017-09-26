include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( netinstall
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        NetInstallViewStep.cpp
        NetInstallPage.cpp
        PackageTreeItem.cpp
        PackageModel.cpp
    UI
        page_netinst.ui
    RESOURCES
        netinstall.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        Qt5::Network
        ${YAMLCPP_LIBRARY}
    SHARED_LIB
)
