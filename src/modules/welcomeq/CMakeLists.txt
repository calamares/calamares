# This is a re-write of the welcome module using QML view steps
# instead of widgets.

set( _welcome ${CMAKE_CURRENT_SOURCE_DIR}/../welcome )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui ${_welcome} )

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
    ${_welcome}/checker/CheckerContainer.cpp
    ${_welcome}/checker/GeneralRequirements.cpp
    ${_welcome}/checker/ResultWidget.cpp
    ${_welcome}/checker/ResultsListWidget.cpp
    ${PARTMAN_SRC}
)

calamares_add_plugin( welcomeq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${CHECKER_SOURCES}
        WelcomeQmlViewStep.cpp
        Config.cpp
    RESOURCES
        welcomeq.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${CHECKER_LINK_LIBRARIES}
        Qt5::DBus
        Qt5::Network
    SHARED_LIB
)
