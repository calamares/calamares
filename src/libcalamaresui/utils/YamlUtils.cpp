/* === This file is part of Calamares - <https://github.com/calamares> ===
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

#include "utils/Logger.h"

#include <yaml-cpp/yaml.h>

#include <QByteArray>
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


void
explainYamlException( const YAML::Exception& e, const QByteArray& yamlData, const char *label )
{
    cWarning() << "YAML error " << e.what() << "in" << label << '.';
    if ( ( e.mark.line >= 0 ) && ( e.mark.column >= 0 ) )
    {
        // Try to show the line where it happened.
        int linestart = 0;
        for ( int linecount = 0; linecount < e.mark.line; ++linecount )
        {
            linestart = yamlData.indexOf( '\n', linestart );
            // No more \ns found, weird
            if ( linestart < 0 )
                break;
            linestart += 1;  // Skip that \n
        }
        int lineend = linestart;
        if ( linestart >= 0 )
        {
            lineend = yamlData.indexOf( '\n', linestart );
            if ( lineend < 0 )
                lineend = yamlData.length();
        }

        int rangestart = linestart;
        int rangeend = lineend;
        // Adjust range (linestart..lineend) so it's not too long
        if ( ( linestart >= 0 ) && ( e.mark.column > 30 ) )
            rangestart += ( e.mark.column - 30 );
        if ( ( linestart >= 0 ) && ( rangeend - rangestart > 40 ) )
            rangeend = rangestart + 40;

        if ( linestart >= 0 )
            cWarning() << "offending YAML data:" << yamlData.mid( rangestart, rangeend-rangestart ).constData();

    }
}

}  // namespace
