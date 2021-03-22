# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
#   Calamares is Free Software: see the License-Identifier above.
#
###
#
# This module implements the "skip modules" part of configuring
# the Calamares repository or an external-modules repository.
#
# It should not be necessary to include() this module explicitly,
# since both AddPlugin and AddModuleSubdirectory do so implicitly.
#
#
# # Usage
#
# The public API is two functions:
#
# - calamares_skip_module(reason)
#   A C++ module (or any that uses CMake) can call this macro to
#   add *reason* to the list of skipped modules. Typically a module
#   will pass in "modulename (why)" so that it is clear **which**
#   module is skipped. This macro should be called at the top-level
#   of a module's CMakeLists.txt and the module should then **not**
#   call calamares_add_plugin().
# - calamares_explain_skipped_modules(list...)
#   This will print out all the module reasons (see above) that have
#   been added to the given *listvar*. When AddModuleSubdirectory is
#   used as the mechanism to add all the subdirectories in the repository
#   that contain modules, with a consistent *listvar* setting,
#   this will show all the modules that have been skipped.
#
# The internal API is one function:
#
# - calamares_check_skip(modulename outvar)
#   Checks if the *modulename* has been listed in the global SKIP_MODULES
#   variable (to skip specifically-named modules) or if there is a USE_*
#   setting applicable to the module. If the module is skipped for this
#   reason, a suitable entry is added to *outvar* as if
#   calamares_skip_module() had been called.
#
# Best practice is to pick a variable to collect all of the skipped
# modules, and to pass the name of that variable to AddModuleSubdirectory
# in each call. After all subdirectories have been added, call
# calamares_explain_skipped_modules() with the value of that variable.


# Convenience function to indicate that a module has been skipped
# (optionally also why). Call this in the module's CMakeLists.txt
macro( calamares_skip_module )
    set( SKIPPED_MODULES ${SKIPPED_MODULES} ${ARGV} PARENT_SCOPE )
endmacro()

function( calamares_explain_skipped_modules )
    if ( ARGN )
        message( "${ColorReset}-- Skipped modules:" )
        foreach( SUBDIRECTORY ${ARGN} )
            message( "${ColorReset}--   Skipped ${BoldRed}${SUBDIRECTORY}${ColorReset}." )
        endforeach()
        message( "" )
    endif()
endfunction()

# Globally, SKIP_MODULES and USE_* affect what modules are built.
# Check if *modulename* should be skipped, and if so, set *outvar* to
# a human-readable reason for skipping it.
function( _calamares_check_skip_impl modulename outvar )
    # Globally-defined SKIP_MODULES may be space- or semicolon- separated
    # so convert it to a list-variable.
    string( REPLACE " " ";" SKIP_LIST "${SKIP_MODULES}" )

    list( FIND SKIP_LIST "${modulename}" DO_SKIP )
    if( NOT DO_SKIP EQUAL -1 )
        set( ${outvar} "user request" PARENT_SCOPE )
        return()
    endif()

    # Not skipped by the global check, see if it has an applicable USE_*
    if( "${modulename}" MATCHES "^[a-zA-Z0-9_]+-" )
        # Split the name into <category>-<implementation>
        string( REGEX REPLACE "-.*" "" _category "${modulename}" )
        string( REGEX REPLACE "^[^-]+-" "" _implementation "${modulename}" )
    else()
        # Not a module to which USE_* applies
        return()
    endif()

    if( "${USE_${_category}}" STREQUAL "none" )
        set( ${outvar} "category ${_category} disabled" PARENT_SCOPE )
        return()
    elseif( "${USE_${_category}}" STREQUAL "" )
        # Category not set at all or nonexistent
        return()
    endif()

    if ( "${USE_${_category}}" STREQUAL "${_implementation}" )
        # Matches, so accept this module
    else()
        set( ${outvar} "category ${_category} selects ${USE_${_category}}" PARENT_SCOPE )
    endif()
endfunction()

# This is the public API;it calls the _impl version so that there
# is an extra intermediate scope for the subdirectory to write results into.
function( calamares_check_skip modulename outvar )
    set( _skip "" )
    _calamares_check_skip_impl( "${modulename}" _skip )
    if ( _skip )
        message( "${ColorReset}-- Skipping module ${BoldRed}${modulename} (${_skip})${ColorReset}." )
        message( "" )
        set( ${outvar} "${modulename} (${_skip})" PARENT_SCOPE )
    endif()
endfunction()
