/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2017 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PLASMALNF_THEMEINFO_H
#define PLASMALNF_THEMEINFO_H

#include <QList>
#include <QString>

class KPluginMetaData;
class ThemeWidget;

/** @brief describes a single plasma LnF theme.
 *
 * A theme description has an id, which is really the name of the desktop
 * file (e.g. org.kde.breeze.desktop), a name which is human-readable and
 * translated, and an optional image Page, which points to a local screenshot
 * of that theme.
 */
struct ThemeInfo
{
    QString id;
    QString name;
    QString description;
    QString imagePath;
    ThemeWidget* widget;

    ThemeInfo()
        : widget( nullptr )
    {
    }

    explicit ThemeInfo( const QString& _id )
        : id( _id )
        , widget( nullptr )
    {
    }

    explicit ThemeInfo( const QString& _id, const QString& image )
        : id( _id )
        , imagePath( image )
        , widget( nullptr )
    {
    }

    // Defined in PlasmaLnfPage.cpp
    explicit ThemeInfo( const KPluginMetaData& );

    bool isValid() const { return !id.isEmpty(); }
};

class ThemeInfoList : public QList< ThemeInfo >
{
public:
    /** @brief Looks for a given @p id in the list of themes, returns nullptr if not found. */
    ThemeInfo* findById( const QString& id )
    {
        for ( ThemeInfo& i : *this )
        {
            if ( i.id == id )
            {
                return &i;
            }
        }
        return nullptr;
    }

    /** @brief Looks for a given @p id in the list of themes, returns nullptr if not found. */
    const ThemeInfo* findById( const QString& id ) const
    {
        for ( const ThemeInfo& i : *this )
        {
            if ( i.id == id )
            {
                return &i;
            }
        }
        return nullptr;
    }

    /** @brief Checks if a given @p id is in the list of themes. */
    bool contains( const QString& id ) const { return findById( id ) != nullptr; }
};

#endif
