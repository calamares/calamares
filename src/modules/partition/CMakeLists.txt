find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

include(KDEInstallDirs)
include(GenerateExportHeader)
find_package( Qt5 REQUIRED DBus )
find_package( KF5 REQUIRED Config CoreAddons I18n WidgetsAddons )

find_package( KPMcore 3.3 )
set_package_properties(
    KPMcore PROPERTIES
    PURPOSE "For partitioning module"
)

if ( KPMcore_FOUND )
    if ( KPMcore_VERSION VERSION_GREATER "3.3.0")
        add_definitions(-DWITH_KPMCOREGT33) # kpmcore greater than 3.3
    endif()

    include_directories( ${KPMCORE_INCLUDE_DIR} )
    include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

    add_subdirectory( tests )

    calamares_add_plugin( partition
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        SOURCES
            core/BootLoaderModel.cpp
            core/ColorUtils.cpp
            core/DeviceList.cpp
            core/DeviceModel.cpp
            core/KPMHelpers.cpp
            core/PartitionActions.cpp
            core/PartitionCoreModule.cpp
            core/PartitionInfo.cpp
            core/PartitionIterator.cpp
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
            gui/PrettyRadioButton.cpp
            gui/ResizeVolumeGroupDialog.cpp
            gui/ScanningDialog.cpp
            gui/ReplaceWidget.cpp
            gui/VolumeGroupBaseDialog.cpp
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
        SHARED_LIB
    )
else()
    calamares_skip_module( "partition (missing suitable KPMcore)" )
endif()
