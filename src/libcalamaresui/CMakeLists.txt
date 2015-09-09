set( CALAMARESUI_LIBRARY_TARGET calamaresui )

list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_SOURCES
    modulesystem/Module.cpp
    modulesystem/ModuleManager.cpp
    modulesystem/ProcessJobModule.cpp
    modulesystem/ViewModule.cpp

    utils/CalamaresUtilsGui.cpp
    utils/DebugWindow.cpp
    utils/ImageRegistry.cpp
    utils/YamlUtils.cpp

    utils/qjsonmodel.cpp
    utils/qjsonitem.cpp

    utils/PluginFactory.cpp

    viewpages/AbstractPage.cpp
    viewpages/ViewStep.cpp

    widgets/ClickableLabel.cpp
    widgets/FixedAspectRatioLabel.cpp
    widgets/QtWaitingSpinner.cpp
    widgets/WaitingWidget.cpp

    ExecutionViewStep.cpp
    Branding.cpp
    Settings.cpp
    ViewManager.cpp
)

list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_UI
    utils/DebugWindow.ui
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
