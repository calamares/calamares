# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
###
#
# Finds KPMcore and consistently sets API flags based on the version.
#
if ( NOT KPMcore_searched_for )
    set( KPMcore_searched_for TRUE )

    find_package( KPMcore 3.3 )
    set_package_properties(
        KPMcore PROPERTIES
        URL "https://invent.kde.org/kde/kpmcore"
        DESCRIPTION "KDE Partitioning library"
        TYPE RECOMMENDED
        PURPOSE "For disk partitioning support"
    )

    if( KPMcore_FOUND )
        set( KPMcore_API_DEFINITIONS "" )
        if( KPMcore_VERSION VERSION_GREATER "3.3.70" AND KPMcore_VERSION VERSION_LESS "4.0" )
            message( FATAL_ERROR "KPMCore beta versions ${KPMcore_VERSION} not supported" )
        endif()
        if ( KPMcore_VERSION VERSION_GREATER "3.3.0")
            list( APPEND KPMcore_API_DEFINITIONS WITH_KPMCORE331API) # kpmcore > 3.3.0 with deprecations
        endif()
        if ( KPMcore_VERSION VERSION_GREATER_EQUAL "4.0")
            list( APPEND KPMcore_API_DEFINITIONS WITH_KPMCORE4API) # kpmcore 4 with new API
        endif()
        if( KPMcore_VERSION VERSION_GREATER_EQUAL "4.2" )
            list( APPEND KPMcore_API_DEFINITIONS WITH_KPMCORE42API) # kpmcore 4.2 with new API
        endif()
    else()
        set( KPMcore_API_DEFINITIONS WITHOUT_KPMcore )
    endif()
endif()
