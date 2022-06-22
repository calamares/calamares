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
    Q_OBJECT
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

public Q_SLOTS:
    /** @brief Checks if a @p fieldName is editable according to presets
     *
     * If the field is named as a preset, **and** the field is set
     * to not-editable, returns @c false. Otherwise, return @c true.
     * Calling this with an unknown field (one for which no presets
     * are accepted) will print a warning and return @c true.
     *
     * @see CONFIG_PREVENT_EDITING
     *
     * Most setters will call isEditable() to check if the field should
     * be editable. Do not count on the setter not being called: the
     * UI might not have set the field to fixed / constant / not-editable
     * and then you can have the setter called by changes in the UI.
     *
     * To prevent the UI from changing **and** to make sure that the UI
     * reflects the unchanged value (rather than the changed value it
     * sent to the Config object), use CONFIG_PREVENT_EDITING, like so:
     *
     *  CONFIG_PREVENT_EDITING( type, "propertyName" );
     *
     * The ; is necessary. <type> is the type of the property; for instance
     * QString. The name of the property is a (constant) string. The
     * macro will return (out of the setter it is used in) if the field
     * is not editable, and will send a notification event with the old
     * value as soon as the event loop resumes.
     */
    bool isEditable( const QString& fieldName ) const;

protected:
    friend class ApplyPresets;
    /** @brief "Builder" class for presets
     *
     * Derived classes should instantiate this (with themselves,
     * and the whole configuration map that is passed to
     * setConfigurationMap()) and then call .apply() to apply
     * the presets specified in the configuration to the **named**
     * QObject properties.
     */
    class ApplyPresets
    {
    public:
        /** @brief Create a preset-applier for this config
         *
         * The @p configurationMap should be the one passed in to
         * setConfigurationMap() . Presets are extracted from the
         * standard key *presets* and can be applied to the configuration
         * with apply() or operator<<.
         */
        ApplyPresets( Config& c, const QVariantMap& configurationMap );
        ~ApplyPresets();

        /** @brief Add a preset for the given @p fieldName
         *
         * This checks for preset-entries in the configuration map that was
         * passed in to the constructor.
         */
        ApplyPresets& apply( const char* fieldName );
        /** @brief Alternate way of writing apply()
         */
        ApplyPresets& operator<<( const char* fieldName ) { return apply( fieldName ); }

    private:
        Config& m_c;
        bool m_bogus = true;
        const QVariantMap m_map;
    };

private:
    class Private;
    std::unique_ptr< Private > d;
    bool m_unlocked = false;
};
}  // namespace ModuleSystem
}  // namespace Calamares

/// @see Config::isEditable()
//
// This needs to be a macro, because Q_ARG() is a macro that stringifies
// the type name.
#define CONFIG_PREVENT_EDITING( type, fieldName ) \
    do \
    { \
        if ( !isEditable( QStringLiteral( fieldName ) ) ) \
        { \
            auto prop = property( fieldName ); \
            const auto& metaobject = metaObject(); \
            auto metaprop = metaobject->property( metaobject->indexOfProperty( fieldName ) ); \
            if ( metaprop.hasNotifySignal() ) \
            { \
                metaprop.notifySignal().invoke( this, Qt::QueuedConnection, Q_ARG( type, prop.value< type >() ) ); \
            } \
            return; \
        } \
    } while ( 0 )


#endif
