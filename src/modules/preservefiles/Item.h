/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *  SPDX-FileCopyrightText: 2018, 2021 Adriaan de Groot <groot@kde.org>
 *  SPDX-License-Identifier: GPL-3.0-or-later
 *
 */
#ifndef PRESERVEFILES_ITEM_H
#define PRESERVEFILES_ITEM_H

#include "utils/Permissions.h"

#include <QString>
#include <QVariant>

#include <memory>

enum class ItemType
{
    None,
    Path,
    Log,
    Config
};

/** @brief Represents one item to copy
 *
 * All item types need a destination (to place the data), this is
 * intepreted within the target system. All items need a permission,
 * which is applied to the data once written.
 *
 * The source may be a path, but not all types need a source.
 */
class Item
{
    QString source;
    QString dest;
    CalamaresUtils::Permissions perm;
    ItemType m_type = ItemType::None;
    bool m_optional = false;

public:
    Item( const QString& src, const QString& d, CalamaresUtils::Permissions p, ItemType t, bool optional )
        : source( src )
        , dest( d )
        , perm( std::move( p ) )
        , m_type( t )
        , m_optional( optional )
    {
    }

    Item()
        : m_type( ItemType::None )
    {
    }

    operator bool() const { return m_type != ItemType::None; }
    ItemType type() const { return m_type; }
    bool isOptional() const { return m_optional; }

    bool exec( const std::function< QString( QString ) >& replacements ) const;


    /** @brief Create an Item -- or one of its subclasses -- from @p v
     *
     * Depending on the structure and contents of @p v, a pointer
     * to an Item is returned. If @p v cannot be interpreted meaningfully,
     * then a nullptr is returned.
     *
     * When the entry contains a *perm* key, use that permission, otherwise
     * apply @p defaultPermissions to the item.
     */
    static Item fromVariant( const QVariant& v, const CalamaresUtils::Permissions& defaultPermissions );
};


#endif
