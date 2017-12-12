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

class QDebug;


struct ThemeInfo
{
    QString id;
    QString name;
    QString imagePath;

    ThemeInfo()
    {}

    ThemeInfo( const QString& _id, const QString& _name, const QString& image = QString() )
        : id( _id )
        , name( _name )
        , imagePath( image )
    {}

    bool isValid() const { return !id.isEmpty(); }
} ;

class ThemeInfoList : public QList< ThemeInfo >
{
public:
    ThemeInfo* findById( const QString& id )
    {
        for ( ThemeInfo& i : *this )
        {
            if ( i.id == id )
                return &i;
        }
        return nullptr;
    }

    const ThemeInfo* findById( const QString& id ) const
    {
        for ( const ThemeInfo& i : *this )
        {
            if ( i.id == id )
                return &i;
        }
        return nullptr;
    }

    bool contains( const QString& id ) const
    {
        return findById( id ) != nullptr;
    }
} ;

#endif
