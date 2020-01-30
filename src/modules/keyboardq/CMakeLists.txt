
set( _keyboard ${CMAKE_CURRENT_SOURCE_DIR}/../keyboardq )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui ${CMAKE_CURRENT_SOURCE_DIR}/../../libcalamares ${_keyboard} )

calamares_add_plugin( keyboardq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        KeyboardQmlViewStep.cpp
        KeyboardLayoutModel.cpp
        SetKeyboardLayoutJob.cpp
        keyboardwidget/keyboardglobal.cpp
        keyboardwidget/keyboardpreview.cpp
      RESOURCES
        keyboard.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${YAMLCPP_LIBRARY}
    SHARED_LIB
)

add_executable( keyboardqmltest qmlmain.cpp Config.cpp KeyboardQmlViewStep.cpp KeyboardLayoutModel.cpp SetKeyboardLayoutJob.cpp keyboardwidget/keyboardglobal.cpp)

target_link_libraries( keyboardqmltest PRIVATE calamaresui Qt5::Core Qt5::Network Qt5::DBus)
set_target_properties( keyboardqmltest
    PROPERTIES
        ENABLE_EXPORTS TRUE
        RUNTIME_OUTPUT_NAME keyboardqmltest
)
calamares_automoc( keyboardqmltest )
calamares_autouic( keyboardqmltest )
