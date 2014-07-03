include( ${PROJECT_BINARY_DIR}/CalamaresUse.cmake )

include_directories( ${CMAKE_CURRENT_BINARY_DIR}/libcalamares )
include_directories( ${CMAKE_CURRENT_LIST_DIR}/libcalamares )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${CMAKE_CURRENT_LIST_DIR} )

# library
add_subdirectory( libcalamares )
add_subdirectory( libcalamaresui )

# application
add_subdirectory( calamares )

include_directories( ${CMAKE_CURRENT_BINARY_DIR}/libcalamaresui )
include_directories( ${CMAKE_CURRENT_LIST_DIR}/libcalamaresui )

# plugins
add_subdirectory( modules )
