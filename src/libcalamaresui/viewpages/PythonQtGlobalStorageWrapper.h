/* === This file is part of Calamares - <https://calamares.io> ===
 *
 *   SPDX-FileCopyrightText: 2016 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018 Adriaan de Groot <groot@kde.org>
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *
 *   Calamares is Free Software: see the License-Identifier above.
 *
 */

#ifndef PYTHONQTGLOBALSTORAGEWRAPPER_H
#define PYTHONQTGLOBALSTORAGEWRAPPER_H

#include <QObject>
#include <QStringList>
#include <QVariant>

namespace Calamares
{
class GlobalStorage;
}


/**
 * @brief This GlobalStorage class is a namespace-free wrapper for
 *        Calamares::GlobalStorage. This is unfortunately a necessity
 *        because PythonQt doesn't like namespaces.
 */
class GlobalStorage : public QObject
{
    Q_OBJECT
public:
    explicit GlobalStorage( Calamares::GlobalStorage* gs );
    virtual ~GlobalStorage() {}

public slots:
    bool contains( const QString& key ) const;
    int count() const;
    void insert( const QString& key, const QVariant& value );
    QStringList keys() const;
    int remove( const QString& key );
    QVariant value( const QString& key ) const;

private:
    Calamares::GlobalStorage* m_gs;
};

#endif  // PYTHONQTGLOBALSTORAGEWRAPPER_H
