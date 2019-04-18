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
#   SPDX-License-Identifier: GPL-3.0+
#   License-Filename: LICENSE
#
###
#
# Helper function for doing automoc on a target.
#
# Sets AUTOMOC TRUE for a target.
#
# If the global variable CALAMARES_AUTOMOC_OPTIONS is set, uses that
# as well to set options passed to MOC. This can be used to add
# libcalamares/utils/moc-warnings.h file to the moc, which in turn
# reduces compiler warnings in generated MOC code.
#

function(calamares_automoc TARGET)
    set_target_properties( ${TARGET} PROPERTIES AUTOMOC TRUE )
    if ( CALAMARES_AUTOMOC_OPTIONS )
        set_target_properties( ${TARGET} PROPERTIES AUTOMOC_MOC_OPTIONS "${CALAMARES_AUTOMOC_OPTIONS}" )
    endif()
endfunction()
