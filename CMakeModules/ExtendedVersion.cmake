# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# This file defines one function for extending a VERSION-like value
# with date and git information (if desired).
#
# - extend_version( version-string short_only short_var long_var )
#   Calling this function will copy *version-string* (which would typically
#   be a semver-style string, like "3.2.40") into the variable *short_var*.
#   If *short_only* is true, then:
#       - the short version is also copied into the variable *long_var*,
#   If *short_only* is false, then:
#       - the *version-string* plus date and git information, is copied
#         into the varialbe *long_var*, in the format {version}-{date}-{hash}
#
#

function( get_git_version_info out_var )
    set(CMAKE_VERSION_SOURCE "")
    if(EXISTS ${CMAKE_SOURCE_DIR}/.git/HEAD)
        find_program(GIT_EXECUTABLE NAMES git git.cmd)
        mark_as_advanced(GIT_EXECUTABLE)
        if(GIT_EXECUTABLE)
            execute_process(
                COMMAND ${GIT_EXECUTABLE} rev-parse --verify -q --short=8 HEAD
                OUTPUT_VARIABLE head
                OUTPUT_STRIP_TRAILING_WHITESPACE
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            )
            if(head)
                set(CMAKE_VERSION_SOURCE "${head}")
                execute_process(
                    COMMAND ${GIT_EXECUTABLE} update-index -q --refresh
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                )
                execute_process(
                    COMMAND ${GIT_EXECUTABLE} diff-index --name-only HEAD --
                    OUTPUT_VARIABLE dirty
                    OUTPUT_STRIP_TRAILING_WHITESPACE
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                )
                if(dirty)
                    set(CMAKE_VERSION_SOURCE "${CMAKE_VERSION_SOURCE}-dirty")
                endif()
            endif()
        endif()
    endif()
    set( ${out_var} "${CMAKE_VERSION_SOURCE}" PARENT_SCOPE )
endfunction()

function( extend_version version short_only short_var long_var )
    set( ${short_var} "${version}" PARENT_SCOPE )
    set( _v "${version}" )
    if ( NOT short_only )
        # Additional info for non-release builds which want "long" version info
        # with date and git information (commit, dirty status). That is used only
        # by CalamaresVersionX.h, which is included by consumers that need a full
        # version number with all that information; normal consumers can include
        # CalamaresVersion.h with more stable numbers.
        string( TIMESTAMP CALAMARES_VERSION_DATE "%Y%m%d" )
        if( CALAMARES_VERSION_DATE GREATER 0 )
            set( _v ${_v}.${CALAMARES_VERSION_DATE} )
        endif()
        get_git_version_info( _gitv )
        if( _gitv )
            set( _v "${_v}-${_gitv}" )
        endif()
    endif()
    set( ${long_var} "${_v}" PARENT_SCOPE )
endfunction()
