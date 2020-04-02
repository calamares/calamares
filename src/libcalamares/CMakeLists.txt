# libcalamares is the non-GUI part of Calamares, which includes handling
# translations, configurations, logging, utilities, global storage, and (non-GUI) jobs.

add_definitions(
    ${QT_DEFINITIONS}
    -DQT_SHARED
    -DQT_SHAREDPOINTER_TRACK_POINTERS
    -DDLLEXPORT_PRO
)

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
set( _kdsagSources
    kdsingleapplicationguard/kdsingleapplicationguard.cpp
    kdsingleapplicationguard/kdsharedmemorylocker.cpp
    kdsingleapplicationguard/kdtoolsglobal.cpp
    kdsingleapplicationguard/kdlockedsharedmemorypointer.cpp
)
set( kdsagSources "" )
foreach( _s ${_kdsagSources} )
    list( APPEND kdsagSources ${CMAKE_SOURCE_DIR}/3rdparty/${_s} )
endforeach()
mark_thirdparty_code( ${kdsagSources} )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
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
add_library( calamares SHARED ${libSources} ${kdsagSources} )
set_target_properties( calamares
    PROPERTIES
        VERSION ${CALAMARES_VERSION_SHORT}
        SOVERSION ${CALAMARES_VERSION_SHORT}
)
calamares_automoc( calamares )

target_link_libraries( calamares
    LINK_PRIVATE
        ${OPTIONAL_PRIVATE_LIBRARIES}
    LINK_PUBLIC
        yamlcpp
        Qt5::Core
        KF5::CoreAddons
        ${OPTIONAL_PUBLIC_LIBRARIES}
)

install( TARGETS calamares
    EXPORT CalamaresLibraryDepends
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
file( GLOB kdsingleapplicationguardHeaders "kdsingleapplicationguard/*.h" )
file( GLOB utilsHeaders "utils/*.h" )

install( FILES ${CMAKE_CURRENT_BINARY_DIR}/CalamaresConfig.h DESTINATION include/libcalamares )
install( FILES ${rootHeaders}                       DESTINATION include/libcalamares )
install( FILES ${kdsingleapplicationguardHeaders}   DESTINATION include/libcalamares/kdsingleapplicationguard )
install( FILES ${utilsHeaders}                      DESTINATION include/libcalamares/utils )

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

if( BUILD_TESTING )
    add_executable( test_geoip geoip/test_geoip.cpp ${geoip_src} )
    target_link_libraries( test_geoip calamares Qt5::Network yamlcpp )
    calamares_automoc( test_geoip )
endif()
