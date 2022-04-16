# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# libcalamaresui is the GUI part of Calamares, which includes handling
# view modules, view steps, widgets, and branding.

# The UI libs use the non-UI library
include_directories(${CMAKE_SOURCE_DIR}/src/libcalamares ${CMAKE_BINARY_DIR}/src/libcalamares ${CMAKE_SOURCE_DIR})

set(calamaresui_SOURCES
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
    widgets/ErrorDialog.cpp
    widgets/FixedAspectRatioLabel.cpp
    widgets/PrettyRadioButton.cpp
    widgets/LogWidget.cpp
    widgets/TranslationFix.cpp
    widgets/WaitingWidget.cpp
    widgets/waitingspinnerwidget.cpp
    Branding.cpp
    ViewManager.cpp
)

if(WITH_PYTHON)
    list(APPEND calamaresui_SOURCES modulesystem/PythonJobModule.cpp)
endif()

if(WITH_QML)
    list(APPEND calamaresui_SOURCES utils/Qml.cpp viewpages/QmlViewStep.cpp)
endif()

calamares_add_library(calamaresui
    SOURCES ${calamaresui_SOURCES}
    EXPORT_MACRO UIDLLEXPORT_PRO
    LINK_LIBRARIES
        Qt5::Svg
    RESOURCES libcalamaresui.qrc
    EXPORT Calamares
    UI
        utils/ErrorDialog/ErrorDialog.ui
    VERSION ${CALAMARES_VERSION_SHORT}
)
target_link_libraries(calamaresui PRIVATE yamlcpp::yamlcpp)
if(KF5CoreAddons_FOUND AND KF5CoreAddons_VERSION VERSION_GREATER_EQUAL 5.58)
    target_compile_definitions(calamaresui PRIVATE WITH_KOSRelease)
    target_link_libraries(calamaresui PRIVATE KF5::CoreAddons)
endif()
if(WITH_QML)
    target_link_libraries(calamaresui PUBLIC Qt5::QuickWidgets)
endif()

add_library(Calamares::calamaresui ALIAS calamaresui)

### Installation
#
#
# The library is already installed through calamares_add_library(),
# so we only need to do headers. Unlike the Calamares source tree,
# where libcalamares and libcalamaresui live in different branches,
# we're going to glom it all together in the installed headers location.

install(FILES Branding.h ViewManager.h DESTINATION include/libcalamares)

# Install each subdir-worth of header files
foreach(subdir modulesystem utils viewpages widgets)
    file(GLOB subdir_headers "${subdir}/*.h")
    install(FILES ${subdir_headers} DESTINATION include/libcalamares/${subdir})
endforeach()

calamares_add_test(test_libcalamaresuipaste SOURCES utils/TestPaste.cpp utils/Paste.cpp LIBRARIES calamaresui)
