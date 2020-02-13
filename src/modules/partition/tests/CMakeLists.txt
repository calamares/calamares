find_package( Qt5 COMPONENTS Gui REQUIRED )

# Roundabout way of saying ..
set( PartitionModule_SOURCE_DIR .. )
# This is set by parent CMakeLists.txt
# set( _partition_defs )

include_directories(
    ${Qt5Gui_INCLUDE_DIRS}
    ${PartitionModule_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

if( ECM_FOUND AND BUILD_TESTING )
    ecm_add_test(
        ${PartitionModule_SOURCE_DIR}/core/KPMHelpers.cpp
        ${PartitionModule_SOURCE_DIR}/core/PartitionInfo.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionTableJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/DeletePartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/PartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/ResizePartitionJob.cpp
        PartitionJobTests.cpp

        TEST_NAME partitionjobtests
        LINK_LIBRARIES
            ${CALAMARES_LIBRARIES}
            kpmcore
            Qt5::Core
            Qt5::Test
    )

    set_target_properties( partitionjobtests PROPERTIES AUTOMOC TRUE )
    target_compile_definitions( partitionjobtests PRIVATE ${_partition_defs} )

    ecm_add_test(
        ${PartitionModule_SOURCE_DIR}/jobs/ClearMountsJob.cpp
        ClearMountsJobTests.cpp

        TEST_NAME clearmountsjobtests
        LINK_LIBRARIES
            ${CALAMARES_LIBRARIES}
            kpmcore
            Qt5::Core
            Qt5::Test
    )

    set_target_properties( clearmountsjobtests PROPERTIES AUTOMOC TRUE )
    target_compile_definitions( clearmountsjobtests PRIVATE ${_partition_defs} )

endif()
