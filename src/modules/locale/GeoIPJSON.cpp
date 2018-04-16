/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014-2016, Teo Mrnjavac <teo@kde.org>
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

#include "GeoIPJSON.h"

#include "utils/Logger.h"
#include "utils/YamlUtils.h"

#include <QByteArray>

#include <yaml-cpp/yaml.h>

GeoIPJSON::GeoIPJSON(const QString& attribute)
    : GeoIP( attribute.isEmpty() ? QLatin1String( "time_zone" ) : attribute )
{
}

GeoIP::RegionZonePair
GeoIPJSON::processReply( const QByteArray& data )
{
    try
    {
        YAML::Node doc = YAML::Load( data );

        QVariant var = CalamaresUtils::yamlToVariant( doc );
        if ( !var.isNull() &&
            var.isValid() &&
            var.type() == QVariant::Map )
        {
            QVariantMap map = var.toMap();
            if ( map.contains( m_element ) &&
                !map.value( m_element ).toString().isEmpty() )
            {
                return splitTZString( map.value( m_element ).toString() );
            }
        }
        else
            cWarning() << "Invalid YAML data for GeoIPJSON";
    }
    catch ( YAML::Exception& e )
    {
        CalamaresUtils::explainYamlException( e, data, "GeoIP data");
    }

    return qMakePair( QString(), QString() );
}
