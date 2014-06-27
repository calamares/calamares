project( calamareslib )

if( WITH_PARTITIONMANAGER )
add_subdirectory( partitionmanager/calamares )
endif()

add_definitions( ${QT_DEFINITIONS} )
add_definitions( -DQT_SHARED )
add_definitions( -DQT_SHAREDPOINTER_TRACK_POINTERS )
add_definitions( -DDLLEXPORT_PRO )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/CalamaresConfig.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/CalamaresConfig.h )
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/../calamares/CalamaresVersion.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/CalamaresVersion.h )

set( libSources
    Job.cpp
    JobQueue.cpp

    kdsingleapplicationguard/kdsingleapplicationguard.cpp
    kdsingleapplicationguard/kdsharedmemorylocker.cpp
    kdsingleapplicationguard/kdtoolsglobal.cpp
    kdsingleapplicationguard/kdlockedsharedmemorypointer.cpp

    utils/CalamaresUtils.cpp
    utils/Logger.cpp
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}

    ${QT_INCLUDE_DIR}
)

add_library( calamareslib SHARED ${libSources} )
set_target_properties( calamareslib
    PROPERTIES
        AUTOMOC TRUE
        VERSION ${CALAMARES_VERSION_SHORT}
        SOVERSION ${CALAMARES_VERSION_SHORT}
        OUTPUT_NAME "calamares"
)

qt5_use_modules( calamareslib Core )

target_link_libraries( calamareslib
    #LINK_PRIVATE
    # internal deps, if any

    LINK_PUBLIC
    # External deps
    Qt5::Core
)

install( TARGETS calamareslib
    EXPORT CalamaresLibraryDepends
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install header files
file( GLOB rootHeaders "*.h" )
file( GLOB kdsingleapplicationguardHeaders "kdsingleapplicationguard/*.h" )
file( GLOB utilsHeaders "utils/*.h" )

install( FILES ${CMAKE_CURRENT_BINARY_DIR}/CalamaresConfig.h DESTINATION include/libcalamares )
install( FILES ${rootHeaders}                       DESTINATION include/libcalamares )
install( FILES ${kdsingleapplicationguardHeaders}   DESTINATION include/libcalamares/kdsingleapplicationguard )
install( FILES ${utilsHeaders}                      DESTINATION include/libcalamares/utils )
