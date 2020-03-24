/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014-2015, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_GLOBALSTORAGE_H
#define CALAMARES_GLOBALSTORAGE_H

#include "CalamaresConfig.h"

#include <QObject>
#include <QString>
#include <QVariantMap>

namespace Calamares
{

class DebugWindow;

class GlobalStorage : public QObject
{
    Q_OBJECT
public:
    explicit GlobalStorage();

    //NOTE: thread safety is guaranteed by JobQueue, which executes jobs one by one.
    //      If at any time jobs become concurrent, this class must be made thread-safe.
    bool contains( const QString& key ) const;
    int count() const;
    void insert( const QString& key, const QVariant& value );
    QStringList keys() const;
    int remove( const QString& key );
    QVariant value( const QString& key ) const;

    /// @brief dump keys and values to the debug log
    void debugDump() const;

    /** @brief write as JSON to the given filename
     *
     * No tidying, sanitization, or censoring is done -- for instance,
     * the user module sets a slightly-obscured password in global storage,
     * and this JSON file will contain that password in-the-only-slightly-
     * obscured form.
     */
    bool save( const QString& filename );

    /** @brief Adds the keys from the given JSON file
     *
     * No tidying, sanitization, or censoring is done.
     * The JSON file is read and each key is added as a value to
     * the global storage.
     */
    bool load( const QString& filename );

    /** @brief write as YAML to the given filename
     *
     * See also save(), above.
     */
    bool saveYaml( const QString& filename );

    /// @brief reads settings from the given filename
    bool loadYaml( const QString& filename );

    /** @brief Get internal mapping as a constant object
     *
     * Note that the VariantMap underneath may change, because
     * it's not constant in itself. Connect to the changed()
     * signal for notifications.
     */
    const QVariantMap& data() const { return m; }

signals:
    void changed();

private:
    QVariantMap m;
};

}  // namespace Calamares

#endif  // CALAMARES_GLOBALSTORAGE_H
