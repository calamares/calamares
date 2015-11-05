include( ${PROJECT_BINARY_DIR}/CalamaresUse.cmake )

include_directories( ${CMAKE_CURRENT_BINARY_DIR}/libcalamares )
include_directories( ${CMAKE_CURRENT_LIST_DIR}/libcalamares )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${CMAKE_CURRENT_LIST_DIR} )

# library
add_subdirectory( libcalamares )

include_directories( ${CMAKE_CURRENT_BINARY_DIR}/libcalamaresui )
include_directories( ${CMAKE_CURRENT_LIST_DIR}/libcalamaresui )
add_subdirectory( libcalamaresui )

# all things qml
add_subdirectory( qml )

# application
add_subdirectory( calamares )

# plugins
add_subdirectory( modules )

# branding components
add_subdirectory( branding )

if( WITH_CRASHREPORTER )
    add_subdirectory( crashreporter )
endif()
