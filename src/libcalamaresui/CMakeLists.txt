project( libcalamaresui CXX )

set( calamaresui_SOURCES
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
    widgets/waitingspinnerwidget.cpp
    widgets/WaitingWidget.cpp

    ExecutionViewStep.cpp
    Branding.cpp
    Settings.cpp
    ViewManager.cpp
)

# Don't warn about third-party sources
mark_thirdparty_code(
    utils/ImageRegistry.cpp
    utils/qjsonitem.cpp
    utils/qjsonmodel.cpp
    widgets/waitingspinnerwidget.cpp
)

set( calamaresui_UI
    utils/DebugWindow.ui
)

if( WITH_PYTHON )
    list( APPEND calamaresui_SOURCES
        modulesystem/PythonJobModule.cpp
    )
endif()

if( WITH_PYTHONQT )
    include_directories(${PYTHON_INCLUDE_DIRS})
    include_directories(${PYTHONQT_INCLUDE_DIR})

    list( APPEND calamaresui_SOURCES
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

calamares_add_library( calamaresui
    SOURCES ${calamaresui_SOURCES}
    UI ${calamaresui_UI}
    EXPORT_MACRO UIDLLEXPORT_PRO
    LINK_PRIVATE_LIBRARIES
        ${YAMLCPP_LIBRARY}
        ${OPTIONAL_PRIVATE_LIBRARIES}
    LINK_LIBRARIES
        Qt5::Svg
        Qt5::QuickWidgets
    RESOURCES libcalamaresui.qrc
    EXPORT CalamaresLibraryDepends
    VERSION ${CALAMARES_VERSION_SHORT}
)
