project( libcalamares CXX )

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

set( libSources
    CppJob.cpp
    GlobalStorage.cpp
    Job.cpp
    JobQueue.cpp
    ProcessJob.cpp
)
set( utilsSources
    utils/CalamaresUtils.cpp
    utils/CalamaresUtilsSystem.cpp
    utils/Logger.cpp
    utils/PluginFactory.cpp
    utils/Retranslator.cpp
)
set( kdsagSources
    kdsingleapplicationguard/kdsingleapplicationguard.cpp
    kdsingleapplicationguard/kdsharedmemorylocker.cpp
    kdsingleapplicationguard/kdtoolsglobal.cpp
    kdsingleapplicationguard/kdlockedsharedmemorypointer.cpp
)
mark_thirdparty_code( ${kdsagSources} )

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if( WITH_PYTHON )
    set( libSources
        ${libSources}
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

    set( OPTIONAL_PRIVATE_LIBRARIES
        ${OPTIONAL_PRIVATE_LIBRARIES}
        ${PYTHON_LIBRARIES}
        ${Boost_LIBRARIES}
    )
endif()

if( WITH_PYTHONQT )
    include_directories(${PYTHON_INCLUDE_DIRS})
    link_directories(${PYTHON_LIBRARIES})

    include_directories(${PYTHONQT_INCLUDE_DIR})
    link_directories(${PYTHONQT_LIBRARY})

    set( OPTIONAL_PRIVATE_LIBRARIES
        ${OPTIONAL_PRIVATE_LIBRARIES}
        ${PYTHON_LIBRARIES}
        ${PYTHONQT_LIBRARY}
    )
endif()


add_library( calamares SHARED ${libSources} ${kdsagSources} ${utilsSources} )
set_target_properties( calamares
    PROPERTIES
        AUTOMOC TRUE
        VERSION ${CALAMARES_VERSION_SHORT}
        SOVERSION ${CALAMARES_VERSION_SHORT}
)

target_link_libraries( calamares
    LINK_PRIVATE ${OPTIONAL_PRIVATE_LIBRARIES}
    LINK_PUBLIC Qt5::Core
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
