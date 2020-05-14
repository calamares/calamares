if( NOT WITH_QML )
    calamares_skip_module( "notesqml (QML is not supported in this build)" )
    return()
endif()

calamares_add_plugin( notesqml
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        NotesQmlViewStep.cpp
    RESOURCES
        notesqml.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
