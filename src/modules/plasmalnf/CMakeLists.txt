find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

find_package( KF5 5.29 REQUIRED CoreAddons Plasma Package )

calamares_add_plugin( plasmalnf
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        PlasmaLnfViewStep.cpp
        PlasmaLnfPage.cpp
        PlasmaLnfJob.cpp
    UI
        page_plasmalnf.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
        KF5::Package
        KF5::Plasma
    SHARED_LIB
)
