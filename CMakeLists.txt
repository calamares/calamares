# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
#   Calamares is Free Software: see the License-Identifier above.
#
#   Individual files may have different licenses (like the CMake
#   infrastructure, which is BSD-2-Clause licensed). Check the SPDX
#   identifiers in each file.
#
###
#
# Generally, this CMakeLists.txt will find all the dependencies for Calamares
# and complain appropriately. See below (later in this file) for CMake-level
# options. There are some "secret" options as well:
#
#   SKIP_MODULES    : a space or semicolon-separated list of directory names
#                     under src/modules that should not be built.
#   USE_<foo>       : fills in SKIP_MODULES for modules called <foo>-<something>.
#   WITH_<foo>      : try to enable <foo> (these usually default to ON). For
#                     a list of WITH_<foo> grep CMakeCache.txt after running
#                     CMake once. These affect the ABI offered by Calamares.
#                       - PYBIND11 (use bundled pybind11, default ON, needs WITH_PYTHON)
#                       - PYTHON (enable Python Job modules, default ON if Python is found)
#                       - QML (enable QML UI View modules, default ON)
#                       - QT6 (use Qt6 rather than Qt5, default to OFF)
#                     The WITH_* options affect the ABI of Calamares: you must
#                     build (C++) modules for Calamares with the same WITH_*
#                     settings, or they may not load at all.
#   BUILD_<foo>     : choose additional things to build
#                       - APPDATA (use AppData in packagechooser, requires QtXml)
#                       - APPSTREAM (use AppStream in packagechooser, requires libappstream-qt)
#                       - BUILD_CRASH_REPORTING (uses KCrash, rather than Calamares internal, for crash reporting)
#                       - SCHEMA_TESTING (requires Python, see ci/configvalidator.py)
#                       - TESTING (standard CMake option)
#   DEBUG_<foo>     : special developer flags for debugging.
#
# Example usage:
#
#   cmake . -DSKIP_MODULES="partition luksbootkeycfg"
#
# To obtain the version number of calamares, run CMake in script mode, e.g.
#   cmake -P CMakeLists.txt

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CALAMARES_VERSION 3.3.6)
set(CALAMARES_RELEASE_MODE ON) # Set to ON during a release

if(CMAKE_SCRIPT_MODE_FILE)
    include(${CMAKE_CURRENT_LIST_DIR}/CMakeModules/ExtendedVersion.cmake)
    set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
    extend_version( ${CALAMARES_VERSION} ${CALAMARES_RELEASE_MODE}  _vshort _vlong )
    message("${_vlong}")
    return()
endif()

# Massage the version for CMake if there is a version-suffix
string(REGEX REPLACE "-.*" "" CALAMARES_VERSION_SHORT "${CALAMARES_VERSION}")
# And preserve the original version (suffix and all) because project() overwrites
# .. but if we're doing non-release builds, this gets replaced with git versioning.
set(CALAMARES_VERSION_LONG "${CALAMARES_VERSION}")

project(CALAMARES VERSION ${CALAMARES_VERSION_SHORT} LANGUAGES C CXX HOMEPAGE_URL "https://calamares.io/")

if(NOT CALAMARES_RELEASE_MODE AND CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build development versions in the source-directory.")
endif()
# Calamares in the 3.3 series promises ABI compatbility, so it sets a
# .so-version equal to the series number. We use ci/abicheck.sh to
# keep track of this. Note that the **alpha** releases also have
# such an .so-version, but are not ABI-stable yet.
set(CALAMARES_SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

### OPTIONS
#
option(INSTALL_POLKIT "Install Polkit configuration" ON)
option(INSTALL_COMPLETION "Install shell completions" OFF)
option(INSTALL_CONFIG "Install configuration files" OFF)
# When adding WITH_* that affects the ABI offered by libcalamares,
# also update libcalamares/CalamaresConfig.h.in
option(WITH_PYBIND11 "Use bundled pybind11 instead of Boost::Python" ON)
option(WITH_PYTHON "Enable Python modules API." ON)
option(WITH_QML "Enable QML UI options." ON)
option(WITH_QT6 "Use Qt6 instead of Qt5" OFF)
#
# Additional parts to build that do not affect ABI
option(BUILD_SCHEMA_TESTING "Enable schema-validation-tests" ON)
# Options for the calamares executable
option(BUILD_CRASH_REPORTING "Enable crash reporting with KCrash." ON)

# Possible debugging flags are:
#  - DEBUG_TIMEZONES draws latitude and longitude lines on the timezone
#    widget and enables chatty debug logging, for dealing with the timezone
#    location database.
#  - DEBUG_FILESYSTEMS does extra logging and checking when looking at
#    partition configuration. Lists known KPMCore FS types.
#  - DEBUG_PARTITION_UNSAFE (see partition/CMakeLists.txt)
#  - DEBUG_PARTITION_BAIL_OUT (see partition/CMakeLists.txt)

### USE_*
#
# By convention, when there are multiple modules that implement similar
# functionality, and it only makes sense to have **at most one** of them
# enabled at any time, those modules are named <foo>-<implementation>.
# For example, services-systemd and services-openrc.
#
# Setting up SKIP_MODULES to ignore "the ones you don't want" can be
# annoying and error-prone (e.g. if a new module shows up). The USE_*
# modules provide a way to do automatic selection. To pick exactly
# one of the implementations from group <foo>, set USE_<foo> to the
# name of the implementation. If USE_<foo> is unset, or empty, then
# all the implementations are enabled (this just means they are
# **available** to `settings.conf`, not that they are used).
#
# To explicitly disable a set of modules, set USE_<foo>=none
# (e.g. the literal string none), which won't match any of the
# modules but is handled specially.
#
# The following USE_* functionalities are available:
#  - *services* picks one of the two service-configuration modules,
#    for either systemd or openrc. This defaults to empty so that
#    **both** modules are available.
set(USE_services "" CACHE STRING "Select the services module to use")

### Calamares application info
#
set(CALAMARES_ORGANIZATION_NAME "Calamares")
set(CALAMARES_ORGANIZATION_DOMAIN "github.com/calamares")
set(CALAMARES_APPLICATION_NAME "Calamares")
set(CALAMARES_DESCRIPTION_SUMMARY "The distribution-independent installer framework")

### Transifex (languages) info
#
# complete = 100% translated,
# good = nearly complete (use own judgement, right now >= 75%)
# ok = incomplete (more than 25% untranslated, at least 5% translated),
# incomplete = <5% translated, placeholder in tx; these are not included.
#
# Language en (source language) is added later. It isn't listed in
# Transifex either. Get the list of languages and their status
# from https://app.transifex.com/calamares/calamares/ , or (preferably)
# use ci/txstats.py to automatically check.
#
# When adding a new language, take care that it is properly loaded
# by the translation framework. Languages with alternate scripts
# (sr@latin in particular) or location (ca@valencia) need special
# handling in libcalamares/locale/Translation.h .
#
# NOTE: move ie (Interlingue) to _ok once Qt supports it.
# NOTE: update these lines by running `txstats.py`, or for full automation
#       `txstats.py -e`. See also
#
# Total 80 languages
set( _tx_complete de en es_AR fi_FI hr hu ja lt tr_TR uk zh_TW )
set( _tx_good az az_AZ be bg ca cs_CZ es fr fur he hi is it_IT ko
    pl pt_BR pt_PT ru si sq sv zh_CN )
set( _tx_ok ar as ast bn ca@valencia da el en_GB eo es_MX et eu fa
    gl id ka ml mr nb nl oc ro sk sl sr sr@latin tg th vi )
set( _tx_incomplete bqi es_PR gu ie ja-Hira kk kn lo lv mk ne_NP
    ro_RO ta_IN te ur uz zh zh_HK )
# Total 80 languages

### Required versions
#
# See DEPENDENCIES section below.
if(WITH_QT6)
    message(STATUS "Building Calamares with Qt6")
    set(qtname "Qt6")
    set(kfname "KF6")
    set(QT_VERSION 6.5.0)
    set(ECM_VERSION 5.240)
    set(KF_VERSION 5.240) # KDE Neon weirdness
    # API that was deprecated before Qt 5.15 causes a compile error
    add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x060400)
    # Something to add to filenames for this specific Qt version
    set(QT_VERSION_SUFFIX "-qt6")
else()
    message(STATUS "Building Calamares with Qt5")
    set(qtname "Qt5")
    set(kfname "KF5")
    set(QT_VERSION 5.15.0)
    set(ECM_VERSION 5.78)
    set(KF_VERSION 5.78)
    # API that was deprecated before Qt 5.15 causes a compile error
    add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050f00)
    # Something to add to filenames for this specific Qt version
    set(QT_VERSION_SUFFIX "")
endif()

set(BOOSTPYTHON_VERSION 1.72.0)
set(PYTHONLIBS_VERSION 3.6)
set(YAMLCPP_VERSION 0.5.1)

### CMAKE SETUP
#
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")

# Enable IN_LIST
if(POLICY CMP0057)
    cmake_policy(SET CMP0057 NEW)
endif()
# Let ``AUTOMOC`` and ``AUTOUIC`` process ``GENERATED`` files.
if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()
# Recognize more macros to trigger automoc
if(NOT CMAKE_VERSION VERSION_LESS "3.10.0")
    list(
        APPEND
        CMAKE_AUTOMOC_MACRO_NAMES
        "K_PLUGIN_FACTORY_WITH_JSON"
        "K_EXPORT_PLASMA_DATAENGINE_WITH_JSON"
        "K_EXPORT_PLASMA_RUNNER"
    )
endif()

# CMake Modules
include(CMakePackageConfigHelpers)
include(CTest)
include(FeatureSummary)

# Calamares Modules
include(CMakeColors)

### C++ SETUP
#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror=return-type")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS_DEBUG "-Og -g")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined -Wl,--fatal-warnings ${CMAKE_SHARED_LINKER_FLAGS}")

# If no build type is set, pick a reasonable one
if(NOT CMAKE_BUILD_TYPE)
    if(CALAMARES_RELEASE_MODE)
        set(CMAKE_BUILD_TYPE "RelWithDebInfo")
    else()
        set(CMAKE_BUILD_TYPE "Debug")
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Found Clang ${CMAKE_CXX_COMPILER_VERSION}, setting up Clang-specific compiler flags.")

    # Clang warnings: doing *everything* is counter-productive, since it warns
    # about things which we can't fix (e.g. C++98 incompatibilities, but
    # Calamares is C++17).
    foreach(
        CLANG_WARNINGS
        -Weverything
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        -Wno-padded
        -Wno-undefined-reinterpret-cast
        -Wno-global-constructors
        -Wno-exit-time-destructors
        -Wno-missing-prototypes
        -Wno-documentation-unknown-command
        -Wno-unknown-warning-option
    )
        string(APPEND CMAKE_CXX_FLAGS " ${CLANG_WARNINGS}")
    endforeach()

    # The dwarf-debugging flags are slightly different, too
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " -gdwarf")
    string(APPEND CMAKE_C_FLAGS_DEBUG " -gdwarf")

    # Third-party code where we don't care so much about compiler warnings
    # (because it's uncomfortable to patch) get different flags; use
    #       mark_thirdparty_code( <file> [<file>...] )
    # to switch off warnings for those sources.
    set(SUPPRESS_3RDPARTY_WARNINGS "-Wno-everything")

    set(CMAKE_TOOLCHAIN_PREFIX "llvm-")

    # The path prefix is only relevant for CMake 3.16 and later, fixes #1286
    set(CMAKE_AUTOMOC_PATH_PREFIX OFF)
    set(CALAMARES_AUTOMOC_OPTIONS "-butils/moc-warnings.h")
    set(CALAMARES_AUTOUIC_OPTIONS --include utils/moc-warnings.h)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual")

    set(SUPPRESS_3RDPARTY_WARNINGS "")
endif()

# Use mark_thirdparty_code() to reduce warnings from the compiler
# on code that we're not going to fix. Call this with a list of files.
macro(mark_thirdparty_code)
    set_source_files_properties(
        ${ARGV}
        PROPERTIES COMPILE_FLAGS "${SUPPRESS_3RDPARTY_WARNINGS}" COMPILE_DEFINITIONS "THIRDPARTY"
    )
endmacro()

if(CMAKE_COMPILER_IS_GNUCXX)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.9 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 4.9)
        message(STATUS "Found GNU g++ ${CMAKE_CXX_COMPILER_VERSION}, enabling colorized error messages.")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=auto")
    endif()
endif()

### DEPENDENCIES
#
find_package(${qtname} ${QT_VERSION} CONFIG REQUIRED Concurrent Core DBus Gui LinguistTools Network Svg Widgets)
if(WITH_QML)
    find_package(${qtname} ${QT_VERSION} CONFIG REQUIRED Quick QuickWidgets)
endif()
# Note that some modules need more Qt modules, optionally.

find_package(YAMLCPP ${YAMLCPP_VERSION})
set_package_properties(
    YAMLCPP
    PROPERTIES
    TYPE REQUIRED
    DESCRIPTION "YAML parser for C++"
    PURPOSE "Parsing of configuration files"
)

find_package(Polkit${qtname}-1)
if(INSTALL_POLKIT)
    set_package_properties(
        Polkit${qtname}-1
        PROPERTIES
        TYPE REQUIRED
    )
endif()
set_package_properties(
    Polkit${qtname}-1
    PROPERTIES
    DESCRIPTION "${qtname} support for Polkit"
    URL "https://cgit.kde.org/polkit-qt-1.git"
    PURPOSE "Polkit${qtname}-1 helps with installing Polkit configuration"
)

# Find ECM once, and add it to the module search path; Calamares
# modules that need ECM can do
#   if(ECM_FOUND)
# no need to mess with the module path after.
find_package(ECM ${ECM_VERSION} NO_MODULE)
if(ECM_FOUND)
    message(STATUS "Found KDE ECM ${ECM_MODULE_PATH}")
    set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})
    if(BUILD_TESTING)
        # ECM implies that we can build the tests, too
        find_package(${qtname} COMPONENTS Test REQUIRED)
        include(ECMAddTests)
    endif()
    include(KDEInstallDirs)
endif()

find_package(${kfname}CoreAddons ${KF_VERSION} QUIET)
set_package_properties(
    ${kfname}CoreAddons
    PROPERTIES
    TYPE REQUIRED
    DESCRIPTION "KDE Framework CoreAddons"
    URL "https://api.kde.org/frameworks/"
    PURPOSE "Essential Framework for AboutData and Macros"
)

# After this point, there should be no REQUIRED find_packages,
# since we want tidy reporting of optional dependencies.
feature_summary(
    WHAT REQUIRED_PACKAGES_NOT_FOUND
    FATAL_ON_MISSING_REQUIRED_PACKAGES
    DESCRIPTION "The following REQUIRED packages were not found:"
    QUIET_ON_EMPTY
)

#
# OPTIONAL DEPENDENCIES
#
# First, set KF back to optional so that any missing components don't trip us up.
find_package(${kfname}Crash ${KF_VERSION} QUIET)
set_package_properties(
    ${kfname}Crash
    PROPERTIES
    TYPE OPTIONAL
    DESCRIPTION "KDE Framework Crash"
    URL "https://api.kde.org/frameworks/"
    PURPOSE "Framework for sending Crash Dumps"
)

if(NOT TARGET ${kfname}::Crash)
    if(BUILD_CRASH_REPORTING)
        message(WARNING "BUILD_CRASH_REPORTING is set, but ${kfname}::Crash is not available.")
    endif()
    set(BUILD_CRASH_REPORTING OFF)
endif()

find_package(Python ${PYTHONLIBS_VERSION} COMPONENTS Interpreter Development)
set_package_properties(
    Python
    PROPERTIES
    DESCRIPTION "Python3 interpreter."
    URL "https://python.org"
    PURPOSE "Python3 interpreter for certain tests."
)

set(_schema_explanation "")
if(Python_Interpreter_FOUND)
    if(BUILD_SCHEMA_TESTING)
        # The configuration validator script has some dependencies,
        # and if they are not installed, don't run. If errors out
        # with exit(1) on missing dependencies.
        if(CALAMARES_CONFIGVALIDATOR_CHECKED)
            message(STATUS "Using cached config-validation result")
            set(_validator_deps ${CALAMARES_CONFIGVALIDATOR_RESULT})
        else()
            execute_process(
                COMMAND ${Python_EXECUTABLE} "${CMAKE_SOURCE_DIR}/ci/configvalidator.py" -x
                RESULT_VARIABLE _validator_deps
            )
            set(CALAMARES_CONFIGVALIDATOR_CHECKED TRUE CACHE INTERNAL "Dependencies for configvalidator checked")
            set(CALAMARES_CONFIGVALIDATOR_RESULT ${_validator_deps}
                CACHE INTERNAL "Result of configvalidator dependency check"
            )
        endif()
        # It should never succeed, but only returns 1 when the imports fail
        if(_validator_deps EQUAL 1)
            message(STATUS "Checked for config-validation dependencies: NOT-FOUND")
            set(_schema_explanation " Missing dependencies for configvalidator.py.")
            set(BUILD_SCHEMA_TESTING OFF)
        else()
            message(STATUS "Checked for config-validation dependencies: found")
        endif()
    else()
        set(CALAMARES_CONFIGVALIDATOR_CHECKED OFF CACHE INTERNAL "Dependencies for configvalidator checked")
    endif()
else()
    # Can't run schema tests without Python3.
    set(_schema_explanation " Missing Python3.")
    set(BUILD_SCHEMA_TESTING OFF)
    set(CALAMARES_CONFIGVALIDATOR_CHECKED OFF CACHE INTERNAL "Dependencies for configvalidator checked")
endif()
add_feature_info(yaml-schema BUILD_SCHEMA_TESTING "Validate YAML (config files) with schema.${_schema_explanation}")

if(NOT Python_Development_FOUND)
    message(STATUS "Disabling Python modules")
    set(WITH_PYTHON OFF)
    set(WITH_PYBIND11 OFF)
    set(WITH_BOOST_PYTHON OFF)
endif()

if(WITH_PYTHON AND NOT WITH_PYBIND11)
    set(WITH_BOOST_PYTHON ON)
    find_package(boost_python)
    if(NOT TARGET Boost::python)
        find_package(Boost ${BOOSTPYTHON_VERSION} COMPONENTS python)
        set_package_properties(Boost PROPERTIES
            PURPOSE "Boost.Python is used for Python job modules (because WITH_PYBIND11 is OFF)."
            TYPE REQUIRED
        )
    else()
        message(STATUS "Found boost_python with target Boost::python")
        set(Boost_FOUND ON)
    endif()
endif()
add_feature_info(python WITH_PYTHON "Enable Python-modules")
add_feature_info(python-pybind11 WITH_PYBIND11 "Python-modules through pybind11")
add_feature_info(python-boost WITH_BOOST_PYTHON "Python-modules through Boost::Python")

# Now we know the state of the ABI-options, copy them into "Calamares_"
# prefixed variables, to match how the variables would-be-named
# when building out-of-tree.
set(Calamares_WITH_PYTHON ${WITH_PYTHON})
set(Calamares_WITH_PYBIND11 ${WITH_PYBIND11})
set(Calamares_WITH_BOOST_PYTHON ${WITH_BOOST_PYTHON})
set(Calamares_WITH_QML ${WITH_QML})
set(Calamares_WITH_QT6 ${WITH_QT6})

### Transifex Translation status
#
# Construct language lists for use. This massages the language lists if
# needed and checks for some obvious errors. The actual work of
# compiling translations is done in the lang/ directory.
#

set(curr_tx ${_tx_complete} ${_tx_good} ${_tx_ok} ${_tx_incomplete})
set(tx_errors OFF)
if(curr_tx)
    # New in list
    foreach(l ${curr_tx})
        set(p_l "lang/calamares_${l}.ts")
        if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${p_l})
            message(WARNING "Language ${l} has no .ts file yet.")
            set(tx_errors ON)
        endif()
    endforeach()

    unset(p_l)
    unset(l)
endif()
unset(curr_tx)
if(tx_errors)
    message(FATAL_ERROR "Translation warnings, see above.")
endif()

set(CALAMARES_TRANSLATION_LANGUAGES en ${_tx_complete} ${_tx_good} ${_tx_ok})
if(NOT CALAMARES_RELEASE_MODE)
    # Outside of release mode, enable all the languages
    list(APPEND CALAMARES_TRANSLATION_LANGUAGES ${_tx_incomplete})
endif()
list(SORT CALAMARES_TRANSLATION_LANGUAGES)
list(REMOVE_DUPLICATES CALAMARES_TRANSLATION_LANGUAGES)

add_subdirectory(lang) # i18n tools

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
find_program(mksquashfs_PROGRAM mksquashfs)
if(mksquashfs_PROGRAM)
    set(mksquashfs_FOUND ON)
    set(src_fs ${CMAKE_SOURCE_DIR}/data/example-root/)
    set(dst_fs ${CMAKE_BINARY_DIR}/example.sqfs)
    if(EXISTS ${src_fs})
        # based on the build host. If /lib64 exists, assume it is needed.
        # Collect directories needed for a minimal binary distro,
        # Note that the last path component is added to the root, so
        # if you add /usr/sbin here, it will be put into /sbin_1.
        # Add such paths to /etc/profile under ${src_fs}.
        set(candidate_fs /sbin /bin /lib /lib64)
        set(host_fs "")
        foreach(c_fs ${candidate_fs})
            if(EXISTS ${c_fs})
                list(APPEND host_fs ${c_fs})
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
    set(mksquashfs_FOUND OFF)
endif()
# Doesn't list mksquashfs as an optional dep, though, because it
# hasn't been sent through the find_package() scheme.
#
# "http://tldp.org/HOWTO/SquashFS-HOWTO/creatingandusing.html"
add_feature_info(ExampleDistro ${mksquashfs_FOUND} "Create example-distro target.")

### CALAMARES PROPER
#

# Additional info for non-release builds. The "extended" version information
# with date and git information (commit, dirty status) is used only
# by CalamaresVersionX.h, which is included by consumers that need a full
# version number with all that information; normal consumers can include
# CalamaresVersion.h with more stable numbers.
if(NOT CALAMARES_RELEASE_MODE AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git/")
    include(ExtendedVersion)
    extend_version( "${CALAMARES_VERSION}" OFF CALAMARES_VERSION_SHORT CALAMARES_VERSION_LONG )
endif()

# Special define for RC (e.g. not-a-release) builds.
# This is consumed via the CalamaresConfig.h header.
if(NOT CALAMARES_RELEASE_MODE)
    set(CALAMARES_VERSION_RC 1)
endif()

# enforce using constBegin, constEnd for const-iterators
add_definitions(-DQT_STRICT_ITERATORS -DQT_SHARED -DQT_SHAREDPOINTER_TRACK_POINTERS)

# set paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Better default installation paths: GNUInstallDirs defines
# CMAKE_INSTALL_FULL_SYSCONFDIR to be CMAKE_INSTALL_PREFIX/etc by default
# but we really want /etc
if(NOT DEFINED CMAKE_INSTALL_SYSCONFDIR)
    set(CMAKE_INSTALL_SYSCONFDIR "/etc")
endif()

# make predefined install dirs available everywhere
include(GNUInstallDirs)

# This is used by CalamaresAddLibrary; once Calamares is installed,
# the CalamaresConfig.cmake module sets this variable to the IMPORTED
# libraries for Calamares.
set(Calamares_LIBRARIES calamares)

add_subdirectory(3rdparty/kdsingleapplication)
if(WITH_PYBIND11)
    add_subdirectory(3rdparty/pybind11)
endif()
add_subdirectory(src)

add_feature_info(Python ${WITH_PYTHON} "Python job modules")
add_feature_info(Pybind11 ${WITH_PYBIND11} "Python using bundled pybind11")
add_feature_info(Qml ${WITH_QML} "QML UI support")
add_feature_info(Polkit ${INSTALL_POLKIT} "Install Polkit files")
add_feature_info(KCrash ${BUILD_CRASH_REPORTING} "Crash dumps via KCrash")

### Post-source configuration
#
#
find_package(${kfname} ${KF_VERSION} QUIET COMPONENTS CoreAddons)

### CMake infrastructure installation
#
#
set(CMAKE_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/Calamares" CACHE PATH "Installation directory for CMake files")
set(CMAKE_INSTALL_FULL_CMAKEDIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_CMAKEDIR}")

export(PACKAGE Calamares)
configure_package_config_file(
    "CalamaresConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/CalamaresConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_CMAKEDIR}"
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR CMAKE_INSTALL_DATADIR
)
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/CalamaresConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(EXPORT Calamares DESTINATION "${CMAKE_INSTALL_CMAKEDIR}" FILE "CalamaresTargets.cmake" NAMESPACE Calamares::)

# Install the cmake files
install(
    FILES
        "${PROJECT_BINARY_DIR}/CalamaresConfig.cmake"
        "${PROJECT_BINARY_DIR}/CalamaresConfigVersion.cmake"
        "CMakeModules/CalamaresAddBrandingSubdirectory.cmake"
        "CMakeModules/CalamaresAddLibrary.cmake"
        "CMakeModules/CalamaresAddModuleSubdirectory.cmake"
        "CMakeModules/CalamaresAddPlugin.cmake"
        "CMakeModules/CalamaresAddTest.cmake"
        "CMakeModules/CalamaresAddTranslations.cmake"
        "CMakeModules/CalamaresAutomoc.cmake"
        "CMakeModules/CalamaresCheckModuleSelection.cmake"
        "CMakeModules/CMakeColors.cmake"
        "CMakeModules/FindYAMLCPP.cmake"
    DESTINATION "${CMAKE_INSTALL_CMAKEDIR}"
)

### Miscellaneous installs
#
#
if(INSTALL_POLKIT)
    install(FILES com.github.calamares.calamares.policy DESTINATION "${POLKITQT-1_POLICY_FILES_INSTALL_DIR}")
endif()

if(INSTALL_COMPLETION)
    if(NOT CMAKE_INSTALL_BASHCOMPLETIONDIR)
        set(CMAKE_INSTALL_BASHCOMPLETIONDIR "${CMAKE_INSTALL_DATADIR}/bash-completion/completions")
    endif()

    install(FILES ${CMAKE_SOURCE_DIR}/data/completion/bash/calamares DESTINATION "${CMAKE_INSTALL_BASHCOMPLETIONDIR}")
endif()

install(FILES calamares.desktop DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

install(FILES man/calamares.8 DESTINATION ${CMAKE_INSTALL_MANDIR}/man8/)

if(INSTALL_CONFIG)
    install(FILES settings.conf DESTINATION share/calamares)
endif()

### Uninstall
#
#
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE
    @ONLY
)

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

### Developer convenience
#
# The module support files -- .desc files, .conf files -- are copied into the build
# directory so that it is possible to run `calamares -d` from there. Copy the
# top-level settings.conf as well, into the build directory.
if( settings.conf IS_NEWER_THAN ${CMAKE_BINARY_DIR}/settings.conf )
    configure_file(settings.conf ${CMAKE_BINARY_DIR}/settings.conf COPYONLY)
endif()



### CMAKE SUMMARY REPORT
#
get_directory_property(SKIPPED_MODULES DIRECTORY src/modules DEFINITION LIST_SKIPPED_MODULES)
calamares_explain_skipped_modules( ${SKIPPED_MODULES} )

feature_summary(WHAT ENABLED_FEATURES DESCRIPTION "The following features are enabled" QUIET_ON_EMPTY)
feature_summary(WHAT DISABLED_FEATURES DESCRIPTION "The following features have been disabled:" QUIET_ON_EMPTY)
feature_summary(
    WHAT OPTIONAL_PACKAGES_NOT_FOUND
    DESCRIPTION "The following OPTIONAL packages were not found:"
    QUIET_ON_EMPTY
)
feature_summary(
    WHAT REQUIRED_PACKAGES_NOT_FOUND
    FATAL_ON_MISSING_REQUIRED_PACKAGES
    DESCRIPTION "The following REQUIRED packages were not found:"
    QUIET_ON_EMPTY
)

### PACKAGING
#
# Note: most distro's will do distro-specific packaging rather than
#       using CPack, and this duplicates information in the AppStream, too.
set(CPACK_PACKAGE_VENDOR calamares)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A Linux system installer")
set(CPACK_PACKAGE_DESCRIPTION
    "Calamares is a Linux system installer, intended for Linux distributions to use on their ISOs and other bootable media to install the distribution to the end-user's computer. Calamares can also be used as an OEM configuration tool. It is modular, extensible and highly-configurable for Linux distributions from all five major Linux families."
)
set(CPACK_PACKAGE_ICON "data/images/squid.png")

include(CPack)
