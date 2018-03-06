calamares_add_plugin( contextualprocess
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ContextualProcessJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)

if( ECM_FOUND )
    find_package( Qt5 COMPONENTS Test REQUIRED )
    include( ECMAddTests )

    ecm_add_test(
            Tests.cpp
            ContextualProcessJob.cpp  # Builds it a second time
        TEST_NAME
            contextualprocesstest
        LINK_LIBRARIES
            ${CALAMARES_LIBRARIES}
            calamaresui
            ${YAMLCPP_LIBRARY}
            Qt5::Core
            Qt5::Test
    )
    set_target_properties( contextualprocesstest PROPERTIES AUTOMOC TRUE )
endif()
