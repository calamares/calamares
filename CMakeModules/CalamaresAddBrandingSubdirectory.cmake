include( CMakeColors )

function( calamares_add_branding_subdirectory )
    set( SUBDIRECTORY ${ARGV0} )

    if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/CMakeLists.txt" )
        add_subdirectory( $SUBDIRECTORY )
        message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} branding component: ${BoldRed}${SUBDIRECTORY}${ColorReset}" )

    elseif( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/branding.desc" )
        set( BRANDING_DIR share/calamares/branding )
        set( BRANDING_COMPONENT_DESTINATION ${BRANDING_DIR}/${SUBDIRECTORY} )

        if( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/lang" )
            message( "-- ${BoldYellow}Warning:${ColorReset} branding component ${BoldRed}${SUBDIRECTORY}${ColorReset} has a translations subdirectory but no CMakeLists.txt." )
            message( "" )
            return()
        endif()

        # We glob all the files inside the subdirectory, and we make sure they are
        # synced with the bindir structure and installed.
        file( GLOB BRANDING_COMPONENT_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY} "${SUBDIRECTORY}/*" )
        foreach( BRANDING_COMPONENT_FILE ${BRANDING_COMPONENT_FILES} )
            if( NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${BRANDING_COMPONENT_FILE} )
                configure_file( ${SUBDIRECTORY}/${BRANDING_COMPONENT_FILE} ${SUBDIRECTORY}/${BRANDING_COMPONENT_FILE} COPYONLY )

                install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${BRANDING_COMPONENT_FILE}
                         DESTINATION ${BRANDING_COMPONENT_DESTINATION} )
            endif()
        endforeach()

        message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} branding component: ${BoldRed}${SUBDIRECTORY}${ColorReset}" )
        if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
            message( "   ${Green}TYPE:${ColorReset} branding component" )
#            message( "   ${Green}FILES:${ColorReset} ${BRANDING_COMPONENT_FILES}" )
            message( "   ${Green}BRANDING_COMPONENT_DESTINATION:${ColorReset} ${BRANDING_COMPONENT_DESTINATION}" )
            message( "" )
        endif()
    else()
        message( "-- ${BoldYellow}Warning:${ColorReset} tried to add branding component subdirectory ${BoldRed}${SUBDIRECTORY}${ColorReset} which has no branding.desc." )
        message( "" )
    endif()
endfunction()
