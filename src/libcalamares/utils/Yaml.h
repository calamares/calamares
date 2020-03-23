/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
 *   Copyright 2017-2018, Adriaan de Groot <groot@kde.org>
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

#ifndef UTILS_YAML_H
#define UTILS_YAML_H

#include <QStringList>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>

class QByteArray;
class QFileInfo;

// The yaml-cpp headers are not C++11 warning-proof, especially
// with picky compilers like Clang 8. Since we use Clang for the
// find-all-the-warnings case, switch those warnings off for
// the we-can't-change-them system headers.
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma clang diagnostic ignored "-Wshadow"
#pragma clang diagnostic ignored "-Wfloat-equal"
#endif

#include <yaml-cpp/yaml.h>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

/// @brief Appends all te elements of @p node to the string list @p v
void operator>>( const YAML::Node& node, QStringList& v );

namespace CalamaresUtils
{
/**
 * Loads a given @p filename and returns the YAML data
 * as a QVariantMap. If filename doesn't exist, or is
 * malformed in some way, returns an empty map and sets
 * @p *ok to false. Otherwise sets @p *ok to true.
 */
QVariantMap loadYaml( const QString& filename, bool* ok = nullptr );
/** Convenience overload. */
QVariantMap loadYaml( const QFileInfo&, bool* ok = nullptr );

QVariant yamlToVariant( const YAML::Node& node );
QVariant yamlScalarToVariant( const YAML::Node& scalarNode );
QVariantList yamlSequenceToVariant( const YAML::Node& sequenceNode );
QVariantMap yamlMapToVariant( const YAML::Node& mapNode );

/// @brief Returns all the elements of @p listNode in a StringList
QStringList yamlToStringList( const YAML::Node& listNode );

/// @brief Save a @p map to @p filename as YAML
bool saveYaml( const QString& filename, const QVariantMap& map );

/**
 * Given an exception from the YAML parser library, explain
 * what is going on in terms of the data passed to the parser.
 * Uses @p label when labeling the data source (e.g. "netinstall data")
 */
void explainYamlException( const YAML::Exception& e, const QByteArray& data, const char* label );
void explainYamlException( const YAML::Exception& e, const QByteArray& data, const QString& label );
void explainYamlException( const YAML::Exception& e, const QByteArray& data );

}  // namespace CalamaresUtils

#endif
