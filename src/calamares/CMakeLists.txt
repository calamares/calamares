# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

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
    set( kdsagSources
        ${CMAKE_SOURCE_DIR}/3rdparty/kdsingleapplicationguard/kdsingleapplicationguard.cpp
        ${CMAKE_SOURCE_DIR}/3rdparty/kdsingleapplicationguard/kdsharedmemorylocker.cpp
        ${CMAKE_SOURCE_DIR}/3rdparty/kdsingleapplicationguard/kdtoolsglobal.cpp
        ${CMAKE_SOURCE_DIR}/3rdparty/kdsingleapplicationguard/kdlockedsharedmemorypointer.cpp
    )
    mark_thirdparty_code( ${kdsagSources} )
    list( APPEND calamaresSources ${kdsagSources} )
endif()

include_directories(
    ${CMAKE_SOURCE_DIR}/src/libcalamares
    ${CMAKE_SOURCE_DIR}/src/libcalamaresui
    ${CMAKE_BINARY_DIR}/src/libcalamares
    ${CMAKE_CURRENT_SOURCE_DIR}
)

### TRANSLATIONS
#
#
set( TS_FILES "" )
set( calamares_i18n_qrc_content "" )

# calamares and qt language files
foreach( lang ${CALAMARES_TRANSLATION_LANGUAGES} )
    foreach( tlsource "calamares_${lang}" "tz_${lang}" "kb_${lang}" )
        if( EXISTS "${CMAKE_SOURCE_DIR}/lang/${tlsource}.ts" )
            set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}<file>${tlsource}.qm</file>\n" )
            list( APPEND TS_FILES "${CMAKE_SOURCE_DIR}/lang/${tlsource}.ts" )
        endif()
    endforeach()
endforeach()

set( trans_file calamares_i18n )
set( trans_infile ${CMAKE_CURRENT_BINARY_DIR}/${trans_file}.qrc )
set( trans_outfile ${CMAKE_CURRENT_BINARY_DIR}/qrc_${trans_file}.cxx )

configure_file( ${CMAKE_SOURCE_DIR}/lang/calamares_i18n.qrc.in ${trans_infile} @ONLY )

qt5_add_translation(QM_FILES ${TS_FILES})

# Run the resource compiler (rcc_options should already be set)
add_custom_command(
    OUTPUT ${trans_outfile}
    COMMAND "${Qt5Core_RCC_EXECUTABLE}"
    ARGS ${rcc_options} --format-version 1 -name ${trans_file} -o ${trans_outfile} ${trans_infile}
    MAIN_DEPENDENCY ${trans_infile}
    DEPENDS ${QM_FILES}
)

### EXECUTABLE
#
# "calamares_bin" is the main application, not to be confused with
# the target "calamares" which is the non-GUI library part.
#
add_executable( calamares_bin ${calamaresSources} calamares.qrc ${trans_outfile} )
target_include_directories( calamares_bin PRIVATE ${CMAKE_SOURCE_DIR} )
set_target_properties(calamares_bin
    PROPERTIES
        ENABLE_EXPORTS TRUE
        RUNTIME_OUTPUT_NAME calamares
)
calamares_automoc( calamares_bin )
calamares_autouic( calamares_bin )
calamares_autorcc( calamares_bin )

if( kdsagSources )
    set_source_files_properties( ${kdsagSources} PROPERTIES AUTOMOC OFF )
endif()

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

### TESTS
#
#
if( BUILD_TESTING )
    # Don't install, these are just for enable_testing
    add_executable( loadmodule testmain.cpp )
    target_link_libraries( loadmodule PRIVATE Qt5::Core Qt5::Widgets calamares calamaresui )

    add_executable( test_conf test_conf.cpp )
    target_link_libraries( test_conf PUBLIC yamlcpp Qt5::Core )
endif()
