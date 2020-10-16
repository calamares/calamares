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

    viewpages/BlankViewStep.cpp
    viewpages/ExecutionViewStep.cpp
    viewpages/Slideshow.cpp
    viewpages/ViewStep.cpp

    widgets/ClickableLabel.cpp
    widgets/FixedAspectRatioLabel.cpp
    widgets/PrettyRadioButton.cpp
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
    list( APPEND calamaresui_SOURCES
        modulesystem/PythonQtViewModule.cpp
        utils/PythonQtUtils.cpp
        viewpages/PythonQtJob.cpp
        viewpages/PythonQtViewStep.cpp
        viewpages/PythonQtGlobalStorageWrapper.cpp
        viewpages/PythonQtUtilsWrapper.cpp
    )
endif()

if( WITH_QML )
    list( APPEND calamaresui_SOURCES
        utils/Qml.cpp
        viewpages/QmlViewStep.cpp
    )
endif()

calamares_add_library( calamaresui
    SOURCES ${calamaresui_SOURCES}
    EXPORT_MACRO UIDLLEXPORT_PRO
    LINK_LIBRARIES
        Qt5::Svg
        yamlcpp
    RESOURCES libcalamaresui.qrc
    EXPORT Calamares
    VERSION ${CALAMARES_VERSION_SHORT}
)

if( KF5CoreAddons_FOUND AND KF5CoreAddons_VERSION VERSION_GREATER_EQUAL 5.58 )
    target_compile_definitions( calamaresui PRIVATE WITH_KOSRelease )
endif()
if( WITH_PYTHONQT )
    # *_DIRS because we also use extensions
    target_include_directories( calamaresui PRIVATE ${PYTHON_INCLUDE_DIRS} ${PYTHONQT_INCLUDE_DIRS} )
    target_link_libraries( calamaresui PRIVATE ${PYTHON_LIBRARIES} ${PYTHONQT_LIBRARIES} )
endif()
if( WITH_QML )
    target_link_libraries( calamaresui PUBLIC Qt5::QuickWidgets )
endif()


### Installation
#
#
# The library is already installed through calamares_add_library(),
# so we only need to do headers. Unlike the Calamares source tree,
# where libcalamares and libcalamaresui live in different branches,
# we're going to glom it all together in the installed headers location.

install(
    FILES
        Branding.h
        ViewManager.h
    DESTINATION include/libcalamares
)

# Install each subdir-worth of header files
foreach( subdir modulesystem utils viewpages widgets )
    file( GLOB subdir_headers "${subdir}/*.h" )
    install( FILES ${subdir_headers} DESTINATION include/libcalamares/${subdir} )
endforeach()
