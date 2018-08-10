# The variable SKIP_MODULES can be set to skip particular modules;
# individual modules can also decide they must be skipped (e.g. OS-specific
# modules, or ones with unmet dependencies). Collect the skipped modules
# in this list.
set( LIST_SKIPPED_MODULES "" )

if( BUILD_TESTING )
    add_executable( test_conf test_conf.cpp )
    target_link_libraries( test_conf ${YAMLCPP_LIBRARY} Qt5::Core )
    target_include_directories( test_conf PUBLIC ${YAMLCPP_INCLUDE_DIR} )
endif()

string( REPLACE " " ";" SKIP_LIST "${SKIP_MODULES}" )

file( GLOB SUBDIRECTORIES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*" )
list( SORT SUBDIRECTORIES )

set( _use_categories "" )
set( _found_categories "" )

foreach( SUBDIRECTORY ${SUBDIRECTORIES} )
    list( FIND SKIP_LIST ${SUBDIRECTORY} DO_SKIP )

    set( _skip_reason "user request" )
    # Handle the USE_<foo> variables by looking for subdirectories
    # with a <foo>-<implementation> kind of name.
    if( SUBDIRECTORY MATCHES "^[a-zA-Z0-9_]+-" )
        string( REGEX REPLACE "^[^-]+-" "" _implementation ${SUBDIRECTORY} )
        string( REGEX REPLACE "-.*" "" _category ${SUBDIRECTORY} )
        if( USE_${_category} )
            list( APPEND _use_categories ${_category} )
            if( "${_implementation}" STREQUAL "${USE_${_category}}" )
                list( APPEND _found_categories ${_category} )
            else()
                list( APPEND SKIP_LIST ${SUBDIRECTORY} )
                set( _skip_reason "USE_${_category}=${USE_${_category}}" )
                set( DO_SKIP 1 )
            endif()
        endif()
    endif()

    if( NOT DO_SKIP EQUAL -1 )
        message( "${ColorReset}-- Skipping module ${BoldRed}${SUBDIRECTORY}${ColorReset}." )
        message( "" )
        list( APPEND LIST_SKIPPED_MODULES "${SUBDIRECTORY} (${_skip_reason})" )
    elseif( ( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}" ) AND
            ( DO_SKIP EQUAL -1 ) )
        set( SKIPPED_MODULES )
        calamares_add_module_subdirectory( ${SUBDIRECTORY} )
        if ( SKIPPED_MODULES )
            list( APPEND LIST_SKIPPED_MODULES "${SKIPPED_MODULES}" )
        endif()
    endif()
endforeach()

# This is *also* done in top-level, so list is displayed
# both before and after the feature summary.
calamares_explain_skipped_modules( ${LIST_SKIPPED_MODULES} )

foreach( _category ${_use_categories} )
    list( FIND _found_categories ${_category} _found )
    if ( _found EQUAL -1 )
        message( FATAL_ERROR "USE_${_category} is set to ${USE_${_category}} and no module matches." )
    endif()
endforeach()

include( CalamaresAddTranslations )
add_calamares_python_translations( ${CALAMARES_TRANSLATION_LANGUAGES} )
