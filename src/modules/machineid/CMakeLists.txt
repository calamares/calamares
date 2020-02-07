calamares_add_plugin( machineid
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        MachineIdJob.cpp
        Workers.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)

if ( ECM_FOUND AND BUILD_TESTING )
    ecm_add_test(
            Tests.cpp
            MachineIdJob.cpp
            Workers.cpp
        TEST_NAME
            machineidtest
        LINK_LIBRARIES
            calamares
            Qt5::Core
            Qt5::Test
    )
    calamares_automoc( machineidtest )
endif()
