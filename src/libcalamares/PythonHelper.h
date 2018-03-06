/* === This file is part of Calamares - <https://github.com/calamares> ===
 *
 *   Copyright 2014, Teo Mrnjavac <teo@kde.org>
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

#ifndef CALAMARES_PYTHONJOBHELPER_H
#define CALAMARES_PYTHONJOBHELPER_H

#include "PythonJob.h"

#include <QStringList>

#undef slots
#include <boost/python/dict.hpp>
#include <boost/python/list.hpp>
#include <boost/python/object.hpp>

namespace CalamaresPython
{

boost::python::object   variantToPyObject( const QVariant& variant );
QVariant                variantFromPyObject( const boost::python::object& pyObject );

boost::python::list     variantListToPyList( const QVariantList& variantList );
QVariantList            variantListFromPyList( const boost::python::list& pyList );

boost::python::dict     variantMapToPyDict( const QVariantMap& variantMap );
QVariantMap             variantMapFromPyDict( const boost::python::dict& pyDict );

boost::python::dict     variantHashToPyDict( const QVariantHash& variantHash );
QVariantHash            variantHashFromPyDict( const boost::python::dict& pyDict );


class Helper : public QObject
{
    Q_OBJECT
public:
    virtual ~Helper();

    boost::python::dict createCleanNamespace();

    QString handleLastError();

private:
    friend Helper* Calamares::PythonJob::helper();
    explicit Helper( QObject* parent = nullptr );
    static Helper* s_instance;

    boost::python::object m_mainModule;
    boost::python::object m_mainNamespace;

    QStringList m_pythonPaths;
};

} // namespace Calamares

#endif // CALAMARES_PYTHONJOBHELPER_H
