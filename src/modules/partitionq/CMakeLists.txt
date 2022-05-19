# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
if( NOT WITH_QML )
    calamares_skip_module( "localeq (QML is not supported in this build)" )
    return()
endif()

# When debugging the timezone widget, add this debugging definition
# to have a debugging-friendly timezone widget, debug logging,
# and no intrusive timezone-setting while clicking around.
option( DEBUG_PARTITION_UNSAFE "Allow unsafe partitioning choices." OFF )
option( DEBUG_PARTITION_BAIL_OUT "Unsafe partitioning will error out on exec." ON )
option( DEBUG_PARTITION_SKIP "Don't actually do any partitioning." OFF)

include_directories( ${CMAKE_SOURCE_DIR} ) # for KPMCoreHelper

# This is very chatty, useful mostly if you don't know what KPMCore offers.
option( DEBUG_FILESYSTEMS      "Log all available Filesystems from KPMCore." OFF )

set( _partition_defs )
if( DEBUG_PARTITION_UNSAFE )
    if( DEBUG_PARTITION_BAIL_OUT )
        list( APPEND _partition_defs DEBUG_PARTITION_BAIL_OUT )
    endif()
    list( APPEND _partition_defs DEBUG_PARTITION_UNSAFE )
endif()
if ( DEBUG_FILESYSTEMS )
    list( APPEND _partition_defs DEBUG_FILESYSTEMS )
endif()
if( DEBUG_PARTITION_SKIP )
    list( APPEND _partition_defs DEBUG_PARTITION_SKIP )
endif()

find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

include( KPMcoreHelper )

find_package( KF5Config CONFIG )
find_package( KF5I18n CONFIG )

if ( KPMcore_FOUND AND Qt5DBus_FOUND AND KF5CoreAddons_FOUND AND KF5Config_FOUND )
    list( APPEND _partition_defs ${KPMcore_API_DEFINITIONS} )
    include_directories( ${KPMCORE_INCLUDE_DIR} )
    include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

    # Because we're sharing sources with the regular partition module
    set( _partition ${CMAKE_CURRENT_SOURCE_DIR}/../partition )
    # set( _partitionCore ${CMAKE_CURRENT_SOURCE_DIR}/../partition/core )
    # set( _partitionJobs ${CMAKE_CURRENT_SOURCE_DIR}/../partition/jobs )


    include_directories( ${_partition} )

    calamares_add_plugin( partitionq
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            PartitionQmlViewStep.cpp
            ChoicePageQml.cpp
            ${_partition}/Config.cpp
            ${_partition}/core/PartUtils.cpp
            ${_partition}/core/DeviceModel.cpp
            ${_partition}/core/PartitionInfo.cpp
            ${_partition}/core/PartitionCoreModule.cpp
            ${_partition}/core/BootLoaderModel.cpp
            ${_partition}/core/ColorUtils.cpp
            ${_partition}/core/DeviceList.cpp
            ${_partition}/core/KPMHelpers.cpp
            ${_partition}/core/PartitionActions.cpp
            ${_partition}/core/PartitionLayout.cpp
            ${_partition}/core/PartitionModel.cpp
            ${_partition}/jobs/AutoMountManagementJob.cpp
            ${_partition}/jobs/ChangeFilesystemLabelJob.cpp
            ${_partition}/jobs/ClearMountsJob.cpp
            ${_partition}/jobs/ClearTempMountsJob.cpp
            ${_partition}/jobs/CreatePartitionJob.cpp
            ${_partition}/jobs/CreatePartitionTableJob.cpp
            ${_partition}/jobs/CreateVolumeGroupJob.cpp
            ${_partition}/jobs/DeactivateVolumeGroupJob.cpp
            ${_partition}/jobs/DeletePartitionJob.cpp
            ${_partition}/jobs/FillGlobalStorageJob.cpp
            ${_partition}/jobs/FormatPartitionJob.cpp
            ${_partition}/jobs/PartitionJob.cpp
            ${_partition}/jobs/RemoveVolumeGroupJob.cpp
            ${_partition}/jobs/ResizePartitionJob.cpp
            ${_partition}/jobs/ResizeVolumeGroupJob.cpp
            ${_partition}/jobs/SetPartitionFlagsJob.cpp

        RESOURCES
            partitionq.qrc
        LINK_PRIVATE_LIBRARIES
            kpmcore
            KF5::CoreAddons
        COMPILE_DEFINITIONS ${_partition_defs}
        SHARED_LIB
    )

else()
    if ( NOT KPMcore_FOUND )
        calamares_skip_module( "partition (missing suitable KPMcore)" )
    else()
        calamares_skip_module( "partition (missing dependencies for KPMcore)" )
    endif()
endif()