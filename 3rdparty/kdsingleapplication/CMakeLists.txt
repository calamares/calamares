set(KDSINGLEAPPLICATION_STATIC ON)

set(KDSINGLEAPPLICATION_SRCS kdsingleapplication.cpp kdsingleapplication_localsocket.cpp)

set(KDSINGLEAPPLICATION_INSTALLABLE_INCLUDES kdsingleapplication.h kdsingleapplication_lib.h)

set(KDSINGLEAPPLICATION_NON_INSTALLABLE_INCLUDES kdsingleapplication_localsocket_p.h)

if(KDSINGLEAPPLICATION_STATIC)
    add_library(kdsingleapplication STATIC ${KDSINGLEAPPLICATION_INSTALLABLE_INCLUDES} ${KDSINGLEAPPLICATION_SRCS})
    target_compile_definitions(kdsingleapplication PUBLIC KDSINGLEAPPLICATION_STATIC_BUILD)
else()
    add_library(kdsingleapplication SHARED ${KDSINGLEAPPLICATION_INSTALLABLE_INCLUDES} ${KDSINGLEAPPLICATION_SRCS})
    target_compile_definitions(kdsingleapplication PRIVATE KDSINGLEAPPLICATION_SHARED_BUILD)
endif()
set_target_properties( kdsingleapplication PROPERTIES AUTOMOC TRUE )

set(KDSINGLEAPPLICATION_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR}/kdsingleapplication)

target_include_directories(
    kdsingleapplication
    PUBLIC $<INSTALL_INTERFACE:${KDSINGLEAPPLICATION_INCLUDEDIR}> $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(kdsingleapplication ${qtname}::Core ${qtname}::Network)
