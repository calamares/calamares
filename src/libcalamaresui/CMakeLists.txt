set( CALAMARESUI_LIBRARY_TARGET calamaresui )

list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_SOURCES
    modulesystem/Module.cpp
    modulesystem/ModuleManager.cpp
    modulesystem/ProcessJobModule.cpp
    modulesystem/ViewModule.cpp

    utils/CalamaresUtilsGui.cpp
    utils/YamlUtils.cpp

    viewpages/AbstractPage.cpp
    viewpages/ViewStep.cpp

    InstallationViewStep.cpp
    Settings.cpp
    ViewManager.cpp
)

list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_UI

)

calamares_add_library( ${CALAMARESUI_LIBRARY_TARGET}
    SOURCES ${${CALAMARESUI_LIBRARY_TARGET}_SOURCES}
    UI ${${CALAMARESUI_LIBRARY_TARGET}_UI}
    EXPORT_MACRO UIDLLEXPORT_PRO
    LINK_LIBRARIES
        yaml-cpp
    EXPORT CalamaresLibraryDepends
    VERSION ${CALAMARES_VERSION_SHORT}
)
