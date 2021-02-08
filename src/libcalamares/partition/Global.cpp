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

STATICTEST
bool
isFilesystemUsedGS( const Calamares::GlobalStorage& gs, const QString& filesystemType )
{

    const QVariantMap fsUse = gs.value( fsUse_key ).toMap();
    if ( fsUse.contains( filesystemType ) )
    {
        const auto v = fsUse.value( filesystemType );
        return v.toBool();
    }
    return false;
}

STATICTEST void
useFilesystemGS( Calamares::GlobalStorage& gs, const QString& filesystemType, bool used )
{
    QVariantMap existingMap = gs.contains( fsUse_key ) ? gs.value( fsUse_key ).toMap() : QVariantMap();
    existingMap.insert( filesystemType, used );
    gs.insert( fsUse_key, existingMap );
}

bool
CalamaresUtils::Partition::isFilesystemUsedGS( const QString& filesystemType )
{
    const auto* jq = Calamares::JobQueue::instance();
    const auto* gs = jq ? jq->globalStorage() : nullptr;

    if ( !gs )
    {
        return false;
    }
    return isFilesystemUsedGS( *gs, filesystemType );
}

void
CalamaresUtils::Partition::useFilesystemGS( const QString& filesystemType, bool used )
{
    const auto* jq = Calamares::JobQueue::instance();
    auto* gs = jq ? jq->globalStorage() : nullptr;

    if ( gs )
    {
        useFilesystemGS( *gs, filesystemType, used );
    }
}
