calamares_add_plugin( dracutlukscfg
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        DracutLuksCfgJob.cpp
    LINK_LIBRARIES
        calamares
    SHARED_LIB
)
