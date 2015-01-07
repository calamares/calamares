include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( keyboard
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        KeyboardViewStep.cpp
        KeyboardPage.cpp
        SetKeyboardLayoutJob.cpp
        keyboardwidget/keyboardglobal.cpp
        keyboardwidget/keyboardpreview.cpp
    UI
        KeyboardPage.ui
    RESOURCES
        keyboard.qrc
    LINK_LIBRARIES
        calamaresui
    SHARED_LIB
)
