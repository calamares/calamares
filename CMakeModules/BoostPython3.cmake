# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2014 Aurélien Gâteau <agateau@kde.org>
#   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
#   SPDX-FileCopyrightText: 2019 Kevin Kofler <kevin.kofler@chello.at>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# Handles the mess that Boost::Python is before CMake 3.16 and
# Boost 1.70 or so.
#
###
#
# On Ubuntu 14.04, the libboost-python1.54-dev package comes with one library
# for each Python version:
# libboost_python-py27.so
# libboost_python-py33.so
# libboost_python-py34.so
#
# Boost upstream however installs Boost.Python3 libboost_python3.so, which is
# what FindBoost.cmake is looking for. It looks for a library named
# "libboost_${component}.so".
#
# On Gentoo instead, the >=dev-libs/boost-1.54 package provides boost library
# with a name like:
# libboost_python-2.7.so
# libboost_python-3.3.so
# libboost_python-3.4.so
# depending on what python's targets you selected during install
#
# On Fedora >= 30 instead, the boost-python3-devel provides boost library with a
# name like:
# libboost_python37.so
# depending on what python's targets you selected during install
#
# find_boost_python3() tries to find the package with different component
# names. By default it tries "python3", "python-py$suffix" and
# "python-$dotsuffix", where suffix is based on the `python_version` argument.
# One can supply a custom component name by setting the
# `CALAMARES_BOOST_PYTHON3_COMPONENT` variable at CMake time.
set( CALAMARES_BOOST_PYTHON3_COMPONENT python3 CACHE STRING
    "Name of the Boost.Python component. If Boost.Python is installed as
    libboost_python-foo.so then this variable should be set to 'python-foo'."
)

include(FindPackageHandleStandardArgs)

macro( _find_boost_python3_int boost_version componentname found_var )
    foreach( _fbp_name ${CALAMARES_BOOST_PYTHON3_COMPONENT} ${componentname} )
        find_package( Boost ${boost_version} QUIET COMPONENTS ${_fbp_name} )
        string( TOUPPER ${_fbp_name} _fbp_uc_name )
        if( Boost_${_fbp_uc_name}_FOUND )
            if( CMAKE_SYSTEM_NAME MATCHES "FreeBSD" )
                # No upcasing
                set( ${found_var} ${_fbp_name} )
            else()
                set( ${found_var} ${_fbp_uc_name} )
            endif()
            break()
        endif()
    endforeach()
endmacro()

macro( find_boost_python3 boost_version python_version found_var )
    set( ${found_var} OFF )
    set( _fbp_found OFF )

    # turns "3.4.123abc" into "34"
    string( REGEX REPLACE "([0-9]+)\\.([0-9]+)\\..*" "\\1\\2" _fbp_python_short_version ${python_version} )
    _find_boost_python3_int( ${boost_version} python-py${_fbp_python_short_version} _fbp_found )

    if (NOT _fbp_found)
        _find_boost_python3_int( ${boost_version} python${_fbp_python_short_version} _fbp_found )
    endif()

    if (NOT _fbp_found)
        # The following loop changes the searched name for Gentoo based distributions
        # turns "3.4.123abc" into "3.4"
        string( REGEX REPLACE "([0-9]+)\\.([0-9]+)\\..*" "\\1.\\2" _fbp_python_short_version ${python_version} )
        _find_boost_python3_int( ${boost_version} python-${_fbp_python_short_version} _fbp_found )
    endif()

    set( ${found_var} ${_fbp_found} )

    # This is superfluous, but allows proper reporting in the features list
    if ( _fbp_found )
        find_package( Boost ${boost_version} COMPONENTS ${_fbp_found} )
    else()
        find_package( Boost ${boost_version} COMPONENTS Python )
    endif()
    set_package_properties(
        Boost PROPERTIES
        DESCRIPTION "A C++ library which enables seamless interoperability between C++ and Python 3."
        URL "http://www.boost.org"
    )
endmacro()
