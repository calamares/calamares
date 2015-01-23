set( QML_FILES
    qmldir
    Presentation.qml
    Slide.qml
)

set( SLIDESHOW_DIR share/calamares/slideshow )

foreach( QML_FILE ${QML_FILES} )
    configure_file( ${QML_FILE} ${QML_FILE} COPYONLY )
    install( FILES ${CMAKE_CURRENT_BINARY_DIR}/${QML_FILE}
             DESTINATION ${SLIDESHOW_DIR} )
endforeach()

