calamares_add_plugin( dummycpp
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        DummyCppJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)
