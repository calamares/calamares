set( CALAMARESUI_LIBRARY_TARGET calamaresui )

list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_SOURCES
    modulesystem/CppJobModule.cpp
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

if( WITH_PYTHONQT )
    include_directories(${PYTHON_INCLUDE_DIRS})
    include_directories(${PYTHONQT_INCLUDE_DIR})

    list( APPEND ${CALAMARESUI_LIBRARY_TARGET}_SOURCES
        modulesystem/PythonQtViewModule.cpp
        utils/PythonQtUtils.cpp
        viewpages/PythonQtJob.cpp
        viewpages/PythonQtViewStep.cpp
        viewpages/PythonQtGlobalStorageWrapper.cpp
        viewpages/PythonQtUtilsWrapper.cpp
    )
    set( OPTIONAL_PRIVATE_LIBRARIES
        ${OPTIONAL_PRIVATE_LIBRARIES}
        ${PYTHON_LIBRARIES}
        ${PYTHONQT_LIBRARIES}
    )
endif()

calamares_add_library( ${CALAMARESUI_LIBRARY_TARGET}
    SOURCES ${${CALAMARESUI_LIBRARY_TARGET}_SOURCES}
    UI ${${CALAMARESUI_LIBRARY_TARGET}_UI}
    EXPORT_MACRO UIDLLEXPORT_PRO
    LINK_PRIVATE_LIBRARIES
        yaml-cpp
        Qt5::Svg
        Qt5::QuickWidgets
        ${OPTIONAL_PRIVATE_LIBRARIES}
    RESOURCES libcalamaresui.qrc
    EXPORT CalamaresLibraryDepends
    VERSION ${CALAMARES_VERSION_SHORT}
)
