# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2023 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# This is a very-stripped-down way of getting the bundled pybind11

add_library(pybind11_headers INTERFACE)
add_library(pybind11::headers ALIAS pybind11_headers)

target_include_directories(pybind11_headers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pybind11_headers INTERFACE Python::Python) # Was searched-for at top-level


