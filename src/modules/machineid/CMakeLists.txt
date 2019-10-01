calamares_add_plugin( machineid
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        MachineIdJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)
