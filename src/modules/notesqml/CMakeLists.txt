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
