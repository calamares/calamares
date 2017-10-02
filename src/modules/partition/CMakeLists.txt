find_package(ECM 5.10.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})

include(KDEInstallDirs)
include(GenerateExportHeader)
find_package( KF5 REQUIRED CoreAddons )

# These are needed because KPMcore links publicly against ConfigCore, I18n, WidgetsAddons and Service
find_package( Qt5 REQUIRED DBus )
find_package( KF5 REQUIRED Config I18n WidgetsAddons Service )

find_package( KPMcore 3.2 REQUIRED )

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
        gui/DeviceInfoWidget.cpp
        gui/EditExistingPartitionDialog.cpp
        gui/EncryptWidget.cpp
        gui/PartitionPage.cpp
        gui/PartitionBarsView.cpp
        gui/PartitionLabelsView.cpp
        gui/PartitionSizeController.cpp
        gui/PartitionSplitterWidget.cpp
        gui/PartitionViewStep.cpp
        gui/PrettyRadioButton.cpp
        gui/ScanningDialog.cpp
        gui/ReplaceWidget.cpp
        jobs/CheckFileSystemJob.cpp
        jobs/ClearMountsJob.cpp
        jobs/ClearTempMountsJob.cpp
        jobs/CreatePartitionJob.cpp
        jobs/CreatePartitionTableJob.cpp
        jobs/DeletePartitionJob.cpp
        jobs/FillGlobalStorageJob.cpp
        jobs/FormatPartitionJob.cpp
        jobs/MoveFileSystemJob.cpp
        jobs/PartitionJob.cpp
        jobs/ResizePartitionJob.cpp
        jobs/SetPartitionFlagsJob.cpp
    UI
        gui/ChoicePage.ui
        gui/CreatePartitionDialog.ui
        gui/CreatePartitionTableDialog.ui
        gui/EditExistingPartitionDialog.ui
        gui/EncryptWidget.ui
        gui/PartitionPage.ui
        gui/ReplaceWidget.ui
    LINK_PRIVATE_LIBRARIES
        kpmcore
        calamaresui
        KF5::CoreAddons
    SHARED_LIB
)
