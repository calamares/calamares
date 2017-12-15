find_package( Qt5 COMPONENTS Gui Test REQUIRED )

include( ECMAddTests )

set( PartitionModule_SOURCE_DIR .. )

set( partitionjobtests_SRCS
    ${PartitionModule_SOURCE_DIR}/core/KPMHelpers.cpp
    ${PartitionModule_SOURCE_DIR}/core/PartitionInfo.cpp
    ${PartitionModule_SOURCE_DIR}/core/PartitionIterator.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionTableJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/DeletePartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/PartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/ResizePartitionJob.cpp
    PartitionJobTests.cpp
)

include_directories(
    ${Qt5Gui_INCLUDE_DIRS}
    ${PartitionModule_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

ecm_add_test( ${partitionjobtests_SRCS}
    TEST_NAME partitionjobtests
    LINK_LIBRARIES
        ${CALAMARES_LIBRARIES}
        kpmcore
        Qt5::Core
        Qt5::Test
)

set_target_properties( partitionjobtests PROPERTIES AUTOMOC TRUE )
