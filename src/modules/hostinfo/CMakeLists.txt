calamares_add_plugin( hostinfo
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        HostInfoJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
)

if ( KF5CoreAddons_FOUND AND KF5CoreAddons_VERSION VERSION_GREATER_EQUAL 5.58 )
    target_compile_definitions( calamares_job_hostinfo PRIVATE WITH_KOSRelease )
endif()

if( ECM_FOUND AND BUILD_TESTING )
    ecm_add_test(
            Tests.cpp
            HostInfoJob.cpp  # Builds it a second time
        TEST_NAME
            hostinfotest
        LINK_LIBRARIES
            ${CALAMARES_LIBRARIES}
            calamaresui
            ${YAMLCPP_LIBRARY}
            Qt5::Core
            Qt5::Test
    )
    calamares_automoc( hostinfotest )
endif()
