# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2014 Kevin Kofler <kevin.kofler@chello.at>
#   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# Defines a handful of strings that, with normal xterm handling,
# will change colors in the output, so it's nicer to read.
if(NOT WIN32)
  set(_use_color ON)
  if("0" STREQUAL "$ENV{CLICOLOR}")
    set(_use_color OFF)
  endif()
  if("0" STREQUAL "$ENV{CLICOLOR_FORCE}")
    set(_use_color OFF)
  endif()
  if(NOT CMAKE_COLOR_MAKEFILE)
    set(_use_color OFF)
  endif()

  if(_use_color)
    string(ASCII 27 Esc)
    set(ColorReset  "${Esc}[m")
    set(ColorBold   "${Esc}[1m")
    set(Red         "${Esc}[31m")
    set(Green       "${Esc}[32m")
    set(Yellow      "${Esc}[33m")
    set(Blue        "${Esc}[34m")
    set(Magenta     "${Esc}[35m")
    set(Cyan        "${Esc}[36m")
    set(White       "${Esc}[37m")
    set(BoldRed     "${Esc}[1;31m")
    set(BoldGreen   "${Esc}[1;32m")
    set(BoldYellow  "${Esc}[1;33m")
    set(BoldBlue    "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan    "${Esc}[1;36m")
    set(BoldWhite   "${Esc}[1;37m")
  endif()
endif()
