include_directories( ${CMAKE_CURRENT_BINARY_DIR}/libcalamares )
include_directories( ${CMAKE_CURRENT_LIST_DIR}/libcalamares )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )
include_directories( ${CMAKE_CURRENT_LIST_DIR} )

# library
add_subdirectory( libcalamares )

# application
add_subdirectory( calamares )
