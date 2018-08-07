include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( preservefiles
    TYPE job
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        permissions.cpp
        PreserveFiles.cpp
    LINK_PRIVATE_LIBRARIES
        calamares
    # REQUIRES mount  # To set the rootMountPoint
    SHARED_LIB
    EMERGENCY
)
