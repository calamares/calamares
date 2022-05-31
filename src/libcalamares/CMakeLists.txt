# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

#
# libcalamares is the non-GUI part of Calamares, which includes handling
# translations, configurations, logging, utilities, global storage, and
# (non-GUI) jobs.
#

add_definitions(-DDLLEXPORT_PRO)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CalamaresConfig.h.in ${CMAKE_CURRENT_BINARY_DIR}/CalamaresConfig.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CalamaresVersion.h.in ${CMAKE_CURRENT_BINARY_DIR}/CalamaresVersion.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CalamaresVersionX.h.in ${CMAKE_CURRENT_BINARY_DIR}/CalamaresVersionX.h)

add_library(
    calamares
    SHARED
    CalamaresAbout.cpp
    CppJob.cpp
    GlobalStorage.cpp
    Job.cpp
    JobExample.cpp
    JobQueue.cpp
    ProcessJob.cpp
    Settings.cpp
    # GeoIP services
    geoip/Interface.cpp
    geoip/GeoIPFixed.cpp
    geoip/GeoIPJSON.cpp
    geoip/Handler.cpp
    # Locale-data service
    locale/Global.cpp
    locale/Lookup.cpp
    locale/TimeZone.cpp
    locale/TranslatableConfiguration.cpp
    locale/TranslatableString.cpp
    locale/Translation.cpp
    locale/TranslationsModel.cpp
    # Modules
    modulesystem/Config.cpp
    modulesystem/Descriptor.cpp
    modulesystem/InstanceKey.cpp
    modulesystem/Module.cpp
    modulesystem/Preset.cpp
    modulesystem/RequirementsChecker.cpp
    modulesystem/RequirementsModel.cpp
    # Network service
    network/Manager.cpp
    # Packages service
    packages/Globals.cpp
    # Partition service
    partition/Global.cpp
    partition/Mount.cpp
    partition/PartitionSize.cpp
    partition/Sync.cpp
    # Utility service
    utils/CalamaresUtilsSystem.cpp
    utils/CommandList.cpp
    utils/Dirs.cpp
    utils/Entropy.cpp
    utils/Logger.cpp
    utils/Permissions.cpp
    utils/PluginFactory.cpp
    utils/Retranslator.cpp
    utils/Runner.cpp
    utils/String.cpp
    utils/StringExpander.cpp
    utils/UMask.cpp
    utils/Variant.cpp
    utils/Yaml.cpp
)

set_target_properties(
    calamares
    PROPERTIES
        VERSION ${CALAMARES_VERSION_SHORT}
        SOVERSION ${CALAMARES_VERSION_SHORT}
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_INSTALL_FULL_INCLUDEDIR}/libcalamares
)
target_link_libraries(calamares LINK_PUBLIC yamlcpp::yamlcpp Qt5::Core KF5::CoreAddons)

### OPTIONAL Automount support (requires dbus)
#
#
if(Qt5DBus_FOUND)
    target_sources(calamares PRIVATE partition/AutoMount.cpp)
    target_link_libraries(calamares PRIVATE Qt5::DBus)
endif()

### OPTIONAL Python support
#
#
if(WITH_PYTHON)
    target_sources(calamares PRIVATE PythonHelper.cpp PythonJob.cpp PythonJobApi.cpp)
    target_link_libraries(calamares PRIVATE Python::Python Boost::python)
endif()

### OPTIONAL GeoIP XML support
#
#
find_package(Qt5 COMPONENTS Xml)
if(Qt5Xml_FOUND)
    target_sources(calamares PRIVATE geoip/GeoIPXML.cpp)
    target_link_libraries(calamares PRIVATE Qt5::Network Qt5::Xml)
endif()

### OPTIONAL KPMcore support
#
#
include(KPMcoreHelper)

if(KPMcore_FOUND)
    find_package(Qt5 REQUIRED DBus) # Needed for KPMCore
    find_package(KF5 REQUIRED I18n WidgetsAddons) # Needed for KPMCore

    foreach(d ${KPMcore_API_DEFINITIONS})
        add_definitions(-D${d})
    endforeach()
    include_directories(${KPMCORE_INCLUDE_DIR})
    target_sources(
        calamares
        PRIVATE
            partition/FileSystem.cpp
            partition/KPMManager.cpp
            partition/PartitionIterator.cpp
            partition/PartitionQuery.cpp
    )
    target_link_libraries(calamares PRIVATE kpmcore)
endif()

### LIBRARY
#
#
calamares_automoc( calamares )
add_library(Calamares::calamares ALIAS calamares)

### Installation
#
#
install(
    TARGETS calamares
    EXPORT Calamares
    RUNTIME
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Make symlink lib/calamares/libcalamares.so to lib/libcalamares.so.VERSION so
# lib/calamares can be used as module path for the Python interpreter.
install(
    CODE
        "
    file( MAKE_DIRECTORY \"\$ENV{DESTDIR}/${CMAKE_INSTALL_FULL_LIBDIR}/calamares\" )
    execute_process( COMMAND \"${CMAKE_COMMAND}\" -E create_symlink ../libcalamares.so.${CALAMARES_VERSION_SHORT} libcalamares.so WORKING_DIRECTORY \"\$ENV{DESTDIR}/${CMAKE_INSTALL_FULL_LIBDIR}/calamares\" )
"
)

# Install header files
file(GLOB rootHeaders "*.h")
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/CalamaresConfig.h ${CMAKE_CURRENT_BINARY_DIR}/CalamaresVersion.h ${rootHeaders}
    DESTINATION include/libcalamares
)
# Install each subdir-worth of header files
foreach(subdir geoip locale modulesystem network partition utils)
    file(GLOB subdir_headers "${subdir}/*.h")
    install(FILES ${subdir_headers} DESTINATION include/libcalamares/${subdir})
endforeach()

### TRANSLATION TESTING
#
# This is a support function, used just once, to help out the localetest
function(calamares_qrc_translations basename)
    set(NAME ${ARGV0})
    set(options "")
    set(oneValueArgs SUBDIRECTORY OUTPUT_VARIABLE)
    set(multiValueArgs LANGUAGES)
    cmake_parse_arguments(_qrt "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT _qrt_OUTPUT_VARIABLE)
        set(_qrt_OUTPUT_VARIABLE "qrc_translations_${basename}")
    endif()

    set(translations_qrc_infile ${CMAKE_CURRENT_BINARY_DIR}/${basename}.qrc)
    set(translations_qrc_outfile ${CMAKE_CURRENT_BINARY_DIR}/qrc_${basename}.cxx)

    # Must use this variable name because of the @ substitution
    set(calamares_i18n_qrc_content "")
    set(calamares_i18n_ts_filelist "")
    foreach(lang ${_qrt_LANGUAGES})
        string(APPEND calamares_i18n_qrc_content "<file>${basename}_${lang}.qm</file>")
        list(
            APPEND
            calamares_i18n_ts_filelist
            "${CMAKE_CURRENT_SOURCE_DIR}/${_qrt_SUBDIRECTORY}/${basename}_${lang}.ts"
        )
    endforeach()

    configure_file(${CMAKE_SOURCE_DIR}/lang/calamares_i18n.qrc.in ${translations_qrc_infile} @ONLY)
    qt5_add_translation(QM_FILES ${calamares_i18n_ts_filelist})

    # Run the resource compiler (rcc_options should already be set)
    add_custom_command(
        OUTPUT ${translations_qrc_outfile}
        COMMAND "${Qt5Core_RCC_EXECUTABLE}"
        ARGS
            ${rcc_options}
            --format-version
            1
            -name
            ${basename}
            -o
            ${translations_qrc_outfile}
            ${translations_qrc_infile}
        MAIN_DEPENDENCY ${translations_qrc_infile}
        DEPENDS ${QM_FILES}
    )

    set(${_qrt_OUTPUT_VARIABLE} ${translations_qrc_outfile} PARENT_SCOPE)
endfunction()

calamares_qrc_translations( localetest OUTPUT_VARIABLE localetest_qrc SUBDIRECTORY testdata LANGUAGES nl )

### TESTING
#
#
calamares_add_test(libcalamarestest SOURCES Tests.cpp)

calamares_add_test(libcalamaresgeoiptest SOURCES geoip/GeoIPTests.cpp ${geoip_src})

calamares_add_test(libcalamareslocaletest SOURCES locale/Tests.cpp ${localetest_qrc})

calamares_add_test(libcalamaresmodulesystemtest SOURCES modulesystem/Tests.cpp)

calamares_add_test(libcalamaresnetworktest SOURCES network/Tests.cpp)

calamares_add_test(libcalamarespackagestest SOURCES packages/Tests.cpp)

if(KPMcore_FOUND)
    calamares_add_test(libcalamarespartitiontest SOURCES partition/Global.cpp partition/Tests.cpp LIBRARIES kpmcore)
    calamares_add_test(libcalamarespartitionkpmtest SOURCES partition/KPMTests.cpp LIBRARIES kpmcore)
endif()

calamares_add_test(libcalamaresutilstest SOURCES utils/Tests.cpp utils/Runner.cpp)

calamares_add_test(libcalamaresutilspathstest SOURCES utils/TestPaths.cpp)

# This is not an actual test, it's a test / demo application
# for experimenting with GeoIP.
add_executable(test_geoip geoip/test_geoip.cpp ${geoip_src})
target_link_libraries(test_geoip Calamares::calamares Qt5::Network yamlcpp::yamlcpp)
calamares_automoc( test_geoip )

if(Qt5DBus_FOUND)
    add_executable(test_automount partition/calautomount.cpp)
    target_link_libraries(test_automount Calamares::calamares Qt5::DBus)
endif()
