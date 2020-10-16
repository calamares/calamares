/* === This file is part of Calamares - <https://github.com/calamares> ===
 * 
 *   SPDX-FileCopyrightText: 2014 Teo Mrnjavac <teo@kde.org>
 *   SPDX-FileCopyrightText: 2018-2020 Adriaan de Groot <groot@kde.org>
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
 *
 *   SPDX-License-Identifier: GPL-3.0-or-later
 *   License-Filename: LICENSE
 *
 */

#ifndef CALAMARES_PYTHONJOBHELPER_H
#define CALAMARES_PYTHONJOBHELPER_H

#include "PythonJob.h"
#include "utils/BoostPython.h"

#include <QStringList>

namespace Calamares
{
class GlobalStorage;
}

namespace CalamaresPython
{

boost::python::object variantToPyObject( const QVariant& variant );
QVariant variantFromPyObject( const boost::python::object& pyObject );

boost::python::list variantListToPyList( const QVariantList& variantList );
QVariantList variantListFromPyList( const boost::python::list& pyList );

boost::python::dict variantMapToPyDict( const QVariantMap& variantMap );
QVariantMap variantMapFromPyDict( const boost::python::dict& pyDict );

boost::python::dict variantHashToPyDict( const QVariantHash& variantHash );
QVariantHash variantHashFromPyDict( const boost::python::dict& pyDict );


class Helper : public QObject
{
    Q_OBJECT
public:
    boost::python::dict createCleanNamespace();

    QString handleLastError();

    static Helper* instance();

private:
    virtual ~Helper();
    explicit Helper();

    boost::python::object m_mainModule;
    boost::python::object m_mainNamespace;

    QStringList m_pythonPaths;
};

class GlobalStoragePythonWrapper
{
public:
    explicit GlobalStoragePythonWrapper( Calamares::GlobalStorage* gs );

    bool contains( const std::string& key ) const;
    int count() const;
    void insert( const std::string& key, const boost::python::api::object& value );
    boost::python::list keys() const;
    int remove( const std::string& key );
    boost::python::api::object value( const std::string& key ) const;

    // This is a helper for scripts that do not go through
    // the JobQueue (i.e. the module testpython script),
    // which allocate their own (singleton) GlobalStorage.
    static Calamares::GlobalStorage* globalStorageInstance() { return s_gs_instance; }

private:
    Calamares::GlobalStorage* m_gs;
    static Calamares::GlobalStorage* s_gs_instance;  // See globalStorageInstance()
};

}  // namespace CalamaresPython

#endif  // CALAMARES_PYTHONJOBHELPER_H
