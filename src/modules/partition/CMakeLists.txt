if( WITH_PARTITIONMANAGER )

## ECM
find_package(ECM 0.0.13 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_MODULE_PATH})
include(KDEInstallDirs)
include(GenerateExportHeader)

find_package( KF5 REQUIRED CoreAddons )

add_definitions( -DCALAMARES )

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
        PartitionCoreModule.cpp
        PartitionInfo.cpp
        PartitionModel.cpp
        PartitionPage.cpp
        PartitionViewStep.cpp
        PMUtils.cpp
    UI
        CreatePartitionDialog.ui
        PartitionPage.ui
    LINK_LIBRARIES
        calapm
        calamaresui
        KF5::CoreAddons
    SHARED_LIB
)

# Temporary, until views are integrated
set( partview_SRCS
    CreatePartitionDialog.cpp
    CreatePartitionJob.cpp
    CreatePartitionTableJob.cpp
    DeletePartitionJob.cpp
    DeviceModel.cpp
    PartitionCoreModule.cpp
    PartitionInfo.cpp
    PartitionModel.cpp
    PartitionPage.cpp
    PMUtils.cpp
    main.cpp
)
qt5_wrap_ui( partview_SRCS
    CreatePartitionDialog.ui
    PartitionPage.ui
)

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

add_executable( partview ${partview_SRCS} )
target_link_libraries( partview
    calapm
    ${CALAMARES_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
    KF5::CoreAddons
)
set_target_properties( partview PROPERTIES AUTOMOC TRUE )

endif( WITH_PARTITIONMANAGER )
