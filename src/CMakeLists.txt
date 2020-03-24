include( CalamaresAddPlugin )
include( CalamaresAddModuleSubdirectory )
include( CalamaresAddLibrary )
include( CalamaresAddBrandingSubdirectory )
include( CalamaresAddTest )

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
