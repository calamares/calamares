#FIXME: this duplicates top level cmakelists: how can we reduce code duplication?

find_package( Qt5 5.3.0 CONFIG REQUIRED Core Gui Widgets LinguistTools )

if(NOT CALAMARES_CMAKE_DIR)
    set(CALAMARES_CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

include( "${CALAMARES_CMAKE_DIR}/CalamaresAddLibrary.cmake" )
include( "${CALAMARES_CMAKE_DIR}/CalamaresAddModuleSubdirectory.cmake" )
include( "${CALAMARES_CMAKE_DIR}/CalamaresAddPlugin.cmake" )
include( "${CALAMARES_CMAKE_DIR}/CalamaresAddBrandingSubdirectory.cmake" )
