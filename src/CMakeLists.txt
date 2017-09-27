include( CalamaresAddPlugin )
include( CalamaresAddModuleSubdirectory )
include( CalamaresAddLibrary )
include( CalamaresAddBrandingSubdirectory )

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/libcalamares
    ${CMAKE_CURRENT_LIST_DIR}/libcalamaresui
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/libcalamares
    ${CMAKE_CURRENT_BINARY_DIR}/libcalamaresui
)

# library
add_subdirectory( libcalamares )

add_subdirectory( libcalamaresui )

# all things qml
add_subdirectory( qml )

# application
add_subdirectory( calamares )

# plugins
add_subdirectory( modules )

# branding components
add_subdirectory( branding )
