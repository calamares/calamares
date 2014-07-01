project( calamares )

add_definitions( -DUIDLLEXPORT_PRO )

if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
    message( "Building in debug mode, enabling all debug updates" )
endif()

set( calamaresSources
    main.cpp
    CalamaresApplication.cpp
    CalamaresWindow.cpp
    Settings.cpp
    ViewManager.cpp
    YamlUtils.cpp

    modulesystem/Module.cpp
    modulesystem/ModuleManager.cpp
    modulesystem/ViewModule.cpp

    progresstree/CategoryItem.cpp
    progresstree/ProgressTreeItem.cpp
    progresstree/ProgressTreeModel.cpp
    progresstree/ProgressTreeView.cpp
    progresstree/ViewStepItem.cpp

    utils/CalamaresUtilsGui.cpp

    viewpages/ViewStep.cpp
    viewpages/AbstractPage.cpp
)

set( calamaresUi
    CalamaresWindow.ui
)

include_directories(
    .
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/../libcalamares

    ../libcalamares
)

include( GNUInstallDirs )

qt5_wrap_ui( calamaresUi_H ${calamaresUi} )

#qt_add_resources( calamaresRc "../../resources.qrc" )

# Translations
include( ${CMAKE_SOURCE_DIR}/lang/translations.cmake )
add_calamares_translations( ${CALAMARES_TRANSLATION_LANGUAGES} )

set( final_src ${calamaresUi_H} ${calamaresSources} ${calamaresRc} )

add_executable( calamares_bin ${final_src} )
SET_TARGET_PROPERTIES(calamares_bin
    PROPERTIES
        AUTOMOC TRUE
        ENABLE_EXPORTS TRUE
        RUNTIME_OUTPUT_NAME calamares
)


qt5_use_modules( calamares_bin Core Widgets )
target_link_libraries( calamares_bin
    ${LINK_LIBRARIES}
    ${CALAMARES_LIBRARIES}
    Qt5::Core
    Qt5::Widgets
    yaml-cpp
)

install( TARGETS calamares_bin
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
