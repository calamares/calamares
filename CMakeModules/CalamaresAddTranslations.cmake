include( CMakeParseArguments )

# Internal macro for adding the C++ / Qt translations to the
# build and install tree. Should be called only once, from
# src/calamares/CMakeLists.txt.
macro(add_calamares_translations language)
    list( APPEND CALAMARES_LANGUAGES ${ARGV} )

    set( calamares_i18n_qrc_content "<!DOCTYPE RCC><RCC version=\"1.0\">\n" )

    # calamares and qt language files
    set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}<qresource prefix=\"/lang\">\n" )
    foreach( lang ${CALAMARES_LANGUAGES} )
        set( calamares_i18n_qrc_content "${calamares_i18n_qrc_content}<file>calamares_${lang}.qm</file>\n" )
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

# Internal macro for Python translations
#
# Translations of the Python modules that don't have their own
# lang/ subdirectories -- these are collected in top-level
# lang/python/<lang>/LC_MESSAGES/python.mo
macro(add_calamares_python_translations language)
    set( CALAMARES_LANGUAGES "" )
    list( APPEND CALAMARES_LANGUAGES ${ARGV} )

    install_calamares_gettext_translations( python
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/lang/python
        FILENAME python.mo
        RENAME calamares-python.mo
    )
endmacro()

# Installs a directory containing language-code-labeled subdirectories with
# gettext data into the appropriate system directory. Allows renaming the
# .mo files during install to avoid namespace clashes.
#
# install_calamares_gettext_translations(
#   NAME <name of module, for human use>
#   SOURCE_DIR path/to/lang
#   FILENAME <name of file.mo>
#   [RENAME <new-name of.mo>]
# )
#
# For all of the (global) translation languages enabled for Calamares,
# try installing $SOURCE_DIR/$lang/LC_MESSAGES/<filename>.mo into the
# system gettext data directory (e.g. share/locale/), possibly renaming
# filename.mo to renamed.mo in the process.
function( install_calamares_gettext_translations )
    # parse arguments ( name needs to be saved before passing ARGN into the macro )
    set( NAME ${ARGV0} )
    set( oneValueArgs NAME SOURCE_DIR FILENAME RENAME )
    cmake_parse_arguments( TRANSLATION "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

    if( NOT TRANSLATION_NAME )
        set( TRANSLATION_NAME ${NAME} )
    endif()
    if( NOT TRANSLATION_FILENAME )
        set( TRANSLATION_FILENAME "${TRANSLATION_NAME}.mo" )
    endif()
    if( NOT TRANSLATION_RENAME )
        set( TRANSLATION_RENAME "${TRANSLATION_FILENAME}" )
    endif()

    message(STATUS "Installing gettext translations for ${TRANSLATION_NAME}")
    message(STATUS "  Installing ${TRANSLATION_FILENAME} from ${TRANSLATION_SOURCE_DIR}")

    set( TRANSLATION_NAME "${NAME}" )
    set( INSTALLED_TRANSLATIONS "" )
    foreach( lang ${CALAMARES_TRANSLATION_LANGUAGES} )  # Global
        set( lang_mo "${TRANSLATION_SOURCE_DIR}/${lang}/LC_MESSAGES/${TRANSLATION_FILENAME}" )
        if( lang STREQUAL "en" )
            message( STATUS "  Skipping ${TRANSLATION_NAME} translations for en_US" )
        else( EXISTS ${lang_mo} )
            list( APPEND INSTALLED_LANGUAGES "${lang}" )
            install(
                FILES ${lang_mo}
                DESTINATION ${CMAKE_INSTALL_LOCALEDIR}/${lang}/LC_MESSAGES/
                RENAME ${TRANSLATION_RENAME}
            )
            # TODO: make translations available in build dir too, for
            #       translation when running calamares -d from builddir.
            set(_build_lc ${CMAKE_BINARY_DIR}/lang/${lang}/LC_MESSAGES/)
            file(COPY ${lang_mo} DESTINATION ${_build_lc})
            if (NOT TRANSLATION_FILENAME STREQUAL TRANSLATION_RENAME)
                file(RENAME ${_build_lc}${TRANSLATION_FILENAME} ${_build_lc}${TRANSLATION_RENAME})
            endif()

        endif()
    endforeach()
endfunction()
