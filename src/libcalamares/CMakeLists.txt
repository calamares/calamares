project( calamareslib )

add_definitions( ${QT_DEFINITIONS} )
add_definitions( -DQT_SHARED )
add_definitions( -DQT_SHAREDPOINTER_TRACK_POINTERS )

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../calamares/Config.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/config.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../calamares/CalamaresVersion.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/CalamaresVersion.h)

set( libSources
    JobQueue.cpp
)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}

    ${QT_INCLUDE_DIR}
)

add_library( calamareslib SHARED ${libSources})
set_target_properties(
    calamareslib
        PROPERTIES
            AUTOMOC TRUE
            VERSION ${CALAMARES_VERSION_SHORT}
            SOVERSION ${CALAMARES_VERSION_SHORT}
            OUTPUT_NAME "calamares"
)

qt5_use_modules( calamareslib Widgets )

target_link_libraries( calamareslib
    #LINK_PRIVATE
    # internal deps, if any

    LINK_PUBLIC
    # External deps
    Qt5Core
)

install( TARGETS calamareslib
    EXPORT CalamaresLibraryDepends
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install header files
file( GLOB rootHeaders "*.h" )

install( FILES ${CMAKE_CURRENT_BINARY_DIR}/config.h DESTINATION include/libcalamares )
install( FILES ${rootHeaders}                       DESTINATION include/libcalamares )
