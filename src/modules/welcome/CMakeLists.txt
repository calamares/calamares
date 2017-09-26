include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

find_package( LIBPARTED REQUIRED )
find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED DBus Network )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

set( CHECKER_SOURCES
    checker/CheckItemWidget.cpp
    checker/CheckerWidget.cpp
    checker/RequirementsChecker.cpp
    checker/partman_devices.c
)
set( CHECKER_LINK_LIBRARIES
    ${LIBPARTED_LIBS}
    Qt5::DBus
    Qt5::Network
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
    SHARED_LIB
)
