# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Calamares is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Calamares is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
#
#   SPDX-License-Identifier: GPL-3.0+
#   License-Filename: LICENSE
#
###
#
# Generally, this CMakeLists.txt will find all the dependencies for Calamares
# and complain appropriately. See below (later in this file) for CMake-level
# options. There are some "secret" options as well:
#
#   SKIP_MODULES    : a space or semicolon-separated list of directory names
#                     under src/modules that should not be built.
#
# Example usage:
#
#   cmake . -DSKIP_MODULES="partition luksbootkeycfg"

project( calamares C CXX )

cmake_minimum_required( VERSION 3.2 )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" )

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_C_STANDARD 99 )
set( CMAKE_C_STANDARD_REQUIRED ON )

if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    message( STATUS "Found Clang ${CMAKE_CXX_COMPILER_VERSION}, setting up Clang-specific compiler flags." )
    set( CMAKE_C_FLAGS                  "${CMAKE_C_FLAGS} -Wall" )
    set( CMAKE_C_FLAGS_DEBUG            "-g" )
    set( CMAKE_C_FLAGS_MINSIZEREL       "-Os -DNDEBUG" )
    set( CMAKE_C_FLAGS_RELEASE          "-O4 -DNDEBUG" )
    set( CMAKE_C_FLAGS_RELWITHDEBINFO   "-O2 -g" )

    # Clang warnings: doing *everything* is counter-productive, since it warns
    # about things which we can't fix (e.g. C++98 incompatibilities, but
    # Calamares is C++14).
    foreach( CLANG_WARNINGS
        -Weverything
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        -Wno-padded
        -Wno-undefined-reinterpret-cast
        -Wno-global-constructors
        -Wno-exit-time-destructors
        -Wno-missing-prototypes
        -Wno-documentation-unknown-command
    )
        string( APPEND CMAKE_CXX_FLAGS " ${CLANG_WARNINGS}" )
    endforeach()

    # Third-party code where we don't care so much about compiler warnings
    # (because it's uncomfortable to patch) get different flags; use
    #       mark_thirdparty_code( <file> [<file>...] )
    # to switch off warnings for those sources.
    set( SUPPRESS_3RDPARTY_WARNINGS "-Wno-everything" )
    set( SUPPRESS_BOOST_WARNINGS " -Wno-zero-as-null-pointer-constant -Wno-disabled-macro-expansion" )

    set( CMAKE_CXX_FLAGS_DEBUG          "-g" )
    set( CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG" )
    set( CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG" )
    set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g" )

    set( CMAKE_TOOLCHAIN_PREFIX "llvm-" )

    set( CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined" )
else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-undefined" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--fatal-warnings -Wnon-virtual-dtor -Woverloaded-virtual -Werror=return-type" )

    set( SUPPRESS_3RDPARTY_WARNINGS "" )
    set( SUPPRESS_BOOST_WARNINGS "" )
endif()

# Use mark_thirdparty_code() to reduce warnings from the compiler
# on code that we're not going to fix. Call this with a list of files.
macro(mark_thirdparty_code)
    set_source_files_properties( ${ARGV}
        PROPERTIES
            COMPILE_FLAGS "${SUPPRESS_3RDPARTY_WARNINGS}"
            COMPILE_DEFINITIONS "THIRDPARTY"
    )
endmacro()

if( CMAKE_COMPILER_IS_GNUCXX )
    if( CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9 OR
        CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.9 )
        message( STATUS "Found GNU g++ ${CMAKE_CXX_COMPILER_VERSION}, enabling colorized error messages." )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto" )
    endif()
endif()

include( FeatureSummary )

set( QT_VERSION 5.6.0 )

find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED Core Gui Widgets LinguistTools Svg Quick QuickWidgets )
find_package( YAMLCPP 0.5.1 REQUIRED )
find_package( PolkitQt5-1 REQUIRED )

# Find ECM once, and add it to the module search path; Calamares
# modules that need ECM can do
#   find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE),
# no need to mess with the module path after.
set( ECM_VERSION 5.10.0 )
find_package(ECM ${ECM_VERSION} NO_MODULE)
if( ECM_FOUND )
    set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})
endif()

option( INSTALL_CONFIG "Install configuration files" ON )
option( WITH_PYTHON "Enable Python modules API (requires Boost.Python)." ON )
option( WITH_PYTHONQT "Enable next generation Python modules API (experimental, requires PythonQt)." OFF )
option( BUILD_TESTING "Build the testing tree." ON )

if( BUILD_TESTING )
    enable_testing()
endif ()

find_package( PythonLibs 3.3 )
set_package_properties(
    PythonLibs PROPERTIES
    DESCRIPTION "C interface libraries for the Python 3 interpreter."
    URL "http://python.org"
    PURPOSE "Python 3 is used for Python job modules."
)

if ( PYTHONLIBS_FOUND )
    include( BoostPython3 )
    find_boost_python3( 1.54.0 ${PYTHONLIBS_VERSION_STRING} CALAMARES_BOOST_PYTHON3_FOUND )
    set_package_properties(
        Boost PROPERTIES
        PURPOSE "Boost.Python is used for Python job modules."
    )

    find_package( PythonQt )
    set_package_properties( PythonQt PROPERTIES
        DESCRIPTION "A Python embedding solution for Qt applications."
        URL "http://pythonqt.sourceforge.net"
        PURPOSE "PythonQt is used for Python view modules."
    )
endif()

if( PYTHONLIBS_NOTFOUND OR NOT CALAMARES_BOOST_PYTHON3_FOUND )
    set( WITH_PYTHON OFF )
endif()
if( PYTHONLIBS_NOTFOUND OR NOT PYTHONQT_FOUND )
    set( WITH_PYTHONQT OFF )
endif()

###
### Calamares application info
###
set( CALAMARES_ORGANIZATION_NAME "Calamares" )
set( CALAMARES_ORGANIZATION_DOMAIN "github.com/calamares" )
set( CALAMARES_APPLICATION_NAME  "Calamares" )
set( CALAMARES_DESCRIPTION_SUMMARY "The distribution-independent installer framework" )
set( CALAMARES_TRANSLATION_LANGUAGES ar ast bg ca cs_CZ da de el en en_GB es_MX es eu fr he hr hu id is it_IT ja lt nl pl pt_BR pt_PT ro ru sk sv th tr_TR zh_CN zh_TW )

### Bump version here
set( CALAMARES_VERSION_MAJOR 3 )
set( CALAMARES_VERSION_MINOR 1 )
set( CALAMARES_VERSION_PATCH 13 )
set( CALAMARES_VERSION_RC 0 )

set( CALAMARES_VERSION ${CALAMARES_VERSION_MAJOR}.${CALAMARES_VERSION_MINOR}.${CALAMARES_VERSION_PATCH} )
set( CALAMARES_VERSION_SHORT "${CALAMARES_VERSION}" )
if( CALAMARES_VERSION_RC )
    set( CALAMARES_VERSION ${CALAMARES_VERSION}rc${CALAMARES_VERSION_RC} )
endif()

# additional info for non-release builds
if( NOT BUILD_RELEASE AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git/" )
    include( CMakeDateStamp )
    set( CALAMARES_VERSION_DATE "${CMAKE_DATESTAMP_YEAR}${CMAKE_DATESTAMP_MONTH}${CMAKE_DATESTAMP_DAY}" )
    if( CALAMARES_VERSION_DATE GREATER 0 )
        set( CALAMARES_VERSION ${CALAMARES_VERSION}.${CALAMARES_VERSION_DATE} )
    endif()

    include( CMakeVersionSource )
    if( CMAKE_VERSION_SOURCE )
        set( CALAMARES_VERSION ${CALAMARES_VERSION}-${CMAKE_VERSION_SOURCE} )
    endif()
endif()

# enforce using constBegin, constEnd for const-iterators
add_definitions( "-DQT_STRICT_ITERATORS" )

# set paths
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" )

# Better default installation paths: GNUInstallDirs defines
# CMAKE_INSTALL_FULL_SYSCONFDIR to be CMAKE_INSTALL_PREFIX/etc by default
# but we really want /etc
if( NOT DEFINED CMAKE_INSTALL_SYSCONFDIR )
    set( CMAKE_INSTALL_SYSCONFDIR "/etc" )
endif()

# make predefined install dirs available everywhere
include( GNUInstallDirs )

# make uninstall support
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

# Early configure these files as we need them later on
set( CALAMARES_CMAKE_DIR "${CMAKE_SOURCE_DIR}/CMakeModules" )
set( CALAMARES_LIBRARIES calamares )

set( THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty" )

### Example Distro
#
# For testing purposes Calamares includes a very, very, limited sample
# distro called "Generic". The root filesystem of "Generic" lives in
# data/example-root and can be squashed up as part of the build, so
# that a pure-upstream run of ./calamares -d from the build directory
# (with all the default settings and configurations) can actually
# do an complete example run.
#
# Some binaries from the build host (e.g. /bin and /lib) are also
# squashed into the example filesystem.
#
# To build the example distro (for use by the default, example,
# unsquashfs module), build the target 'example-distro', eg.:
#
#   make example-distro
#
find_program( mksquashfs_PROGRAM mksquashfs )
if( mksquashfs_PROGRAM )
    set( mksquashfs_FOUND ON )
    set( src_fs ${CMAKE_SOURCE_DIR}/data/example-root/ )
    set( dst_fs ${CMAKE_BINARY_DIR}/example.sqfs )
    if( EXISTS ${src_fs} )
        # based on the build host. If /lib64 exists, assume it is needed.
        # Collect directories needed for a minimal binary distro,
        # Note that the last path component is added to the root, so
        # if you add /usr/sbin here, it will be put into /sbin_1.
        # Add such paths to /etc/profile under ${src_fs}.
        set( candidate_fs /sbin /bin /lib /lib64 )
        set( host_fs "" )
        foreach( c_fs ${candidate_fs} )
            if( EXISTS ${c_fs} )
                list( APPEND host_fs ${c_fs} )
            endif()
        endforeach()
        add_custom_command(
            OUTPUT ${dst_fs}
            COMMAND ${mksquashfs_PROGRAM} ${src_fs} ${dst_fs} -all-root
            COMMAND ${mksquashfs_PROGRAM} ${host_fs} ${dst_fs} -all-root
        )
        add_custom_target(example-distro DEPENDS ${dst_fs})
    endif()
else()
    set( mksquashfs_FOUND OFF )
endif()
# Doesn't list mksquashfs as an optional dep, though, because it
# hasn't been sent through the find_package() scheme.
#
# "http://tldp.org/HOWTO/SquashFS-HOWTO/creatingandusing.html"
add_feature_info( ExampleDistro ${mksquashfs_FOUND} "Create example-distro target.")

# add_subdirectory( thirdparty )
add_subdirectory( src )

add_feature_info(Python ${WITH_PYTHON} "Python job modules")
add_feature_info(PythonQt ${WITH_PYTHONQT} "Python view modules")
add_feature_info(Config ${INSTALL_CONFIG} "Install Calamares configuration")

feature_summary(WHAT ALL)

# Add all targets to the build-tree export set
set( CMAKE_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/Calamares" CACHE PATH  "Installation directory for CMake files" )
set( CMAKE_INSTALL_FULL_CMAKEDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_CMAKEDIR}" )
export( TARGETS calamares
    FILE "${PROJECT_BINARY_DIR}/CalamaresLibraryDepends.cmake" )

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export( PACKAGE Calamares )

# Create a CalamaresBuildTreeSettings.cmake file for the use from the build tree
configure_file( CalamaresBuildTreeSettings.cmake.in "${PROJECT_BINARY_DIR}/CalamaresBuildTreeSettings.cmake" @ONLY )

# Create the CalamaresConfig.cmake and CalamaresConfigVersion files
file( RELATIVE_PATH CONF_REL_INCLUDE_DIR "${CMAKE_INSTALL_FULL_CMAKEDIR}" "${CMAKE_INSTALL_FULL_INCLUDEDIR}" )

configure_file( CalamaresConfig.cmake.in "${PROJECT_BINARY_DIR}/CalamaresConfig.cmake" @ONLY )
configure_file( CalamaresConfigVersion.cmake.in "${PROJECT_BINARY_DIR}/CalamaresConfigVersion.cmake" @ONLY )

# Install the cmake files
install(
    FILES
        "${PROJECT_BINARY_DIR}/CalamaresConfig.cmake"
        "${PROJECT_BINARY_DIR}/CalamaresConfigVersion.cmake"
        "CMakeModules/CalamaresAddPlugin.cmake"
        "CMakeModules/CalamaresAddModuleSubdirectory.cmake"
        "CMakeModules/CalamaresAddLibrary.cmake"
        "CMakeModules/CalamaresAddBrandingSubdirectory.cmake"
    DESTINATION
        "${CMAKE_INSTALL_CMAKEDIR}"
)

# Install the export set for use with the install-tree
install(
    EXPORT
        CalamaresLibraryDepends
    DESTINATION
        "${CMAKE_INSTALL_CMAKEDIR}"
)

if( INSTALL_CONFIG )
    install(
        FILES
            settings.conf
        DESTINATION
            share/calamares
    )
endif()

install(
  FILES
      com.github.calamares.calamares.policy
  DESTINATION
      "${POLKITQT-1_POLICY_FILES_INSTALL_DIR}"
)

install(
  FILES
      calamares.desktop
  DESTINATION
      ${CMAKE_INSTALL_DATADIR}/applications
)

install(
    FILES
        man/calamares.8
    DESTINATION
        ${CMAKE_INSTALL_MANDIR}/man8/
)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY
)

add_custom_target( uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
)
