/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#include "GeoIPJSON.h"

#include "utils/Logger.h"
#include "utils/Variant.h"
#include "utils/Yaml.h"

#include <QByteArray>

namespace CalamaresUtils
{
namespace GeoIP
{

GeoIPJSON::GeoIPJSON( const QString& attribute )
    : Interface( attribute.isEmpty() ? QStringLiteral( "time_zone" ) : attribute )
{
}

/** @brief Indexes into a map @m by selectors @p l
 *
 * Each element of @p l is an index into map @m or a sub-map thereof,
 * so that "foo.bar.baz" looks up "baz" in the sub-map "bar" of sub-map
 * "foo" of @p m, like a regular JSON lookup would.
 */
static QString
selectMap( const QVariantMap& m, const QStringList& l, int index )
{
    if ( index >= l.count() )
    {
        return QString();
    }

    QString attributeName = l[ index ];
    if ( index == l.count() - 1 )
    {
        return CalamaresUtils::getString( m, attributeName );
    }
    else
    {
        bool success = false;  // bogus
        if ( m.contains( attributeName ) )
        {
            return selectMap( CalamaresUtils::getSubMap( m, attributeName, success ), l, index + 1 );
        }
        return QString();
    }
}

QString
GeoIPJSON::rawReply( const QByteArray& data )
{
    try
    {
        YAML::Node doc = YAML::Load( data );

        QVariant var = CalamaresUtils::yamlToVariant( doc );
        if ( !var.isNull() && var.isValid() && var.type() == QVariant::Map )
        {
            return selectMap( var.toMap(), m_element.split( '.' ), 0 );
        }
        else
        {
            cWarning() << "Invalid YAML data for GeoIPJSON";
        }
    }
    catch ( YAML::Exception& e )
    {
        CalamaresUtils::explainYamlException( e, data, "GeoIP data" );
    }

    return QString();
}

GeoIP::RegionZonePair
GeoIPJSON::processReply( const QByteArray& data )
{
    return splitTZString( rawReply( data ) );
}

}  // namespace GeoIP
}  // namespace CalamaresUtils
