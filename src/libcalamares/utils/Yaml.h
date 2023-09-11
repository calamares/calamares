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
void operator>>( const ::YAML::Node& node, QStringList& v );

namespace Calamares
{
namespace YAML
{
/**
 * Loads a given @p filename and returns the YAML data
 * as a QVariantMap. If filename doesn't exist, or is
 * malformed in some way, returns an empty map and sets
 * @p *ok to false. Otherwise sets @p *ok to true.
 */
QVariantMap load( const QString& filename, bool* ok = nullptr );
/** Convenience overload. */
QVariantMap load( const QFileInfo&, bool* ok = nullptr );

QVariant toVariant( const ::YAML::Node& node );
QVariant scalarToVariant( const ::YAML::Node& scalarNode );
QVariantList sequenceToVariant( const ::YAML::Node& sequenceNode );
QVariantMap mapToVariant( const ::YAML::Node& mapNode );

/// @brief Returns all the elements of @p listNode in a StringList
QStringList toStringList( const ::YAML::Node& listNode );

/// @brief Save a @p map to @p filename as YAML
bool save( const QString& filename, const QVariantMap& map );

/**
 * Given an exception from the YAML parser library, explain
 * what is going on in terms of the data passed to the parser.
 * Uses @p label when labeling the data source (e.g. "netinstall data")
 */
void explainException( const ::YAML::Exception& e, const QByteArray& data, const char* label );
void explainException( const ::YAML::Exception& e, const QByteArray& data, const QString& label );
void explainException( const ::YAML::Exception& e, const QByteArray& data );

}  // namespace YAML
}  // namespace Calamares

#endif
