/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2014-2015 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2017-2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 *
 */

#ifndef CALAMARES_GLOBALSTORAGE_H
#define CALAMARES_GLOBALSTORAGE_H

#include <QMutex>
#include <QObject>
#include <QString>
#include <QVariantMap>

namespace Calamares
{

/** @brief Storage for data that passes between Calamares modules.
 *
 * The Global Storage is global to the Calamares JobQueue and
 * everything that depends on that: all of its modules use the
 * same instance of the JobQueue, and so of the Global Storage.
 *
 * GS is used to pass data between modules; there is only convention
 * about what keys are used, and individual modules should document
 * what they put in to GS or what they expect to find in it.
 *
 * GS behaves as a basic key-value store, with a QVariantMap behind
 * it. Any QVariant can be put into the storage, and the signal
 * changed() is emitted when any data is modified.
 *
 * In general, see QVariantMap (possibly after calling data()) for details.
 *
 * This class is thread-safe -- most accesses go through JobQueue, which
 * handles threading itself, but because modules load in parallel and can
 * have asynchronous tasks like GeoIP lookups, the storage itself also
 * has locking. All methods are thread-safe, use data() to make a snapshot
 * copy for use outside of the thread-safe API.
 */
class GlobalStorage : public QObject
{
    Q_OBJECT
public:
    /** @brief Create a GS object
     *
     * **Generally** there is only one GS object (hence, "global") which
     * is owned by the JobQueue instance (which is a singleton). However,
     * it is possible to create more GS objects.
     */
    explicit GlobalStorage( QObject* parent = nullptr );

    /** @brief Insert a key and value into the store
     *
     * The @p value is added to the store with key @p key. If @p key
     * already exists in the store, its existing value is overwritten.
     * The changed() signal is emitted regardless.
     */
    void insert( const QString& key, const QVariant& value );
    /** @brief Removes a key and its value
     *
     * The @p key is removed from the store. If the @p key does not
     * exist, nothing happens. changed() is emitted regardless.
     *
     * @return the number of keys remaining
     */
    int remove( const QString& key );

    /** @brief dump keys and values to the debug log
     *
     * All the keys and their values are written to the debug log.
     * See save() for caveats: this can leak sensitive information.
     */
    void debugDump() const;

    /** @brief write as JSON to the given filename
     *
     * The file named @p filename is overwritten with a JSON representation
     * of the entire global storage (this may be structured, for instance
     * if maps or lists have been inserted).
     *
     * No tidying, sanitization, or censoring is done -- for instance,
     * the user module sets a slightly-obscured password in global storage,
     * and this JSON file will contain that password in-the-only-slightly-
     * obscured form.
     */
    bool saveJson( const QString& filename ) const;

    /** @brief Adds the keys from the given JSON file
     *
     * No tidying, sanitization, or censoring is done.
     * The JSON file is read and each key is added as a value to
     * the global storage. The storage is not cleared first: existing
     * keys will remain; keys that also occur in the JSON file are overwritten.
     */
    bool loadJson( const QString& filename );

    /** @brief write as YAML to the given filename
     *
     * See also save(), above.
     */
    bool saveYaml( const QString& filename ) const;

    /** @brief reads settings from the given filename
     *
     * See also load(), above.
     */
    bool loadYaml( const QString& filename );

    /** @brief Make a complete copy of the data
     *
     * Provides a snapshot of the data at a given time.
     */
    QVariantMap data() const { return m; }

public Q_SLOTS:
    /** @brief Does the store contain the given key?
     *
     * This can distinguish an explicitly-inserted QVariant() from
     * a no-value-exists QVariant. See value() for details.
     */
    bool contains( const QString& key ) const;
    /** @brief The number of keys in the store
     *
     * This should be unsigned, but the underlying QMap uses signed as well.
     * Equal to keys().length(), in theory.
     */
    int count() const;
    /** @brief The keys in the store
     *
     * This makes a copy of all the keys currently in the store, which
     * could be used for iterating over all the values in the store.
     */
    QStringList keys() const;
    /** @brief Gets a value from the store
     *
     * If a value has been previously inserted, returns that value.
     * If @p key does not exist in the store, returns a QVariant()
     * (an invalid QVariant, which boolean-converts to false). Since
     * QVariant() van also be inserted explicitly, use contains()
     * to check for the presence of a key if you need that.
     */
    QVariant value( const QString& key ) const;

signals:
    /** @brief Emitted any time the store changes
     *
     * Also emitted sometimes when the store does not change, e.g.
     * when removing a non-existent key or inserting a value that
     * is already present.
     */
    void changed();

private:
    class ReadLock;
    class WriteLock;
    QVariantMap m;
    mutable QMutex m_mutex;
};

}  // namespace Calamares

#endif  // CALAMARES_GLOBALSTORAGE_H
