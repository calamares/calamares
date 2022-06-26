set(KDSINGLEAPPLICATION_SRCS
	kdsingleapplication.cpp
	kdsingleapplication_localsocket.cpp)

set(KDSINGLEAPPLICATION_INSTALLABLE_INCLUDES
       kdsingleapplication.h
       kdsingleapplication_lib.h
    )

set(KDSINGLEAPPLICATION_NON_INSTALLABLE_INCLUDES
       kdsingleapplication_localsocket_p.h
   )

if (${PROJECT_NAME}_STATIC)
    add_library(kdsingleapplication STATIC ${KDSINGLEAPPLICATION_INSTALLABLE_INCLUDES} ${KDSINGLEAPPLICATION_SRCS})
    target_compile_definitions(kdsingleapplication PUBLIC KDSINGLEAPPLICATION_STATIC_BUILD)
else()
    add_library(kdsingleapplication SHARED ${KDSINGLEAPPLICATION_INSTALLABLE_INCLUDES} ${KDSINGLEAPPLICATION_SRCS})
    target_compile_definitions(kdsingleapplication PRIVATE KDSINGLEAPPLICATION_SHARED_BUILD)
endif()

include(GNUInstallDirs)

set(KDSINGLEAPPLICATION_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR}/kdsingleapplication)

target_include_directories(kdsingleapplication
    PUBLIC
        $<INSTALL_INTERFACE:${KDSINGLEAPPLICATION_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

if (WIN32)
    target_link_libraries(kdsingleapplication kernel32)
endif()
target_link_libraries(kdsingleapplication Qt5::Core Qt5::Network)

install (FILES ${KDSINGLEAPPLICATION_INSTALLABLE_INCLUDES} DESTINATION ${KDSINGLEAPPLICATION_INCLUDEDIR})

install (TARGETS kdsingleapplication
         EXPORT kdsingleapplicationTargets
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    KDSingleApplicationConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

install(EXPORT kdsingleapplicationTargets
    FILE KDSingleApplicationTargets.cmake
    NAMESPACE KDAB::
    DESTINATION lib/cmake/KDSingleApplication
    )
configure_file(KDSingleApplicationConfig.cmake.in KDSingleApplicationConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KDSingleApplicationConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KDSingleApplicationConfigVersion.cmake"
    DESTINATION lib/cmake/KDSingleApplication
    )
