# Shared CMake core for finding KPMCore
#
# This is wrapped into a CMake include file because there's a bunch of
# pre-requisites that need searching for before looking for KPMCore.
# If you just do find_package( KPMCore ) without finding the things
# it links against first, you get CMake errors.
#
#
find_package(ECM 5.10.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})

include(KDEInstallDirs)
include(GenerateExportHeader)
find_package( KF5 REQUIRED CoreAddons )
find_package( KF5 REQUIRED Config I18n IconThemes KIO Service )

find_package( KPMcore 3.0.3 REQUIRED )
