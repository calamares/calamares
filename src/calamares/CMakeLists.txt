# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

set(calamaresSources
    main.cpp
    CalamaresApplication.cpp
    CalamaresWindow.cpp
    DebugWindow.cpp
    VariantModel.cpp
    progresstree/ProgressTreeDelegate.cpp
    progresstree/ProgressTreeView.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src/libcalamares
    ${CMAKE_SOURCE_DIR}/src/libcalamaresui
    ${CMAKE_BINARY_DIR}/src/libcalamares
    ${CMAKE_CURRENT_SOURCE_DIR}
)

### EXECUTABLE
#
# "calamares_bin" is the main application, not to be confused with
# the target "calamares" which is the non-GUI library part.
#
# The calamares-i18n.cxx file -- full path in CALAMARES_TRANSLATIONS_SOURCE --
# is created as a target in the lang/ directory. This is compiled to a
# library (it's just the result of a QRC compile).
add_executable(calamares_bin ${calamaresSources} calamares.qrc)
target_include_directories(calamares_bin PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(calamares_bin PROPERTIES ENABLE_EXPORTS TRUE RUNTIME_OUTPUT_NAME calamares)
calamares_automoc( calamares_bin )
calamares_autouic( calamares_bin )
calamares_autorcc( calamares_bin )

if(kdsagSources)
    set_source_files_properties(${kdsagSources} PROPERTIES AUTOMOC OFF)
endif()

target_link_libraries(
    calamares_bin
    PRIVATE calamares calamaresui calamares-i18n Qt5::Core Qt5::Widgets KF5::CoreAddons KF5::DBusAddons
)
if(BUILD_KF5Crash)
    target_link_libraries(calamares_bin PRIVATE KF5::Crash)
    target_compile_definitions(calamares_bin PRIVATE BUILD_KF5Crash)
endif()

install(TARGETS calamares_bin BUNDLE DESTINATION . RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(
    FILES ${CMAKE_SOURCE_DIR}/data/images/squid.svg
    RENAME calamares.svg
    DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
)

### TESTS
#
#
if(BUILD_TESTING)
    # Don't install, these are just for enable_testing
    add_executable(loadmodule testmain.cpp)
    target_link_libraries(loadmodule PRIVATE Qt5::Core Qt5::Widgets calamares calamaresui)

    add_executable(test_conf test_conf.cpp)
    target_link_libraries(test_conf PUBLIC yamlcpp::yamlcpp Qt5::Core)
endif()
