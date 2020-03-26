set( _keyboard ${CMAKE_CURRENT_SOURCE_DIR}/../keyboard )

calamares_add_plugin( keyboardq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        ${_keyboard}/Config.cpp
        ${_keyboard}/KeyboardLayoutModel.cpp
        ${_keyboard}/SetKeyboardLayoutJob.cpp
        ${_keyboard}/keyboardwidget/keyboardglobal.cpp
    RESOURCES
        ${_keyboard}/keyboard.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
    SHARED_LIB
)
