project( calamares CXX )

# The partition manager uses ECM but ECMConfig.cmake
# will complain if we require CMake less than 2.8.13,
# so never change this.
cmake_minimum_required( VERSION 3.2 )

set( CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" )

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

    set( CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded" )
    set( CMAKE_CXX_FLAGS_DEBUG          "-g" )
    set( CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG" )
    set( CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG" )
    set( CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g" )

    set( CMAKE_TOOLCHAIN_PREFIX "llvm-" )

    set( CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined" )
else()
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--no-undefined" )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--fatal-warnings -Wnon-virtual-dtor -Woverloaded-virtual -Werror=return-type" )
endif()

if( CMAKE_COMPILER_IS_GNUCXX )
    if( CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9 OR
        CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.9 )
        message( STATUS "Found GNU g++ ${CMAKE_CXX_COMPILER_VERSION}, enabling colorized error messages." )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto" )
    endif()
endif()

cmake_policy( SET CMP0023 OLD )
cmake_policy( SET CMP0028 NEW ) # double colons in KF5::Foo and Qt5::Foo are necessarily IMPORTED or ALIAS targets, don't search further
cmake_policy( SET CMP0043 OLD )

include( MacroOptionalFindPackage )
include( MacroLogFeature )

set( QT_VERSION 5.6.0 )

find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED Core Gui Widgets LinguistTools Svg Quick QuickWidgets )
find_package( YAMLCPP 0.5.1 REQUIRED )
find_package( PolkitQt5-1 REQUIRED )

option( WITH_PYTHON "Enable Python modules API (requires Boost.Python)." ON )
option( WITH_CRASHREPORTER "Build with CrashReporter" ON )
option( INSTALL_CONFIG "Install configuration files" ON)
option( WITH_PYTHONQT "Enable next generation Python modules API (experimental, requires PythonQt)." OFF )
option(BUILD_TESTING "Build the testing tree." ON)

if(BUILD_TESTING)
    enable_testing()
endif ()

if( CMAKE_SYSTEM_PROCESSOR MATCHES "arm" OR NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libcrashreporter-qt/CMakeLists.txt" )
    message( STATUS "Build of crashreporter disabled." )
    set( WITH_CRASHREPORTER OFF )
endif()

macro_optional_find_package( PythonLibs 3.3 )
macro_log_feature(
    PYTHONLIBS_FOUND
    "Python"
    "C interface libraries for the Python 3 interpreter."
    "http://python.org"
    FALSE "3.3"
    "Python 3 is used for some Calamares job modules."
)

if ( PYTHONLIBS_FOUND )
    include( BoostPython3 )
    find_boost_python3( 1.54.0 ${PYTHONLIBS_VERSION_STRING} CALAMARES_BOOST_PYTHON3_FOUND )
    macro_log_feature(
        CALAMARES_BOOST_PYTHON3_FOUND
        "Boost.Python"
        "A C++ library which enables seamless interoperability between C++ and Python 3."
        "http://www.boost.org"
        FALSE "1.54.0"
        "Boost.Python is used for interfacing with Calamares job modules written in Python 3."
    )

    macro_optional_find_package( PythonQt )
    macro_log_feature( PYTHONQT_FOUND
        "PythonQt"
        "A Python embedding solution for Qt applications."
        "http://pythonqt.sourceforge.net"
        FALSE "3.1"
        "PythonQt is used for the Python modules API."
    )
endif()

if ( PYTHONLIBS_NOTFOUND OR NOT CALAMARES_BOOST_PYTHON3_FOUND )
    set( WITH_PYTHON OFF )
endif()
if ( PYTHONLIBS_NOTFOUND OR NOT PYTHONQT_FOUND )
    set( WITH_PYTHONQT OFF )
endif()

###
### Calamares application info
###
set( CALAMARES_ORGANIZATION_NAME "Calamares" )
set( CALAMARES_ORGANIZATION_DOMAIN "github.com/calamares" )
set( CALAMARES_APPLICATION_NAME  "Calamares" )
set( CALAMARES_DESCRIPTION_SUMMARY "The distribution-independent installer framework" )
set( CALAMARES_TRANSLATION_LANGUAGES ar ast bg ca cs_CZ da de el en en_GB es_MX es eu fr hr hu id is it_IT ja lt nl pl pt_BR pt_PT ro ru sk sv th tr_TR zh_CN zh_TW )

### Bump version here
set( CALAMARES_VERSION_MAJOR 3 )
set( CALAMARES_VERSION_MINOR 1 )
set( CALAMARES_VERSION_PATCH 1 )
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
configure_file( CalamaresUse.cmake.in "${PROJECT_BINARY_DIR}/CalamaresUse.cmake" @ONLY )
file( COPY CalamaresAddLibrary.cmake DESTINATION "${PROJECT_BINARY_DIR}" )
file( COPY CalamaresAddModuleSubdirectory.cmake DESTINATION "${PROJECT_BINARY_DIR}" )
file( COPY CalamaresAddPlugin.cmake DESTINATION "${PROJECT_BINARY_DIR}" )
file( COPY CalamaresAddBrandingSubdirectory.cmake DESTINATION "${PROJECT_BINARY_DIR}" )

set( CALAMARES_LIBRARIES calamares )

set( THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty" )

add_subdirectory( thirdparty )
add_subdirectory( src )

macro_display_feature_log()

if ( NOT WITH_PYTHON )
    message( "-- WARNING: Building Calamares without Python support. Legacy Python job modules will not work.\n" )
endif()
if ( NOT WITH_PYTHONQT )
    message( "-- WARNING: Building Calamares without PythonQt support. Python modules will not work.\n" )
endif()


if ( NOT INSTALL_CONFIG )
    message( "-- WARNING: Configuration files will not be installed.\n" )
endif()

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
        "${PROJECT_BINARY_DIR}/CalamaresUse.cmake"
        "${PROJECT_BINARY_DIR}/CalamaresAddPlugin.cmake"
        "${PROJECT_BINARY_DIR}/CalamaresAddModuleSubdirectory.cmake"
        "${PROJECT_BINARY_DIR}/CalamaresAddLibrary.cmake"
        "${PROJECT_BINARY_DIR}/CalamaresAddBrandingSubdirectory.cmake"
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

if (INSTALL_CONFIG)
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
