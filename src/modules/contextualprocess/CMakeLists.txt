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
    GUI  # It's not
    SOURCES
        Tests.cpp
        ContextualProcessJob.cpp  # Builds it a second time
    LIBRARIES
        ${YAMLCPP_LIBRARY}
)
