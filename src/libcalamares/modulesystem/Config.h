/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2021 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef CALAMARES_MODULESYSTEM_CONFIG_H
#define CALAMARES_MODULESYSTEM_CONFIG_H

#include "DllMacro.h"

#include <QObject>
#include <QStringList>
#include <QVariantMap>

#include <memory>

namespace Calamares
{
namespace ModuleSystem
{
/** @brief Base class for Config-objects
 *
 * This centralizes the things every Config-object should
 * do and provides one source of preset-data. A Config-object
 * for a module can **optionally** inherit from this class
 * to get presets-support.
 *
 * TODO:3.3 This is not optional
 * TODO:3.3 Put consistent i18n for Configurations in here too
 */
class DLLEXPORT Config : public QObject
{
public:
    Config( QObject* parent = nullptr );
    ~Config() override;

    /** @brief Set the configuration from the config file
     *
     * Subclasses must implement this to load configuration data;
     * that subclass **should** also call loadPresets() with the
     * same map, to pick up the "presets" key consistently.
     */
    virtual void setConfigurationMap( const QVariantMap& ) = 0;

protected:
    void loadPresets( const QVariantMap& configurationMap );
    void loadPresets( const QVariantMap& configurationMap, const QStringList& recognizedKeys );

private:
    class Private;
    std::unique_ptr< Private > d;
};
}  // namespace ModuleSystem
}  // namespace Calamares

#endif
