set( _keyboard ${CMAKE_CURRENT_SOURCE_DIR}/../keyboard )

include_directories( ${_keyboard} )

calamares_add_plugin( keyboardq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        KeyboardQmlViewStep.cpp
        ${_keyboard}/Config.cpp
        ${_keyboard}/KeyboardLayoutModel.cpp
        ${_keyboard}/SetKeyboardLayoutJob.cpp
        ${_keyboard}/keyboardwidget/keyboardglobal.cpp
    RESOURCES
        keyboardq.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
