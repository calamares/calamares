#   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
# Note that Calamares itself is GPL-3.0-or-later: the above license
# applies to **this** CMake file.
#
# Config file for the Calamares package
#
# The following IMPORTED targets are defined:
#   - Calamares::calamares      - the core library
#   - Calamares::calamaresui    - the UI (and QML) library
#
# For legacy use it defines the following variables:
#   - Calamares_INCLUDE_DIRS    - include directories for Calamares
#   - Calamares_LIB_DIRS        - library directories
#   - Calamares_LIBRARIES       - libraries to link against


####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was CalamaresConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

# Use original install prefix when loaded through a "/usr move"
# cross-prefix symbolic link such as /lib -> /usr/lib.
get_filename_component(_realCurr "${CMAKE_CURRENT_LIST_DIR}" REALPATH)
get_filename_component(_realOrig "/usr/lib/cmake/Calamares" REALPATH)
if(_realCurr STREQUAL _realOrig)
  set(PACKAGE_PREFIX_DIR "/usr")
endif()
unset(_realOrig)
unset(_realCurr)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

### Versioning and IMPORTED targets
#
#
include(${CMAKE_CURRENT_LIST_DIR}/CalamaresConfigVersion.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/CalamaresTargets.cmake)
if (NOT TARGET Calamares::calamares OR NOT TARGET Calamares::calamaresui)
    message(FATAL_ERROR "Calamares found with missing CMake targets")
endif()

# Need various CMake files that are installed alongside this one.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

### Dependencies
#
# The libraries can depend on a variety of Qt and KDE Frameworks
# components, so accumulate them and find (just once).
#
macro(accumulate_deps outvar target namespace)
    string(LENGTH ${namespace} _nslen)
    get_target_property(_libs ${target} INTERFACE_LINK_LIBRARIES)
    foreach(_lib ${_libs})
        if (_lib MATCHES ^${namespace})
            string(SUBSTRING ${_lib} ${_nslen} -1 _component)
            list(APPEND ${outvar} ${_component})
        endif()
    endforeach()
endmacro()

# Qt5 infrastructure for translations is required
set(qt5_required Core Widgets LinguistTools)
accumulate_deps(qt5_required Calamares::calamares Qt5::)
accumulate_deps(qt5_required Calamares::calamaresui Qt5::)
find_package(Qt5 CONFIG REQUIRED ${qt5_required})

set(kf5_required "")
accumulate_deps(kf5_required Calamares::calamares KF5::)
accumulate_deps(kf5_required Calamares::calamaresui KF5::)
if(kf5_required)
    find_package(ECM ${ECM_VERSION} NO_MODULE)
    if( ECM_FOUND )
        list(INSERT CMAKE_MODULE_PATH 0 ${ECM_MODULE_PATH})
        find_package(KF5 REQUIRED COMPONENTS ${kf5_required})
    endif()
endif()

find_package(YAMLCPP REQUIRED)

### Legacy support
#
#
set(Calamares_LIB_DIRS "${PACKAGE_PREFIX_DIR}/lib")
set(Calamares_INCLUDE_DIRS "${PACKAGE_PREFIX_DIR}/include")
set(Calamares_LIBRARIES Calamares::calamares)

### CMake support
#
#
include(CalamaresAddBrandingSubdirectory)
include(CalamaresAddLibrary)
include(CalamaresAddModuleSubdirectory)
include(CalamaresAddPlugin)

# These are feature-settings that affect consumers of Calamares
# libraries as well; without Python-support in the libs, for instance,
# there's no point in having a Python plugin.
#
# This list should match the one in libcalamares/CalamaresConfig.h,
# which is the C++-language side of the same configuration.
set(Calamares_WITH_PYTHON ON)
set(Calamares_WITH_PYTHONQT OFF)
set(Calamares_WITH_QML ON)
