macro(add_calamares_translations language)
    list( APPEND CALAMARES_LANGUAGES ${ARGV} )

    set( calamares_i18n_qrc_content "<!DOCTYPE RCC><RCC version=\"1.0\">\n" )

    # calamares and qt language files
    set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}<qresource prefix=\"/lang\">\n" )
    foreach( lang ${CALAMARES_LANGUAGES} )
        set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}<file>calamares_${lang}.qm</file>\n" )
        if( NOT lang STREQUAL "en" AND EXISTS ${QT_TRANSLATIONS_DIR}/qt_${lang}.qm )
            file( COPY ${QT_TRANSLATIONS_DIR}/qt_${lang}.qm DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )
            set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}<file>qt_${lang}.qm</file>\n" )
        endif()

        # build explicitly enabled languages
        list( APPEND TS_FILES "${CMAKE_SOURCE_DIR}/lang/calamares_${lang}.ts" )
    endforeach()

    set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}</qresource>\n" )
    set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}</RCC>\n" )

    file( WRITE ${CMAKE_BINARY_DIR}/lang/calamares_i18n.qrc "${calamares_i18n_qrc_content}" )

    qt5_add_translation(QM_FILES ${TS_FILES})

    ## HACK HACK HACK - around rcc limitations to allow out of source-tree building
    set( trans_file calamares_i18n )
    set( trans_srcfile ${CMAKE_BINARY_DIR}/lang/${trans_file}.qrc )
    set( trans_infile ${CMAKE_CURRENT_BINARY_DIR}/${trans_file}.qrc )
    set( trans_outfile ${CMAKE_CURRENT_BINARY_DIR}/qrc_${trans_file}.cxx )

    # Copy the QRC file to the output directory
    add_custom_command(
        OUTPUT ${trans_infile}
        COMMAND ${CMAKE_COMMAND} -E copy ${trans_srcfile} ${trans_infile}
        MAIN_DEPENDENCY ${trans_srcfile}
    )

    # Run the resource compiler (rcc_options should already be set)
    add_custom_command(
        OUTPUT ${trans_outfile}
        COMMAND "${Qt5Core_RCC_EXECUTABLE}"
        ARGS ${rcc_options} -name ${trans_file} -o ${trans_outfile} ${trans_infile}
        MAIN_DEPENDENCY ${trans_infile}
        DEPENDS ${QM_FILES}
    )
endmacro()

