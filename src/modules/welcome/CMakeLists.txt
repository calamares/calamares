include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED DBus Network )

find_package( LIBPARTED )
if ( LIBPARTED_FOUND )
    set( PARTMAN_SRC checker/partman_devices.c )
    set( CHECKER_LINK_LIBRARIES ${LIBPARTED_LIBRARY} )
else()
    set( PARTMAN_SRC )
    set( CHECKER_LINK_LIBRARIES )
    add_definitions( -DWITHOUT_LIBPARTED )
endif()

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

set( CHECKER_SOURCES
    checker/CheckItemWidget.cpp
    checker/CheckerWidget.cpp
    checker/RequirementsChecker.cpp
    ${PARTMAN_SRC}
)

calamares_add_plugin( welcome
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${CHECKER_SOURCES}
        WelcomeViewStep.cpp
        WelcomePage.cpp
    UI
        WelcomePage.ui
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${CHECKER_LINK_LIBRARIES}
        Qt5::DBus
        Qt5::Network
    SHARED_LIB
)
