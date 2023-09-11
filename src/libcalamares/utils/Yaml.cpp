/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 *
 */
#include "Yaml.h"

#include "compat/Variant.h"
#include "utils/Logger.h"

#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QRegularExpression>

void
operator>>( const ::YAML::Node& node, QStringList& v )
{
    for ( size_t i = 0; i < node.size(); ++i )
    {
        v.append( QString::fromStdString( node[ i ].as< std::string >() ) );
    }
}

namespace Calamares
{
namespace YAML
{
QVariant
toVariant( const ::YAML::Node& node )
{
    switch ( node.Type() )
    {
    case ::YAML::NodeType::Scalar:
        return scalarToVariant( node );

    case ::YAML::NodeType::Sequence:
        return sequenceToVariant( node );

    case ::YAML::NodeType::Map:
        return mapToVariant( node );

    case ::YAML::NodeType::Null:
    case ::YAML::NodeType::Undefined:
        return QVariant();
    }
    __builtin_unreachable();
}

QVariant
scalarToVariant( const ::YAML::Node& scalarNode )
{
    static const auto yamlScalarTrueValues = QRegularExpression( "^(true|True|TRUE|on|On|ON)$" );
    static const auto yamlScalarFalseValues = QRegularExpression( "^(false|False|FALSE|off|Off|OFF)$" );
    static const auto yamlIntegerValues = QRegularExpression( "^[-+]?\\d+$" );
    static const auto yamlFloatValues = QRegularExpression( "^[-+]?\\d*\\.?\\d+$" );

    std::string stdScalar = scalarNode.as< std::string >();
    QString scalarString = QString::fromStdString( stdScalar );
    if ( yamlScalarTrueValues.match( scalarString ).hasMatch() )
    {
        return QVariant( true );
    }
    if ( yamlScalarFalseValues.match( scalarString ).hasMatch() )
    {
        return QVariant( false );
    }
    if ( yamlIntegerValues.match( scalarString ).hasMatch() )
    {
        return QVariant( scalarString.toLongLong() );
    }
    if ( yamlFloatValues.match( scalarString ).hasMatch() )
    {
        return QVariant( scalarString.toDouble() );
    }
    return QVariant( scalarString );
}

QVariantList
sequenceToVariant( const ::YAML::Node& sequenceNode )
{
    QVariantList vl;
    for ( ::YAML::const_iterator it = sequenceNode.begin(); it != sequenceNode.end(); ++it )
    {
        vl << toVariant( *it );
    }
    return vl;
}

QVariantMap
mapToVariant( const ::YAML::Node& mapNode )
{
    QVariantMap vm;
    for ( ::YAML::const_iterator it = mapNode.begin(); it != mapNode.end(); ++it )
    {
        vm.insert( QString::fromStdString( it->first.as< std::string >() ), toVariant( it->second ) );
    }
    return vm;
}

QStringList
toStringList( const ::YAML::Node& listNode )
{
    QStringList l;
    listNode >> l;
    return l;
}

void
explainException( const ::YAML::Exception& e, const QByteArray& yamlData, const char* label )
{
    cWarning() << "YAML error " << e.what() << "in" << label << '.';
    explainException( e, yamlData );
}

void
explainException( const ::YAML::Exception& e, const QByteArray& yamlData, const QString& label )
{
    cWarning() << "YAML error " << e.what() << "in" << label << '.';
    explainException( e, yamlData );
}

void
explainException( const ::YAML::Exception& e, const QByteArray& yamlData )
{
    if ( ( e.mark.line >= 0 ) && ( e.mark.column >= 0 ) )
    {
        // Try to show the line where it happened.
        int linestart = 0;
        for ( int linecount = 0; linecount < e.mark.line; ++linecount )
        {
            linestart = yamlData.indexOf( '\n', linestart );
            // No more \ns found, weird
            if ( linestart < 0 )
            {
                break;
            }
            linestart += 1;  // Skip that \n
        }
        int lineend = linestart;
        if ( linestart >= 0 )
        {
            lineend = yamlData.indexOf( '\n', linestart );
            if ( lineend < 0 )
            {
                lineend = yamlData.length();
            }
        }

        int rangestart = linestart;
        int rangeend = lineend;
        // Adjust range (linestart..lineend) so it's not too long
        if ( ( linestart >= 0 ) && ( e.mark.column > 30 ) )
        {
            rangestart += ( e.mark.column - 30 );
        }
        if ( ( linestart >= 0 ) && ( rangeend - rangestart > 40 ) )
        {
            rangeend = rangestart + 40;
        }

        if ( linestart >= 0 )
        {
            cWarning() << "offending YAML data:" << yamlData.mid( rangestart, rangeend - rangestart ).constData();
        }
    }
}

QVariantMap
load( const QFileInfo& fi, bool* ok )
{
    return load( fi.absoluteFilePath(), ok );
}

QVariantMap
load( const QString& filename, bool* ok )
{
    if ( ok )
    {
        *ok = false;
    }

    QFile yamlFile( filename );
    QVariant yamlContents;
    if ( yamlFile.exists() && yamlFile.open( QFile::ReadOnly | QFile::Text ) )
    {
        QByteArray ba = yamlFile.readAll();
        try
        {
            ::YAML::Node doc = ::YAML::Load( ba.constData() );
            yamlContents = toVariant( doc );
        }
        catch ( ::YAML::Exception& e )
        {
            explainException( e, ba, filename );
            return QVariantMap();
        }
    }

    if ( yamlContents.isValid() && !yamlContents.isNull()
         && Calamares::typeOf( yamlContents ) == Calamares::MapVariantType )
    {
        if ( ok )
        {
            *ok = true;
        }
        return yamlContents.toMap();
    }

    return QVariantMap();
}

/// @brief Convenience function writes @p indent times four spaces
static void
writeIndent( QFile& f, int indent )
{
    while ( indent-- > 0 )
    {
        f.write( "  " );
    }
}

// forward declaration
static bool dumpYaml( QFile& f, const QVariantMap& map, int indent );

// It's a quote
static const char quote[] = "\"";
static const char newline[] = "\n";

/// @brief Recursive helper to dump a single value
static void
dumpYamlElement( QFile& f, const QVariant& value, int indent )
{
    const auto t = Calamares::typeOf( value );
    if ( t == Calamares::BoolVariantType )
    {
        f.write( value.toBool() ? "true" : "false" );
    }
    else if ( t == Calamares::StringVariantType )
    {
        f.write( quote );
        f.write( value.toString().toUtf8() );
        f.write( quote );
    }
    else if ( t == Calamares::IntVariantType )
    {
        f.write( QString::number( value.toInt() ).toUtf8() );
    }
    else if ( t == Calamares::LongLongVariantType )
    {
        f.write( QString::number( value.toLongLong() ).toUtf8() );
    }
    else if ( t == Calamares::DoubleVariantType )
    {
        f.write( QString::number( value.toDouble(), 'f', 2 ).toUtf8() );
    }
    else if ( value.canConvert< qulonglong >() )
    {
        // This one needs to be *after* bool, int, double to avoid this branch
        // .. grabbing those convertible types un-necessarily.
        f.write( QString::number( value.toULongLong() ).toUtf8() );
    }
    else if ( t == Calamares::ListVariantType )
    {
        int c = 0;
        for ( const auto& it : value.toList() )
        {
            ++c;
            f.write( newline );
            writeIndent( f, indent + 1 );
            f.write( "- " );
            dumpYamlElement( f, it, indent + 1 );
        }
        if ( !c )  // i.e. list was empty
        {
            f.write( "[]" );
        }
    }
    else if ( t == Calamares::MapVariantType )
    {
        f.write( newline );
        dumpYaml( f, value.toMap(), indent + 1 );
    }
    else
    {
        f.write( "<" );
        f.write( value.typeName() );
        f.write( ">" );
    }
}

/// @brief Recursive helper to dump @p map to file
static bool
dumpYaml( QFile& f, const QVariantMap& map, int indent )
{
    for ( auto it = map.cbegin(); it != map.cend(); ++it )
    {
        writeIndent( f, indent );
        f.write( quote );
        f.write( it.key().toUtf8() );
        f.write( quote );
        f.write( ": " );
        dumpYamlElement( f, it.value(), indent );
        f.write( newline );
    }
    return true;
}

bool
save( const QString& filename, const QVariantMap& map )
{
    QFile f( filename );
    if ( !f.open( QFile::WriteOnly ) )
    {
        return false;
    }

    f.write( "# YAML dump\n---\n" );
    return dumpYaml( f, map, 0 );
}

}  // namespace YAML
}  // namespace Calamares
