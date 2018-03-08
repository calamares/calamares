include( CMakeParseArguments)

include( CMakeColors )

# Usage calamares_add_branding( NAME <name> [SUBDIRECTORY <dir>])
#
# Adds a branding component to the build:
# - the component's top-level files are copied into the build-dir;
#   CMakeLists.txt is excluded from the glob.
# - the component's top-level files are installed into the component branding dir
#
# The branding component lives in <dir> if given, otherwise the
# current source directory. The branding component is installed
# with the given <name>, which is usually the name of the
# directory containing the component, and which must match the
# *componentName* in `branding.desc`.
function( calamares_add_branding )
    set( _CABT_SUBDIRECTORY "." )
    cmake_parse_arguments( _CABT "" "NAME;SUBDIRECTORY" "" ${ARGN} )
    if ( NOT _CABT_NAME )
        message( FATAL_ERROR "Branding component must have a NAME" )
    endif()

    set( NAME ${_CABT_NAME} )
    set( SUBDIRECTORY ${_CABT_SUBDIRECTORY} )

    set( BRANDING_DIR share/calamares/branding )
    set( BRANDING_COMPONENT_DESTINATION ${BRANDING_DIR}/${NAME} )

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

    message( "-- ${BoldYellow}Found ${CALAMARES_APPLICATION_NAME} branding component: ${BoldRed}${NAME}${ColorReset}" )
    if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
        message( "   ${Green}TYPE:${ColorReset} branding component" )
        message( "   ${Green}BRANDING_COMPONENT_DESTINATION:${ColorReset} ${BRANDING_COMPONENT_DESTINATION}" )
    endif()
endfunction()

# Usage calamares_add_branding_translations( NAME <name> [SUBDIRECTORY <dir>])
#
# Adds the translations for a branding component to the build:
# - the component's lang/ directory is scanned for .ts files
# - the component's translations are installed into the component branding dir
#
# Translation files must be called calamares-<name>_<lang>.ts . Optionally
# the lang/ dir is found in the given <dir> instead of the current source
# directory.
function( calamares_add_branding_translations )
    set( _CABT_SUBDIRECTORY "." )
    cmake_parse_arguments( _CABT "" "NAME;SUBDIRECTORY" "" ${ARGN} )
    if ( NOT _CABT_NAME )
        message( FATAL_ERROR "Branding component must have a NAME" )
    endif()

    set( NAME ${_CABT_NAME} )
    set( SUBDIRECTORY ${_CABT_SUBDIRECTORY} )

    set( BRANDING_DIR share/calamares/branding )
    set( BRANDING_COMPONENT_DESTINATION ${BRANDING_DIR}/${NAME} )

    file( GLOB BRANDING_TRANSLATION_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${SUBDIRECTORY}/lang/calamares-${NAME}_*.ts" )
    if ( BRANDING_TRANSLATION_FILES )
        qt5_add_translation( QM_FILES ${BRANDING_TRANSLATION_FILES} )
        add_custom_target( branding-translation-${NAME} ALL DEPENDS ${QM_FILES} )
        install( FILES ${QM_FILES} DESTINATION ${BRANDING_COMPONENT_DESTINATION}/lang/ )
        list( LENGTH BRANDING_TRANSLATION_FILES _branding_count )
        message( "   ${Green}BRANDING_TRANSLATIONS:${ColorReset} ${_branding_count} language(s)" )
    endif()
endfunction()

# Usage calamares_add_branding_subdirectory( <dir> )
#
# Adds a branding component from a subdirectory:
# - if there is a CMakeLists.txt, use that
# - otherwise assume a "standard" setup with top-level files and a lang/ dir for translations
#
function( calamares_add_branding_subdirectory SUBDIRECTORY )
    if( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/CMakeLists.txt" )
        add_subdirectory( ${SUBDIRECTORY} )
    elseif( EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/branding.desc" )
        calamares_add_branding( NAME ${SUBDIRECTORY} SUBDIRECTORY ${SUBDIRECTORY} )
        if( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/lang" )
            calamares_add_branding_translations( NAME ${SUBDIRECTORY} SUBDIRECTORY ${SUBDIRECTORY} )
        endif()
    else()
        message( "-- ${BoldYellow}Warning:${ColorReset} tried to add branding component subdirectory ${BoldRed}${SUBDIRECTORY}${ColorReset} which has no branding.desc." )
    endif()
    message( "" )
endfunction()
