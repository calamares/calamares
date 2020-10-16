# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
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
#   SPDX-License-Identifier: GPL-3.0-or-later
#   License-Filename: LICENSE
#
#
# libcalamares is the non-GUI part of Calamares, which includes handling
# translations, configurations, logging, utilities, global storage, and (non-GUI) jobs.

add_definitions( -DDLLEXPORT_PRO )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/CalamaresConfig.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/CalamaresConfig.h )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/../calamares/CalamaresVersion.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/CalamaresVersion.h )

set( OPTIONAL_PRIVATE_LIBRARIES "" )
set( OPTIONAL_PUBLIC_LIBRARIES "" )

set( libSources
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
    locale/Label.cpp
    locale/LabelModel.cpp
    locale/Lookup.cpp
    locale/TimeZone.cpp
    locale/TranslatableConfiguration.cpp

    # Modules
    modulesystem/InstanceKey.cpp
    modulesystem/Module.cpp
    modulesystem/Requirement.cpp
    modulesystem/RequirementsChecker.cpp
    modulesystem/RequirementsModel.cpp

    # Network service
    network/Manager.cpp

    # Partition service
    partition/Mount.cpp
    partition/PartitionSize.cpp
    partition/Sync.cpp

    # Utility service
    utils/CalamaresUtilsSystem.cpp
    utils/CommandList.cpp
    utils/Dirs.cpp
    utils/Entropy.cpp
    utils/Logger.cpp
    utils/PluginFactory.cpp
    utils/Retranslator.cpp
    utils/String.cpp
    utils/UMask.cpp
    utils/Variant.cpp
    utils/Yaml.cpp
)

### OPTIONAL Python support
#
#
if( WITH_PYTHON )
    list( APPEND libSources
        PythonHelper.cpp
        PythonJob.cpp
        PythonJobApi.cpp
    )
    set_source_files_properties( PythonJob.cpp
        PROPERTIES COMPILE_FLAGS "${SUPPRESS_BOOST_WARNINGS}"
    )

    include_directories(${PYTHON_INCLUDE_DIRS})
    link_directories(${PYTHON_LIBRARIES})

    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    list( APPEND OPTIONAL_PRIVATE_LIBRARIES
        ${PYTHON_LIBRARIES}
        ${Boost_LIBRARIES}
    )
endif()

### OPTIONAL GeoIP XML support
#
#
find_package(Qt5 COMPONENTS Xml)
if( Qt5Xml_FOUND )
    list( APPEND libSources geoip/GeoIPXML.cpp )
    list( APPEND OPTIONAL_PUBLIC_LIBRARIES Qt5::Network Qt5::Xml )
endif()

### OPTIONAL KPMcore support
#
#
find_package( KPMcore 3.3 )
set_package_properties(
    KPMcore PROPERTIES
    URL "https://invent.kde.org/kde/kpmcore"
    DESCRIPTION "KDE Partitioning library"
    TYPE RECOMMENDED
    PURPOSE "For partitioning service"
)

if ( KPMcore_FOUND )
    find_package( Qt5 REQUIRED DBus )  # Needed for KPMCore
    find_package( KF5 REQUIRED I18n WidgetsAddons )  # Needed for KPMCore

    if( KPMcore_VERSION VERSION_GREATER_EQUAL "4.2" )
        add_definitions(
            -DWITH_KPMCORE42API
            -DWITH_KPMCORE4API
        ) # kpmcore 4.2 with new API
    elseif( KPMcore_VERSION VERSION_GREATER_EQUAL "4.0" )
        add_definitions( -DWITH_KPMCORE4API ) # kpmcore 4 with new API
    elseif( KPMcore_VERSION VERSION_GREATER "3.3.70" )
        message( FATAL_ERROR "KPMCore beta versions ${KPMcore_VERSION} not supported" )
    endif()

    include_directories( ${KPMCORE_INCLUDE_DIR} )
    list( APPEND libSources
        partition/FileSystem.cpp
        partition/KPMManager.cpp
        partition/PartitionIterator.cpp
        partition/PartitionQuery.cpp
    )
    list( APPEND OPTIONAL_PRIVATE_LIBRARIES kpmcore )
endif()

### LIBRARY
#
#
add_library( calamares SHARED ${libSources} )
set_target_properties( calamares
    PROPERTIES
        VERSION ${CALAMARES_VERSION_SHORT}
        SOVERSION ${CALAMARES_VERSION_SHORT}
        INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_INSTALL_FULL_INCLUDEDIR}/libcalamares
)
calamares_automoc( calamares )

target_link_libraries( calamares
    LINK_PRIVATE
        ${OPTIONAL_PRIVATE_LIBRARIES}
        yamlcpp
    LINK_PUBLIC
        Qt5::Core
        KF5::CoreAddons
        ${OPTIONAL_PUBLIC_LIBRARIES}
)

### Installation
#
#
install( TARGETS calamares
    EXPORT Calamares
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Make symlink lib/calamares/libcalamares.so to lib/libcalamares.so.VERSION so
# lib/calamares can be used as module path for the Python interpreter.
install( CODE "
    file( MAKE_DIRECTORY \"\$ENV{DESTDIR}/${CMAKE_INSTALL_FULL_LIBDIR}/calamares\" )
    execute_process( COMMAND \"${CMAKE_COMMAND}\" -E create_symlink ../libcalamares.so.${CALAMARES_VERSION_SHORT} libcalamares.so WORKING_DIRECTORY \"\$ENV{DESTDIR}/${CMAKE_INSTALL_FULL_LIBDIR}/calamares\" )
")

# Install header files
file( GLOB rootHeaders "*.h" )
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/CalamaresConfig.h
        ${rootHeaders}
    DESTINATION include/libcalamares
)
# Install each subdir-worth of header files
foreach( subdir geoip locale modulesystem network partition utils )
    file( GLOB subdir_headers "${subdir}/*.h" )
    install( FILES ${subdir_headers} DESTINATION include/libcalamares/${subdir} )
endforeach()


### TESTING
#
#
calamares_add_test(
    libcalamarestest
    SOURCES
        utils/Tests.cpp
)

calamares_add_test(
    libcalamarestestpaths
    SOURCES
        utils/TestPaths.cpp
)

calamares_add_test(
    geoiptest
    SOURCES
        geoip/GeoIPTests.cpp
        ${geoip_src}
)

calamares_add_test(
    libcalamarespartitiontest
    SOURCES
        partition/Tests.cpp
)

if( KPMcore_FOUND )
    calamares_add_test(
        libcalamarespartitionkpmtest
        SOURCES
            partition/KPMTests.cpp
        LIBRARIES
            ${OPTIONAL_PRIVATE_LIBRARIES}
    )
endif()

calamares_add_test(
    libcalamareslocaletest
    SOURCES
        locale/Tests.cpp
)

calamares_add_test(
    libcalamaresnetworktest
    SOURCES
        network/Tests.cpp
)

calamares_add_test(
    libcalamaresmodulesystemtest
    SOURCES
        modulesystem/Tests.cpp
)

# This is not an actual test, it's a test / demo application
# for experimenting with GeoIP.
add_executable( test_geoip geoip/test_geoip.cpp ${geoip_src} )
target_link_libraries( test_geoip calamares Qt5::Network yamlcpp )
calamares_automoc( test_geoip )
