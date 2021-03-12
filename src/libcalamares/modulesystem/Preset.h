/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_MODULESYSTEM_PRESET_H
#define CALAMARES_MODULESYSTEM_PRESET_H

#include <QString>
#include <QVariantMap>
#include <QVector>

namespace Calamares
{
namespace ModuleSystem
{
/** @brief The settings for a single field
 *
 * The settings apply to a single field; **often** this will
 * correspond to a single value or property of a Config
 * object, but there is no guarantee of a correspondence
 * between names here and names in the code.
 *
 * The value is stored as a string; consumers (e.g. the UI)
 * will need to translate the value to whatever is actually
 * used (e.g. in the case of an integer field).
 *
 * By default, presets are still editable. Set that to @c false
 * to make the field unchangeable (again, the UI is responsible
 * for setting that up).
 */
struct PresetField
{
    QString fieldName;
    QString value;
    bool editable = true;
};

/** @brief All the presets for one UI entity
 *
 * This is a collection of presets read from a module
 * configuration file, one setting per field.
 */
class Presets : public QVector< PresetField >
{
public:
    explicit Presets( const QVariantMap& configurationMap );
    Presets( const QVariantMap& configurationMap, const QStringList& recognizedKeys );
};
}  // namespace ModuleSystem
}  // namespace Calamares

#endif
