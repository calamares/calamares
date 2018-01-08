include( CMakeColors )
include( CalamaresAddTranslations )

set( MODULE_DATA_DESTINATION share/calamares/modules )

# Convenience function to indicate that a module has been skipped
# (optionally also why). Call this in the module's CMakeLists.txt
macro( calamares_skip_module )
    set( SKIPPED_MODULES ${SKIPPED_MODULES} ${ARGV} PARENT_SCOPE )
endmacro()

function( calamares_add_module_subdirectory )
    set( SUBDIRECTORY ${ARGV0} )

    set( SKIPPED_MODULES )
    set( MODULE_CONFIG_FILES "" )

    # If this subdirectory has a CMakeLists.txt, we add_subdirectory it...
    if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/CMakeLists.txt" )
        add_subdirectory( ${SUBDIRECTORY} )
        file( GLOB MODULE_CONFIG_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY} "${SUBDIRECTORY}/*.conf" )
        # Module has indicated it should be skipped, show that in
        # the calling CMakeLists (which is src/modules/CMakeLists.txt normally).
        if ( SKIPPED_MODULES )
            set( SKIPPED_MODULES ${SKIPPED_MODULES} PARENT_SCOPE )
        endif()
    # ...otherwise, we look for a module.desc.
    elseif( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/module.desc" )
        set( MODULES_DIR ${CMAKE_INSTALL_LIBDIR}/calamares/modules )
        set( MODULE_DESTINATION ${MODULES_DIR}/${SUBDIRECTORY} )

        # We glob all the files inside the subdirectory, and we make sure they are
        # synced with the bindir structure and installed.
        file( GLOB MODULE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY} "${SUBDIRECTORY}/*" )
        foreach( MODULE_FILE ${MODULE_FILES} )
            if( NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${MODULE_FILE} )
                configure_file( ${SUBDIRECTORY}/${MODULE_FILE} ${SUBDIRECTORY}/${MODULE_FILE} COPYONLY )

                get_filename_component( FLEXT ${MODULE_FILE} EXT )
                if( "${FLEXT}" STREQUAL ".conf" AND INSTALL_CONFIG)
                    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${MODULE_FILE}
                             DESTINATION ${MODULE_DATA_DESTINATION} )
                    list( APPEND MODULE_CONFIG_FILES ${MODULE_FILE} )
                else()
                    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${MODULE_FILE}
                             DESTINATION ${MODULE_DESTINATION} )
                endif()
            endif()
        endforeach()

        message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} module: ${BoldRed}${SUBDIRECTORY}${ColorReset}" )
        if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
            message( "   ${Green}TYPE:${ColorReset} jobmodule" )
#            message( "   ${Green}FILES:${ColorReset} ${MODULE_FILES}" )
            message( "   ${Green}MODULE_DESTINATION:${ColorReset} ${MODULE_DESTINATION}" )
            if( MODULE_CONFIG_FILES )
                if ( INSTALL_CONFIG )
                    message( "   ${Green}CONFIGURATION_FILES:${ColorReset} ${MODULE_CONFIG_FILES} => ${MODULE_DATA_DESTINATION}" )
                else()
                    message( "   ${Green}CONFIGURATION_FILES:${ColorReset} ${MODULE_CONFIG_FILES} => [Skipping installation]" )
                endif()
            endif()
            message( "" )
        endif()
        # We copy over the lang directory, if any
        if( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/lang" )
            install_calamares_gettext_translations(
                ${SUBDIRECTORY}
                SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/lang"
                FILENAME ${SUBDIRECTORY}.mo
                RENAME calamares-${SUBDIRECTORY}.mo
            )
        endif()
    else()
        message( "-- ${BoldYellow}Warning:${ColorReset} tried to add module subdirectory ${BoldRed}${SUBDIRECTORY}${ColorReset} which has no CMakeLists.txt or module.desc." )
        message( "" )
    endif()

    # Check any config files for basic correctness
    if ( BUILD_TESTING AND MODULE_CONFIG_FILES )
        set( _count 0 )
        foreach( _config_file ${MODULE_CONFIG_FILES} )
            set( _count_str "-${_count}" )
            if ( _count EQUAL 0 )
                set( _count_str "" )
            endif()
            add_test(
                NAME config-${SUBDIRECTORY}${_count_str}
                COMMAND test_conf ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${_config_file} )
            math( EXPR _count "${_count} + 1" )
        endforeach()
    endif()
endfunction()
