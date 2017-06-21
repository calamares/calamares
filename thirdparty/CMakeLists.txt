if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    # Suppress warnings entirely; not interesting in third-party code
    set( CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -w" )
endif()

if( WITH_CRASHREPORTER )
    macro( qt_wrap_ui )
        qt5_wrap_ui( ${ARGN} )
    endmacro()
    add_subdirectory( libcrashreporter-qt )
endif()
