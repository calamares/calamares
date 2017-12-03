find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

find_package( KF5 5.29 REQUIRED CoreAddons Plasma Service )

calamares_add_plugin( plasmalnf
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        PlasmaLnfJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
        KF5::Plasma
        KF5::Service
    SHARED_LIB
)
