/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2016, Teo Mrnjavac <teo@kde.org>
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

#ifndef PYTHONQTGLOBALSTORAGEWRAPPER_H
#define PYTHONQTGLOBALSTORAGEWRAPPER_H


#include <QObject>

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

#endif // PYTHONQTGLOBALSTORAGEWRAPPER_H
