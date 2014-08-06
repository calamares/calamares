find_package( Qt5 COMPONENTS Test REQUIRED )
include( ECMAddTests )

set( jobtests_SRCS
    ${PartitionModule_SOURCE_DIR}/CheckFileSystemJob.cpp
    ${PartitionModule_SOURCE_DIR}/CreatePartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/CreatePartitionTableJob.cpp
    ${PartitionModule_SOURCE_DIR}/DeletePartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/MoveFileSystemJob.cpp
    ${PartitionModule_SOURCE_DIR}/PartitionInfo.cpp
    ${PartitionModule_SOURCE_DIR}/PartitionIterator.cpp
    ${PartitionModule_SOURCE_DIR}/PartitionJob.cpp
    ${PartitionModule_SOURCE_DIR}/PMUtils.cpp
    ${PartitionModule_SOURCE_DIR}/ResizePartitionJob.cpp
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
