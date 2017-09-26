list( APPEND CALA_WEBVIEW_INCLUDE_DIRECTORIES
    ${PROJECT_BINARY_DIR}/src/libcalamaresui
)
list( APPEND CALA_WEBVIEW_LINK_LIBRARIES
    calamaresui
)

option( WEBVIEW_FORCE_WEBKIT "Always build webview with WebKit instead of WebEngine regardless of Qt version." OFF)

message( STATUS "Found Qt version ${Qt5Core_VERSION}")
if ( Qt5Core_VERSION VERSION_LESS 5.6 OR WEBVIEW_FORCE_WEBKIT )
    message( STATUS " .. using webkit")
    find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED WebKit WebKitWidgets )

    list( APPEND CALA_WEBVIEW_INCLUDE_DIRECTORIES
        ${QT_QTWEBKIT_INCLUDE_DIR}
    )
    list( APPEND CALA_WEBVIEW_LINK_LIBRARIES
        Qt5::WebKit
        Qt5::WebKitWidgets
    )
    set( WEBVIEW_WITH_WEBKIT 1 )
else()
    message( STATUS " .. using webengine")
    find_package( Qt5 ${QT_VERSION} CONFIG REQUIRED WebEngine WebEngineWidgets )

    list( APPEND CALA_WEBVIEW_INCLUDE_DIRECTORIES
        ${QT_QTWEBENGINE_INCLUDE_DIR}
    )
    list( APPEND CALA_WEBVIEW_LINK_LIBRARIES
        Qt5::WebEngine
        Qt5::WebEngineWidgets
    )
    set( WEBVIEW_WITH_WEBENGINE 1 )
endif()

include_directories( ${CALA_WEBVIEW_INCLUDE_DIRECTORIES} )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                       ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules )

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/WebViewConfig.h.in
                ${CMAKE_CURRENT_BINARY_DIR}/WebViewConfig.h )

calamares_add_plugin( webview
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        WebViewStep.cpp
    LINK_PRIVATE_LIBRARIES
        ${CALA_WEBVIEW_LINK_LIBRARIES}
    SHARED_LIB
)
