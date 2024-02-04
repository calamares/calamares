# === This file is part of Calamares - <https://calamares.io> ===
#
#   SPDX-FileCopyrightText: 2020 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
include(CalamaresAddBrandingSubdirectory)
include(CalamaresAddLibrary)
include(CalamaresAddModuleSubdirectory)
include(CalamaresAddPlugin)
include(CalamaresAddTest)
include(CalamaresAddTranslations)

# library
add_subdirectory(libcalamares)
add_subdirectory(libcalamaresui)

add_subdirectory(qml)

# application
add_subdirectory(calamares)

# plugins
add_subdirectory(modules)

# branding components
add_subdirectory(branding)
