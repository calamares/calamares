file( GLOB SUBDIRECTORIES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*" )

# Iterate over all the subdirectories which have a qmldir file, copy them over to the build dir,
# and install them into share/calamares/qml/calamares
foreach( SUBDIRECTORY ${SUBDIRECTORIES} )
    if( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}"
        AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/qmldir" )

        set( QML_DIR share/calamares/qml )
        set( QML_MODULE_DESTINATION ${QML_DIR}/calamares/${SUBDIRECTORY} )

        # We glob all the files inside the subdirectory, and we make sure they are
        # synced with the bindir structure and installed.
        file( GLOB QML_MODULE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY} "${SUBDIRECTORY}/*" )
        foreach( QML_MODULE_FILE ${QML_MODULE_FILES} )
            if( NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${QML_MODULE_FILE} )
                configure_file( ${SUBDIRECTORY}/${QML_MODULE_FILE} ${SUBDIRECTORY}/${QML_MODULE_FILE} COPYONLY )

                install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${QML_MODULE_FILE}
                         DESTINATION ${QML_MODULE_DESTINATION} )
            endif()
        endforeach()

        message( "-- ${BoldYellow}Configured QML module: ${BoldRed}calamares.${SUBDIRECTORY}${ColorReset}" )

    endif()
endforeach()
