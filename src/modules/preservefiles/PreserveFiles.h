/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef PRESERVEFILES_H
#define PRESERVEFILES_H

#include "CppJob.h"
#include "DllMacro.h"
#include "utils/Permissions.h"
#include "utils/PluginFactory.h"

#include <QList>
#include <QObject>
#include <QVariantMap>

class PLUGINDLLEXPORT PreserveFiles : public Calamares::CppJob
{
    Q_OBJECT

    enum class ItemType
    {
        None,
        Path,
        Log,
        Config
    };

    struct Item
    {
        QString source;
        QString dest;
        CalamaresUtils::Permissions perm;
        ItemType type;
    };

    using ItemList = QList< Item >;

public:
    explicit PreserveFiles( QObject* parent = nullptr );
    ~PreserveFiles() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    ItemList m_items;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PreserveFilesFactory )

#endif  // PRESERVEFILES_H
