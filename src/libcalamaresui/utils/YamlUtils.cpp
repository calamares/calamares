/* === This file is part of Calamares - <http://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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
#include "YamlUtils.h"

#include <yaml-cpp/yaml.h>

#include <QRegExp>

void
operator>>( const YAML::Node& node, QStringList& v )
{
    for ( size_t i = 0; i < node.size(); ++i )
    {
        v.append( QString::fromStdString( node[ i ].as< std::string >() ) );
    }
}

namespace CalamaresUtils
{

const QRegExp _yamlScalarTrueValues = QRegExp( "true|True|TRUE|on|On|ON" );
const QRegExp _yamlScalarFalseValues = QRegExp( "false|False|FALSE|off|Off|OFF" );

QVariant
yamlToVariant( const YAML::Node& node )
{
    switch ( node.Type() )
    {
    case YAML::NodeType::Scalar:
        return yamlScalarToVariant( node );

    case YAML::NodeType::Sequence:
        return yamlSequenceToVariant( node );

    case YAML::NodeType::Map:
        return yamlMapToVariant( node );

    case YAML::NodeType::Null:
    case YAML::NodeType::Undefined:
        return QVariant();
    }

    // NOTREACHED
    return QVariant();
}


QVariant
yamlScalarToVariant( const YAML::Node& scalarNode )
{
    std::string stdScalar = scalarNode.as< std::string >();
    QString scalarString = QString::fromStdString( stdScalar );
    if ( _yamlScalarTrueValues.exactMatch( scalarString ) )
        return QVariant( true );
    if ( _yamlScalarFalseValues.exactMatch( scalarString ) )
        return QVariant( false );
    if ( QRegExp( "[-+]?\\d+" ).exactMatch( scalarString ) )
        return QVariant( scalarString.toInt() );
    if ( QRegExp( "[-+]?\\d*\\.?\\d+" ).exactMatch( scalarString ) )
        return QVariant( scalarString.toDouble() );
    return QVariant( scalarString );
}


QVariant
yamlSequenceToVariant( const YAML::Node& sequenceNode )
{
    QVariantList vl;
    for ( YAML::const_iterator it = sequenceNode.begin();
          it != sequenceNode.end(); ++it )
    {
        vl << yamlToVariant( *it );
    }
    return vl;
}


QVariant
yamlMapToVariant( const YAML::Node& mapNode )
{
    QVariantMap vm;
    for ( YAML::const_iterator it = mapNode.begin();
          it != mapNode.end(); ++it )
    {
        vm.insert( QString::fromStdString( it->first.as< std::string >() ),
                   yamlToVariant( it->second ) );
    }
    return vm;
}


}
