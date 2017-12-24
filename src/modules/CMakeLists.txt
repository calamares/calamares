include( CMakeColors )

# The variable SKIP_MODULES can be set to skip particular modules;
# individual modules can also decide they must be skipped (e.g. OS-specific
# modules, or ones with unmet dependencies). Collect the skipped modules
# in this list.
set( LIST_SKIPPED_MODULES "" )

if( BUILD_TESTING )
    add_executable( test_conf test_conf.cpp )
    target_link_libraries( test_conf ${YAMLCPP_LIBRARY} )
endif()

file( GLOB SUBDIRECTORIES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*" )
string( REPLACE " " ";" SKIP_LIST "${SKIP_MODULES}" )
foreach( SUBDIRECTORY ${SUBDIRECTORIES} )
    list( FIND SKIP_LIST ${SUBDIRECTORY} DO_SKIP )

    if( NOT DO_SKIP EQUAL -1 )
        message( "${ColorReset}-- Skipping module ${BoldRed}${SUBDIRECTORY}${ColorReset}." )
        message( "" )
        list( APPEND LIST_SKIPPED_MODULES "${SUBDIRECTORY} (user request)" )
    elseif( ( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}" ) AND
            ( DO_SKIP EQUAL -1 ) )
        set( SKIPPED_MODULES )
        calamares_add_module_subdirectory( ${SUBDIRECTORY} )
        if ( SKIPPED_MODULES )
            list( APPEND LIST_SKIPPED_MODULES "${SKIPPED_MODULES}" )
        endif()
    endif()
endforeach()

if ( LIST_SKIPPED_MODULES )
    message( "${ColorReset}-- Skipped modules:" )
    foreach( SUBDIRECTORY ${LIST_SKIPPED_MODULES} )
        message( "${ColorReset}--   Skipped ${BoldRed}${SUBDIRECTORY}${ColorReset}." )
    endforeach()
    message( "" )
endif()

include( CalamaresAddTranslations )
add_calamares_python_translations( ${CALAMARES_TRANSLATION_LANGUAGES} )
