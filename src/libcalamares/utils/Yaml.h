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

/*
 * YAML conversions and YAML convenience header.
 *
 * Includes the system YAMLCPP headers without warnings (by switching off
 * the expected warnings) and provides a handful of methods for
 * converting between YAML and QVariant.
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
#pragma clang diagnostic ignored "-Wsuggest-destructor-override"
#endif

#include <yaml-cpp/yaml.h>

#ifdef __clang__
#pragma clang diagnostic pop
#endif

/// @brief Appends all the elements of @p node to the string list @p v
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
