set( calamaresSources
    main.cpp
    CalamaresApplication.cpp
    CalamaresWindow.cpp

    DebugWindow.cpp
    VariantModel.cpp

    progresstree/ProgressTreeDelegate.cpp
    progresstree/ProgressTreeView.cpp
)

if( NOT WITH_KF5DBus )
    set( kdsagSources "" )
    foreach( _s
        kdsingleapplicationguard/kdsingleapplicationguard.cpp
        kdsingleapplicationguard/kdsharedmemorylocker.cpp
        kdsingleapplicationguard/kdtoolsglobal.cpp
        kdsingleapplicationguard/kdlockedsharedmemorypointer.cpp
    )
        list( APPEND kdsagSources ${CMAKE_SOURCE_DIR}/3rdparty/${_s} )
    endforeach()
    mark_thirdparty_code( ${kdsagSources} )
    list( APPEND calamaresSources ${kdsagSources} )
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src/libcalamares
    ${CMAKE_SOURCE_DIR}/src/libcalamaresui
    ${CMAKE_BINARY_DIR}/src/libcalamares
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Translations
include( CalamaresAddTranslations )
add_calamares_translations( ${CALAMARES_TRANSLATION_LANGUAGES} )
qt5_add_resources( calamaresRc calamares.qrc )

add_executable( calamares_bin ${calamaresSources} ${calamaresRc} ${trans_outfile} )
target_include_directories( calamares_bin PRIVATE ${CMAKE_SOURCE_DIR} )
set_target_properties(calamares_bin
    PROPERTIES
        ENABLE_EXPORTS TRUE
        RUNTIME_OUTPUT_NAME calamares
)
calamares_automoc( calamares_bin )
calamares_autouic( calamares_bin )

target_link_libraries( calamares_bin
    PRIVATE
        calamares
        calamaresui
        Qt5::Core
        Qt5::Widgets
        KF5::CoreAddons
)
if( WITH_KF5Crash )
    target_link_libraries( calamares_bin PRIVATE KF5::Crash )
    target_compile_definitions( calamares_bin PRIVATE WITH_KF5Crash )
endif()
if( WITH_KF5DBus )
    target_link_libraries( calamares_bin PRIVATE KF5::DBusAddons )
    target_compile_definitions( calamares_bin PRIVATE WITH_KF5DBus )
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
    # Don't install, these are just for enable_testing
    add_executable( loadmodule testmain.cpp )
    target_link_libraries( loadmodule PRIVATE Qt5::Core Qt5::Widgets calamares calamaresui )

    add_executable( test_conf test_conf.cpp )
    target_link_libraries( test_conf PUBLIC yamlcpp Qt5::Core )
endif()
