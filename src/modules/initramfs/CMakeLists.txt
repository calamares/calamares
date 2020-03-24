calamares_add_plugin( initramfs
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        InitramfsJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)

calamares_add_test(
    initramfstest
    SOURCES
        Tests.cpp
    LIBRARIES
        calamares_job_initramfs # From above
        yamlcpp
)
