# - Find libcrypt
# Find the libcrypt includes and the libcrypt libraries
# This module defines
# LIBCRYPT_INCLUDE_DIR, root crypt include dir. Include crypt with crypt.h
# LIBCRYPT_LIBRARY, the path to libcrypt
# LIBCRYPT_FOUND, whether libcrypt was found


find_path( CRYPT_INCLUDE_DIR NAMES crypt.h
    HINTS
        ${CMAKE_INSTALL_INCLUDEDIR}
)

find_library( CRYPT_LIBRARIES NAMES crypt
    HINTS
        ${CMAKE_INSTALL_LIBDIR}
)

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( Crypt
                                   REQUIRED_VARS CRYPT_LIBRARIES CRYPT_INCLUDE_DIR )

mark_as_advanced( CRYPT_INCLUDE_DIR CRYPT_LIBRARIES )
