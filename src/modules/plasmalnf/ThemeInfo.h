/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2017, Adriaan de Groot <groot@kde.org>
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
    {}

    explicit ThemeInfo( const QString& _id )
        : id( _id )
        , widget( nullptr )
    {
    }

    explicit ThemeInfo( const QString& _id, const QString& image )
        : id( _id )
        , imagePath( image )
        , widget( nullptr )
    {}

    // Defined in PlasmaLnfPage.cpp
    explicit ThemeInfo( const KPluginMetaData& );

    bool isValid() const { return !id.isEmpty(); }
} ;

class ThemeInfoList : public QList< ThemeInfo >
{
public:
    /** @brief Looks for a given @p id in the list of themes, returns nullptr if not found. */
    ThemeInfo* findById( const QString& id )
    {
        for ( ThemeInfo& i : *this )
        {
            if ( i.id == id )
                return &i;
        }
        return nullptr;
    }

    /** @brief Looks for a given @p id in the list of themes, returns nullptr if not found. */
    const ThemeInfo* findById( const QString& id ) const
    {
        for ( const ThemeInfo& i : *this )
        {
            if ( i.id == id )
                return &i;
        }
        return nullptr;
    }

    /** @brief Checks if a given @p id is in the list of themes. */
    bool contains( const QString& id ) const
    {
        return findById( id ) != nullptr;
    }
} ;

#endif
