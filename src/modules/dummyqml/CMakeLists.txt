calamares_add_plugin( dummyqml
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        DummyQmlViewStep.cpp
    RESOURCES
        dummyqml.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
