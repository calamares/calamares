# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
find_package(Qt5 COMPONENTS Gui REQUIRED)

set(PartitionModule_SOURCE_DIR ..)

include_directories(
    ${Qt5Gui_INCLUDE_DIRS}
    ${PartitionModule_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

calamares_add_test(
    partitionjobtest
    SOURCES
        PartitionJobTests.cpp
        ${PartitionModule_SOURCE_DIR}/core/KPMHelpers.cpp
        ${PartitionModule_SOURCE_DIR}/core/PartitionInfo.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/CreatePartitionTableJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/DeletePartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/PartitionJob.cpp
        ${PartitionModule_SOURCE_DIR}/jobs/ResizePartitionJob.cpp
    LIBRARIES kpmcore
    DEFINITIONS ${_partition_defs}
)

calamares_add_test(
    partitionclearmountsjobtest
    SOURCES ${PartitionModule_SOURCE_DIR}/jobs/ClearMountsJob.cpp ClearMountsJobTests.cpp
    LIBRARIES kpmcore
    DEFINITIONS ${_partition_defs}
)

calamares_add_test(
    partitioncreatelayoutstest
    SOURCES
        CreateLayoutsTests.cpp
        ${PartitionModule_SOURCE_DIR}/core/KPMHelpers.cpp
        ${PartitionModule_SOURCE_DIR}/core/PartitionInfo.cpp
        ${PartitionModule_SOURCE_DIR}/core/PartitionLayout.cpp
        ${PartitionModule_SOURCE_DIR}/core/PartUtils.cpp
        ${PartitionModule_SOURCE_DIR}/core/DeviceModel.cpp
    LIBRARIES kpmcore Calamares::calamaresui
    DEFINITIONS ${_partition_defs}
)

calamares_add_test(
    partitionautomounttest
    SOURCES ${PartitionModule_SOURCE_DIR}/jobs/AutoMountManagementJob.cpp AutoMountTests.cpp
    DEFINITIONS ${_partition_defs}
)

calamares_add_test(
    partitiondevicestest
    SOURCES DevicesTests.cpp ${PartitionModule_SOURCE_DIR}/core/DeviceList.cpp
    LIBRARIES kpmcore
    DEFINITIONS ${_partition_defs}
)
