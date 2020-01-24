# Configuration for hostinfo
#
# There isn't anything to configure for the hostinfo module.
#
# Hostinfo puts information about the host system into Calamares
# GlobalStorage. This information is generally unchanging. Put
# this module somewhere early in the exec: section to pick up
# the variables. Use a contextualprocess module later to
# react to the values, if needed.
#
# GlobalStorage keys:
#
#   - *hostOS* the OS this module was built under; value is "Linux" or
#       "FreeBSD" or blank.
#   - *hostOSName* the NAME value from /etc/os-release if it exists,
#       otherwise the same as *hostOS*.
#   - *hostCPU* the make (brand) of the CPU, if it can be determined.
#       Values are "Intel" or "AMD" or blank.

calamares_add_plugin( hostinfo
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        HostInfoJob.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    SHARED_LIB
    NO_CONFIG
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
