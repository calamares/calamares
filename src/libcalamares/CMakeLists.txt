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

# Map the available translations names into a suitable constexpr list
# of names in C++. This gets us Calamares::Locale::availableLanguages,
# a QStringList of names.
set(_names_tu
    "
#ifndef CALAMARES_TRANSLATIONS_H
#define CALAMARES_TRANSLATIONS_H
#include <QStringList>
namespace {
static const QStringList availableLanguageList{
"
)
foreach(l ${CALAMARES_TRANSLATION_LANGUAGES})
    string(APPEND _names_tu "\"${l}\",\n")
endforeach()
string(APPEND _names_tu "};\n} // namespace\n#endif\n\n")
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/CalamaresTranslations.cc "${_names_tu}")

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
    utils/System.cpp
    utils/UMask.cpp
    utils/Variant.cpp
    utils/Yaml.cpp
)

set_target_properties(
    calamares
    PROPERTIES
        VERSION ${CALAMARES_VERSION_SHORT}
        SOVERSION ${CALAMARES_SOVERSION}
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_INSTALL_FULL_INCLUDEDIR}/libcalamares
)
target_link_libraries(calamares LINK_PUBLIC yamlcpp::yamlcpp ${qtname}::Core ${qtname}::Network)
target_link_libraries(calamares LINK_PUBLIC ${kfname}::CoreAddons)

### OPTIONAL Automount support (requires dbus)
#
#
if(TARGET ${qtname}::DBus)
    target_sources(calamares PRIVATE partition/AutoMount.cpp)
    target_link_libraries(calamares PRIVATE ${qtname}::DBus)
endif()

### OPTIONAL Python support
#
#
if(WITH_PYTHON)
    if(WITH_PYBIND11)
        target_sources(calamares PRIVATE python/Api.cpp python/PythonJob.cpp)
        target_link_libraries(calamares PRIVATE Python::Python pybind11::headers)
    else()
        target_sources(calamares PRIVATE PythonHelper.cpp PythonJob.cpp PythonJobApi.cpp)
        target_link_libraries(calamares PRIVATE Python::Python Boost::python)
    endif()
endif()

### OPTIONAL GeoIP XML support
#
#
find_package(${qtname} ${QT_VERSION} COMPONENTS Xml)
if(TARGET ${qtname}::Xml)
    target_sources(calamares PRIVATE geoip/GeoIPXML.cpp)
    target_link_libraries(calamares PRIVATE ${qtname}::Network ${qtname}::Xml)
endif()

### OPTIONAL KPMcore support
#
#
include(KPMcoreHelper)

if(KPMcore_FOUND)
    target_sources(
        calamares
        PRIVATE
            partition/FileSystem.cpp
            partition/KPMManager.cpp
            partition/PartitionIterator.cpp
            partition/PartitionQuery.cpp
    )
endif()
# Always, since this also handles the no-KPMcore case; we don't
# call it calamares::kpmcore because that name exists only
# when KPMcore is actually found.
target_link_libraries(calamares PRIVATE calapmcore)

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
foreach(subdir geoip locale modulesystem network partition utils compat packages)
    file(GLOB subdir_headers "${subdir}/*.h")
    install(FILES ${subdir_headers} DESTINATION include/libcalamares/${subdir})
endforeach()

### TRANSLATION TESTING
#

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
    calamares_add_test(
        libcalamarespartitiontest
        SOURCES partition/Global.cpp partition/Tests.cpp
        LIBRARIES calamares::kpmcore
    )
    calamares_add_test(libcalamarespartitionkpmtest SOURCES partition/KPMTests.cpp LIBRARIES calamares::kpmcore)
endif()

calamares_add_test(libcalamaresutilstest SOURCES utils/Tests.cpp utils/Runner.cpp)

calamares_add_test(libcalamaresutilspathstest SOURCES utils/TestPaths.cpp)

# This is not an actual test, it's a test / demo application
# for experimenting with GeoIP.
add_executable(test_geoip geoip/test_geoip.cpp ${geoip_src})
target_link_libraries(test_geoip Calamares::calamares ${qtname}::Network yamlcpp::yamlcpp)
calamares_automoc( test_geoip )

if(TARGET ${qtname}::DBus)
    add_executable(test_automount partition/calautomount.cpp)
    target_link_libraries(test_automount Calamares::calamares ${qtname}::DBus)
endif()
