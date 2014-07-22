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
    CONFIG_FILE module.conf
    SOURCES
        CreatePartitionDialog.cpp
        CreatePartitionJob.cpp
        CreatePartitionTableJob.cpp
        DeletePartitionJob.cpp
        DeviceModel.cpp
        EditExistingPartitionDialog.cpp
        FormatPartitionJob.cpp
        PartitionCoreModule.cpp
        PartitionInfo.cpp
        PartitionIterator.cpp
        PartitionJob.cpp
        PartitionModel.cpp
        PartitionPage.cpp
        PartitionViewStep.cpp
        PMUtils.cpp
    UI
        CreatePartitionDialog.ui
        CreatePartitionTableDialog.ui
        EditExistingPartitionDialog.ui
        PartitionPage.ui
    LINK_LIBRARIES
        calapm
        calamaresui
        KF5::CoreAddons
    SHARED_LIB
)

endif( WITH_PARTITIONMANAGER )
