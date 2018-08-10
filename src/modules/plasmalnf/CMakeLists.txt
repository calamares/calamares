find_package(ECM ${ECM_VERSION} REQUIRED NO_MODULE)

# Requires a sufficiently recent Plasma framework, but also
# needs a runtime support component (which we don't test for).
set( lnf_ver 5.41 )

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
    if ( KF5Config_FOUND )
        set( option_kf5 Config )
        set( option_defs WITH_KCONFIG )
        # set( option_libs KF5::Config )  # Not needed anyway
    endif()

    find_package( KF5 ${lnf_ver} REQUIRED CoreAddons Plasma Package ${option_kf5} )

    calamares_add_plugin( plasmalnf
        TYPE viewmodule
        EXPORT_MACRO PLUGINDLLEXPORT_PRO
        COMPILE_DEFINITIONS
            ${option_defs}
        SOURCES
            PlasmaLnfViewStep.cpp
            PlasmaLnfPage.cpp
            PlasmaLnfJob.cpp
            ThemeWidget.cpp
        RESOURCES
            page_plasmalnf.qrc
        UI
            page_plasmalnf.ui
        LINK_PRIVATE_LIBRARIES
            calamaresui
            ${option_libs}
            KF5::Package
            KF5::Plasma
        SHARED_LIB
    )
else()
    calamares_skip_module( "plasmalnf (missing requirements)" )
endif()
