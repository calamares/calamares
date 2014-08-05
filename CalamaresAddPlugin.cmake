include( CMakeParseArguments )
include( ${CALAMARES_CMAKE_DIR}/CalamaresAddLibrary.cmake )

function( calamares_add_plugin )
    # parse arguments ( name needs to be saved before passing ARGN into the macro )
    set( NAME ${ARGV0} )
    set( options NO_INSTALL SHARED_LIB )
    set( oneValueArgs NAME TYPE EXPORT_MACRO )
    set( multiValueArgs SOURCES UI LINK_LIBRARIES COMPILE_DEFINITIONS )
    cmake_parse_arguments( PLUGIN "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
    set( PLUGIN_NAME ${NAME} )
    set( PLUGIN_DESTINATION ${CMAKE_INSTALL_LIBDIR}/calamares/modules/${PLUGIN_NAME} )
    set( PLUGIN_DESC_FILE module.desc )
    set( PLUGIN_CONFIG_FILE ${NAME}.conf )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" )

    include( CMakeColors )
    message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} module: ${BoldRed}${PLUGIN_NAME}${ColorReset}" )
    if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
        message( "   ${Green}TYPE:${ColorReset} ${PLUGIN_TYPE}" )
        message( "   ${Green}LINK_LIBRARIES:${ColorReset} ${PLUGIN_LINK_LIBRARIES}" )
#        message( "   ${Green}SOURCES:${ColorReset} ${PLUGIN_SOURCES}" )
#        message( "   ${Green}UI:${ColorReset} ${PLUGIN_UI}" )
#        message( "   ${Green}EXPORT_MACRO:${ColorReset} ${PLUGIN_EXPORT_MACRO}" )
#        message( "   ${Green}NO_INSTALL:${ColorReset} ${PLUGIN_NO_INSTALL}" )
#        message( "   ${Green}CONFIG_FILE:${ColorReset} ${PLUGIN_CONFIG_FILE}" )
        message( "   ${Green}PLUGIN_DESTINATION:${ColorReset} ${PLUGIN_DESTINATION}" )
        message( "" )
    endif()
    # create target name once for convenience
    set( target "calamares_${PLUGIN_TYPE}_${PLUGIN_NAME}" )

    # determine target type
    if( NOT ${PLUGIN_SHARED_LIB} )
        set( target_type "MODULE" )
    else()
        set( target_type "SHARED" )
    endif()

    list( APPEND calamares_add_library_args
        "${target}"
        "EXPORT_MACRO" "${PLUGIN_EXPORT_MACRO}"
        "TARGET_TYPE" "${target_type}"
        "SOURCES" "${PLUGIN_SOURCES}"
    )

    if( PLUGIN_UI )
        list( APPEND calamares_add_library_args "UI" "${PLUGIN_UI}" )
    endif()

    if( PLUGIN_LINK_LIBRARIES )
        list( APPEND calamares_add_library_args "LINK_LIBRARIES" "${PLUGIN_LINK_LIBRARIES}" )
    endif()

    if( PLUGIN_COMPILE_DEFINITIONS )
        list( APPEND calamares_add_library_args "COMPILE_DEFINITIONS" ${PLUGIN_COMPILE_DEFINITIONS} )
    endif()

    list( APPEND calamares_add_library_args "NO_VERSION" )

    list( APPEND calamares_add_library_args "INSTALL_BINDIR" "${PLUGIN_DESTINATION}" )

    calamares_add_library( ${calamares_add_library_args} )

    configure_file( ${PLUGIN_DESC_FILE} ${PLUGIN_DESC_FILE} COPYONLY )
    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_DESC_FILE}
             DESTINATION ${PLUGIN_DESTINATION} )

    if( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_CONFIG_FILE}" )
        configure_file( ${PLUGIN_CONFIG_FILE} ${PLUGIN_CONFIG_FILE} COPYONLY )
        install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${PLUGIN_CONFIG_FILE}
                 DESTINATION share/calamares/modules )
    endif()
endfunction()
