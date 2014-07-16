/* === This file is part of Calamares - <http://github.com/calamares> ===
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

#undef slots
#include <boost/python/object.hpp>

namespace Calamares {

class PythonJobHelper : public QObject
{
    Q_OBJECT
public:
    explicit PythonJobHelper( QObject* parent = nullptr );
    virtual ~PythonJobHelper();

    boost::python::object createCleanNamespace();

private:
    friend PythonJobHelper* PythonJob::helper();
    static PythonJobHelper* s_instance;

    boost::python::object m_mainModule;
    boost::python::object m_mainNamespace;
};

} // namespace Calamares

#endif // CALAMARES_PYTHONJOBHELPER_H
