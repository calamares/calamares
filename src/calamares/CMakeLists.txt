add_definitions( -DUIDLLEXPORT_PRO )

set( calamaresSources
    main.cpp
    CalamaresApplication.cpp
    CalamaresWindow.cpp

    DebugWindow.cpp
    VariantModel.cpp

    progresstree/ProgressTreeDelegate.cpp
    progresstree/ProgressTreeItem.cpp
    progresstree/ProgressTreeModel.cpp
    progresstree/ProgressTreeView.cpp
    progresstree/ViewStepItem.cpp
)

include_directories(
    .
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/../libcalamares

    ${CMAKE_SOURCE_DIR}/src/libcalamares
    ${CMAKE_SOURCE_DIR}/src//libcalamaresui
    ${CMAKE_SOURCE_DIR}
)

# Translations
include( CalamaresAddTranslations )
add_calamares_translations( ${CALAMARES_TRANSLATION_LANGUAGES} )

set( final_src ${calamaresSources} ${calamaresRc} ${trans_outfile} )

add_executable( calamares_bin ${final_src} )
set_target_properties(calamares_bin
    PROPERTIES
        ENABLE_EXPORTS TRUE
        RUNTIME_OUTPUT_NAME calamares
)
calamares_automoc( calamares_bin )
calamares_autouic( calamares_bin )

target_link_libraries( calamares_bin
    PRIVATE
        ${CALAMARES_LIBRARIES}
        calamaresui
        Qt5::Core
        Qt5::Widgets
        KF5::CoreAddons
)
if( WITH_KF5Crash )
    target_link_libraries( calamares_bin
        PRIVATE
            KF5::Crash
    )
    target_compile_definitions( calamares_bin PRIVATE WITH_KF5Crash )
endif()

install( TARGETS calamares_bin
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install( FILES ${CMAKE_SOURCE_DIR}/data/images/squid.svg
    RENAME calamares.svg
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
)

if( BUILD_TESTING )
    add_executable( loadmodule testmain.cpp )
    target_link_libraries( loadmodule ${CALAMARES_LIBRARIES} Qt5::Core Qt5::Widgets calamaresui )
    # Don't install, it's just for enable_testing
endif()
