find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

find_package( KPMcore 3.3 )
find_package( Qt5 REQUIRED DBus )  # Needed for KPMCore
find_package( KF5 REQUIRED I18n WidgetsAddons )  # Needed for KPMCore

if ( KPMcore_FOUND )
    if ( KPMcore_VERSION VERSION_GREATER "3.3.0")
        add_definitions(-DWITH_KPMCOREGT33) # kpmcore greater than 3.3
    endif()

    include_directories( ${KPMCORE_INCLUDE_DIR} )
    include_directories( ${PROJECT_BINARY_DIR}/src/libcalamares )

    calamares_add_plugin( fsresizer
        TYPE job
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            ResizeFSJob.cpp
        LINK_PRIVATE_LIBRARIES
            kpmcore
            calamares
        SHARED_LIB
    )
else()
    calamares_skip_module( "fsresizer (missing suitable KPMcore)" )
endif()
