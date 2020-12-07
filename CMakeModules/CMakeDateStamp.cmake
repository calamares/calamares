# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# Find today's date, for versioning purposes.
find_program(DATE_EXECUTABLE NAMES date)
mark_as_advanced(DATE_EXECUTABLE)

if(DATE_EXECUTABLE)
  execute_process(
    COMMAND ${DATE_EXECUTABLE} +%Y
    OUTPUT_VARIABLE CMAKE_DATESTAMP_YEAR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
  execute_process(
    COMMAND ${DATE_EXECUTABLE} +%m
    OUTPUT_VARIABLE CMAKE_DATESTAMP_MONTH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
  execute_process(
    COMMAND ${DATE_EXECUTABLE} +%d
    OUTPUT_VARIABLE CMAKE_DATESTAMP_DAY
    OUTPUT_STRIP_TRAILING_WHITESPACE
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  )
endif()
