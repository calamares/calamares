calamares_add_plugin( contextualprocess
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ContextualProcessJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)

calamares_add_test(
    contextualprocesstest
    SOURCES
        Tests.cpp
        ContextualProcessJob.cpp  # Builds it a second time
    LIBRARIES
        yamlcpp
)
