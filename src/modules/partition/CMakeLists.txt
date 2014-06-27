if( WITH_PARTITIONMANAGER )

add_definitions( -DCALAMARES )

include_directories( ${PROJECT_BINARY_DIR}/src/calamares )
calamares_add_plugin( partition
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    CONFIG_FILE module.conf
    SOURCES
        DeviceModel.cpp
        PartitionModel.cpp
        PartitionPage.cpp
        PartitionViewPlugin.cpp
    UI
        PartitionPage.ui
    LINK_LIBRARIES
        calapm
        ${CALAMARES_LIBRARIES}
        calamares_bin
    SHARED_LIB
)

# Temporary, until views are integrated
set( partview_SRCS
    DeviceModel.cpp
    PartitionModel.cpp
    PartitionPage.cpp
    ${calamares_SOURCE_DIR}/viewpages/AbstractPage.cpp
    main.cpp
)
qt5_wrap_ui( partview_SRCS PartitionPage.ui )

include_directories( ${CMAKE_CURRENT_BINARY_DIR} )

add_executable( partview ${partview_SRCS} )
target_link_libraries( partview
    calapm
    ${CALAMARES_LIBRARIES}
    Qt5::Widgets
    Qt5::Gui
    Qt5::Core
)
set_target_properties( partview PROPERTIES AUTOMOC TRUE )

endif( WITH_PARTITIONMANAGER )
