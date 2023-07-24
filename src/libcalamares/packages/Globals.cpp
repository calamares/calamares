/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */
#include "string.h"
#include "Globals.h"

#include "GlobalStorage.h"
#include "utils/Logger.h"

static bool
additions( Calamares::GlobalStorage* gs,
           const QString& key,
           const QVariantList& installPackages,
           const QVariantList& tryInstallPackages,
           const char *backend = nullptr )
{
    static const char PACKAGEOP_[] = "packageOperations";
    int backendreplength = backend == nullptr ? 0 : strlen(backend);
    char PACKAGEOP[sizeof("packageOperations") + backendreplength ];

    // Check if there's already a PACAKGEOP entry in GS, and if so we'll
    // extend that one (overwriting the value in GS at the end of this method)
    QVariantList packageOperations = gs->contains( PACKAGEOP ) ? gs->value( PACKAGEOP ).toList() : QVariantList();
    cDebug() << "Existing package operations length" << packageOperations.length();

    PACKAGEOP[0] = '\0';
    if (backend)
    {
      strcat(PACKAGEOP, backend);
      PACKAGEOP[backendreplength] = 'P';
      strcat(PACKAGEOP, &PACKAGEOP_[1]);
    }
    else
    {
       strcat(PACKAGEOP, PACKAGEOP_);
    }

    // Clear out existing operations for this module, going backwards:
    // Sometimes we remove an item, and we don't want the index to
    // fall off the end of the list.
    bool somethingRemoved = false;
    for ( int index = packageOperations.length() - 1; 0 <= index; index-- )
    {
        const QVariantMap op = packageOperations.at( index ).toMap();
        if ( op.contains( "source" ) && op.value( "source" ).toString() == key )
        {
            cDebug() << Logger::SubEntry << "Removing existing operations for" << key;
            packageOperations.removeAt( index );
            somethingRemoved = true;
        }
    }

    if ( !installPackages.empty() )
    {
        QVariantMap op;
        op.insert( "install", QVariant( installPackages ) );
        op.insert( "source", key );
        packageOperations.append( op );
        cDebug() << Logger::SubEntry << installPackages.length() << "critical packages.";
    }
    if ( !tryInstallPackages.empty() )
    {
        QVariantMap op;
        op.insert( "try_install", QVariant( tryInstallPackages ) );
        op.insert( "source", key );
        packageOperations.append( op );
        cDebug() << Logger::SubEntry << tryInstallPackages.length() << "non-critical packages.";
    }

    if ( somethingRemoved || !packageOperations.isEmpty() )
    {
        gs->insert( PACKAGEOP, packageOperations );
        return true;
    }
    return false;
}

bool
CalamaresUtils::Packages::setGSPackageAdditions( Calamares::GlobalStorage* gs,
                                                 const Calamares::ModuleSystem::InstanceKey& module,
                                                 const QVariantList& installPackages,
                                                 const QVariantList& tryInstallPackages,
                                                 const char *backend )
{
    return additions( gs, module.toString(), installPackages, tryInstallPackages, backend );
}

bool
CalamaresUtils::Packages::setGSPackageAdditions( Calamares::GlobalStorage* gs,
                                                 const Calamares::ModuleSystem::InstanceKey& module,
                                                 const QStringList& installPackages,
                                                 const char *backend )
{
    QVariantList l;
    for ( const auto& s : installPackages )
    {
        l << s;
    }
    return additions( gs, module.toString(), l, QVariantList(), backend );
}
