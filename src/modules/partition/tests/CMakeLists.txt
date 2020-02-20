find_package( Qt5 COMPONENTS Gui REQUIRED )

set( PartitionModule_SOURCE_DIR .. )

include_directories(
    ${Qt5Gui_INCLUDE_DIRS}
    ${PartitionModule_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

calamares_add_test(
    partitionjobtests
    SOURCES
        PartitionJobTests.cpp
        ${PartitionModule_SOURCE_DIR}/core/KPMHelpers.cpp
        ${PartitionModule_SOURCE_DIR}/core/PartitionInfo.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionTableJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/DeletePartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/PartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/ResizePartitionJob.cpp
    LIBRARIES
        kpmcore
    DEFINITIONS ${_partition_defs}
)

calamares_add_test(
    clearmountsjobtests
    SOURCES
        ${PartitionModule_SOURCE_DIR}/jobs/ClearMountsJob.cpp
        ClearMountsJobTests.cpp
    LIBRARIES
        kpmcore
    DEFINITIONS ${_partition_defs}
)

