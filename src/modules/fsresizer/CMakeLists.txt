find_package( KPMcore 3.3 )
find_package( KF5Config CONFIG )
find_package( KF5I18n CONFIG )
find_package( KF5WidgetsAddons CONFIG )

set( _partition_defs "" )

if ( KPMcore_FOUND AND Qt5DBus_FOUND AND KF5CoreAddons_FOUND AND KF5Config_FOUND )
    include_directories( ${KPMCORE_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/modules/partition )

    if( KPMcore_VERSION VERSION_GREATER_EQUAL "4.2" )
        list( APPEND _partition_defs WITH_KPMCORE42API WITH_KPMCORE4API ) # kpmcore 4.2 with new API
    elseif( KPMcore_VERSION VERSION_GREATER_EQUAL "4.0" )
        list( APPEND _partition_defs WITH_KPMCORE4API ) # kpmcore 4 with new API
    elseif( KPMcore_VERSION VERSION_GREATER "3.3.70" )
        message( FATAL_ERROR "KPMCore beta versions ${KPMcore_VERSION} are not supported" )
    endif()

    # The PartitionIterator is a small class, and it's easiest -- but also a
    # gross hack -- to just compile it again from the partition module tree.
    calamares_add_plugin( fsresizer
        TYPE job
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            ResizeFSJob.cpp
        LINK_PRIVATE_LIBRARIES
            kpmcore
            calamares
        COMPILE_DEFINITIONS ${_partition_defs}
        SHARED_LIB
    )

    calamares_add_test(
        fsresizertest
        SOURCES
            Tests.cpp
        LIBRARIES
            calamares_job_fsresizer  # From above
            yamlcpp
        DEFINITIONS ${_partition_defs}
    )
else()
    if ( NOT KPMcore_FOUND )
        calamares_skip_module( "fsresizer (missing suitable KPMcore)" )
    else()
        calamares_skip_module( "fsresizer (missing dependencies for KPMcore)" )
    endif()
endif()
