# Find PythonQt
#
# Sets PYTHONQT_FOUND, PYTHONQT_INCLUDE_DIR, PYTHONQT_LIBRARY, PYTHONQT_LIBRARIES
#

# Python is required
find_package(PythonLibs)
if(NOT PYTHONLIBS_FOUND)
  message(FATAL_ERROR "error: Python is required to build PythonQt")
endif()

if(NOT EXISTS "${PYTHONQT_INSTALL_DIR}")
  find_path(PYTHONQT_INSTALL_DIR include/PythonQt/PythonQt.h DOC "Directory where PythonQt was installed.")
endif()
# XXX Since PythonQt 3.0 is not yet cmakeified, depending
#     on how PythonQt is built, headers will not always be
#     installed in "include/PythonQt". That is why "src"
#     is added as an option. See [1] for more details.
#     [1] https://github.com/commontk/CTK/pull/538#issuecomment-86106367
find_path(PYTHONQT_INCLUDE_DIR PythonQt.h
  PATHS "${PYTHONQT_INSTALL_DIR}/include/PythonQt"
        "${PYTHONQT_INSTALL_DIR}/src"
  DOC "Path to the PythonQt include directory")

# Minimum v3.1 is needed
find_library(PYTHONQT_LIBRARY_RELEASE PythonQt PATHS "${PYTHONQT_INSTALL_DIR}/lib" DOC "The PythonQt library.")
find_library(PYTHONQT_LIBRARY_DEBUG NAMES PythonQt${CTK_CMAKE_DEBUG_POSTFIX} PythonQt${CMAKE_DEBUG_POSTFIX} PythonQt PATHS "${PYTHONQT_INSTALL_DIR}/lib" DOC "The PythonQt library.")
find_library(PYTHONQT_QTALL_LIBRARY_RELEASE PythonQt_QtAll PATHS "${PYTHONQT_INSTALL_DIR}/lib" DOC "Full Qt bindings for the PythonQt library.")
find_library(PYTHONQT_QTALL_LIBRARY_DEBUG NAMES PythonQt_QtAll${CTK_CMAKE_DEBUG_POSTFIX} PythonQt_QtAll${CMAKE_DEBUG_POSTFIX} PythonQt_QtAll PATHS "${PYTHONQT_INSTALL_DIR}/lib" DOC "Full Qt bindings for the PythonQt library.")

# Also check for v3.2+
find_library(PYTHONQT_LIBRARY_RELEASE PythonQt-Qt5-Python3 PATHS "${PYTHONQT_INSTALL_DIR}/lib" DOC "The PythonQt library.")
find_library(PYTHONQT_LIBRARY_DEBUG NAMES PythonQt-Qt5-Python3${CTK_CMAKE_DEBUG_POSTFIX} PythonQt-Qt5-Python3${CMAKE_DEBUG_POSTFIX} PythonQt-Qt5-Python3 PATHS "${PYTHONQT_INSTALL_DIR}/lib" DOC "The PythonQt library.")
find_library(PYTHONQT_QTALL_LIBRARY_RELEASE PythonQt_QtAll-Qt5-Python3 PATHS "${PYTHONQT_INSTALL_DIR}/lib" DOC "Full Qt bindings for the PythonQt library.")
find_library(PYTHONQT_QTALL_LIBRARY_DEBUG NAMES PythonQt_QtAll-Qt5-Python3${CTK_CMAKE_DEBUG_POSTFIX} PythonQt_QtAll-Qt5-Python3${CMAKE_DEBUG_POSTFIX} PythonQt_QtAll-Qt5-Python3 PATHS "${PYTHONQT_INSTALL_DIR}/lib" DOC "Full Qt bindings for the PythonQt library.")

set(PYTHONQT_LIBRARY)
if(PYTHONQT_LIBRARY_RELEASE)
  list(APPEND PYTHONQT_LIBRARY optimized ${PYTHONQT_LIBRARY_RELEASE})
endif()
if(PYTHONQT_LIBRARY_DEBUG)
  list(APPEND PYTHONQT_LIBRARY debug ${PYTHONQT_LIBRARY_DEBUG})
endif()

set(PYTHONQT_QTALL_LIBRARY)
if(PYTHONQT_QTALL_LIBRARY_RELEASE)
  list(APPEND PYTHONQT_QTALL_LIBRARY optimized ${PYTHONQT_QTALL_LIBRARY_RELEASE})
endif()
if(PYTHONQT_QTALL_LIBRARY_DEBUG)
  list(APPEND PYTHONQT_QTALL_LIBRARY debug ${PYTHONQT_QTALL_LIBRARY_DEBUG})
endif()

mark_as_advanced(PYTHONQT_INSTALL_DIR)
mark_as_advanced(PYTHONQT_INCLUDE_DIR)
mark_as_advanced(PYTHONQT_LIBRARY_RELEASE)
mark_as_advanced(PYTHONQT_LIBRARY_DEBUG)
mark_as_advanced(PYTHONQT_QTALL_LIBRARY_RELEASE)
mark_as_advanced(PYTHONQT_QTALL_LIBRARY_DEBUG)

# On linux, also find libutil
if(UNIX AND NOT APPLE)
  find_library(PYTHONQT_LIBUTIL util)
  mark_as_advanced(PYTHONQT_LIBUTIL)
endif()

# All upper case _FOUND variable is maintained for backwards compatibility.
set(PYTHONQT_FOUND 0)
set(PythonQt_FOUND 0)

if(PYTHONQT_INCLUDE_DIR AND PYTHONQT_LIBRARY AND PYTHONQT_QTALL_LIBRARY)
  # Currently CMake'ified PythonQt only supports building against a python Release build.
  # This applies independently of CTK build type (Release, Debug, ...)
  add_definitions(-DPYTHONQT_USE_RELEASE_PYTHON_FALLBACK)
  set(PYTHONQT_FOUND 1)
  set(PythonQt_FOUND ${PYTHONQT_FOUND})
  set(PYTHONQT_LIBRARIES ${PYTHONQT_LIBRARY} ${PYTHONQT_LIBUTIL} ${PYTHONQT_QTALL_LIBRARY})
endif()
