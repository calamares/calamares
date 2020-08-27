# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###

include( CalamaresAddTranslations )

find_package(Qt5 COMPONENTS Xml)
if( Qt5Xml_FOUND )
    add_executable(txload txload.cpp)
    target_link_libraries(txload Qt5::Xml)
endif()

install_calamares_gettext_translations( python
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/lang/python
    FILENAME python.mo
    RENAME calamares-python.mo
)
