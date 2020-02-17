calamares_add_plugin( shellprocess
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ShellProcessJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)

calamares_add_test(
    shellprocesstest
    GUI  # It's not
    SOURCES
        Tests.cpp
    LIBRARIES
        ${YAMLCPP_LIBRARY}
)
