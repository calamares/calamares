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

target_link_libraries(
    calamares_bin
    PRIVATE calamares calamaresui calamares-i18n kdsingleapplication ${qtname}::Core ${qtname}::Widgets
)
target_link_libraries(calamares_bin PRIVATE ${kfname}::CoreAddons)
if(BUILD_CRASH_REPORTING)
    target_link_libraries(calamares_bin PRIVATE ${kfname}::Crash)
    target_compile_definitions(calamares_bin PRIVATE BUILD_CRASH_REPORTING)
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
    target_link_libraries(loadmodule PRIVATE ${qtname}::Core ${qtname}::Widgets calamares calamaresui)

    add_executable(test_conf test_conf.cpp)
    target_link_libraries(test_conf PUBLIC yamlcpp::yamlcpp ${qtname}::Core)

    if(WITH_PYBIND11)
        target_compile_definitions(loadmodule PRIVATE WITH_PYBIND11=1)
    endif()

endif()
