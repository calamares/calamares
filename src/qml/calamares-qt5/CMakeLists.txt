# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# Install "slideshows" and other QML-sources for Calamares.
#
# In practice, in the central source repositoy, this means
# just-install-the-slideshow-example. For alternative slideshows,
# see the approach in the calamares-extensions repository.

# Iterate over all the subdirectories which have a qmldir file, copy them over to the build dir,
# and install them into share/calamares/qml/calamares
file(GLOB SUBDIRECTORIES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*")
foreach(SUBDIRECTORY ${SUBDIRECTORIES})
    if(
        IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}"
        AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/qmldir"
    )
        set(QML_DIR share/calamares/qml)
        set(QML_MODULE_DESTINATION ${QML_DIR}/calamares/${SUBDIRECTORY})

        # We glob all the files inside the subdirectory, and we make sure they are
        # synced with the bindir structure and installed.
        file(GLOB QML_MODULE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY} "${SUBDIRECTORY}/*")
        foreach(QML_MODULE_FILE ${QML_MODULE_FILES})
            if(NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${SUBDIRECTORY}/${QML_MODULE_FILE})
                configure_file(${SUBDIRECTORY}/${QML_MODULE_FILE} ${SUBDIRECTORY}/${QML_MODULE_FILE} COPYONLY)

                install(
                    FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBDIRECTORY}/${QML_MODULE_FILE}
                    DESTINATION ${QML_MODULE_DESTINATION}
                )
            endif()
        endforeach()

        message("-- ${BoldYellow}Configured QML module: ${BoldRed}calamares.${SUBDIRECTORY}${ColorReset}")
    endif()
endforeach()

message("")
