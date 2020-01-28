# include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )
#
# set( _keyboard ${CMAKE_CURRENT_SOURCE_DIR}/../keyboard )
#
# calamares_add_plugin( keyboard
#     TYPE viewmodule
#     EXPORT_MACRO PLUGINDLLEXPORT_PRO
#     SOURCES
#         KeyboardViewStep.cpp
#         KeyboardPage.cpp
#         KeyboardLayoutModel.cpp
#         SetKeyboardLayoutJob.cpp
#         keyboardwidget/keyboardglobal.cpp
#         keyboardwidget/keyboardpreview.cpp
#     UI
#         KeyboardPage.ui
#     RESOURCES
#         keyboard.qrc
#     LINK_PRIVATE_LIBRARIES
#         calamaresui
#     SHARED_LIB
# )
