/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2018, Adriaan de Groot <groot@kde.org>
 *
 *   Calamares is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Calamares is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Calamares. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PRESERVEFILES_H
#define PRESERVEFILES_H

#include <QList>
#include <QObject>
#include <QVariantMap>

#include "CppJob.h"
#include "DllMacro.h"

#include "utils/PluginFactory.h"

#include "permissions.h"

class PLUGINDLLEXPORT PreserveFiles : public Calamares::CppJob
{
    Q_OBJECT

    enum class ItemType
    {
        None,
        Path,
        Log,
        Config
    } ;

    struct Item
    {
        QString source;
        QString dest;
        Permissions perm;
        ItemType type;
    } ;

    using ItemList = QList< Item >;

public:
    explicit PreserveFiles( QObject* parent = nullptr );
    virtual ~PreserveFiles() override;

    QString prettyName() const override;

    Calamares::JobResult exec() override;

    void setConfigurationMap( const QVariantMap& configurationMap ) override;

private:
    ItemList m_items;
};

CALAMARES_PLUGIN_FACTORY_DECLARATION( PreserveFilesFactory )

#endif // PRESERVEFILES_H
