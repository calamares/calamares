set( CALAMARESUI_LIBRARY_TARGET calamaresui )

list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_SOURCES
    modulesystem/Module.cpp
    modulesystem/ModuleManager.cpp
    modulesystem/ProcessJobModule.cpp
    modulesystem/ViewModule.cpp

    utils/CalamaresUtilsGui.cpp
    utils/ImageRegistry.cpp
    utils/YamlUtils.cpp

    viewpages/AbstractPage.cpp
    viewpages/ViewStep.cpp

    widgets/ClickableLabel.cpp
    widgets/QtWaitingSpinner.cpp
    widgets/WaitingWidget.cpp

    InstallationViewStep.cpp
    Branding.cpp
    Settings.cpp
    ViewManager.cpp
)

list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_UI

)

if( WITH_PYTHON )
    list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_SOURCES
        modulesystem/PythonJobModule.cpp
    )
endif()

calamares_add_library( ${CALAMARESUI_LIBRARY_TARGET}
    SOURCES ${${CALAMARESUI_LIBRARY_TARGET}_SOURCES}
    UI ${${CALAMARESUI_LIBRARY_TARGET}_UI}
    EXPORT_MACRO UIDLLEXPORT_PRO
    LINK_LIBRARIES
        yaml-cpp
        Qt5::Svg
	Qt5::QuickWidgets
    RESOURCES libcalamaresui.qrc
    EXPORT CalamaresLibraryDepends
    VERSION ${CALAMARES_VERSION_SHORT}
)

add_subdirectory( slideshow )
