include( CMakeColors )

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
    elseif( ( IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}" ) AND
            ( DO_SKIP EQUAL -1 ) )
        calamares_add_module_subdirectory( ${SUBDIRECTORY} )
    endif()
endforeach()

include( CalamaresAddTranslations )
add_calamares_python_translations( ${CALAMARES_TRANSLATION_LANGUAGES} )
