project( PartitionModule )

if( WITH_PARTITIONMANAGER )

add_subdirectory( partitionmanager/calamares )

## ECM
find_package(ECM 0.0.13 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})
include(KDEInstallDirs)
include(GenerateExportHeader)

find_package( KF5 REQUIRED CoreAddons )

add_definitions( -DCALAMARES )

add_subdirectory( tests )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( partition
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
        core/BootLoaderModel.cpp
        core/ColorUtils.cpp
        core/DeviceModel.cpp
        core/PartitionCoreModule.cpp
        core/PartitionInfo.cpp
        core/PartitionIterator.cpp
        core/PartitionModel.cpp
        core/PMUtils.cpp
        gui/ChoicePage.cpp
        gui/CreatePartitionDialog.cpp
        gui/EditExistingPartitionDialog.cpp
        gui/EraseDiskPage.cpp
        gui/PartitionPage.cpp
        gui/PartitionPreview.cpp
        gui/PartitionSizeController.cpp
        gui/PartitionViewStep.cpp
        gui/PrettyRadioButton.cpp
        jobs/CheckFileSystemJob.cpp
        jobs/CreatePartitionJob.cpp
        jobs/CreatePartitionTableJob.cpp
        jobs/DeletePartitionJob.cpp
        jobs/FillGlobalStorageJob.cpp
        jobs/FormatPartitionJob.cpp
        jobs/MoveFileSystemJob.cpp
        jobs/PartitionJob.cpp
        jobs/ResizePartitionJob.cpp
    UI
        gui/CreatePartitionDialog.ui
        gui/CreatePartitionTableDialog.ui
        gui/EditExistingPartitionDialog.ui
        gui/PartitionPage.ui
    LINK_LIBRARIES
        calapm
        calamaresui
        KF5::CoreAddons
    SHARED_LIB
)

endif( WITH_PARTITIONMANAGER )
