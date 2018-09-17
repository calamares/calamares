find_package( KPMcore 3.3 )
find_package( Qt5 REQUIRED DBus )  # Needed for KPMCore
find_package( KF5 REQUIRED I18n WidgetsAddons )  # Needed for KPMCore

if ( KPMcore_FOUND )
    if ( KPMcore_VERSION VERSION_GREATER "3.3.0")
        add_definitions(-DWITH_KPMCOREGT33) # kpmcore greater than 3.3
    endif()

    include_directories( ${KPMCORE_INCLUDE_DIR} )
    include_directories( ${PROJECT_BINARY_DIR}/src/libcalamares )

    calamares_add_plugin( fsresizer
        TYPE job
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            ResizeFSJob.cpp
        LINK_PRIVATE_LIBRARIES
            kpmcore
            calamares
        SHARED_LIB
    )
    
    if( ECM_FOUND )
        find_package( Qt5 COMPONENTS Test REQUIRED )
        include( ECMAddTests )

        ecm_add_test(
                Tests.cpp
            TEST_NAME
                fsresizertest
            LINK_LIBRARIES
                ${CALAMARES_LIBRARIES}
                calamares
                calamares_job_fsresizer  # From above
                ${YAMLCPP_LIBRARY}
                Qt5::Core
                Qt5::Test
        )
        set_target_properties( fsresizertest PROPERTIES AUTOMOC TRUE )
        target_include_directories(fsresizertest PRIVATE /usr/local/include )
    endif()
else()
    calamares_skip_module( "fsresizer (missing suitable KPMcore)" )
endif()
