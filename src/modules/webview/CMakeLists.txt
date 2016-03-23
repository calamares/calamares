find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED WebEngine WebEngineWidgets )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui
                     ${QT_QTWEBENGINE_INCLUDE_DIR} )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                       ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules )


calamares_add_plugin( webview
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        WebViewStep.cpp
    LINK_LIBRARIES
        calamaresui
        Qt5::WebEngine
        Qt5::WebEngineWidgets
    SHARED_LIB
)
