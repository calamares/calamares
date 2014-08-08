find_package( Qt5 COMPONENTS Test REQUIRED )
include( ECMAddTests )

set( jobtests_SRCS
    ${PartitionModule_SOURCE_DIR}/core/PMUtils.cpp
    ${PartitionModule_SOURCE_DIR}/core/PartitionInfo.cpp
    ${PartitionModule_SOURCE_DIR}/core/PartitionIterator.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/CheckFileSystemJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionTableJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/DeletePartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/MoveFileSystemJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/PartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/jobs/ResizePartitionJob.cpp
    JobTests.cpp
)

include_directories(
    ${PartitionModule_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

ecm_add_test( ${jobtests_SRCS}
    TEST_NAME jobtests
    LINK_LIBRARIES
        calapm
        ${CALAMARES_LIBRARIES}
        Qt5::Core
        Qt5::Test
)

set_target_properties( jobtests PROPERTIES AUTOMOC TRUE )
