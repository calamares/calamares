calamares_add_plugin( shellprocess
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ShellProcessJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)

if( ECM_FOUND )
    find_package( Qt5 COMPONENTS Test REQUIRED )
    include( ECMAddTests )

    ecm_add_test(
            Tests.cpp
        TEST_NAME
            shellprocesstest
        LINK_LIBRARIES
            ${CALAMARES_LIBRARIES}
            calamaresui
            ${YAMLCPP_LIBRARY}
            Qt5::Core
            Qt5::Test
    )
    set_target_properties( shellprocesstest PROPERTIES AUTOMOC TRUE )
endif()
