# This is a re-write of the welcome module using QML view steps
# instead of widgets.

if( NOT WITH_QML )
    calamares_skip_module( "welcomeq (QML is not supported in this build)" )
    return()
endif()

set( _welcome ${CMAKE_CURRENT_SOURCE_DIR}/../welcome )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui ${CMAKE_CURRENT_SOURCE_DIR}/../../libcalamares ${_welcome} )

# DUPLICATED WITH WELCOME MODULE
find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED DBus Network )

find_package( LIBPARTED )
if ( LIBPARTED_FOUND )
    set( PARTMAN_SRC ${_welcome}/checker/partman_devices.c )
    set( CHECKER_LINK_LIBRARIES ${LIBPARTED_LIBRARY} )
else()
    set( PARTMAN_SRC )
    set( CHECKER_LINK_LIBRARIES )
    add_definitions( -DWITHOUT_LIBPARTED )
endif()

set( CHECKER_SOURCES
    ${_welcome}/checker/GeneralRequirements.cpp
    ${PARTMAN_SRC}
)

calamares_add_plugin( welcomeq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${CHECKER_SOURCES}
        WelcomeQmlViewStep.cpp
        ${_welcome}/Config.cpp
    RESOURCES
        welcomeq.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${CHECKER_LINK_LIBRARIES}
        Qt5::DBus
        Qt5::Network
    SHARED_LIB
)

# add_executable( welcomeqmltest qmlmain.cpp Config.cpp WelcomeQmlViewStep.cpp ${CHECKER_SOURCES} )
# target_link_libraries( welcomeqmltest PRIVATE calamaresui Qt5::Core Qt5::Network Qt5::DBus ${CHECKER_LINK_LIBRARIES})
# set_target_properties( welcomeqmltest
#     PROPERTIES
#         ENABLE_EXPORTS TRUE
#         RUNTIME_OUTPUT_NAME welcomeqmltest
# )
# calamares_automoc( welcomeqmltest )
# calamares_autouic( welcomeqmltest )
