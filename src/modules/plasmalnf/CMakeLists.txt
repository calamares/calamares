find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

find_package( KF5 5.29 REQUIRED CoreAddons Plasma Service Package )

calamares_add_plugin( plasmalnf
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        PlasmaLnfViewStep.cpp
        PlasmaLnfPage.cpp
        PlasmaLnfInfo.cpp
    UI
        page_plasmalnf.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
        KF5::Package
        KF5::Plasma
        KF5::Service
    SHARED_LIB
)
