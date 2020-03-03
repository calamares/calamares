calamares_add_plugin( removeuser
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        RemoveUserJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)
