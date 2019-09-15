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
    locale/TranslatableConfiguration.cpp

    # Network service
    network/Manager.cpp

    # Partition service
    partition/PartitionSize.cpp

    # Utility service
    utils/CalamaresUtilsSystem.cpp
    utils/CommandList.cpp
    utils/Dirs.cpp
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
    ${YAMLCPP_INCLUDE_DIR}
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
        ${YAMLCPP_LIBRARY}
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
if ( ECM_FOUND AND BUILD_TESTING )
    ecm_add_test(
            utils/Tests.cpp
        TEST_NAME
            libcalamarestest
        LINK_LIBRARIES
            calamares
            Qt5::Core
            Qt5::Test
    )
    calamares_automoc( libcalamarestest )

    ecm_add_test(
            geoip/GeoIPTests.cpp
            ${geoip_src}
        TEST_NAME
            geoiptest
        LINK_LIBRARIES
            calamares
            Qt5::Test
            ${YAMLCPP_LIBRARY}
    )
    calamares_automoc( geoiptest )

    ecm_add_test(
            partition/Tests.cpp
        TEST_NAME
            libcalamarespartitiontest
        LINK_LIBRARIES
            calamares
            Qt5::Test
    )
    calamares_automoc( libcalamarespartitiontest )

    ecm_add_test(
            locale/Tests.cpp
        TEST_NAME
            libcalamareslocaletest
        LINK_LIBRARIES
            calamares
            Qt5::Test
    )
    calamares_automoc( libcalamareslocaletest )

    ecm_add_test(
            network/Tests.cpp
        TEST_NAME
            libcalamaresnetworktest
        LINK_LIBRARIES
            calamares
            Qt5::Test
    )
    calamares_automoc( libcalamaresnetworktest )

    ecm_add_test(
            modulesystem/Tests.cpp
        TEST_NAME
            libcalamaresmodulesystemtest
        LINK_LIBRARIES
            calamares
            Qt5::Test
    )
    calamares_automoc( libcalamaresmodulesystemtest )
endif()

if( BUILD_TESTING )
    add_executable( test_geoip geoip/test_geoip.cpp ${geoip_src} )
    target_link_libraries( test_geoip calamares Qt5::Network ${YAMLCPP_LIBRARY} )
    calamares_automoc( test_geoip )
endif()
