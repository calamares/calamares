find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

find_package( KF5 REQUIRED CoreAddons Service )

calamares_add_plugin( plasmalnf
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        PlasmaLnfJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)
