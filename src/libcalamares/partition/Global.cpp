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
    QString key = filesystemType.toLower();
    if ( fsUse.contains( key ) )
    {
        const auto v = fsUse.value( key );
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
        QString key = filesystemType.toLower();
        existingMap.insert( key, used );
        gs->insert( fsUse_key, existingMap );
    }
}

void
CalamaresUtils::Partition::clearFilesystemGS( Calamares::GlobalStorage* gs )
{
    if ( gs )
    {
        gs->remove( fsUse_key );
    }
}
