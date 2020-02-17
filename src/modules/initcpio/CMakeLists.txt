calamares_add_plugin( initcpio
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        InitcpioJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)

calamares_add_test(
    initcpiotest
    SOURCES
        Tests.cpp
    LIBRARIES
        calamares_job_initcpio # From above
        yamlcpp
)
