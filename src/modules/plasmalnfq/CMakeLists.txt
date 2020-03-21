find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

# Requires a sufficiently recent Plasma framework, but also
# needs a runtime support component (which we don't test for).
set( lnf_ver 5.41 )

set( _plasmalnf ${CMAKE_CURRENT_SOURCE_DIR}/../plasmalnfq )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui ${CMAKE_CURRENT_SOURCE_DIR}/../../libcalamares ${_plasmalnf} )

find_package( KF5Config ${lnf_ver} )
find_package( KF5Plasma ${lnf_ver} )
find_package( KF5Package ${lnf_ver} )
set_package_properties(
    KF5Config PROPERTIES
    PURPOSE "For finding default Plasma Look-and-Feel"
)
set_package_properties(
    KF5Plasma PROPERTIES
    PURPOSE "For Plasma Look-and-Feel selection"
)
set_package_properties(
    KF5Package PROPERTIES
    PURPOSE "For Plasma Look-and-Feel selection"
)

if ( KF5Plasma_FOUND AND KF5Package_FOUND )
    calamares_add_plugin( plasmalnfq
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        COMPILE_DEFINITIONS
            ${option_defs}
        SOURCES
            PlasmaQmlLnfViewStep.cpp
            Config.cpp
            PlasmaLnfJob.cpp
            ThemeWidget.cpp
        RESOURCES
            page_plasmalnf.qrc
        LINK_PRIVATE_LIBRARIES
            calamaresui
            KF5::Package
            KF5::Plasma
KF5::ConfigCore
        SHARED_LIB
    )

    add_executable( plasmalnfqtest qmlmain.cpp Config.cpp PlasmaQmlLnfViewStep.cpp Config.cpp PlasmaLnfJob.cpp )
    target_link_libraries( plasmalnfqtest PRIVATE calamaresui Qt5::Core Qt5::Network Qt5::DBus KF5::Package KF5::Plasma KF5::ConfigCore)

        if ( KF5Config_FOUND )
        target_compile_definitions(plasmalnfqtest PRIVATE WITH_KCONFIG)
    endif()

    set_target_properties( plasmalnfqtest
        PROPERTIES
            ENABLE_EXPORTS TRUE
            RUNTIME_OUTPUT_NAME plasmalnfqtest
    )
    calamares_automoc( plasmalnfqtest )
    calamares_autouic( plasmalnfqtest )


else()
    calamares_skip_module( "plasmalnfq (missing requirements)" )
endif()
