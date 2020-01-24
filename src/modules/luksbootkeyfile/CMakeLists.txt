calamares_add_plugin( luksbootkeyfile
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        LuksBootKeyFileJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
    NO_CONFIG
)
