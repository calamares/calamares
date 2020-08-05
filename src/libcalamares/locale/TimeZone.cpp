/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   SPDX-FileCopyrightText: 2019 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#include "TimeZone.h"

#include "utils/Logger.h"

static const char TZ_DATA_FILE[] = "/usr/share/zoneinfo/zone.tab";

/** @brief Turns a string longitude or latitude notation into a double
 *
 * This handles strings like "+4230+00131" from zone.tab,
 * which is degrees-and-minutes notation, and + means north or east.
 */
static double
getRightGeoLocation( QString str )
{
    double sign = 1, num = 0.00;

    // Determine sign
    if ( str.startsWith( '-' ) )
    {
        sign = -1;
        str.remove( 0, 1 );
    }
    else if ( str.startsWith( '+' ) )
    {
        str.remove( 0, 1 );
    }

    if ( str.length() == 4 || str.length() == 6 )
    {
        num = str.mid( 0, 2 ).toDouble() + str.mid( 2, 2 ).toDouble() / 60.0;
    }
    else if ( str.length() == 5 || str.length() == 7 )
    {
        num = str.mid( 0, 3 ).toDouble() + str.mid( 3, 2 ).toDouble() / 60.0;
    }

    return sign * num;
}

/** @brief Massage an identifier into a human-readable form
 *
 * Makes a copy of @p s, caller must free() it.
 */
static char*
munge( const char* s )
{
    char* t = strdup( s );
    if ( !t )
    {
        return nullptr;
    }

    // replace("_"," ") in the Python script
    char* p = t;
    while ( *p )
    {
        if ( ( *p ) == '_' )
        {
            *p = ' ';
        }
        ++p;
    }

    return t;
}


namespace CalamaresUtils
{
namespace Locale
{

struct Private
{
};

static Private*
privateInstance()
{
    static Private* s_p = new Private;
    return s_p;
}

RegionsModel::RegionsModel( QObject* parent )
    : QAbstractListModel( parent )
    , m_private( privateInstance() )
{
}

RegionsModel::~RegionsModel() {}

int
RegionsModel::rowCount( const QModelIndex& parent ) const
{
    return 0;
}

QVariant
RegionsModel::data( const QModelIndex& index, int role ) const
{
    return QVariant();
}


}  // namespace Locale
}  // namespace CalamaresUtils
