# libcalamaresui is the GUI part of Calamares, which includes handling
# view modules, view steps, widgets, and branding.

# The UI libs use the non-UI library
include_directories( ${CMAKE_SOURCE_DIR}/src/libcalamares ${CMAKE_BINARY_DIR}/src/libcalamares ${CMAKE_SOURCE_DIR} )

set( calamaresui_SOURCES
    modulesystem/CppJobModule.cpp
    modulesystem/ModuleFactory.cpp
    modulesystem/ModuleManager.cpp
    modulesystem/ProcessJobModule.cpp
    modulesystem/ViewModule.cpp

    utils/CalamaresUtilsGui.cpp
    utils/ImageRegistry.cpp
    utils/Paste.cpp
    utils/Qml.cpp

    viewpages/BlankViewStep.cpp
    viewpages/ExecutionViewStep.cpp
    viewpages/QmlViewStep.cpp
    viewpages/ViewStep.cpp

    widgets/ClickableLabel.cpp
    widgets/FixedAspectRatioLabel.cpp
    widgets/WaitingWidget.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/waitingspinnerwidget.cpp

    Branding.cpp
    ViewManager.cpp
)

# Don't warn about third-party sources
mark_thirdparty_code(
    ${CMAKE_SOURCE_DIR}/3rdparty/qjsonitem.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/qjsonmodel.cpp
    ${CMAKE_SOURCE_DIR}/3rdparty/waitingspinnerwidget.cpp
)

if( WITH_PYTHON )
    list( APPEND calamaresui_SOURCES
        modulesystem/PythonJobModule.cpp
    )
endif()

if( WITH_PYTHONQT )
    include_directories(${PYTHON_INCLUDE_DIRS})
    # *_DIRS because we also use extensions
    include_directories(${PYTHONQT_INCLUDE_DIRS})

    list( APPEND calamaresui_SOURCES
        modulesystem/PythonQtViewModule.cpp
        utils/PythonQtUtils.cpp
        viewpages/PythonQtJob.cpp
        viewpages/PythonQtViewStep.cpp
        viewpages/PythonQtGlobalStorageWrapper.cpp
        viewpages/PythonQtUtilsWrapper.cpp
    )
    set( OPTIONAL_PYTHON_LIBRARIES
        ${PYTHON_LIBRARIES}
        ${PYTHONQT_LIBRARIES}
    )
endif()

calamares_add_library( calamaresui
    SOURCES ${calamaresui_SOURCES}
    EXPORT_MACRO UIDLLEXPORT_PRO
    LINK_PRIVATE_LIBRARIES
        ${OPTIONAL_PYTHON_LIBRARIES}
    LINK_LIBRARIES
        Qt5::Svg
        Qt5::QuickWidgets
    RESOURCES libcalamaresui.qrc
    EXPORT CalamaresLibraryDepends
    VERSION ${CALAMARES_VERSION_SHORT}
)

if ( KF5CoreAddons_FOUND AND KF5CoreAddons_VERSION VERSION_GREATER_EQUAL 5.58 )
    target_compile_definitions( calamaresui PRIVATE WITH_KOSRelease )
endif()
