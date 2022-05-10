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
#   USE_<foo>       : fills in SKIP_MODULES for modules called <foo>-<something>
#   WITH_<foo>      : try to enable <foo> (these usually default to ON). For
#                     a list of WITH_<foo> grep CMakeCache.txt after running
#                     CMake once. These affect the ABI offered by Calamares.
#                       - PYTHON (enable Python Job modules)
#                       - QML (enable QML UI View modules)
#                     The WITH_* options affect the ABI of Calamares: you must
#                     build (C++) modules for Calamares with the same WITH_*
#                     settings, or they may not load at all.
#   BUILD_<foo>     : choose additional things to build
#                       - TESTING (standard CMake option)
#                       - SCHEMA_TESTING (requires Python, see ci/configvalidator.py)
#                       - KF5Crash (uses KCrash, rather than Calamares internal, for crash reporting)
#   DEBUG_<foo>     : special developer flags for debugging
#
# Example usage:
#
#   cmake . -DSKIP_MODULES="partition luksbootkeycfg"
#
# One special target is "show-version", which can be built
# to obtain the version number from here.

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

set(CALAMARES_VERSION 3.3.0)
set(CALAMARES_RELEASE_MODE OFF) # Set to ON during a release

if(CMAKE_SCRIPT_MODE_FILE)
    include(${CMAKE_CURRENT_LIST_DIR}/CMakeModules/ExtendedVersion.cmake)
    set(CMAKE_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
    extend_version( ${CALAMARES_VERSION} OFF _vshort _vlong )
    message("${_vlong}")
    return()
endif()

project(CALAMARES VERSION ${CALAMARES_VERSION} LANGUAGES C CXX HOMEPAGE_URL "https://calamares.io/")

if(NOT CALAMARES_RELEASE_MODE AND CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build development versions in the source-directory.")
endif()

### OPTIONS
#
option(INSTALL_CONFIG "Install configuration files" OFF)
option(INSTALL_POLKIT "Install Polkit configuration" ON)
option(INSTALL_COMPLETION "Install shell completions" OFF)
# When adding WITH_* that affects the ABI offered by libcalamares,
# also update libcalamares/CalamaresConfig.h.in
option(WITH_PYTHON "Enable Python modules API (requires Boost.Python)." ON)
option(WITH_QML "Enable QML UI options." ON)
#
# Additional parts to build that do not affect ABI
option(BUILD_SCHEMA_TESTING "Enable schema-validation-tests" ON)
# Options for the calamares executable
option(BUILD_KF5Crash "Enable crash reporting with KCrash." ON)

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
# from https://transifex.com/calamares/calamares/ , or (preferably)
# use ci/txstats.py to automatically check.
#
# When adding a new language, take care that it is properly loaded
# by the translation framework. Languages with alternate scripts
# (sr@latin in particular) or location (ca@valencia) need special
# handling in libcalamares/locale/Translation.h .
#
# NOTE: move eo (Esperanto) to _ok once Qt can actually create a
#       locale for it. (Qt 5.12.2 can, see Translation Status section).
# NOTE: move ie (Interlingue) to _ok once Qt supports it.
# NOTE: update these lines by running `txstats.py`, or for full automation
#       `txstats.py -e`. See also
#
# Total 74 languages
set( _tx_complete az az_AZ ca es fi_FI he hi hr ja ko lt pt_BR
    pt_PT sq sv tr_TR uk zh_TW )
set( _tx_good as be ca@valencia cs_CZ da de fa fr fur it_IT ml nl
    ru si sk tg vi zh_CN )
set( _tx_ok ar ast bg bn el en_GB es_MX et eu gl hu id is mr nb oc
    pl ro sl sr sr@latin th )
set( _tx_incomplete eo es_PR gu ie ja-Hira kk kn lo lv mk ne_NP
    ta_IN te ur zh zh_HK )
# Total 74 languages

### Required versions
#
# See DEPENDENCIES section below.
set(QT_VERSION 5.15.0)
set(YAMLCPP_VERSION 0.5.1)
set(ECM_VERSION 5.18)
set(PYTHONLIBS_VERSION 3.6)
set(BOOSTPYTHON_VERSION 1.72.0)

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
set(CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined -Wl,--fatal-warnings")

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

# API that was deprecated before Qt 5.15 causes a compile error
add_compile_definitions(QT_DISABLE_DEPRECATED_BEFORE=0x050f00)

### DEPENDENCIES
#
find_package(Qt5 ${QT_VERSION} CONFIG REQUIRED Concurrent Core Gui LinguistTools Network Svg Widgets)
if(WITH_QML)
    find_package(Qt5 ${QT_VERSION} CONFIG REQUIRED Quick QuickWidgets)
endif()
# Optional Qt parts
find_package(Qt5DBus CONFIG)

find_package(YAMLCPP ${YAMLCPP_VERSION} REQUIRED)
if(INSTALL_POLKIT)
    find_package(PolkitQt5-1 REQUIRED)
else()
    # Find it anyway, for dependencies-reporting
    find_package(PolkitQt5-1)
endif()
set_package_properties(
    PolkitQt5-1
    PROPERTIES
    DESCRIPTION "Qt5 support for Polkit"
    URL "https://cgit.kde.org/polkit-qt-1.git"
    PURPOSE "PolkitQt5-1 helps with installing Polkit configuration"
)

# Find ECM once, and add it to the module search path; Calamares
# modules that need ECM can do
#   find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE),
# no need to mess with the module path after.
find_package(ECM ${ECM_VERSION} NO_MODULE)
if(ECM_FOUND)
    set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})
    if(BUILD_TESTING)
        # ECM implies that we can build the tests, too
        find_package(Qt5 COMPONENTS Test REQUIRED)
        include(ECMAddTests)
    endif()
    include(KDEInstallDirs)
endif()

find_package(KF5 QUIET COMPONENTS CoreAddons Crash DBusAddons)
set_package_properties(
    KF5::CoreAddons
    PROPERTIES
    TYPE REQUIRED
    DESCRIPTION "Classes built on QtCore for About Data"
    URL "https://api.kde.org/frameworks/kcoreaddons/"
    PURPOSE "About Calamares"
)
set_package_properties(
    KF5::DBusAddons
    PROPERTIES
    TYPE REQUIRED
    DESCRIPTION "Classes for DBus activation"
    URL "https://api.kde.org/frameworks/dbusaddons/"
    PURPOSE "Unique instance of Calamares"
)
if(NOT KF5Crash_FOUND)
    if(BUILD_KF5Crash)
        message(WARNING "BUILD_KF5Crash is set, but KF5::Crash is not available.")
    endif()
    set(BUILD_KF5Crash OFF)
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
            set(_validator_deps ${CALAMARES_CONFIGVALIDATOR_RESULT})
        else()
            exec_program(
                ${Python_EXECUTABLE}
                ARGS
                "${CMAKE_SOURCE_DIR}/ci/configvalidator.py"
                -x
                RETURN_VALUE
                _validator_deps
            )
            set(CALAMARES_CONFIGVALIDATOR_CHECKED TRUE CACHE INTERNAL "Dependencies for configvalidator checked")
            set(CALAMARES_CONFIGVALIDATOR_RESULT ${_validator_deps}
                CACHE INTERNAL "Result of configvalidator dependency check"
            )
        endif()
        # It should never succeed, but only returns 1 when the imports fail
        if(_validator_deps EQUAL 1)
            set(_schema_explanation " Missing dependencies for configvalidator.py.")
            set(BUILD_SCHEMA_TESTING OFF)
        endif()
    endif()
else()
    # Can't run schema tests without Python3.
    set(_schema_explanation " Missing Python3.")
    set(BUILD_SCHEMA_TESTING OFF)
endif()
add_feature_info(yaml-schema BUILD_SCHEMA_TESTING "Validate YAML (config files) with schema.${_schema_explanation}")

if(Python_Development_FOUND)
    find_package(boost_python)
    if(NOT TARGET Boost::python)
        find_package(Boost ${BOOSTPYTHON_VERSION} COMPONENTS python)
        set_package_properties(Boost PROPERTIES PURPOSE "Boost.Python is used for Python job modules.")
    else()
        message(STATUS "Found boost_python with target Boost::python")
        set(Boost_FOUND ON)
    endif()
endif()

if(NOT Python_Development_FOUND OR NOT Boost_FOUND)
    message(STATUS "Disabling Boost::Python modules")
    set(WITH_PYTHON OFF)
endif()

# Now we know the state of the ABI-options, copy them into "Calamares_"
# prefixed variables, to match how the variables would-be-named
# when building out-of-tree.
set(Calamares_WITH_PYTHON ${WITH_PYTHON})
set(Calamares_WITH_QML ${WITH_QML})

### Transifex Translation status
#
# Construct language lists for use. This massages the language lists
# for use with older Qt (which does not support Esperanto) and checks
# for some obvious error. The actual work of compiling translations
# is done in the lang/ directory.
#
if(Qt5_VERSION VERSION_GREATER 5.12.1)
    # At least Qt 5.12.2 seems to support Esperanto in QLocale
    if("eo" IN_LIST _tx_incomplete)
        message(STATUS "Esperanto support since Qt 5.12.2, enabling Esperanto locale")
        list(REMOVE_ITEM _tx_incomplete "eo")
        list(APPEND _tx_ok "eo")
    endif()
endif()

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
list(SORT CALAMARES_TRANSLATION_LANGUAGES)

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
set(CALAMARES_VERSION ${CALAMARES_VERSION_MAJOR}.${CALAMARES_VERSION_MINOR}.${CALAMARES_VERSION_PATCH})
# In rare cases we have hotfix-releases with a tweak
if(CALAMARES_VERSION_TWEAK)
    set(CALAMARES_VERSION "${CALAMARES_VERSION}.${CALAMARES_VERSION_TWEAK}")
endif()
set(CALAMARES_VERSION_SHORT "${CALAMARES_VERSION}")

# Additional info for non-release builds. The "extended" version information
# with date and git information (commit, dirty status) is used only
# by CalamaresVersionX.h, which is included by consumers that need a full
# version number with all that information; normal consumers can include
# CalamaresVersion.h with more stable numbers.
if(NOT BUILD_RELEASE AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git/")
    include(ExtendedVersion)
    extend_version( "${CALAMARES_VERSION}" OFF CALAMARES_VERSION_SHORT CALAMARES_VERSION )
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

add_subdirectory(src)

add_feature_info(Python ${WITH_PYTHON} "Python job modules")
add_feature_info(Qml ${WITH_QML} "QML UI support")
add_feature_info(Config ${INSTALL_CONFIG} "Install Calamares configuration")
add_feature_info(Polkit ${INSTALL_POLKIT} "Install Polkit files")
add_feature_info(KCrash ${BUILD_KF5Crash} "Crash dumps via KCrash")

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
if(INSTALL_CONFIG)
    install(FILES settings.conf DESTINATION share/calamares)
endif()

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

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE
    @ONLY
)

add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

### CMAKE SUMMARY REPORT
#
get_directory_property(SKIPPED_MODULES DIRECTORY src/modules DEFINITION LIST_SKIPPED_MODULES)
calamares_explain_skipped_modules( ${SKIPPED_MODULES} )

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
