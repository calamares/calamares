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

    find_package( KPMcore 21.12.0 )
    set_package_properties(
        KPMcore PROPERTIES
        URL "https://invent.kde.org/kde/kpmcore"
        DESCRIPTION "KDE Partitioning library"
        TYPE RECOMMENDED
        PURPOSE "For disk partitioning support"
    )

    if( KPMcore_FOUND )
        set( KPMcore_API_DEFINITIONS "" )
    else()
        set( KPMcore_API_DEFINITIONS WITHOUT_KPMcore )
    endif()
endif()
