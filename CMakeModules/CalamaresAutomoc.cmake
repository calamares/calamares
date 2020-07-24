# === This file is part of Calamares - <https://github.com/calamares> ===
#
#   Calamares is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   Calamares is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
#
#   SPDX-License-Identifier: GPL-3.0-or-later
#   License-Filename: LICENSE
#
###
#
# Helper function for doing automoc, autouic, autorcc on targets,
# and on the corresponding .ui or .rcc files.
#
# calamares_automoc(target)
#   Sets AUTOMOC TRUE for a target.
#
#   If the global variable CALAMARES_AUTOMOC_OPTIONS is set, uses that
#   as well to set options passed to MOC. This can be used to add
#   libcalamares/utils/moc-warnings.h file to the moc, which in turn
#   reduces compiler warnings in generated MOC code.
#
# calamares_autouic(target [uifile ..])
#   Sets AUTOUIC TRUE for a target.
#
#   If the global variable CALAMARES_AUTOUIC_OPTIONS is set, adds that
#   to the options passed to uic for each of the named uifiles.
#
# calamares_autorcc(target [rcfile ..])
#   Sets AUTOUIC TRUE for a target.
#
#   If the global variable CALAMARES_AUTORCC_OPTIONS is set, adds that
#   to the options passed to rcc for each of the named rcfiles.

function(calamares_automoc TARGET)
    set_target_properties( ${TARGET} PROPERTIES AUTOMOC TRUE )
    if ( CALAMARES_AUTOMOC_OPTIONS )
        set_target_properties( ${TARGET} PROPERTIES AUTOMOC_MOC_OPTIONS "${CALAMARES_AUTOMOC_OPTIONS}" )
    endif()
endfunction()

function(calamares_autouic TARGET)
    set_target_properties( ${TARGET} PROPERTIES AUTOUIC TRUE )
    if ( CALAMARES_AUTOUIC_OPTIONS )
        foreach(S ${ARGN})
            set_property(SOURCE ${S} PROPERTY AUTOUIC_OPTIONS "${CALAMARES_AUTOUIC_OPTIONS}")
        endforeach()
    endif()
endfunction()

function(calamares_autorcc TARGET)
    set_target_properties( ${TARGET} PROPERTIES AUTORCC TRUE )
    if ( CALAMARES_AUTORCC_OPTIONS )
        foreach(S ${ARGN})
            set_property(SOURCE ${S} PROPERTY AUTORCC_OPTIONS "${CALAMARES_AUTORCC_OPTIONS}")
        endforeach()
    endif()
endfunction()
