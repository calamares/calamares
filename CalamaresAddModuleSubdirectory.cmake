include( CMakeColors )

function( calamares_add_module_subdirectory )
    set( SUBDIRECTORY ${ARGV0} )

    # If this subdirectory has a CMakeLists.txt, we add_subdirectory it...
    if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/CMakeLists.txt" )
        add_subdirectory( ${SUBDIRECTORY} )
    # ...otherwise, we look for a module.desc.
    elseif( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/module.desc" )
        set( MODULES_DIR ${CMAKE_INSTALL_LIBDIR}/calamares/modules )
        set( MODULE_DESTINATION ${MODULES_DIR}/${SUBDIRECTORY} )
        set( MODULE_CONFIG_FILE ${SUBDIRECTORY}.conf )

        # We glob all the files inside the subdirectory, and we make sure they are
        # synced with the bindir structure and installed.
        file( GLOB MODULE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY} "${SUBDIRECTORY}/*" )
        foreach( MODULE_FILE ${MODULE_FILES} )
            if( NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${MODULE_FILE} )
                configure_file( ${SUBDIRECTORY}/${MODULE_FILE} ${SUBDIRECTORY}/${MODULE_FILE} COPYONLY )

                if( "${MODULE_FILE}" STREQUAL "${MODULE_CONFIG_FILE}" )
                    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${MODULE_FILE}
                             DESTINATION share/calamares/modules )
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
            message( "" )
        endif()
    else()
        message( "-- ${BoldYellow}Warning:${ColorReset} tried to add module subdirectory ${BoldRed}${SUBDIRECTORY}${ColorReset} which has no CMakeLists.txt or module.desc." )
        message( "" )
    endif()
endfunction()
