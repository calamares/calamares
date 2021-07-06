if( NOT WITH_QML )
    calamares_skip_module( "summaryq (QML is not supported in this build)" )
    return()
endif()

set( _summary ${CMAKE_CURRENT_SOURCE_DIR}/../summary )
include_directories( ${_finished} )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
calamares_add_plugin( summaryq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        SummaryQmlViewStep.cpp
        Config.cpp
    UI
    RESOURCES
        summaryq.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
