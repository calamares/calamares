/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */
#include "Global.h"

#include "FileSystem.h"
#include "GlobalStorage.h"
#include "JobQueue.h"

#include <QVariantMap>

static const QString fsUse_key = QStringLiteral( "filesystem_use" );

bool
CalamaresUtils::Partition::isFilesystemUsedGS( const Calamares::GlobalStorage* gs, const QString& filesystemType )
{
    if ( !gs )
    {
        return false;
    }
    const QVariantMap fsUse = gs->value( fsUse_key ).toMap();
    if ( fsUse.contains( filesystemType ) )
    {
        const auto v = fsUse.value( filesystemType );
        return v.toBool();
    }
    return false;
}

void
CalamaresUtils::Partition::useFilesystemGS( Calamares::GlobalStorage* gs, const QString& filesystemType, bool used )
{
    if ( gs )
    {
        QVariantMap existingMap = gs->contains( fsUse_key ) ? gs->value( fsUse_key ).toMap() : QVariantMap();
        existingMap.insert( filesystemType, used );
        gs->insert( fsUse_key, existingMap );
    }
}
