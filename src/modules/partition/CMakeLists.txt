# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#

# When debugging the partitioning widget, or experimenting, you may
# want to allow unsafe partitioning choices (e.g. doing things to the
# current disk). Set DEBUG_PARTITION_UNSAFE to allow that (it turns off
# some filtering of devices). If you **do** allow unsafe partitioning,
# it will error out unless you **also** switch **off** DEBUG_PARTITION_LAME,
# at which point you are welcome to shoot yourself in the foot.
option( DEBUG_PARTITION_UNSAFE "Allow unsafe partitioning choices." OFF )
option( DEBUG_PARTITION_LAME   "Unsafe partitioning will error out on exec." ON )

# This is very chatty, useful mostly if you don't know what KPMCore offers.
option( DEBUG_FILESYSTEMS      "Log all available Filesystems from KPMCore." OFF )

include_directories( ${CMAKE_SOURCE_DIR} )  # For 3rdparty

set( _partition_defs )
if( DEBUG_PARTITION_UNSAFE )
    if( DEBUG_PARTITION_LAME )
        list( APPEND _partition_defs DEBUG_PARTITION_LAME )
    endif()
    list( APPEND _partition_defs DEBUG_PARTITION_UNSAFE )
endif()
if ( DEBUG_FILESYSTEMS )
    list( APPEND _partition_defs DEBUG_FILESYSTEMS )
endif()

find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

include( KPMcoreHelper )

find_package( KF5Config CONFIG )
find_package( KF5I18n CONFIG )
find_package( KF5WidgetsAddons CONFIG )

if ( KPMcore_FOUND AND Qt5DBus_FOUND AND KF5CoreAddons_FOUND AND KF5Config_FOUND )
    list( APPEND _partition_defs ${KPMcore_API_DEFINITIONS} )
    include_directories( ${KPMCORE_INCLUDE_DIR} )
    include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

    add_subdirectory( tests )

    calamares_add_plugin( partition
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            core/BootLoaderModel.cpp
            core/ColorUtils.cpp
            core/Config.cpp
            core/DeviceList.cpp
            core/DeviceModel.cpp
            core/KPMHelpers.cpp
            core/PartitionActions.cpp
            core/PartitionCoreModule.cpp
            core/PartitionInfo.cpp
            core/PartitionLayout.cpp
            core/PartitionModel.cpp
            core/PartUtils.cpp
            gui/BootInfoWidget.cpp
            gui/ChoicePage.cpp
            gui/CreatePartitionDialog.cpp
            gui/CreateVolumeGroupDialog.cpp
            gui/DeviceInfoWidget.cpp
            gui/EditExistingPartitionDialog.cpp
            gui/EncryptWidget.cpp
            gui/ListPhysicalVolumeWidgetItem.cpp
            gui/PartitionPage.cpp
            gui/PartitionBarsView.cpp
            gui/PartitionDialogHelpers.cpp
            gui/PartitionLabelsView.cpp
            gui/PartitionSizeController.cpp
            gui/PartitionSplitterWidget.cpp
            gui/PartitionViewStep.cpp
            gui/ResizeVolumeGroupDialog.cpp
            gui/ScanningDialog.cpp
            gui/ReplaceWidget.cpp
            gui/VolumeGroupBaseDialog.cpp
            jobs/AutoMountManagementJob.cpp
            jobs/ClearMountsJob.cpp
            jobs/ClearTempMountsJob.cpp
            jobs/CreatePartitionJob.cpp
            jobs/CreatePartitionTableJob.cpp
            jobs/CreateVolumeGroupJob.cpp
            jobs/DeactivateVolumeGroupJob.cpp
            jobs/DeletePartitionJob.cpp
            jobs/FillGlobalStorageJob.cpp
            jobs/FormatPartitionJob.cpp
            jobs/PartitionJob.cpp
            jobs/RemoveVolumeGroupJob.cpp
            jobs/ResizePartitionJob.cpp
            jobs/ResizeVolumeGroupJob.cpp
            jobs/SetPartitionFlagsJob.cpp
        UI
            gui/ChoicePage.ui
            gui/CreatePartitionDialog.ui
            gui/CreatePartitionTableDialog.ui
            gui/EditExistingPartitionDialog.ui
            gui/EncryptWidget.ui
            gui/PartitionPage.ui
            gui/ReplaceWidget.ui
            gui/VolumeGroupBaseDialog.ui
        LINK_PRIVATE_LIBRARIES
            kpmcore
            calamaresui
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
