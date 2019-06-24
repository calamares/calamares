calamares_add_plugin( initramfs
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        InitramfsJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)
