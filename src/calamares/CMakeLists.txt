project( calamares )

add_definitions( -DUIDLLEXPORT_PRO )

if( NOT CMAKE_BUILD_TYPE STREQUAL "Release" )
    message( "Building in debug mode, enabling all debug updates" )
endif()

set( calamaresSources
    main.cpp
    CalamaresApplication.cpp
    CalamaresWindow.cpp

    progresstree/ProgressTreeDelegate.cpp
    progresstree/ProgressTreeItem.cpp
    progresstree/ProgressTreeModel.cpp
    progresstree/ProgressTreeView.cpp
    progresstree/ViewStepItem.cpp
)

set( calamaresUi
    #nothing to do here
)

include_directories(
    .
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/../libcalamares

    ../libcalamares
    ../libcalamaresui
)

include( GNUInstallDirs )

qt5_wrap_ui( calamaresUi_H ${calamaresUi} )

# Translations
include( CalamaresAddTranslations )
add_calamares_translations( ${CALAMARES_TRANSLATION_LANGUAGES} )

set( final_src ${calamaresUi_H} ${calamaresSources} ${calamaresRc} ${trans_outfile} )

add_executable( calamares_bin ${final_src} )
SET_TARGET_PROPERTIES(calamares_bin
    PROPERTIES
        AUTOMOC TRUE
        ENABLE_EXPORTS TRUE
        RUNTIME_OUTPUT_NAME calamares
)

target_link_libraries( calamares_bin
    PRIVATE
        ${CALAMARES_LIBRARIES}
        calamaresui
        Qt5::Core
        Qt5::Widgets
        ${LINK_LIBRARIES}
)

install( TARGETS calamares_bin
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install( FILES ${CMAKE_SOURCE_DIR}/data/images/squid.svg
    RENAME calamares.svg
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
)
