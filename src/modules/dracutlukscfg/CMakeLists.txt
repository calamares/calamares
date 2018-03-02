calamares_add_plugin( dracutlukscfg
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        DracutLuksCfgJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)
