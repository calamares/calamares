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
# find_boost_python3() tries to find the package with different component
# names. By default it tries "python3", "python-py$suffix" and
# "python-$dotsuffix", where suffix is based on the `python_version` argument.
# One can supply a custom component name by setting the
# `CALAMARES_BOOST_PYTHON3_COMPONENT` variable at CMake time.

set( CALAMARES_BOOST_PYTHON3_COMPONENT python3 CACHE STRING
    "Name of the Boost.Python component. If Boost.Python is installed as
    libboost_python-foo.so then this variable should be set to 'python-foo'."
)

macro( find_boost_python3 boost_version python_version found_var )
    set( ${found_var} OFF )

    # turns "3.4.123abc" into "34"
    string( REGEX REPLACE "([0-9]+)\\.([0-9]+)\\..*" "\\1\\2" _fbp_python_short_version ${python_version} )

    foreach( _fbp_name ${CALAMARES_BOOST_PYTHON3_COMPONENT} python-py${_fbp_python_short_version} )
        find_package( Boost ${boost_version} QUIET COMPONENTS ${_fbp_name} )
        string( TOUPPER ${_fbp_name} _fbp_uc_name )
        if( Boost_${_fbp_uc_name}_FOUND )
            set( ${found_var} ON )
            break()
        endif()
    endforeach()

    if (NOT ${found_var})
        # The following loop changes the searched name for Gentoo based distributions
        # turns "3.4.123abc" into "3.4"
        string( REGEX REPLACE "([0-9]+)\\.([0-9]+)\\..*" "\\1.\\2" _fbp_python_short_version ${python_version} )
        foreach( _fbp_name ${CALAMARES_BOOST_PYTHON3_COMPONENT} python-${_fbp_python_short_version} )
            find_package( Boost ${boost_version} QUIET COMPONENTS ${_fbp_name} )
            string( TOUPPER ${_fbp_name} _fbp_uc_name )
            if( Boost_${_fbp_uc_name}_FOUND )
                set( ${found_var} ON )
                break()
            endif()
        endforeach()
    endif()
endmacro()
